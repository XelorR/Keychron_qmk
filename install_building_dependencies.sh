#!/usr/bin/env bash
set -euo pipefail

# ============================================================
# QMK build / flash script for Keychron K11 Max JIS
#
# Usage:
#   ./build.sh
#   ./build.sh --flash
#
# Without --flash: compile only
# With --flash:    compile and immediately flash
# ============================================================

# qmk compile -kb keychron/k11_max/jis_encoder/rgb -km miryoku

KEYBOARD="keychron/k11_max/jis_encoder/rgb"
KEYMAP="miryoku"
JOBS=0

FLASH=false

# ------------------------------------------------------------
# Helpers
# ------------------------------------------------------------

die() {
    echo "ERROR: $*" >&2
    exit 1
}

info() {
    echo
    echo "==> $*"
}

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# ------------------------------------------------------------
# Arguments
# ------------------------------------------------------------

while [[ $# -gt 0 ]]; do
    case "$1" in
        --flash)
            FLASH=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [--flash]"
            echo
            echo "  without --flash   Compile firmware only"
            echo "  --flash           Compile and immediately flash firmware"
            exit 0
            ;;
        *)
            die "Unknown argument: $1"
            ;;
    esac
done

# ------------------------------------------------------------
# Check OS
# ------------------------------------------------------------

[[ -f /etc/arch-release ]] || die "This script is intended for Arch Linux."

# ------------------------------------------------------------
# Determine QMK repository
# ------------------------------------------------------------

if [[ -n "${QMK_REPO:-}" ]]; then
    QMK_REPO="$(realpath "$QMK_REPO")"
else
    SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

    if git -C "$SCRIPT_DIR" rev-parse --show-toplevel >/dev/null 2>&1; then
        QMK_REPO="$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel)"
    else
        QMK_REPO="$SCRIPT_DIR"
    fi
fi

[[ -d "$QMK_REPO" ]] || die "QMK repository not found: $QMK_REPO"
[[ -f "$QMK_REPO/Makefile" ]] || die \
    "This does not look like a QMK repository: $QMK_REPO"

info "QMK repository: $QMK_REPO"

cd "$QMK_REPO"

# ------------------------------------------------------------
# Basic Arch dependencies
# ------------------------------------------------------------

info "Checking basic dependencies"

MISSING=()

for cmd in git curl python; do
    if ! command_exists "$cmd"; then
        MISSING+=("$cmd")
    fi
done

if (( ${#MISSING[@]} > 0 )); then
    info "Installing basic dependencies: ${MISSING[*]}"

    sudo pacman -S --needed --noconfirm \
        git \
        curl \
        python
fi

# ------------------------------------------------------------
# Install QMK CLI if necessary
# ------------------------------------------------------------

if ! command_exists qmk; then
    info "QMK CLI not found. Installing it..."

    curl -fsSL https://install.qmk.fm | sh

    # Make QMK available immediately if the installer
    # installed it into one of these standard locations.
    export PATH="$HOME/.local/bin:$HOME/.qmk/bin:$PATH"
fi

command_exists qmk || die \
    "QMK CLI was installed but 'qmk' is not in PATH. Restart your shell and run again."

info "QMK CLI: $(qmk --version)"

# ------------------------------------------------------------
# Configure QMK to use this repository
# ------------------------------------------------------------

info "Configuring QMK"

CURRENT_QMK_HOME="$(qmk config -ro user.qmk_home 2>/dev/null || true)"

if [[ "$CURRENT_QMK_HOME" != "$QMK_REPO" ]]; then
    qmk config user.qmk_home="$QMK_REPO"
fi

# ------------------------------------------------------------
# QMK setup / dependencies
# ------------------------------------------------------------

info "Running QMK setup"

qmk setup -H "$QMK_REPO" -y

# ------------------------------------------------------------
# udev rules
# ------------------------------------------------------------

info "Checking QMK udev rules"

UDEV_RULES_DIR="/etc/udev/rules.d"

# QMK's installer currently installs rules with this name.
# Also check for the older QMK rule name for compatibility.
UDEV_RULES_FOUND=false

for rule in \
    "$UDEV_RULES_DIR/50-qmk.rules" \
    "$UDEV_RULES_DIR/55-qmk.rules"
do
    if [[ -f "$rule" ]]; then
        UDEV_RULES_FOUND=true
        break
    fi
done

if [[ "$UDEV_RULES_FOUND" == false ]]; then
    info "QMK udev rules not found. Installing..."

    [[ -x "$QMK_REPO/util/install_udev.sh" ]] || die \
        "QMK udev installer not found: $QMK_REPO/util/install_udev.sh"

    sudo "$QMK_REPO/util/install_udev.sh"
    sudo cp ./util/udev/50-qmk.rules /etc/udev/rules.d/

    # Reload rules immediately.
    sudo udevadm control --reload-rules
    sudo udevadm trigger

    info "QMK udev rules installed."
else
    info "QMK udev rules already installed."
fi

# ------------------------------------------------------------
# Validate environment
# ------------------------------------------------------------

info "Running QMK doctor"

qmk doctor

# ------------------------------------------------------------
# Validate keyboard
# ------------------------------------------------------------

info "Checking keyboard: $KEYBOARD"

if ! qmk list-keyboards | grep -Fxq "$KEYBOARD"; then
    echo
    echo "Available Keychron K11 targets:"
    qmk list-keyboards | grep -i 'keychron/k11' || true
    echo
    die "Keyboard '$KEYBOARD' was not found."
fi

# ------------------------------------------------------------
# Validate keymap
# ------------------------------------------------------------

info "Checking keymap: $KEYMAP"

if ! qmk list-keymaps -kb "$KEYBOARD" | grep -Fxq "$KEYMAP"; then
    echo
    echo "Available keymaps for $KEYBOARD:"
    qmk list-keymaps -kb "$KEYBOARD"
    echo
    die "Keymap '$KEYMAP' was not found for '$KEYBOARD'."
fi

# ------------------------------------------------------------
# Compile
# ------------------------------------------------------------

info "Compiling $KEYBOARD:$KEYMAP"

qmk compile \
    -kb "$KEYBOARD" \
    -km "$KEYMAP" \
    -j "$JOBS"

info "Build completed successfully."

# ------------------------------------------------------------
# Flash
# ------------------------------------------------------------

if [[ "$FLASH" == true ]]; then
    info "Flashing $KEYBOARD:$KEYMAP"

    echo
    echo "Attempting to flash the keyboard..."
    echo "Make sure the keyboard is in bootloader mode."
    echo

    qmk flash \
        -kb "$KEYBOARD" \
        -km "$KEYMAP"

    info "Flash completed successfully."
else
    info "Flash skipped (use --flash to flash the keyboard)."
fi

# qmk compile -kb keychron/k11_max/jis_encoder/rgb -km miryoku
