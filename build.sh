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
# Check repository / OS
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

for cmd in git curl python; do
    if ! command -v "$cmd" >/dev/null 2>&1; then
        echo "    Installing $cmd..."
        sudo pacman -S --needed --noconfirm "$cmd"
    fi
done

# ------------------------------------------------------------
# QMK CLI
# ------------------------------------------------------------

if ! command -v qmk >/dev/null 2>&1; then
    echo "==> Installing QMK CLI"

    curl -fsSL https://install.qmk.fm | sh

    export PATH="$HOME/.local/bin:$HOME/.qmk/bin:$PATH"
fi

command -v qmk >/dev/null 2>&1 || {
    echo "ERROR: qmk is not in PATH." >&2
    echo "Restart your shell and run the script again." >&2
    exit 1
}

echo "==> QMK: $(qmk --version)"

# ------------------------------------------------------------
# QMK setup
# ------------------------------------------------------------

echo "==> Running QMK setup"

qmk setup -H "$(pwd)" -y

# ------------------------------------------------------------
# udev rules
# ------------------------------------------------------------

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

# ------------------------------------------------------------
# Build
# ------------------------------------------------------------

echo
echo "==> Building $KEYBOARD:$KEYMAP"

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
    echo "==> Flashing $FIRMWARE"

    qmk flash "./$FIRMWARE"

    echo
    echo "==> Flash successful."
fi
