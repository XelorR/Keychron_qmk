#pragma once

#include QMK_KEYBOARD_H

// Implements cmd-tab like behavior on a single key. On first tap of trigger
// cmdish is held and tabish is tapped; cmdish then remains held until some
// other key is hit or released.
void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t reverse_key,
    uint16_t keycode,
    keyrecord_t *record
);
