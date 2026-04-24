/* Copyright 2019 Louwii
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

// �^�b�v�_���X�̃L�[�R�[�h
enum td_keycodes {
    TD_CAPS_L1,
};

// �^�b�v�_���X��Ԃ��܂ރ^�C�v
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD
} td_state_t;

// ���݂̃^�b�v�_���X�̏�Ԃ���肷�邽�߂̊֐�
uint8_t cur_dance(tap_dance_state_t *state);

// ���ꂼ��̃^�b�v�_���X�L�[�R�[�h�ɓK�p���� `finished` �� `reset` �֐�
void capsl1_finished(tap_dance_state_t *state, void *user_data);
void capsl1_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_tkl_ansi(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                  KC_PSCR, KC_SCRL, KC_PAUS,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,        KC_INS,  KC_HOME, KC_PGUP,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_DEL,  KC_END,  KC_PGDN,
      KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,                 KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, MO(2),   KC_APP,  KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT   ),
  [1] = LAYOUT_tkl_ansi(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                  KC_PSCR, KC_SCRL, KC_PAUS,
      JU_GRV,  KC_1,    JU_2,    KC_3,    KC_4,    KC_5,    JU_6,    JU_7,    JU_8,    JU_9,    JU_0,    JU_MINS, JU_EQL,  KC_BSPC,        KC_INS,  KC_HOME, KC_PGUP,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JU_LBRC, JU_RBRC, JU_BSLS,        KC_DEL,  KC_END,  KC_PGDN,
      TD(TD_CAPS_L1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    JU_SCLN, JU_QUOT, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,                 KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, MO(2),   KC_APP,  KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT   ),
  [2] = LAYOUT_tkl_ansi(
      QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, UG_SPDU, UG_SPDD,                 UG_TOGG, UG_NEXT, UG_PREV,
      KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,         KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, PDF(0),  KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END,  MS_BTN3,        KC_TRNS, KC_TRNS, KC_TRNS,
      KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, PDF(1),  KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN,          MS_BTN1,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_DEL,                    MS_BTN2,                 MS_UP,
      KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                                     KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS,        MS_LEFT, MS_DOWN, MS_RGHT   ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_jtu(keycode, record);
  if (continue_process == false) {
    return false;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

// �^�b�v�_���X�̏�Ԃ̌^�̃O���[�o���C���X�^���X
static td_state_t td_state;

// �ԋp����^�b�v�_���X��Ԃ���肵�܂�
uint8_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else {
        // ��L�ŕԋp����ő�̏�Ԃ̒l���傫���C�ӂ̐�
        return SINGLE_HOLD + 1; 
    }
}

//--- TD_CAPS_L1 ---------------------------------------------------------------
void capsl1_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(S(KC_CAPS));
            break;
        case SINGLE_HOLD:
            layer_on(1);
            break;
    }
}

void capsl1_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(S(KC_CAPS));
            break;
        case SINGLE_HOLD:
            layer_off(1);
            break;
    }
}
//------------------------------------------------------------------------------

// �e�^�b�v�_���X�L�[�R�[�h�� `ACTION_TAP_DANCE_FN_ADVANCED()` ���`���A`finished` �� `reset` �֐���n���܂�
tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, capsl1_finished, capsl1_reset)
};
