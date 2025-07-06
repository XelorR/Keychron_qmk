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

// Hardcoding language switching combinations
#define LANG_ENG_MAC C(S(KC_8))
#define LANG_RUS_MAC C(S(KC_9))
#define LANG_ENG_WIN C(KC_8)
#define LANG_RUS_WIN C(KC_9)

// Layers
#define SPC_NAV LT(NAV_WIN,KC_SPC)
#define ENT_MAC LT(NUM,KC_ENT)

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
#define SH_LCTL LM(SHORTCUT_WIN,MOD_LCTL)
#define SH_RCTL LM(SHORTCUT_WIN,MOD_RCTL)
#define SH_LWIN LM(SHORTCUT_WIN,MOD_LGUI)
#define SH_RWIN LM(SHORTCUT_WIN,MOD_RGUI)
#define SH_LALT LM(SHORTCUT_WIN,MOD_LALT)
#define SH_RALT LM(SHORTCUT_WIN,MOD_RALT)

// CUA

#define UNDO  C(KC_Z)
#define CUT   C(KC_X)
#define COPY  C(KC_C)
#define PASTE C(KC_V)
#define REDO1 C(S(KC_Z))
#define REDO2 C(KC_Y)

enum custom_keycodes {
   LG_ENG_MAC = NEW_SAFE_RANGE, // layer and system layout to english - 64
   LG_RUS_MAC,  // layer and system layout to russian - 65
   LG_GAME_MAC, // layer to gaming, layout to english - 66
   LG_ENG_WIN, // layer and system layout to english - 67
   LG_RUS_WIN, // layer and system layout to english - 67
   LG_GAME_WIN, // layer to gaming, layout to english - 66
};

enum layers {
    EN_MAC,
    EN_WIN,
    RU_MAC,
    RU_WIN,
    SHORTCUT_MAC,
    SHORTCUT_WIN,
    GAMING_MAC,
    GAMING_WIN,
    NUM,
    NAV_MAC,
    NAV_WIN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [EN_WIN] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_ESC,   HG_A,     HA_R,     HC_S,     HS_T,     KC_D,               KC_H,     HS_N,     HC_E,     HA_I,     HG_O,     KC_QUOT,  KC_BSLS,  ENT_MAC,  KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        SH_LCTL,  SH_LWIN,  SH_LWIN,  KC_LALT,  SPC_NAV,  KC_NO,             KC_NO,   SPC_NAV,  SH_RALT,  KC_NO,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [RU_WIN] = LAYOUT_73_jis(
        KC_GRV,   KC_NO,     KC_NO,     KC_3,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_9,     KC_0,     KC_NO,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_W,     KC_NO,  KC_Z,     KC_NO, KC_NO,   KC_P,     KC_D,     KC_R,     KC_L,     KC_X,     KC_I,     KC_O,                         KC_DEL,
        KC_ESC,   HG_E,     HA_B,     HC_T,     HS_J,     KC_F,               KC_K,     HS_Y,     HC_N,     HA_C,     HG_H,     KC_Q,     KC_BSLS,  ENT_MAC,  KC_HOME,
        KC_LSFT,  KC_A,     KC_QUOT,  KC_LBRC,  KC_S,     KC_DOT,   KC_DOT,   KC_COMM,  KC_V,     KC_G,     KC_U,     KC_SCLN,  KC_RSFT,  KC_RSFT,  KC_UP,
        SH_LCTL,  SH_LWIN,  SH_LWIN,  KC_LALT,  SPC_NAV,  KC_NO,             KC_NO,   SPC_NAV,  SH_RALT,  KC_NO,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [SHORTCUT_WIN] = LAYOUT_73_jis(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_ESC,   HG_A,     HA_R,     HC_S,     HS_T,     KC_D,               KC_H,     HS_N,     HC_E,     HA_I,     HG_O,     KC_QUOT,  KC_BSLS,  ENT_MAC,  KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LWIN,  KC_LALT,  KC_SPC,   KC_NO,             KC_NO,   KC_SPC,   KC_RALT,  KC_NO,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [GAMING_WIN] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LCMMD, KC_LALT,  KC_SPC,   KC_NO,             KC_NO,   KC_SPC,   KC_RALT,  KC_NO,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [NAV_WIN] = LAYOUT_73_jis(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        KC_TAB,  A(KC_F4), C(S(KC_TAB)), KC_TAB, C(KC_TAB), KC_NO,         KC_INS,   KC_HOME,  KC_UP,    KC_END,   KC_DEL,   KC_NO,   KC_NO,  _______,
        KC_ESC,   KC_LWIN, KC_LALT, OSM(MOD_LCTL), KC_LSFT, KC_PSCR,        S(KC_RSFT), KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_NO, KC_NO, KC_ENT,   _______,
        KC_RSFT,  UNDO,     CUT,      COPY,     PASTE,    REDO1,    REDO2,    KC_RALT,  KC_PGUP,  KC_APP,   KC_PGDN,  KC_ENT,   KC_NO, _______,  _______,
        KC_RCTL,  KC_RWIN,  KC_RCMMD, KC_RALT,  KC_SPC,             KC_NO,   KC_NO,             KC_SPC,   KC_RALT,  KC_NO,            _______,  _______,  _______),

    [NUM] = LAYOUT_73_jis(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  QK_MACRO_2,  QK_MACRO_3,                    KC_INS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,            _______,  _______,  _______,  _______,  QK_MACRO_6, QK_MACRO_1, QK_MACRO_0, KC_ENT, KC_END,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  QK_MACRO_4,  QK_MACRO_5,  KC_PGUP,
        DM_REC1,  DM_RSTP,  DM_PLY1,  _______,  _______,            _______,  _______,            _______,  _______,  _______,            _______,  KC_PGDN,  _______)
};

// ----------------------------------------------
// Mapping encoder
#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [EN_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [EN_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [RU_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [RU_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [SHORTCUT_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [SHORTCUT_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [GAMING_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [GAMING_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [NUM] = { ENCODER_CCW_CW(_______, _______)},
        [NAV_MAC]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [NAV_WIN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    };
#endif // ENCODER_MAP_ENABLE

// ==============================================
// Magic starts here
// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_record_keychron_common(keycode, record)) { return false; }

    switch (keycode)
    {
        case LG_ENG_MAC:
        if (record->event.pressed) {
            tap_code16(LANG_ENG_MAC);
            default_layer_set(1 << EN_MAC);
        }
        return false;

        case LG_RUS_MAC:
        if (record->event.pressed) {
            tap_code16(LANG_RUS_MAC);
            default_layer_set(1 << RU_MAC);
        }
        return false;

        case LG_GAME_MAC:
        if (record->event.pressed) {
            tap_code16(LANG_ENG_MAC);
            default_layer_set(1 << GAMING_MAC);
        }
        return false;

        case LG_ENG_WIN:
        if (record->event.pressed) {
            tap_code16(LANG_ENG_WIN);
            default_layer_set(1 << EN_WIN);
        }
        return false;

        case LG_RUS_WIN:
        if (record->event.pressed) {
            tap_code16(LANG_RUS_WIN);
            default_layer_set(1 << RU_WIN);
        }
        return false;

        case LG_GAME_WIN:
        if (record->event.pressed) {
            tap_code16(LANG_ENG_WIN);
            default_layer_set(1 << GAMING_WIN);
        }
        return false;

        default:
            return true;
    }
}
