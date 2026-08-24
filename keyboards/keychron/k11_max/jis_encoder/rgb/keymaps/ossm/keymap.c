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
#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define MIRYOKU_CLIPBOARD_INS
#if defined (MIRYOKU_CLIPBOARD_FUN)
  #define U_RDO KC_AGIN
  #define U_PST KC_PSTE
  #define U_CPY KC_COPY
  #define U_CUT KC_CUT
  #define U_UND KC_UNDO
#elif defined (MIRYOKU_CLIPBOARD_MAC)
  #define U_RDO SCMD(KC_Z)
  #define U_PST LCMD(KC_V)
  #define U_CPY LCMD(KC_C)
  #define U_CUT LCMD(KC_X)
  #define U_UND LCMD(KC_Z)
#elif defined (MIRYOKU_CLIPBOARD_WIN)
  #define U_RDO C(KC_Y)
  #define U_PST C(KC_V)
  #define U_CPY C(KC_C)
  #define U_CUT C(KC_X)
  #define U_UND C(KC_Z)
#elif defined (MIRYOKU_CLIPBOARD_INS)
  #define U_RDO C(KC_Y)
  #define U_PST S(KC_INS)
  #define U_CPY C(KC_INS)
  #define U_CUT C(KC_X)
  #define U_UND C(KC_Z)
#else
  #define U_RDO KC_AGIN
  #define U_PST S(KC_INS)
  #define U_CPY C(KC_INS)
  #define U_CUT S(KC_DEL)
  #define U_UND KC_UNDO
#endif

enum layers {
    U_BASE,
    U_TAP,
    U_EXTRA,
    U_BUTTON,
    U_NAV,
    U_MOUSE,
    U_MEDIA,
    U_NUM,
    U_SYM,
    U_FUN,
};

enum {
    U_TD_BOOT,
    U_TD_U_BASE,
    U_TD_U_TAP,
    U_TD_U_EXTRA,
    U_TD_U_NAV,
    U_TD_U_MOUSE,
    U_TD_U_MEDIA,
    U_TD_U_NUM,
    U_TD_U_SYM,
    U_TD_U_FUN,
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
}

#define TD_LAYER(name, layer) \
void u_td_fn_##name(tap_dance_state_t *state, void *user_data) { \
    if (state->count == 2) { \
        default_layer_set(1UL << (layer)); \
    } \
}

TD_LAYER(U_BASE,   U_BASE)
TD_LAYER(U_TAP,    U_TAP)
TD_LAYER(U_EXTRA,  U_EXTRA)
TD_LAYER(U_NAV,    U_NAV)
TD_LAYER(U_MOUSE,  U_MOUSE)
TD_LAYER(U_MEDIA,  U_MEDIA)
TD_LAYER(U_NUM,    U_NUM)
TD_LAYER(U_SYM,    U_SYM)
TD_LAYER(U_FUN,    U_FUN)

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT]     = ACTION_TAP_DANCE_FN(u_td_fn_boot),
    [U_TD_U_BASE]   = ACTION_TAP_DANCE_FN(u_td_fn_U_BASE),
    [U_TD_U_TAP]    = ACTION_TAP_DANCE_FN(u_td_fn_U_TAP),
    [U_TD_U_EXTRA]  = ACTION_TAP_DANCE_FN(u_td_fn_U_EXTRA),
    [U_TD_GAM]      = ACTION_TAP_DANCE_FN(u_td_fn_GAM),
    [U_TD_U_NAV]    = ACTION_TAP_DANCE_FN(u_td_fn_U_NAV),
    [U_TD_U_MOUSE]  = ACTION_TAP_DANCE_FN(u_td_fn_U_MOUSE),
    [U_TD_U_MEDIA]  = ACTION_TAP_DANCE_FN(u_td_fn_U_MEDIA),
    [U_TD_U_NUM]    = ACTION_TAP_DANCE_FN(u_td_fn_U_NUM),
    [U_TD_U_SYM]    = ACTION_TAP_DANCE_FN(u_td_fn_U_SYM),
    [U_TD_U_FUN]    = ACTION_TAP_DANCE_FN(u_td_fn_U_FUN),
};

enum custom_keycodes {
    JIGGLE = NEW_SAFE_RANGE,

    BSPC_5, // 5x backspace
    MINS_5,  // 5x minus
};

// _______

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [U_BASE] = LAYOUT_73_jis(
        KC_ESC,            KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              KC_6,              KC_7,              KC_8,              KC_9,              KC_0,                 KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,                 KC_LBRC,  KC_RBRC,            KC_DEL,
        LT(U_MEDIA,KC_ESC),LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_SCLN),      KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,           LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,     KC_B,    KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH), KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,           KC_LCTL,           KC_LWIN,           KC_LALT,           LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), KC_RALT,           KC_RCTL,                                           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [U_EXTRA] = LAYOUT_73_jis(
        KC_ESC,            KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              KC_6,              KC_7,              KC_8,              KC_9,              KC_0,                 KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,            KC_Q,              KC_W,              KC_F,              KC_P,              KC_G,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_SCLN,              KC_LBRC,  KC_RBRC,            KC_DEL,
        LT(U_MEDIA,KC_ESC),LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_D,              KC_H,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),         KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,           LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,     KC_B,    KC_K,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH), KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,           KC_LCTL,           KC_LWIN,           KC_LALT,           LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), KC_RALT,           KC_RCTL,                                           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [U_TAP] = LAYOUT_73_jis(
        KC_ESC,            KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              KC_6,              KC_7,              KC_8,              KC_9,              KC_0,                 KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,                 KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,           KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_SCLN,              KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,           KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,     KC_B,    KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,              KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,           KC_LCTL,           KC_LWIN,           KC_LALT,           KC_SPC,            LT(U_NAV,KC_TAB),  LT(U_NUM,KC_ENT),  KC_SPC,            KC_RALT,           KC_RCTL,                                           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [U_BUTTON] = LAYOUT_73_jis(
        _______,           _______,           _______,           _______,           _______,           _______,          _______,            _______,           _______,           _______,           _______,              _______,  _______,  _______,  _______,  _______,
        _______,           _______,           _______,           _______,           _______,           _______,          _______,            _______,           _______,           _______,           _______,              _______,  _______,            _______,
        _______,           _______,           _______,           _______,           _______,           _______,          _______,            _______,           _______,           _______,           _______,              _______,  _______,  _______,  _______,
        _______,           _______,           _______,           _______,           _______,           _______, _______, _______,            _______,           _______,           _______,           _______,              _______,  _______,  _______,
        _______,           _______,           _______,           _______,           _______,           _______,          _______,            _______,           _______,           _______,                                           _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [U_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [U_EXTRA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [U_TAP] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [U_BUTTON]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [U_NAV] = { ENCODER_CCW_CW(U_UND, U_RDO)},
        [U_MOUSE] = { ENCODER_CCW_CW(U_UND, U_RDO)},
        [U_MEDIA]  = { ENCODER_CCW_CW(U_UND, U_RDO)},
        [U_SYM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [U_NUM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [U_FUN]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
    };
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

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

    switch (keycode) {
        case BSPC_5:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < 5; i++) {
                    tap_code(KC_BSPC);
                }
            }
            return false;

        case MINS_5:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < 5; i++) {
                    tap_code(KC_MINS);
                }
            }
            return false;

    }

    return process_english_shifted_symbol(keycode, record);
}
