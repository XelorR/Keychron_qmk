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
#include "swapper.h"

#define LA_NAV_M MO(MAC_NAV)
#define LA_NAV_W MO(WIN_NAV)
#define LA_SYM_M MO(MAC_SYM)
#define LA_SYM_W MO(WIN_SYM)
#define LA_NUM_M MO(MAC_NUM)
#define LA_NUM_W MO(WIN_NUM)
#define LA_MOUSE MO(MOUSE)

#define WN_SNAP G(S(KC_S))
#define MC_SNAP G(S(KC_4))
#define MC_PSCR G(S(KC_3))
#define MC_HOME G(KC_LEFT)
#define MC_END G(KC_RGHT)
#define WN_LANG G(KC_SPC)
#define MC_LANG C(KC_SPC)

#define WN_TABL C(KC_PGUP)
#define WN_TABR C(KC_PGDN)
#define MC_TABL G(S(KC_LBRC))
#define MC_TABR G(S(KC_RBRC))
#define MC_EMOJ G(C(KC_SPC))
#define WN_EMOJ G(KC_DOT)

#define MC_UNDO G(KC_Z)
#define MC_REDO G(S(KC_Z))
#define WN_UNDO C(KC_Z)
#define WN_REDO C(KC_Y)
#define MC_SAVE G(KC_S)
#define WN_SAVE C(KC_S)

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_SYM,
    WIN_SYM,
    MAC_NUM,
    WIN_NUM,
    MAC_NAV,
    WIN_NAV,
    MOUSE,
    MAC_FUN,
    WIN_FUN,
};

enum custom_keycodes {
    JIGGLE = NEW_SAFE_RANGE,

    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    MC_TAB, // Cmd-Tab for Mac
    WN_TAB, // Alt-Tab for Win

    EN_EXLM,
    EN_AT,
    EN_HASH,
    EN_DLR,
    EN_PERC,
    EN_CIRC,
    EN_AMPR,
    EN_ASTR,
    EN_LPRN,
    EN_RPRN,
    EN_LBRC,
    EN_RBRC,
    EN_QUOT,
    EN_PIPE,
    EN_GRV,

