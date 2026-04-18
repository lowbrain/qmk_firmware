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

#define _US 0
#define _JP 1
#define _FN0 2
#define _FN1 3
#define _FN2 4
#define _FN3 5
#define _FN4 6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_US] = LAYOUT_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL,     KC_PSCR,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_END,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,         KC_UP,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                         LT(_FN0, KC_APP), KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_JP] = LAYOUT_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL,     KC_PSCR,
        JU_GRV,  KC_1,    JU_2,    KC_3,    KC_4,    KC_5,    JU_6,    JU_7,    JU_8,    JU_9,    JU_0,    JU_MINS, JU_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JU_LBRC, JU_RBRC, JU_BSLS,        KC_END,
        JU_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    JU_SCLN, JU_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,         KC_UP,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                         LT(_FN0, KC_APP), KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN0] = LAYOUT_ansi(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______,    _______,  _______,
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,            KC_PGUP,
        _______,     _______, KC_UP,   _______, _______, _______, _______, PDF(_US), _______, _______, KC_PSCR, KC_HOME,  KC_END, MS_BTN3,        KC_PGDN,
        _______,       KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, PDF(_JP), _______, _______, KC_PGUP, KC_PGDN, MS_BTN1,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______,  KC_INS,  KC_DEL, MS_BTN2,        MS_UP,
        _______,   _______,   _______,                       _______,                             _______,     MO(_FN1),       MS_LEFT,MS_DOWN,MS_RGHT
    ),
    [_FN1] = LAYOUT_ansi(
        QK_BOOT, _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______,     UG_TOGG, _______, UG_NEXT, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, _______, _______, _______, _______,        _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,            _______, _______, BL_DOWN, BL_TOGG, BL_UP,   NK_TOGG, _______, _______, _______, _______, _______,          BL_UP, 
        _______,   _______,   _______,                      _______,                              _______,     _______,        BL_TOGG, BL_DOWN, BL_STEP
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_jtu(keycode, record);
  if (continue_process == false) {
    return false;
  }
  return true;
}
