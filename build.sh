#!/usr/bin/env bash
set -euo pipefail

# ============================================================
# QMK build / flash script for Keychron K11 Max JIS RGB
#
# Run from the root of the QMK repository:
#   ./build.sh
#   ./build.sh --flash
# ============================================================

KEYBOARD="keychron/k11_max/jis_encoder/rgb"
KEYMAP="miryoku"
FIRMWARE="keychron_k11_max_jis_encoder_rgb_miryoku.bin"

UDEV_SOURCE="./util/udev/50-qmk.rules"
UDEV_TARGET="/etc/udev/rules.d/50-qmk.rules"

JOBS=0
FLASH=false

# Make QMK's install locations available even in a fresh shell where
# ~/.local/bin has not been added to PATH yet.
if [[ -n "${QMK_DISTRIB_DIR:-}" ]]; then
    export PATH="$QMK_DISTRIB_DIR/bin:$PATH"
fi
export PATH="${XDG_BIN_HOME:-$HOME/.local/bin}:$HOME/.local/share/qmk/bin:$HOME/.qmk/bin:$PATH"

# ------------------------------------------------------------
# Arguments
# ------------------------------------------------------------

case "${1:-}" in
"")
    ;;
--flash)
    FLASH=true
    ;;
-h | --help)
    echo "Usage: $0 [--flash]"
    echo
    echo "  ./build.sh          Build firmware"
    echo "  ./build.sh --flash  Build and flash firmware"
    exit 0
    ;;
*)
    echo "ERROR: Unknown argument: $1" >&2
    exit 1
    ;;
esac

# ------------------------------------------------------------
# Check environment
# ------------------------------------------------------------

[[ -f /etc/arch-release ]] || {
    echo "ERROR: This script requires Arch Linux." >&2
    exit 1
}

[[ -f ./Makefile && -d ./keyboards ]] || {
    echo "ERROR: Run this script from the root of the QMK repository." >&2
    exit 1
}

# ------------------------------------------------------------
# Basic dependencies
# ------------------------------------------------------------

echo "==> Checking dependencies"

for cmd in git curl python make gcc unzip zip wget; do
    if ! command -v "$cmd" >/dev/null 2>&1; then
        echo "    Installing $cmd..."
        sudo pacman -S --needed --noconfirm "$cmd"
    fi
done

# ------------------------------------------------------------
# Git submodules
# ------------------------------------------------------------

echo "==> Checking git submodules"

# A copied repository may be owned by a different user, which makes Git
# refuse to operate on it. Trust just this checkout.
if ! GIT_ERROR="$(git rev-parse --is-inside-work-tree 2>&1)"; then
    if [[ "$GIT_ERROR" == *"dubious ownership"* ]]; then
        echo "    Marking $(pwd) as a safe Git directory"
        git config --global --add safe.directory "$(pwd)" || {
            echo "WARNING: Could not mark the repository as safe for Git." >&2
        }
    fi
fi

if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    # ChibiOS must match the commits pinned by this repository. Older
    # checkouts use LIBINC instead of OSLIBINC and fail to compile.
    git submodule sync --quiet -- lib/chibios lib/chibios-contrib

    if ! git submodule update --init lib/chibios lib/chibios-contrib; then
        echo "ERROR: Could not update the ChibiOS submodules." >&2
        echo "       Check your network connection. If the checkout is corrupt, run:" >&2
        echo "       git submodule deinit -f lib/chibios lib/chibios-contrib" >&2
        echo "       git submodule update --init lib/chibios lib/chibios-contrib" >&2
        exit 1
    fi

    SUBMODULE_STATUS="$(git submodule status lib/chibios lib/chibios-contrib)"
    if grep -qE '^[+-U]' <<<"$SUBMODULE_STATUS"; then
        echo "ERROR: ChibiOS submodules are not at the pinned commits:" >&2
        echo "$SUBMODULE_STATUS" >&2
        exit 1
    fi
