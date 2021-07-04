/* Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
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
#include "jtu_custom_keycodes.h"

#define _DEF 0
#define _FN1 1
#define _FN2 2
#define _FN3 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_INS,     KC_DEL,
        JU_GRV,  KC_1,    JU_2,    KC_3,    KC_4,    KC_5,    JU_6,    JU_7,    JU_8,    JU_9,    JU_0,    JU_MINS, JU_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JU_LBRC, JU_RBRC, JU_BSLS,        KC_END,
        JU_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    JU_SCLN, JU_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                     LT(_FN1, KC_APP),     KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT(
        RESET,    TO(_DEF),TO(_FN1),TO(_FN2),TO(_FN3),   _______, _______, _______, _______,   _______, _______, _______, _______,    KC_MUTE,   KC_PSCR,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_PGUP,
        _______,     _______,KC_MS_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_BTN2,     KC_PGDN,
        _______,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,_______, _______, _______, _______, _______, _______, _______, _______, KC_MS_BTN1,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        KC_MS_WH_UP,
        _______,   _______,   _______,                      _______,                              _______,     _______, KC_MS_WH_LEFT,KC_MS_WH_DOWN,KC_MS_WH_RIGHT
    ),
    [_FN2] = LAYOUT(
        RGB_TOG,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            RGB_SAI,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        RGB_SAD,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_VAI,
        _______,   _______,   _______,                      _______,                              _______,     _______,        RGB_HUI, RGB_VAD,  RGB_HUD
    ),
    [_FN3] = LAYOUT(
        BL_TOGG,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   BL_STEP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          BL_INC,
        _______,   _______,   _______,                      _______,                              _______,     _______,        _______, BL_DEC,  _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_jtu(keycode, record);
  if (continue_process == false) {
    return false;
  }
  return true;
}