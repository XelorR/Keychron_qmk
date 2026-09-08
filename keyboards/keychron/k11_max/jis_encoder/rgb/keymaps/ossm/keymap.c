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
#define LA_NUM_M MO(MAC_NUM)
#define LA_NUM_W MO(WIN_NUM)
#define LA_MOU_M MO(MAC_MOU)
#define LA_MOU_W MO(WIN_MOU)

#define WN_SNAP G(S(KC_S))
#define MC_SNAP G(S(KC_4))
#define MC_PSCR G(S(KC_3))
#define WN_LANG G(KC_SPC)
#define MC_LANG C(KC_SPC)
#define UC_LAN1 C(S(KC_7))
#define UC_LAN2 C(S(KC_8))

#define MC_PST G(KC_V)
#define MC_CPY G(KC_C)
#define MC_CUT G(KC_X)

#define WN_PST S(KC_INS)
#define WN_CPY C(KC_INS)
#define WN_CUT C(KC_X)

#define MC_MCTL C(KC_UP)
#define WN_MCTL G(KC_TAB)

#define WN_TABL C(KC_PGUP)
#define WN_TABR C(KC_PGDN)
#define MC_TABL G(S(KC_LBRC))
#define MC_TABR G(S(KC_RBRC))
#define MC_WINL C(KC_LEFT)
#define MC_WINR C(KC_RGHT)
#define WN_WINL G(C(KC_LEFT))
#define WN_WINR G(C(KC_RGHT))

#define MC_EMOJ G(C(KC_SPC))
#define WN_EMOJ G(KC_DOT)
#define MC_APP S(KC_F10)
#define UC_SNUB S(KC_NUBS)
#define UC_SNUH S(KC_NUHS)

#define MC_CWIN G(KC_Q)
#define WN_CWIN A(KC_F4)

#define MC_UNDO G(KC_Z)
#define MC_REDO G(S(KC_Z))
#define WN_UNDO C(KC_Z)
#define WN_REDO C(KC_Y)
#define MC_SAVE G(KC_S)
#define WN_SAVE C(KC_S)

#define MC_LOCK G(C(KC_Q))
#define WN_LOCK G(KC_L)
#define MC_KILL G(A(KC_ESC))
#define WN_KILL C(S(KC_ESC))

