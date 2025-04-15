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

#define LANG_ENG C(KC_8)
#define LANG_RUS C(KC_9)

// Layers
#define SPC_NAV LT(NAVIGATION,KC_SPC)
#define ENT_MAC LT(MACRO,KC_ENT)

// Mod-taps
#define HG_A LGUI_T(KC_A)
#define HA_R LALT_T(KC_R)
#define HC_S LCTL_T(KC_S)
#define HS_T LSFT_T(KC_T)
#define HS_N RSFT_T(KC_N)
#define HC_E LCTL_T(KC_E)
#define HA_I LALT_T(KC_I)
#define HG_O LGUI_T(KC_O)

#define HG_E LGUI_T(KC_E)
#define HA_B LALT_T(KC_B)
#define HC_T LCTL_T(KC_T)
#define HS_J LSFT_T(KC_J)
#define HS_Y RSFT_T(KC_Y)
#define HC_N LCTL_T(KC_N)
#define HA_C LALT_T(KC_C)
#define HG_H LGUI_T(KC_H)

// Modifiers to shortcut layer
#define SH_LCTL LM(SHORTCUT,MOD_LCTL)
#define SH_RCTL LM(SHORTCUT,MOD_RCTL)
#define SH_LWIN LM(SHORTCUT,MOD_LGUI)
#define SH_RWIN LM(SHORTCUT,MOD_RGUI)
#define SH_LALT LM(SHORTCUT,MOD_LALT)
#define SH_RALT LM(SHORTCUT,MOD_RALT)

// CUA

#define UNDO  C(KC_Z)
#define CUT   C(KC_X)
#define COPY  C(KC_C)
#define PASTE C(KC_V)
#define REDO1 C(S(KC_Z))
#define REDO2 C(KC_Y)

enum custom_keycodes {
    LG_ENG = NEW_SAFE_RANGE, // layer and system layout to english - 64
    LG_RUS,  // layer and system layout to russian - 65
    LG_GAME, // layer to gaming, layout to english - 66

    CO_RUB, // ₽ 96
    CO_QU_SMART_PAIR, // «» for russian and “” for english 97
    QU_COMP_PAIR, // "" 98
    CO_EMDASH, // — 99
    CO_DEGREE, // ° 100

    // Punctuation
    SUPER_DOT, // . ! — 101
    SUPER_COMMA, // , ? «» “” 102

    // Launchers
    TERMINAL,
};