else
    echo "    Not a Git checkout; skipping submodule update."
fi

# Catch a copied tree with missing or stale ChibiOS sources before the
# compiler fails with a confusing missing-header error.
if [[ ! -f lib/chibios/os/oslib/include/chlib.h ]] || ! grep -q '^OSLIBINC' lib/chibios/os/oslib/oslib.mk; then
    echo "ERROR: ChibiOS sources are missing or out of date." >&2
    echo "       Clone the repository with Git so its submodules can be restored:" >&2
    echo "       git clone --recurse-submodules <repository-url>" >&2
    exit 1
fi

# ------------------------------------------------------------
# QMK CLI
# ------------------------------------------------------------

if ! command -v qmk >/dev/null 2>&1; then
    echo "==> Installing QMK CLI and toolchains"

    curl -fsSL https://install.qmk.fm | sh -s -- --confirm

    export PATH="${XDG_BIN_HOME:-$HOME/.local/bin}:$HOME/.local/share/qmk/bin:$HOME/.qmk/bin:$PATH"
fi

command -v qmk >/dev/null 2>&1 || {
    echo "ERROR: qmk is not in PATH." >&2
    echo "Add '${XDG_BIN_HOME:-$HOME/.local/bin}' to your PATH and run the script again." >&2
    exit 1
}

echo "==> QMK: $(qmk --version)"

# ------------------------------------------------------------
# Configure QMK home
# ------------------------------------------------------------

# `qmk config` appends the value's source, e.g. "path (config)".
QMK_HOME="$(qmk config -ro user.qmk_home 2>/dev/null | sed -e 's/^user\.qmk_home=//' -e 's/ ([^()]*)$//')"

if [[ "$QMK_HOME" != "$(pwd)" ]]; then
    qmk config user.qmk_home="$(pwd)" || {
        echo "WARNING: Could not save QMK_HOME; continuing with this checkout." >&2
    }
fi

export QMK_HOME="$(pwd)"

# ------------------------------------------------------------
# Build toolchain
# ------------------------------------------------------------

if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "==> Installing missing build dependencies"

    # `qmk doctor` installs the compiler and flashing tools when they are
    # missing. It exits 1 for warnings (e.g. a dirty tree), so ignore that.
    qmk doctor -y || true

    if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
        echo "ERROR: arm-none-eabi-gcc is still not available." >&2
        echo "       Run 'qmk doctor' for details." >&2
        exit 1
    fi
fi

# ------------------------------------------------------------
# Build
# ------------------------------------------------------------

echo
echo "==> Building $KEYBOARD:$KEYMAP"

# Never let a stale binary from a previous machine hide a failed build.
rm -f "./$FIRMWARE"

qmk compile \
    -kb "$KEYBOARD" \
    -km "$KEYMAP" \
    -j "$JOBS"

[[ -f "./$FIRMWARE" ]] || {
    echo "ERROR: Firmware was not created: $FIRMWARE" >&2
    exit 1
}

echo
echo "==> Build successful: $FIRMWARE"

# ------------------------------------------------------------
# Flash
# ------------------------------------------------------------

if [[ "$FLASH" == true ]]; then
    echo
    echo "==> Checking QMK udev rules"

    [[ -f "$UDEV_SOURCE" ]] || {
        echo "ERROR: QMK udev rules not found: $UDEV_SOURCE" >&2
        exit 1
    }

    if [[ ! -f "$UDEV_TARGET" ]]; then
        echo "    Installing $UDEV_TARGET"

        sudo install -Dm644 \
            "$UDEV_SOURCE" \
            "$UDEV_TARGET"

        sudo udevadm control --reload-rules
        sudo udevadm trigger
    else
        echo "    Already installed."
    fi

    echo
    echo "==> Flashing $FIRMWARE"

    qmk flash "./$FIRMWARE"

    echo
    echo "==> Flash successful."
fi
