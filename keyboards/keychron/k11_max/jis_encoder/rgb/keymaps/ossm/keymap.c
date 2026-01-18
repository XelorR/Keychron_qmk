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

#define LA_NAV_W MO(NAV)
#define LA_SYM_W MO(SYM)

#define WN_SNAP G(S(KC_S))

#define WN_TABL (C(S(KC_TAB)))
#define WN_TABR (C(KC_TAB))
#define WN_WSPL G(C(KC_LEFT))
#define WN_WSPR G(C(KC_RGHT))
#define UC_HYPR G(C(S(KC_LALT))) // Copylot/Office365 button

#define MC_GBSP G(KC_BSPC)

enum layers {
    BASE,
    SYM,
    NAV,
    MACRO,
};

enum custom_keycodes {
    JIGGLE = NEW_SAFE_RANGE,

    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    IN_ROW_WIN,

    WN_GBSP, // windows version of Mac's Cmd-Backspace
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_RWIN,  KC_LALT,  KC_SPC,   LA_NAV_W,           LA_SYM_W,           KC_RSFT,  KC_APP,   UC_HYPR,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [SYM] = LAYOUT_73_jis(
        KC_TILD,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_MYCM,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,  _______,                      KC_INS,
        RGB_TOG,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    KC_MINS,            KC_PLUS,  OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   KC_DQUO,  _______,  KC_PSCR,  KC_END,
        _______,  KC_BSLS,  KC_PIPE,  KC_LBRC,  KC_RBRC,  KC_UNDS,  BAT_LVL,  KC_EQL,   KC_LCBR,  KC_RCBR,  KC_QUOT,  KC_QUES,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______),

    [NAV] = LAYOUT_73_jis(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,  KC_DEL,   WN_TABL,  KC_TAB,   WN_TABR,  KC_ESC,             KC_ESC,   KC_HOME,  KC_UP,    KC_END,   KC_DEL,   _______, _______,             _______,
        _______,  OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  KC_ENT,             KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  _______,  _______,  WN_SNAP,  _______,
        _______,  WN_WSPL,  WN_WSPR,  KC_LGUI,  KC_PSCR,  KC_TAB,   BAT_LVL,  KC_TAB,   KC_PGUP, IN_ROW_WIN, KC_PGDN, WN_GBSP,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______),

    [MACRO] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_F23,   KC_F24,                       _______,
        _______,  OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  KC_F11,             KC_F12,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  JIGGLE,   _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    BAT_LVL,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [SYM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [NAV]  = { ENCODER_CCW_CW(_______, _______)},
        [MACRO]  = { ENCODER_CCW_CW(_______, _______)},
    };
#endif // ENCODER_MAP_ENABLE

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM_W:
    case LA_NAV_W:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
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
            token  = INVALID_DEFERRED_TOKEN;
            report = (report_mouse_t){};  // Clear the mouse.
            host_mouse_send(&report);
        } else {
            switch (keycode) {
                case JIGGLE: {
                    uint32_t jiggler_callback(uint32_t trigger_time, void *cb_arg) {
                        // Deltas to move in a circle of radius 20 pixels over 32 frames.
                        static const int8_t deltas[32] = {
                            0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
                            0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0
                        };
                        static uint8_t phase = 0;
                        // Get x delta from table and y delta by rotating a quarter cycle.
                        report.x = deltas[phase];
                        report.y = deltas[(phase + 8) & 31];
                        phase    = (phase + 1) & 31;
                        host_mouse_send(&report);
                        return 16;  // Call the callback every 16 ms.
                    }
                    token = defer_exec(1, jiggler_callback, NULL);  // Schedule callback.
                } break;

                case IN_ROW_WIN: {
                    uint8_t mods = get_mods();
                    bool shift_held = mods & MOD_MASK_SHIFT;
                    clear_mods();
                    // insert row below
                    if (!shift_held) {
                        tap_code(KC_END);
                        tap_code16(LSFT(KC_ENT));
                        return false;
                    }
                    // with shift - insert row above
                    tap_code(KC_HOME);
                    tap_code16(LSFT(KC_ENT));
                    tap_code(KC_UP);
                    //
                    set_mods(mods);
                    return false;
                }

                case WN_GBSP:
                    tap_code16(LSFT(KC_HOME));
                    tap_code(KC_BSPC);
                    return false;

                default:
                    break;
            }
        }
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, SYM, NAV, MACRO);
    return state;
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_73_jis(
        '*',  '*',  '*',  '*',  '*',  '*',     '*',     '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',
        '*',  'L',  'L',  'L',  'L',  'L',              'R',  'R',  'R',  'R',  'R',  'R',  'R',  '*',
        '*',  'L',  'L',  'L',  'L',  'L',              'R',  'R',  'R',  'R',  'R',  'R',  '*',  '*',  '*',
        '*',  'L',  'L',  'L',  'L',  'L',     '*',     'R',  'R',  'R',  'R',  'R',  '*',  '*',  '*',
        '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*',  '*'
    );

// Combo definitions
enum combos {
    COMBO_ENG,
    COMBO_RUS,
    COMBO_GRAVE,
    COMBO_BACKSLASH,
    COMBO_UNDO,
    COMBO_CUT,
    COMBO_COPY,
    COMBO_PASTE,
    COMBO_REDO,
    COMBO_SELECTALL,
};

// Combo positions
const uint16_t PROGMEM combo_eng[]           = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_rus[]           = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_grave[]         = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo_backslash[]     = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo_undo[]          = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_cut[]           = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM combo_copy[]          = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_paste[]         = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_redo[]          = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM combo_selectall[]     = {KC_Z, KC_V, COMBO_END};

// Combo assignments
combo_t key_combos[] = {
    [COMBO_ENG]       = COMBO(combo_eng,           KC_CAPS),
    [COMBO_RUS]       = COMBO(combo_rus,           S(KC_CAPS)),
    [COMBO_GRAVE]     = COMBO(combo_grave,         KC_GRV),
    [COMBO_BACKSLASH] = COMBO(combo_backslash,     KC_BSLS),
    [COMBO_UNDO]      = COMBO(combo_undo,          C(KC_Z)),
    [COMBO_CUT]       = COMBO(combo_cut,           C(KC_X)),
    [COMBO_COPY]      = COMBO(combo_copy,          C(KC_C)),
    [COMBO_PASTE]     = COMBO(combo_paste,         C(KC_V)),
    [COMBO_REDO]      = COMBO(combo_redo,          C(KC_Y)),
    [COMBO_SELECTALL] = COMBO(combo_selectall,     C(KC_A)),
};

