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

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define MODE_WIN
#if defined MODE_WIN
  #define U_RDO C(KC_Y)
  #define U_PST S(KC_INS)
  #define U_CPY C(KC_INS)
  #define U_CUT C(KC_X)
  #define U_UND C(KC_Z)
  #define U_WIN KC_LGUI
  #define U_ALT KC_LALT
  #define U_CMD KC_RCTL
  #define U_MCTL KC_TASK
  #define U_MYCM KC_MYCM
#if defined MODE_MAC
  #define U_RDO SCMD(KC_Z)
  #define U_PST LCMD(KC_V)
  #define U_CPY LCMD(KC_C)
  #define U_CUT LCMD(KC_X)
  #define U_UND LCMD(KC_Z)
  #define U_WIN KC_LALT
  #define U_ALT KC_LGUI
  #define U_CMD KC_RGUI
  #define U_MCTL KC_MCTRL
  #define U_MYCM KC_LNPAD
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
    U_GAM_FN,
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

    CO_BASE_GUI,  // combo: switch default layer to U_BASE  + send GUI-Space
    CO_EXTRA_GUI, // combo: switch default layer to U_EXTRA + send GUI-Space
    CO_BASE_CTL,  // combo: switch default layer to U_BASE  + send Ctrl-Space
    CO_EXTRA_CTL, // combo: switch default layer to U_EXTRA + send Ctrl-Space

    CO_TAP_BASE,
};

