/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#define LSFT_A  SFT_T(KC_A)
#define RSFT_CN SFT_T(KC_SCLN)
#define ALT_SFT A(KC_LSFT)
#define CTL_SPC CTL_T(KC_SPC)
#define CTL_ESC CTL_T(KC_ESC)
#define GUI_BSP LGUI_T(KC_BSPC)
#define ALT_DEL LALT_T(KC_DEL)
#define ALT_CPS LALT_T(KC_CLCK)
#define SFT_DEL LSFT_T(KC_DEL)
#define LOW_ENT LT(_LOWER, KC_ENT)
#define RAI_TAB LT(_RAISE, KC_TAB)
#define CTL_BSP CTL_T(KC_BSPC)
#define CTL_DEL CTL_T(KC_DEL)

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  VI_PLUS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VI_PLUS:
      if (record->event.pressed) {
        SEND_STRING("\"+");
      }
      break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CLCK,  LSFT_A,  KC_S,    KC_D,    KC_F,    KC_G,                                                 KC_H,    KC_J,    KC_K,    KC_L,    RSFT_CN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ALGR,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ALGR, _______,         _______, ALT_SFT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_MUTE,  RAI_TAB, LOW_ENT, CTL_SPC, _______,         _______,  CTL_ESC, GUI_BSP, ALT_DEL, _______
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),

    [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_MUTE, KC_VOLU, _______, KC_WH_U, _______,                                              VI_PLUS, KC_ACL0, KC_ACL2, KC_HOME, KC_END,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LSFT, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R,                                              KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_VOLD, _______, KC_WH_D, _______, RESET,    _______,          _______,KC_INS,  _______, KC_APP,  KC_LBRC, KC_RBRC, KC_PGDN, _______,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                 _______, _______, _______, _______, _______,         _______, CTL_BSP, KC_BTN1, KC_BTN2, _______
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),

    [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______,  KC_F7,   KC_F8,   KC_F9,   KC_F12,                                               KC_GRV,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,  KC_F4,   KC_F5,   KC_F6,   KC_F11,                                               KC_EQL,  KC_4,    KC_5,    KC_6,    KC_QUOT, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F10, _______, _______,           _______, KC_PSCR, _______, KC_1,    KC_2,    KC_3,    KC_MINS, _______,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, _______, _______, _______, _______,          _______, CTL_DEL,  KC_0,    KC_DOT,  _______
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
