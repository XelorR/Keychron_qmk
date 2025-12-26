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
#include "oneshot.h"

#define LA_NAV_M MO(MAC_NAV)
#define LA_NAV_W MO(WIN_NAV)
#define LA_SYM_M MO(MAC_SYM)
#define LA_SYM_W MO(WIN_SYM)

#define WN_SNAP G(S(KC_S))
#define MC_SNAP G(S(KC_4))
#define MC_PSCR G(S(KC_3))

#define WN_TABL (C(S(KC_TAB)))
#define WN_TABR (C(KC_TAB))
#define MC_TABL G(S(KC_LBRC))
#define MC_TABR G(S(KC_RBRC))
#define UC_HYPR G(C(S(KC_LALT))) // Copylot/Office365 button

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
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,   KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LOPTN, KC_LCMMD, KC_SPC,   LA_NAV_M,           LA_SYM_M,           KC_SPC,   KC_RCMMD, KC_RCMMD,           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LWIN,  KC_LALT,  KC_SPC,   LA_NAV_W,           LA_SYM_W,           KC_SPC,   KC_APP,   UC_HYPR,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_SYM] = LAYOUT_73_jis(
        KC_TILD,  KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      KC_INS,
        RGB_TOG,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,            _______,  OS_SHFT,  OS_CMD,   OS_ALT,   OS_CTRL,  _______,  _______,  MC_PSCR,  KC_END,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______),

    [WIN_SYM] = LAYOUT_73_jis(
        KC_TILD,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_MYCM,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      KC_INS,
        RGB_TOG,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,            _______,  OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  KC_PSCR,  KC_END,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______),

    [MAC_NAV] = LAYOUT_73_jis(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  KC_BSPC,  MC_TABL,  KC_TAB,   MC_TABR,  _______,  _______,  _______,  _______,  _______,  KC_DEL,   _______,  _______,                      _______,
        _______,  OS_CTRL,  OS_ALT,   OS_CMD,   OS_SHFT,  MC_SNAP,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_BSPC,  _______,  _______,  MC_PSCR,  _______,
        _______,  G(KC_Z),  G(KC_X),  G(KC_C),  G(KC_V), G(S(KC_Z)), BAT_LVL, KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [WIN_NAV] = LAYOUT_73_jis(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  KC_DEL,   WN_TABL,  KC_TAB,   WN_TABR,  _______,  _______,  _______,  _______,  _______,  KC_DEL,   _______,  _______,                      _______,
        _______,  OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  WN_SNAP,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_BSPC,  _______,  _______,  KC_PSCR,  _______,
        _______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_Y),  BAT_LVL,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [MAC_NUM] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_F13,   KC_F14,   KC_15,    KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,                       _______,
        _______,  OS_CTRL,  OS_ALT,   OS_CMD,   OS_SHFT,  _______,            _______,  OS_SHFT,  OS_CMD,   OS_ALT,   OS_CTRL,  _______,  _______,  JIGGLE,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [WIN_NUM] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_F13,   KC_F14,   KC_15,    KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,                       _______,
        _______,  OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  _______,            _______,  OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  JIGGLE,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [MAC_SYM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [WIN_SYM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [MAC_NAV]  = { ENCODER_CCW_CW(_______, _______)},
        [WIN_NAV]  = { ENCODER_CCW_CW(_______, _______)},
        [MAC_NUM]  = { ENCODER_CCW_CW(_______, _______)},
        [WIN_NUM]  = { ENCODER_CCW_CW(_______, _______)},
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

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, MAC_SYM, MAC_NAV, MAC_NUM);
    state = update_tri_layer_state(state, WIN_SYM, WIN_NAV, WIN_NUM);
    return state;
}
