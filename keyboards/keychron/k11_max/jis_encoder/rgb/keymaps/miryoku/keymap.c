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

#define LA_MEDIA LT(MEDIA,KC_ESC)
#define LA_NAV LT(WIN_NAV,KC_SPC)
#define LA_MOUSE LT(MOUSE,KC_TAB)
#define LA_NUM LT(NUM,KC_ENT)
#define LA_SYM LT(SYM,KC_BSPC)
#define TO_TAP DF(TAP)
#define TO_EXTRA DF(EXTRA)
#define TO_BASE DF(BASE)

#define WN_LANG G(KC_SPC)
#define MC_LANG C(KC_SPC)
#define LG_SWI1 C(S(KC_7))
#define LG_SWI2 C(S(KC_8))

#define WN_MCTL G(KC_TAB)

#define WN_EMOJ G(KC_DOT)
#define UC_SNUB S(KC_NUBS)
#define UC_SNUH S(KC_NUHS)

#define MC_LOCK G(C(KC_Q))
#define WN_LOCK G(KC_L)
#define MC_KILL G(A(KC_ESC))
#define WN_KILL C(S(KC_ESC))

#define U_HISTL A(KC_LEFT)
#define U_HISTR A(KC_RGHT)
#define WN_SNAP G(S(KC_S))

#define UC_MC0 QK_MACRO_0
#define UC_MC1 QK_MACRO_1
#define UC_MC2 QK_MACRO_2
#define UC_MC3 QK_MACRO_3

#define MTB_A LGUI_T(KC_A)
#define MTB_R LALT_T(KC_R)
#define MTB_S LCTL_T(KC_S)
#define MTB_T LSFT_T(KC_T)
#define MTB_N LSFT_T(KC_N)
#define MTB_E LCTL_T(KC_E)
#define MTB_I LALT_T(KC_I)
#define MTB_O LGUI_T(KC_O)

#define MTE_A LGUI_T(KC_A)
#define MTE_S LALT_T(KC_S)
#define MTE_D LCTL_T(KC_D)
#define MTE_F LSFT_T(KC_F)
#define MTE_J LSFT_T(KC_J)
#define MTE_K LCTL_T(KC_K)
#define MTE_L LALT_T(KC_L)
#define MTE_SEM LGUI_T(KC_SEMI)

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
    BASE,
    EXTRA,
    TAP,
    SHORTCUT,
    NAV,
    MOUSE,
    NUM,
    SYM,
    NUM_EXTRA,
    SYM_EXTRA,
    NEDIA,
};

enum custom_keycodes {
    JIGGLE = NEW_SAFE_RANGE,

    BSPC_5, // 5x backspace
    MINS_5,  // 5x minus
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,               KC_J,     KC_L,     KC_U,     KC_Y,     KC_QUOT,  KC_LBRC,  KC_RBRC,            KC_DEL,
        LA_MEDIA, MTB_A,    MTB_R,    MTB_S,    MTB_T,    KC_D,               KC_H,     MTB_N,    MTB_E,    MTB_I,    MTB_O,    KC_SCLN,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCTL,  KC_LWIN,  KC_LALT,  LA_NAV,   LA_MOUSE,           LA_SYM,   LA_NUM,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [EXTRA] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,
        LA_MEDIA, MTE_A,    MTE_S,    MTE_D,    MTE_F,    KC_G,               KC_H,     MTE_J,    MTE_K,    MTE_L,    KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCTL,  KC_LWIN,  KC_LALT,  LA_NAV,   LA_MOUSE,           LA_SYM,   LA_NUM,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [TAP] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCTL,  KC_LWIN,  KC_LALT,  KC_SPC,   MO(MOUSE),          MO(SYM),  LA_NUM,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [SHORTCUT] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,               KC_J,     KC_L,     KC_U,     KC_Y,     KC_QUOT,  KC_LBRC,  KC_RBRC,            KC_DEL,
        LA_MEDIA, MTB_A,    MTB_R,    MTB_S,    MTB_T,    KC_D,               KC_H,     MTB_N,    MTB_E,    MTB_I,    MTB_O,    KC_SCLN,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCTL,  KC_LWIN,  KC_LALT,  LA_NAV,   LA_MOUSE,           LA_SYM,   LA_NUM,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [NAV] = LAYOUT_73_jis(
        WN_LOCK,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  WN_SAVE,
        KC_I,     _______,  TO_TAP,   TO_EXTRA, TO_BASE,  _______,            KC_ESC,   KC_HOME,  KC_UP,    KC_END,   KC_PGUP,  _______,  _______,            _______,
        KC_M,     KC_LWIN,  KC_LALT,  KC_LCTL,  KC_LSFT,  WN_SNAP,            KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  UC_MC2,   UC_MC3,   _______,  _______,
        KC_J,     U_UND,    U_CUT,    U_CPY,    U_PST,    U_RDO,    BAT_LVL,  KC_TAB,   KC_BSPC,  WN_LANG,  KC_DEL,   KC_INS,   _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            KC_HOME,  KC_PGDN,  KC_END),

