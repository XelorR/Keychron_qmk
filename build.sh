#!/usr/bin/env bash
set -euo pipefail

# ============================================================
# QMK build / flash script for Keychron K11 Max JIS RGB
#
# Run from the root of the QMK repository:
#   ./build.sh
#   ./build.sh --flash
# ============================================================

REPO_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
KEYBOARD="keychron/k11_max/jis_encoder/rgb"
KEYMAP="miryoku"
FIRMWARE="keychron_k11_max_jis_encoder_rgb_miryoku.bin"

UDEV_SOURCE="${REPO_ROOT}/util/udev/50-qmk.rules"
UDEV_TARGET="/etc/udev/rules.d/50-qmk.rules"
VENV_DIR="${REPO_ROOT}/.qmk-venv"

JOBS="${QMK_JOBS:-$(nproc 2>/dev/null || printf '1')}"
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
# Check environment
# ------------------------------------------------------------

[[ -f /etc/arch-release ]] || {
    echo "ERROR: This script requires Arch Linux or CachyOS." >&2
    exit 1
}

[[ -f "${REPO_ROOT}/Makefile" && -d "${REPO_ROOT}/keyboards" ]] || {
    echo "ERROR: Run this script from the root of the QMK repository." >&2
    exit 1
}

cd -- "${REPO_ROOT}"

command -v sudo >/dev/null 2>&1 || {
    echo "ERROR: sudo is required to install Arch packages and udev rules." >&2
    exit 1
}

# ------------------------------------------------------------
# Basic dependencies
# ------------------------------------------------------------

echo "==> Installing/checking Arch dependencies"

sudo pacman --needed --noconfirm -S \
    arm-none-eabi-binutils \
    arm-none-eabi-gcc \
    arm-none-eabi-newlib \
    base-devel \
    clang \
    dfu-util \
    diffutils \
    git \
    hidapi \
    libffi \
    python \
    python-pip \
    unzip \
    wget \
    zip

echo "==> Initializing QMK submodules"
git submodule update --init --recursive

# ------------------------------------------------------------
# QMK CLI
# ------------------------------------------------------------

echo "==> Preparing isolated QMK Python environment"
if [[ ! -x "${VENV_DIR}/bin/python" ]]; then
    python -m venv "${VENV_DIR}"
fi

QMK_PYTHON="${VENV_DIR}/bin/python"
QMK="${VENV_DIR}/bin/qmk"
export PATH="${VENV_DIR}/bin:${PATH}"

"${QMK_PYTHON}" -m pip install --upgrade pip
"${QMK_PYTHON}" -m pip install --upgrade qmk appdirs
"${QMK_PYTHON}" -m pip install --requirement requirements.txt

[[ -x "${QMK}" ]] || {
    echo "ERROR: QMK CLI was not installed in ${VENV_DIR}." >&2
    exit 1
}

echo "==> QMK: $("${QMK}" --version)"

# ------------------------------------------------------------
# Configure QMK home
# ------------------------------------------------------------

QMK_HOME="$("${QMK}" config -ro user.qmk_home 2>/dev/null || true)"

if [[ "$QMK_HOME" != "${REPO_ROOT}" ]]; then
    "${QMK}" config user.qmk_home="${REPO_ROOT}"
fi

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

"${QMK}" compile \
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

    "${QMK}" flash "./$FIRMWARE"

    echo
    echo "==> Flash successful."
fi
