/* Copyright 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

#define LA_NAV_M MO(MAC_NAV)
#define LA_NAV_W MO(WIN_NAV)
#define LA_SYM_M MO(MAC_SYM)
#define LA_SYM_W MO(WIN_SYM)

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_SYM,
    WIN_SYM,
    MAC_NAV,
    WIN_NAV,
    MAC_NUM,
    WIN_NUM,
};

enum custom_keycodes {
    JIGGLE = NEW_SAFE_RANGE,

    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_INT3,  KC_BSPC,   KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_INT1,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD, KC_LNG2,  KC_SPC,   LA_NAV_M,           LA_SYM_M,           KC_SPC,   KC_LNG1,  KC_RCMMD,           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_INT3,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_INT1,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,  KC_INT5,  KC_SPC,   LA_NAV_W,           LA_SYM_W,           KC_SPC,   KC_INT4,  KC_RALT,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_SYM] = LAYOUT_73_jis(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      KC_INS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_END,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______),

    [WIN_SYM] = LAYOUT_73_jis(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      KC_INS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_END,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______),

    [MAC_NAV] = LAYOUT_73_jis(
        KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  JIGGLE,   _______,
        _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [WIN_NAV] = LAYOUT_73_jis(
        KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  JIGGLE,   _______,
        _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [MAC_NUM] = LAYOUT_73_jis(
        KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  JIGGLE,   _______,
        _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [WIN_NUM] = LAYOUT_73_jis(
        KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  JIGGLE,   _______,
        _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [MAC_SYM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [WIN_SYM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [MAC_NAV]      = { ENCODER_CCW_CW(_______, _______)},
    };
#endif // ENCODER_MAP_ENABLE

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM_M:
    case LA_NAV_M:
    case LA_SYM_W:
    case LA_NAV_W:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM_M:
    case LA_NAV_M:
    case LA_SYM_W:
    case LA_NAV_W:
    case KC_LSFT:
    case KC_RSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    if (record->event.pressed) {
        static deferred_token token = INVALID_DEFERRED_TOKEN;
        static report_mouse_t report = {0};
        if (token) {
        // If jiggler is currently running, stop when any key is pressed.
        cancel_deferred_exec(token);
        token = INVALID_DEFERRED_TOKEN;
        report = (report_mouse_t){};  // Clear the mouse.
        host_mouse_send(&report);
        } else if (keycode == JIGGLE) {

        uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
            // Deltas to move in a circle of radius 20 pixels over 32 frames.
            static const int8_t deltas[32] = {
                0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
                0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
            static uint8_t phase = 0;
            // Get x delta from table and y delta by rotating a quarter cycle.
            report.x = deltas[phase];
            report.y = deltas[(phase + 8) & 31];
            phase = (phase + 1) & 31;
            host_mouse_send(&report);
            return 16;  // Call the callback every 16 ms.
        }

        token = defer_exec(1, jiggler_callback, NULL);  // Schedule callback.
    }
  }
    return true;
}