    [MOUSE] = LAYOUT_73_jis(
        WN_LOCK,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        KC_I,     _______,  TO_TAP,   TO_EXTRA, TO_BASE,  _______,            _______,  MS_WHLL,  MS_WHLD,  MS_WHLU,  MS_WHLR,  _______,  _______,            _______,
        KC_M,     KC_LWIN,  KC_LALT,  KC_LCTL,  KC_LSFT,  WN_SNAP,            JIGGLE,   MS_LEFT,  MS_DOWN,  MS_UP,    MS_RGHT,  _______,  _______,  _______,  _______,
        KC_J,     U_UND,    U_CUT,    U_CPY,    U_PST,    U_RDO,    BAT_LVL,  _______,  KC_BSPC,  U_HISTL,  U_HISTR,  KC_DEL,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            MS_BTN2,  MS_BTN1,            _______,  _______,            _______,  _______,  _______),

    [NUM] = LAYOUT_73_jis(
        _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,  KC_KP_5,            KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_0,  _______,  _______,  _______,  _______,  WN_SAVE,
        _______,  KC_LBRC,  KC_7,     KC_8,     KC_9,     KC_RBRC,            KC_NUM,   KC_LBRC,  KC_RBRC,  KC_LPRN,  KC_RPRN,  _______,  _______,            _______,
        _______,  KC_QUOT,  KC_4,     KC_5,     KC_6,     KC_MINS,            KC_EQL,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  _______,  _______,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_BSLS,  _______,  KC_NUBS,  KC_PSLS,  WN_EMOJ,  KC_PDOT,  KC_NUHS,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  KC_0,     _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [SYM] = LAYOUT_73_jis(
        KC_ESC,   EN_EXLM,  EN_AT,    EN_HASH,  EN_DLR,   EN_PERC,            EN_CIRC,  EN_AMPR,  EN_ASTR,  EN_LPRN,  EN_RPRN,  KC_UNDS,  KC_PLUS,  _______,  _______,  WN_SAVE,
        _______,  KC_LCBR,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RCBR,            KC_NUM,   KC_LCBR,  KC_RCBR,  KC_LPRN,  KC_RPRN,  EN_LBRC,  EN_RBRC,            KC_INS,
        RGB_TOG,  KC_DQUO,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_UNDS,            KC_PLUS,  OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   EN_QUOT,  EN_PIPE,  KC_PSCR,  KC_END,
        _______,  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_PIPE,  BAT_LVL,  UC_SNUB,  KC_PSLS,  WN_EMOJ,  KC_PDOT,  UC_SNUH,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  KC_PGDN,  _______),

    [MEDIA] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [MAC_SYM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [WIN_SYM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [MAC_NUM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [WIN_NUM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [MAC_NAV] = { ENCODER_CCW_CW(MC_UNDO, MC_REDO)},
        [WIN_NAV] = { ENCODER_CCW_CW(WN_UNDO, WN_REDO)},
        [MOUSE]  = { ENCODER_CCW_CW(_______, _______)},
        [MAC_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [WIN_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
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
}