    BSPC_5, // 5x backspace
    MINS_5,  // 5x minus
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMMD, KC_LOPTN, KC_LCMMD, KC_SPC,   LA_NAV_M,           LA_SYM_M, LA_NUM_M,           KC_RALT,  KC_RCMMD,           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCTL,  KC_LWIN,  KC_LALT,  KC_SPC,   LA_NAV_W,           LA_SYM_W, LA_NUM_W,           KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_SYM] = LAYOUT_73_jis(
        KC_ESC,   EN_EXLM,  EN_AT,    EN_HASH,  EN_DLR,   EN_PERC,            EN_CIRC,  EN_AMPR,  EN_ASTR,  EN_LPRN,  EN_RPRN,  KC_UNDS,  KC_PLUS,  _______,  _______,  RGB_TOG,
        _______,  KC_LCBR,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RCBR,            KC_NUM,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  EN_LBRC,  EN_RBRC,            KC_INS,
        RGB_TOG,  KC_DQUO,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_UNDS,            KC_PLUS,  OS_SHFT,  OS_CMD,   OS_ALT,   OS_CTRL,  EN_QUOT,  EN_PIPE,  KC_PSCR,  KC_END,
        _______,  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_PIPE,  BAT_LVL,  _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  KC_PGDN,  _______),

    [WIN_SYM] = LAYOUT_73_jis(
        KC_ESC,   EN_EXLM,  EN_AT,    EN_HASH,  EN_DLR,   EN_PERC,            EN_CIRC,  EN_AMPR,  EN_ASTR,  EN_LPRN,  EN_RPRN,  KC_UNDS,  KC_PLUS,  _______,  _______,  RGB_TOG,
        _______,  KC_LCBR,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RCBR,            KC_NUM,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  EN_LBRC,  EN_RBRC,            KC_INS,
        RGB_TOG,  KC_DQUO,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_UNDS,            KC_PLUS,  OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   EN_QUOT,  EN_PIPE,  KC_PSCR,  KC_END,
        _______,  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_PIPE,  BAT_LVL,  _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  KC_PGDN,  _______),

    [MAC_NUM] = LAYOUT_73_jis(
        _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,  KC_KP_5,            KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_0,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_LBRC,  KC_7,     KC_8,     KC_9,     KC_RBRC,            KC_NUM,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,  _______,            _______,
        _______,  KC_QUOT,  KC_4,     KC_5,     KC_6,     KC_MINS,            KC_EQL,   OS_SHFT,  OS_CMD,   OS_ALT,   OS_CTRL,  _______,  _______,  _______,  _______,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_BSLS,  _______,  _______,  KC_PSLS,  MC_EMOJ,  KC_PDOT,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  KC_0,     _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [WIN_NUM] = LAYOUT_73_jis(
        _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,  KC_KP_5,            KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_0,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_LBRC,  KC_7,     KC_8,     KC_9,     KC_RBRC,            KC_NUM,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,  _______,            _______,
        _______,  KC_QUOT,  KC_4,     KC_5,     KC_6,     KC_MINS,            KC_EQL,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  _______,  _______,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_BSLS,  _______,  _______,  KC_PSLS,  WN_EMOJ,  KC_PDOT,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  KC_0,     _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [MAC_NAV] = LAYOUT_73_jis(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  MC_SAVE,
        KC_I,     KC_BSPC,  MC_TABL,  MC_TAB,   MC_TABR,  KC_ESC,             KC_ESC,   MC_HOME,  KC_UP,    MC_END,   KC_PGUP,  _______,  _______,            _______,
        KC_M,     OS_CTRL,  OS_ALT,   OS_CMD,   OS_SHFT,  KC_ENT,             KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  _______,  _______,  _______,  _______,
        KC_J,     JIGGLE,   KC_WBAK,  MC_SNAP,  KC_WFWD,  KC_TAB,   BAT_LVL,  KC_TAB,   KC_BSPC,  MC_LANG,  KC_DEL,   KC_INS,   _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  LA_MOUSE, _______,            _______,  _______,            _______,  _______,            KC_HOME,  KC_PGDN,  KC_END),

    [WIN_NAV] = LAYOUT_73_jis(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  WN_SAVE,
        KC_I,     KC_DEL,   WN_TABL,  WN_TAB,   WN_TABR,  KC_ESC,             KC_ESC,   KC_HOME,  KC_UP,    KC_END,   KC_PGUP,  _______,  _______,            _______,
        KC_M,     OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  KC_ENT,             KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  _______,  _______,  _______,  _______,
        KC_J,     JIGGLE,   KC_WBAK,  KC_PSCR,  KC_WFWD,  KC_TAB,   BAT_LVL,  KC_TAB,   KC_BSPC,  WN_LANG,  KC_DEL,   KC_INS,   _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  LA_MOUSE, _______,            _______,  _______,            _______,  _______,            KC_HOME,  KC_PGDN,  KC_END),

    [MOUSE] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  MS_WHLL,  MS_UP,    MS_WHLR,  MS_WHLU,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  MS_LEFT,  MS_DOWN,  MS_RGHT,  MS_WHLD,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            MS_BTN2,  MS_BTN1,            _______,  _______,            _______,  _______,  _______),

    [MAC_FUN] = LAYOUT_73_jis(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,            RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  _______,            _______,
        _______,  OS_CTRL,  OS_ALT,   OS_CMD,   OS_SHFT,  KC_F11,             KC_F12,   OS_SHFT,  OS_CMD,   OS_ALT,   OS_CTRL,  _______,  _______,  _______,  _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    BAT_LVL,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [WIN_FUN] = LAYOUT_73_jis(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_MYCM,  RGB_VAD,            RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  _______,            _______,
        _______,  OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  KC_F11,             KC_F12,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  _______,  _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    BAT_LVL,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [MAC_SYM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [WIN_SYM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [MAC_NUM]  = { ENCODER_CCW_CW(_______, _______)},
        [MAC_NAV] = { ENCODER_CCW_CW(MC_UNDO, MC_REDO)},
        [WIN_NAV] = { ENCODER_CCW_CW(WN_UNDO, WN_REDO)},
        [MOUSE]  = { ENCODER_CCW_CW(_______, _______)},
        [MAC_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [WIN_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
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

bool mac_tabber_active = false;
bool win_tabber_active = false;

static bool process_english_shifted_symbol(uint16_t keycode, keyrecord_t *record) {
    uint16_t symbol_keycode;

    switch (keycode) {
        case EN_EXLM:
            symbol_keycode = KC_EXLM;
            break;
        case EN_AT:
            symbol_keycode = KC_AT;
            break;
        case EN_HASH:
            symbol_keycode = KC_HASH;
            break;
        case EN_DLR:
            symbol_keycode = KC_DLR;
            break;
        case EN_PERC:
            symbol_keycode = KC_PERC;
            break;
        case EN_CIRC:
            symbol_keycode = KC_CIRC;
            break;
        case EN_AMPR:
            symbol_keycode = KC_AMPR;
            break;
        case EN_ASTR:
            symbol_keycode = KC_ASTR;
            break;
        case EN_LPRN:
            symbol_keycode = KC_LPRN;
            break;
        case EN_RPRN:
            symbol_keycode = KC_RPRN;
            break;
        case EN_LBRC:
            symbol_keycode = KC_LBRC;
            break;
        case EN_RBRC:
            symbol_keycode = KC_RBRC;
            break;
        case EN_QUOT:
            symbol_keycode = KC_QUOT;
            break;
        case EN_PIPE:
            symbol_keycode = KC_PIPE;
            break;
        case EN_GRV:
            symbol_keycode = KC_GRV;
            break;
        default:
            return true;
    }

    if (record->event.pressed) {
        const uint16_t lang_keycode = layer_state_is(WIN_SYM) ? WN_LANG : MC_LANG;

        tap_code16(lang_keycode);
        wait_ms(50);
        tap_code16(symbol_keycode);
        wait_ms(50);
        tap_code16(lang_keycode);
    }

    return false;
}

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &mac_tabber_active, KC_LWIN, KC_TAB, MC_TAB, OS_SHFT,
        keycode, record
    );
    update_swapper(
        &win_tabber_active, KC_LALT, KC_TAB, WN_TAB, OS_SHFT,
        keycode, record
    );

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

    if (record->event.pressed) {
        switch (keycode) {
            case BSPC_5:
                for (uint8_t i = 0; i < 5; i++) {
                    tap_code(KC_BSPC);
                }
                return false;
            case MINS_5:
                for (uint8_t i = 0; i < 5; i++) {
                    tap_code(KC_MINS);
                }
                return false;
        }
    }

    return process_english_shifted_symbol(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, MAC_SYM, MAC_NAV, MAC_FUN);
    state = update_tri_layer_state(state, WIN_SYM, WIN_NAV, WIN_FUN);
    return state;
}