// _______

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [U_BASE] = LAYOUT_73_jis(
        KC_GRV,            KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              KC_6,              KC_7,              KC_8,              KC_9,              KC_0,                 KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,            KC_B,              KC_L,              KC_D,              KC_C,              KC_V,              KC_J,              KC_F,              KC_O,              KC_U,              KC_COMM,              KC_LBRC,  KC_RBRC,            KC_DEL,
        LT(U_MEDIA,KC_ESC),LGUI_T(KC_N),      LALT_T(KC_R),      LCTL_T(KC_T),      LSFT_T(KC_S),      KC_G,              KC_Y,              LSFT_T(KC_H),      LCTL_T(KC_A),      LALT_T(KC_E),      LGUI_T(KC_I),         KC_SLSH,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,           LT(U_BUTTON,KC_X), ALGR_T(KC_Q),      KC_M,              KC_W,              KC_Z,     KC_Z,    KC_K,              KC_P,              KC_QUOT,           ALGR_T(KC_SCLN),   LT(U_BUTTON,KC_DOT),  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,           U_CMD,             U_WIN,             U_ALT,             LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_CMD,                                             KC_LEFT,  KC_DOWN,  KC_RGHT),

    [U_EXTRA] = LAYOUT_73_jis(
        KC_GRV,            KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              KC_6,              KC_7,              KC_8,              KC_9,              KC_0,                 KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,                 KC_LBRC,  KC_RBRC,            KC_DEL,
        LT(U_MEDIA,KC_ESC),LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_SCLN),      KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,           LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,     KC_B,    KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH), KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,           U_CMD,             U_WIN,             U_ALT,             LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_CMD,                                             KC_LEFT,  KC_DOWN,  KC_RGHT),

    [U_TAP] = LAYOUT_73_jis(
        KC_ESC,            KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              KC_6,              KC_7,              KC_8,              KC_9,              KC_0,                 KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,                 KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,           KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_SCLN,              KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,           KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,     KC_B,    KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,              KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,           U_CMD,             U_WIN,             U_ALT,             KC_SPC,            MO(U_GAM_FN),      LT(U_NUM,KC_ENT),  KC_SPC,            KC_RALT,           U_CMD,                                             KC_LEFT,  KC_DOWN,  KC_RGHT),

    [U_BUTTON] = LAYOUT_73_jis(
        _______,           _______,           _______,           _______,           _______,           _______,           _______,           _______,           _______,           _______,           _______,              _______,  _______,  _______,  _______,  _______,
        _______,           U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,                _______,  _______,            _______,
        _______,           KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NU,              U_NU,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,              _______,  _______,  _______,  _______,
        _______,           U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,   _______,  U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,                _______,  _______,  _______,
        _______,           _______,           _______,           KC_BTN3,           KC_BTN1,           KC_BTN2,           KC_BTN2,           KC_BTN1,           KC_BTN3,           _______,                                           _______,  _______,  _______),

    [U_NAV] = LAYOUT_73_jis(
        _______,           KC_F1,             KC_F2,             KC_F3,             KC_F4,             KC_F5,             KC_F6,             KC_F7,             KC_F8,             KC_F9,             KC_F10,               KC_F11,      KC_F12,      _______,  _______,  RGB_TOG,
        _______,           TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,                _______,     _______,               _______,
        _______,           KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              CW_TOGG,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,              QK_MACRO_0,  QK_MACRO_1,  _______,  _______,
        _______,           U_NA,              KC_ALGR,           TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    U_NA,    BAT_LVL,  KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,               QK_MACRO_2,  QK_MACRO_3,  _______,
        _______,           _______,           _______,           _______,           U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL,            _______,                                              _______,     _______,  _______),

    [U_MOUSE] = LAYOUT_73_jis(
        _______,           KC_F1,             KC_F2,             KC_F3,             KC_F4,             KC_F5,             KC_F6,             KC_F7,             KC_F8,             KC_F9,             KC_F10,               KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
        _______,           TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,                _______,  _______,            _______,
        _______,           KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              JIGGLE,            KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,              _______,  _______,  _______,  _______,
        _______,           U_NA,              KC_ALGR,           TD(U_TD_U_SYM),    TD(U_TD_U_MOUSE),  U_NA,    BAT_LVL,  U_NU,              KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,              _______,  _______,  _______,
        _______,           _______,           _______,           _______,           U_NA,              U_NA,              KC_BTN2,           KC_BTN1,           KC_BTN3,           _______,                                           _______,  _______,  _______),

    [U_MEDIA] = LAYOUT_73_jis(
        _______,           KC_BRID,           KC_BRIU,           U_MCTL,            U_MYCM,            RGB_VAD,           RGB_VAI,           KC_MPRV,           KC_MPLY,           KC_MNXT,           KC_MUTE,              KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,           TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA,              RGB_TOG,           RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,              _______,  _______,            _______,
        _______,           KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              U_NU,              KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,              _______,  _______,  _______,  _______,
        _______,           U_NA,              KC_ALGR,           TD(U_TD_U_FUN),    TD(U_TD_U_MEDIA),  U_NA,    BAT_LVL,  U_NU,              BT_HST1,           BT_HST2,           BT_HST3,           P2P4G,                _______,  _______,  _______,
        _______,           _______,           _______,           _______,           U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE,           _______,                                           _______,  _______,  _______),

    [U_NUM] = LAYOUT_73_jis(
        _______,           KC_BRID,           KC_BRIU,           U_MCTL,            U_MYCM,            RGB_VAD,           RGB_VAI,           KC_MPRV,           KC_MPLY,           KC_MNXT,           KC_MUTE,              KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,           KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),        _______,  _______,            _______,
        KC_NUBS,           KC_SLSH,           KC_4,              KC_5,              KC_6,              KC_EQL,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,              _______,  _______,  _______,  _______,
        _______,           KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS, BAT_LVL,  U_NA,              TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    KC_ALGR,           U_NA,                 _______,  _______,  _______,
        _______,           _______,           _______,           KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA,              _______,                                           _______,  _______,  _______),

    [U_SYM] = LAYOUT_73_jis(
        _______,           KC_BRID,           KC_BRIU,           U_MCTL,            U_MYCM,            RGB_VAD,           RGB_VAI,           KC_MPRV,           KC_MPLY,           KC_MNXT,           KC_MUTE,              KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,           KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),        _______,  _______,            _______,
        S(KC_NUBS),        KC_QUES,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_PLUS,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,              _______,  _______,  _______,  _______,
        _______,           KC_TILD,           KC_EXLM,           KC_AT,             KC_HASH,           KC_PIPE, BAT_LVL,  U_NA,              TD(U_TD_U_SYM),    TD(U_TD_U_MOUSE),  KC_ALGR,           U_NA,                 _______,  _______,  _______,
        _______,           _______,           _______,           KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA,              _______,                                           _______,  _______,  _______),

    [U_FUN] = LAYOUT_73_jis(
        _______,           KC_BRID,           KC_BRIU,           U_MCTL,            U_MYCM,            RGB_VAD,           RGB_VAI,           KC_MPRV,           KC_MPLY,           KC_MNXT,           KC_MUTE,              KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,           KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),        _______,  _______,            _______,
        _______,           KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SCRL,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,              _______,  _______,  _______,  _______,
        _______,           KC_F10,            KC_F1,             KC_F2,             KC_F3,             KC_PAUS, BAT_LVL,  U_NA,              TD(U_TD_U_FUN),    TD(U_TD_U_MEDIA),  KC_ALGR,           U_NA,                 _______,  _______,  _______,
        _______,           _______,           _______,           KC_APP,            KC_SPC,            KC_TAB,            U_NA,              U_NA,              U_NA,              _______,                                           _______,  _______,  _______),

    [U_GAM_FN] = LAYOUT_73_jis(
        _______,           KC_F1,             KC_F2,             KC_F3,             KC_F4,             KC_F5,             KC_F6,             KC_F7,             KC_F8,             KC_F9,             KC_F10,               KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
        KC_J,              KC_DOT,            KC_7,              KC_8,              KC_9,              KC_GRV,            U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,                _______,  _______,            _______,
        KC_I,              KC_COMM,           KC_4,              KC_5,              KC_6,              KC_H,              CW_TOGG,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,              _______,  _______,  _______,  _______,
        KC_M,              KC_SLSH,           KC_1,              KC_2,              KC_3,              KC_MUTE, BAT_LVL,  KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,               _______,  _______,  _______,
        _______,           _______,           _______,           KC_ENT,            KC_0,              _______,           DF(U_BASE),        KC_PSCR,           U_NA,              _______,                                           _______,  _______,  _______),

};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [U_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [U_EXTRA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [U_TAP] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [U_BUTTON]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [U_NAV] = { ENCODER_CCW_CW(U_UND, U_RDO)},
        [U_MOUSE] = { ENCODER_CCW_CW(U_UND, U_RDO)},
        [U_MEDIA]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [U_SYM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [U_NUM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [U_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [U_GAM_FN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    };
#endif // ENCODER_MAP_ENABLE

#if defined(COMBO_ENABLE)
uint8_t combo_ref_from_layer(uint8_t layer) {
    switch (layer) {
        case U_BASE:
        case U_EXTRA:
            return U_TAP;
        default:
            return layer;
    }
}

enum combos {
    CO_WR,
    CO_UO,
    CO_XV,
    CO_MDOT,
    CO_UI,
    CO_IO,
    CO_WE,
    CO_ER,
    CO_QP,
};

const uint16_t PROGMEM combo_wr[]  = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM combo_uo[]  = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM combo_xv[]  = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM combo_mdot[] = {KC_M, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_ui[]  = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_io[]  = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_we[]  = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_er[]  = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_qp[]  = {KC_Q, KC_P, COMBO_END};

combo_t key_combos[] = {
    [CO_WR]   = COMBO(combo_wr,   CO_BASE_GUI),
    [CO_UO]   = COMBO(combo_uo,   CO_EXTRA_GUI),
    [CO_XV]   = COMBO(combo_xv,   CO_BASE_CTL),
    [CO_MDOT] = COMBO(combo_mdot, CO_EXTRA_CTL),
    [CO_UI]   = COMBO(combo_ui,   KC_LBRC),
    [CO_IO]   = COMBO(combo_io,   KC_RBRC),
    [CO_WE]   = COMBO(combo_we,   KC_QUOT),
    [CO_ER]   = COMBO(combo_er,   KC_GRV),
    [CO_QP]   = COMBO(combo_qp,   CO_TAP_BASE),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case CO_QP:
            return get_highest_layer(layer_state | default_layer_state) == U_TAP;

        default:
            switch (get_highest_layer(layer_state | default_layer_state)) {
                case U_BASE:
                case U_EXTRA:
                    return true;
                default:
                    return false;
            }
    }
}

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

        case CO_BASE_GUI:
            if (record->event.pressed) {
                default_layer_set(1UL << U_BASE);
                tap_code16(LGUI(KC_SPC));
            }
            return false;

        case CO_EXTRA_GUI:
            if (record->event.pressed) {
                default_layer_set(1UL << U_EXTRA);
                tap_code16(LGUI(KC_SPC));
            }
            return false;

        case CO_BASE_CTL:
            if (record->event.pressed) {
                default_layer_set(1UL << U_BASE);
                tap_code16(LCTL(KC_SPC));
            }
            return false;

        case CO_EXTRA_CTL:
            if (record->event.pressed) {
                default_layer_set(1UL << U_EXTRA);
                tap_code16(LCTL(KC_SPC));
            }
            return false;

        case CO_TAP_BASE:
            if (record->event.pressed) {
                default_layer_set(1UL << U_BASE);
            }
            return false;


    }

    return true;
}

#endif // COMBO_ENABLE