#define UC_MC0 QK_MACRO_0
#define UC_MC1 QK_MACRO_1
#define UC_MC2 QK_MACRO_2
#define UC_MC3 QK_MACRO_3

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_NUM,
    WIN_NUM,
    MAC_NAV,
    WIN_NAV,
    MAC_MOU,
    WIN_MOU,
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
    CT_TAB, // Ctl-Tab for Tab navigation

    MC_HOME,
    MC_END,
    MC_PGUP,
    MC_PGDN,

    BSPC_5, // 5x backspace
    MINS_5,  // 5x minus
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMMD, KC_LOPTN, KC_LCMMD, KC_SPC,   LA_NUM_M,           LA_NAV_M, KC_LSFT,            KC_RALT,  KC_RCMMD,           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_73_jis(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_ENT,   KC_HOME,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCTL,  KC_LWIN,  KC_LALT,  KC_SPC,   LA_NUM_W,           LA_NAV_W, KC_LSFT,            KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_NUM] = LAYOUT_73_jis(
        _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,  KC_KP_5,            KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_0,  _______,  _______,  _______,  _______,  MC_SAVE,
        KC_J,     MC_CWIN,  MC_TAB,   CT_TAB,   MC_MCTL,  KC_ESC,             KC_LBRC,  KC_7,     KC_8,     KC_9,     KC_RBRC,  _______,  _______,            _______,
        KC_I,     OS_CTRL,  OS_ALT,   OS_CMD,   OS_SHFT,  KC_ENT,             KC_EQL,   KC_4,     KC_5,     KC_6,     KC_MINS,  _______,  _______,  _______,  _______,
        KC_M,     KC_BSPC,  MC_CUT,   MC_CPY,   MC_PST,   KC_TAB,   BAT_LVL,  KC_BSLS,  KC_1,     KC_2,     KC_3,     KC_GRV,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            KC_QUOT,  KC_0,               _______,  _______,            _______,  _______,  _______),

    [WIN_NUM] = LAYOUT_73_jis(
        _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,  KC_KP_5,            KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_0,  _______,  _______,  _______,  _______,  WN_SAVE,
        KC_J,     WN_CWIN,  WN_TAB,   CT_TAB,   WN_MCTL,  KC_ESC,             KC_LBRC,  KC_7,     KC_8,     KC_9,     KC_RBRC,  _______,  _______,            _______,
        KC_I,     OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  KC_ENT,             KC_EQL,   KC_4,     KC_5,     KC_6,     KC_MINS,  _______,  _______,  _______,  _______,
        KC_M,     KC_DEL,   WN_CUT,   WN_CPY,   WN_PST,   KC_TAB,   BAT_LVL,  KC_BSLS,  KC_1,     KC_2,     KC_3,     KC_GRV,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            KC_QUOT,  KC_0,               _______,  _______,            _______,  _______,  _______),

    [MAC_NAV] = LAYOUT_73_jis(
        MC_LOCK,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  MC_SAVE,
        _______,  MC_PGUP,  MC_HOME,  KC_UP,    MC_END,   KC_ESC,             KC_ESC,   MC_MCTL,  CT_TAB,   MC_TAB,   MC_CWIN,  _______,  _______,            _______,
        _______,  MC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_ENT,             KC_ENT,   OS_SHFT,  OS_CMD,   OS_ALT,   OS_CTRL,  UC_MC2,   UC_MC3,   _______,  _______,
        _______,  KC_DEL,   UC_LAN1,  UC_LAN2,  KC_BSPC,  KC_TAB,   BAT_LVL,  KC_TAB,   MC_PST,   MC_CPY,   MC_CUT,   KC_BSPC,  _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  MC_LANG,  _______,            _______,  LA_MOU_M,           _______,  _______,            KC_HOME,  KC_PGDN,  KC_END),

    [WIN_NAV] = LAYOUT_73_jis(
        WN_LOCK,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  WN_SAVE,
        _______,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   KC_ESC,             KC_ESC,   WN_MCTL,  CT_TAB,   WN_TAB,   WN_CWIN,  _______,  _______,            _______,
        _______,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_ENT,             KC_ENT,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   UC_MC2,   UC_MC3,   _______,  _______,
        _______,  KC_DEL,   UC_LAN1,  UC_LAN2,  KC_BSPC,  KC_TAB,   BAT_LVL,  KC_TAB,   WN_PST,   WN_CPY,   WN_CUT,   KC_DEL,   _______,  _______,  KC_PGUP,
        _______,  _______,  _______,  _______,  WN_LANG,  _______,            _______,  LA_MOU_W,           _______,  _______,            KC_HOME,  KC_PGDN,  KC_END),

    [MAC_MOU] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  MS_WHLU,  MS_WHLL,  MS_UP,    MS_WHLR,  KC_ESC,             KC_ESC,   MC_MCTL,  CT_TAB,   MC_TAB,   MC_CWIN,  _______,  _______,            _______,
        _______,  MS_WHLD,  MS_LEFT,  MS_DOWN,  MS_RGHT,  KC_ENT,             KC_ENT,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  _______,  _______,
        _______,  KC_BSPC,  MC_CUT,   MC_CPY,   MC_PST,   KC_TAB,   BAT_LVL,  KC_TAB,   MC_PST,   MC_CPY,   MC_CUT,   KC_BSPC,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  MS_BTN1,  MS_BTN2,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [WIN_MOU] = LAYOUT_73_jis(
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  MS_WHLU,  MS_WHLL,  MS_UP,    MS_WHLR,  KC_ESC,             KC_ESC,   WN_MCTL,  CT_TAB,   WN_TAB,   WN_CWIN,  _______,  _______,            _______,
        _______,  MS_WHLD,  MS_LEFT,  MS_DOWN,  MS_RGHT,  KC_ENT,             KC_ENT,   OS_SHFT,  OS_CTRL,  OS_ALT,   OS_CMD,   _______,  _______,  _______,  _______,
        _______,  KC_DEL,   WN_CUT,   WN_CPY,   WN_PST,   KC_TAB,   BAT_LVL,  KC_TAB,   WN_PST,   WN_CPY,   WN_CUT,   KC_DEL,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  MS_BTN1,  MS_BTN2,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [MAC_FUN] = LAYOUT_73_jis(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,            RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    KC_MPLY,            MC_LOCK,  KC_F7,    KC_F8,    KC_F9,    KC_F12,   _______,  _______,            _______,
        CL_CTRL,  OS_CTRL,  OS_ALT,   OS_CMD,   OS_SHFT,  CW_TOGG,            MC_PSCR,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   EC_SWAP,  _______,  _______,  _______,
        CL_CAPS,  JIGGLE,   KC_VOLD,  KC_MUTE,  KC_VOLU,  MC_KILL,  BAT_LVL,  MC_APP,   KC_F1,    KC_F2,    KC_F3,    KC_F10,   EC_NORM,  _______,  _______
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______),

    [WIN_FUN] = LAYOUT_73_jis(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_MYCM,  RGB_VAD,            RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    KC_MPLY,            WN_LOCK,  KC_F7,    KC_F8,    KC_F9,    KC_F12,   _______,  _______,            _______,
        CL_CTRL,  OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  CW_TOGG,            KC_PSCR,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   EC_SWAP,  _______,  _______,  _______,
        CL_CAPS,  JIGGLE,   KC_VOLD,  KC_MUTE,  KC_VOLU,  WN_KILL,  BAT_LVL,  KC_APP,   KC_F1,    KC_F2,    KC_F3,    KC_F10,   EC_NORM,  _______,  _______
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,            _______,  _______,            _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [MAC_NUM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [WIN_NUM]  = { ENCODER_CCW_CW(BSPC_5, MINS_5)},
        [MAC_NAV] = { ENCODER_CCW_CW(MC_UNDO, MC_REDO)},
        [WIN_NAV] = { ENCODER_CCW_CW(WN_UNDO, WN_REDO)},
        [MAC_MOU]  = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},
        [WIN_MOU]  = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},
        [MAC_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [WIN_FUN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    };
#endif // ENCODER_MAP_ENABLE

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NAV_M:
    case LA_NUM_M:
    case LA_NAV_W:
    case LA_NUM_W:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NAV_M:
    case LA_NUM_M:
    case LA_NAV_W:
    case LA_NUM_W:
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
bool ctl_tabber_active = false;


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
    update_swapper(
        &ctl_tabber_active, KC_LCTL, KC_TAB, CT_TAB, OS_SHFT,
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

        case MC_HOME:
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_GUI) {
                    del_mods(MOD_MASK_GUI);
                    tap_code16(G(KC_UP)); // Document start
                    set_mods(mods);
                } else {
                    tap_code16(G(KC_LEFT)); // Row start
                }
            }
            return false;

        case MC_END:
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_GUI) {
                    del_mods(MOD_MASK_GUI);
                    tap_code16(G(KC_DOWN)); // Document end
                    set_mods(mods);
                } else {
                    tap_code16(G(KC_RGHT)); // Row end
                }
            }
            return false;

        case MC_PGUP:
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_GUI) {
                    del_mods(MOD_MASK_GUI);
                    tap_code16(MC_TABL); // Cmd+Shift+[ — previous tab
                    set_mods(mods);
                } else {
                    register_code(KC_PGUP); // Standard Page Up
                }
            } else {
                unregister_code(KC_PGUP);
            }
            return false;

        case MC_PGDN:
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_GUI) {
                    del_mods(MOD_MASK_GUI);
                    tap_code16(MC_TABR); // Cmd+Shift+] — next tab
                    set_mods(mods);
                } else {
                    register_code(KC_PGDN); // Standard Page Down
                }
            } else {
                unregister_code(KC_PGDN);
            }
            return false;
    }

}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, MAC_NUM, MAC_NAV, MAC_FUN);
    state = update_tri_layer_state(state, WIN_NUM, WIN_NAV, WIN_FUN);
    return state;
}