enum layers {
    ENGLISH_COLEMAC,
    RUSSIAN_DIKTOR,
    SHORTCUT,
    GAMING,
    NAVIGATION,
    MACRO,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ENGLISH_COLEMAC] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_ESC,   HG_A,     HA_R,     HC_S,     HS_T,     KC_D,               KC_H,     HS_N,     HC_E,     HA_I,     HG_O,     KC_QUOT,  KC_BSLS,  ENT_MAC,  KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        SH_LCTL,  SH_LWIN,  SH_RWIN,  KC_LALT,  SPC_NAV,  LG_ENG,             LG_RUS,   SPC_NAV,  SH_RALT,  LG_GAME,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [RUSSIAN_DIKTOR] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_W,     KC_M,     KC_Z,     KC_QUES,  KC_SLSH,  KC_P,     KC_D,     KC_R,     KC_L,     KC_X,     KC_I,     KC_O,                         KC_DEL,
        KC_ESC,   HG_E,     HA_B,     HC_T,     HS_J,     KC_F,               KC_K,     HS_Y,     HC_N,     HA_C,     HG_H,     KC_Q,     KC_BSLS,  ENT_MAC,  KC_HOME,
        KC_LSFT,  KC_A,     KC_QUOT,  KC_LBRC,  KC_S,     KC_DOT,   KC_RBRC,  KC_COMM,  KC_V,     KC_G,     KC_U,     KC_SCLN,  KC_RSFT,  KC_RSFT,  KC_UP,
        SH_LCTL,  SH_LWIN,  SH_RWIN,  KC_LALT,  SPC_NAV,  LG_ENG,             LG_RUS,   SPC_NAV,  SH_RALT,  LG_GAME,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [SHORTCUT] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_ESC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_D,               KC_H,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_RCMMD, KC_LALT,  KC_SPC,   LG_ENG,             LG_RUS,   KC_SPC,   KC_RALT,  LG_GAME,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [GAMING] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LCMMD, KC_LALT,  KC_SPC,   LG_ENG,             LG_RUS,   KC_SPC,   KC_RALT,  LG_GAME,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [NAVIGATION] = LAYOUT_73_jis(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        KC_TAB,  A(KC_F4), C(S(KC_TAB)), KC_TAB, C(KC_TAB), TERMINAL,         KC_ESC,   KC_HOME,  KC_UP,    KC_END,   KC_DEL,   CO_QU_SMART_PAIR,   _______,  _______,
        KC_ESC,   KC_LWIN, KC_LALT, OSM(MOD_LCTL), KC_LSFT, KC_PSCR,        S(KC_RSFT), KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  CO_EMDASH, _______, KC_ENT,   _______,
        KC_RSFT,  UNDO,     CUT,      COPY,     PASTE,    REDO1,    REDO2,    G(KC_E),  KC_PGUP,  KC_APP,   KC_PGDN,  KC_ENT,   _______,  _______,  _______,
        KC_RCTL,  KC_RWIN,  KC_RCMMD, KC_RALT,  KC_SPC,             LG_ENG,   LG_RUS,             KC_SPC,   KC_RALT,  LG_GAME,            _______,  _______,  _______),

    [MACRO] = LAYOUT_73_jis(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  QK_MACRO_2,  QK_MACRO_3,                    KC_INS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,            _______,  _______,  _______,  _______,  QK_MACRO_6, QK_MACRO_1, QK_MACRO_0, KC_ENT, KC_END,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  QK_MACRO_4,  QK_MACRO_5,  KC_PGUP,
        _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [ENGLISH_COLEMAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [RUSSIAN_DIKTOR] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [SHORTCUT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [GAMING] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [NAVIGATION] = { ENCODER_CCW_CW(_______, _______)},
        [MACRO]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    };
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    if (!process_record_keychron_common(keycode, record)) { return false; }

    switch (keycode)
    {
        case LG_ENG:
        if (record->event.pressed) {
            tap_code16(LANG_ENG);
            default_layer_set(1 << 0);
        }
        return false;

        case LG_RUS:
        if (record->event.pressed) {
            tap_code16(LANG_RUS);
            default_layer_set(1 << 1);
        }
        return false;

        case LG_GAME:
        if (record->event.pressed) {
            tap_code16(LANG_ENG);
            default_layer_set(1 << 3);
        }
        return false;

        case SUPER_DOT:  // . ! —
        if (record->event.pressed) {
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                SEND_STRING("!");
          } else if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_MINS);
                wait_ms(10);
                tap_code16(KC_MINS);
                wait_ms(10);
                tap_code16(KC_MINS);
          } else {
             bool is_russian = (get_highest_layer(default_layer_state) == 1);
             if (is_russian) {
                tap_code16(LANG_RUS);
                SEND_STRING("/");
            } else {
                tap_code16(LANG_ENG);
                SEND_STRING(".");
            }
          }
          register_mods(mods);  // Restore mods.
        }
        return false;

        case SUPER_COMMA:  // , ? «» “”
        if (record->event.pressed) {
          bool is_russian = (get_highest_layer(default_layer_state) == 1);
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
            if (is_russian) {
                tap_code16(LANG_RUS);
                SEND_STRING("&");
            } else {
                tap_code16(LANG_ENG);
                SEND_STRING("?");
            }
          } else if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
            if (is_russian) {
                tap_code16(LANG_ENG);
                wait_ms(20);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(S(KC_COMMA));
                wait_ms(10);
                tap_code16(S(KC_COMMA));
                wait_ms(10);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(S(KC_DOT));
                wait_ms(10);
                tap_code16(S(KC_DOT));
                wait_ms(10);
                tap_code16(KC_LEFT);
                wait_ms(20);
                tap_code16(LANG_RUS);
            } else {
                tap_code16(LANG_ENG);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_DQUO);
                wait_ms(10);
                tap_code16(KC_LT);
                wait_ms(10);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_DQUO);
                wait_ms(10);
                tap_code16(KC_GT);
                wait_ms(10);
                tap_code16(KC_LEFT);
            }
          } else {
            if (is_russian) {
                tap_code16(LANG_RUS);
                SEND_STRING("?");
            } else {
                tap_code16(LANG_ENG);
                SEND_STRING(",");
            }
          }
          register_mods(mods);  // Restore mods.
        }
        return false;

        case CO_QU_SMART_PAIR:
        if (record->event.pressed) {
            bool is_russian = (get_highest_layer(default_layer_state) == 1);
            if (is_russian) {
                tap_code16(LANG_ENG);
                wait_ms(20);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(S(KC_COMMA));
                wait_ms(10);
                tap_code16(S(KC_COMMA));
                wait_ms(10);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(S(KC_DOT));
                wait_ms(10);
                tap_code16(S(KC_DOT));
                wait_ms(10);
                tap_code16(KC_LEFT);
                wait_ms(20);
                tap_code16(LANG_RUS);
            } else {
                tap_code16(LANG_ENG);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_DQUO);
                wait_ms(10);
                tap_code16(KC_LT);
                wait_ms(10);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_DQUO);
                wait_ms(10);
                tap_code16(KC_GT);
                wait_ms(10);
                tap_code16(KC_LEFT);
            }
        }
        return false;

        case CO_EMDASH:
        if (record->event.pressed) {
            tap_code16(KC_RALT);
            wait_ms(10);
            tap_code16(KC_MINS);
            wait_ms(10);
            tap_code16(KC_MINS);
            wait_ms(10);
            tap_code16(KC_MINS);
        }
        return false;

        case CO_RUB:
        if (record->event.pressed) {
            bool is_russian = (get_highest_layer(default_layer_state) == 1);
            if (is_russian) {
                tap_code16(LANG_ENG);
                wait_ms(20);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_EQL);
                wait_ms(10);
                tap_code16(KC_P);
                wait_ms(20);
                tap_code16(LANG_RUS);
            } else {
                tap_code16(LANG_ENG);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_EQL);
                wait_ms(10);
                tap_code16(KC_P);
            }
        }
        return false;

        case QU_COMP_PAIR:
        if (record->event.pressed) {
            bool is_russian = (get_highest_layer(default_layer_state) == 1);
            if (is_russian) {
                tap_code16(LANG_RUS);
                tap_code16(KC_AT);
                wait_ms(10);
                tap_code16(KC_AT);
                wait_ms(10);
                tap_code16(KC_LEFT);
                wait_ms(20);
            } else {
                tap_code16(LANG_ENG);
                tap_code16(KC_DQUO);
                wait_ms(10);
                tap_code16(KC_DQUO);
                wait_ms(10);
                tap_code16(KC_LEFT);
            }
        }
        return false;

        case TERMINAL:
        if (record->event.pressed) {
            bool is_russian = (get_highest_layer(default_layer_state) == 1);
            if (is_russian) {
                tap_code16(LANG_ENG);
                wait_ms(50);
                tap_code16(KC_LGUI);
                wait_ms(250);
                SEND_STRING("Terminal");
                wait_ms(350);
                tap_code16(KC_ENT);
                wait_ms(50);
                tap_code16(LANG_RUS);
            } else {
                tap_code16(LANG_ENG);
                wait_ms(50);
                tap_code16(KC_LGUI);
                wait_ms(250);
                SEND_STRING("Terminal");
                wait_ms(350);
                tap_code16(KC_ENT);
                wait_ms(50);            }
        }
        return false;

        case CO_DEGREE:
        if (record->event.pressed) {
            bool is_russian = (get_highest_layer(default_layer_state) == 1);
            if (is_russian) {
                tap_code16(LANG_ENG);
                wait_ms(20);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_O);
                wait_ms(10);
                tap_code16(KC_O);
                wait_ms(20);
                tap_code16(LANG_RUS);
            } else {
                tap_code16(LANG_ENG);
                tap_code16(KC_RALT);
                wait_ms(10);
                tap_code16(KC_O);
                wait_ms(10);
                tap_code16(KC_O);
            }
        }
        return false;

        default:
            return true;
    }
}
