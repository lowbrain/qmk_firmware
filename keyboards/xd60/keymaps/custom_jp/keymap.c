#include QMK_KEYBOARD_H
#include "jtu_custom_keycodes.h"

// タップダンスのキーコード
enum td_keycodes {
    TD_MO,
};

// タップダンス状態を含むタイプ
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD
} td_state_t;

// 現在のタップダンスの状態を特定するための関数
uint8_t cur_dance(qk_tap_dance_state_t *state);

// それぞれのタップダンスキーコードに適用する `finished` と `reset` 関数
void capsl1_finished(qk_tap_dance_state_t *state, void *user_data);
void capsl1_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  LAYOUT_all(
      KC_ESC,         KC_1,    JU_2,    KC_3,    KC_4,    KC_5,    JU_6,    JU_7,    JU_8,    JU_9,    JU_0,      JU_MINS,  JU_EQL,  JU_BSLS, KC_DEL, \
      KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      JU_LBRC,  JU_RBRC,          KC_BSPC,\
      JU_CAPS,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    JU_SCLN,   JU_QUOT,  KC_NO,            KC_ENT, \
      KC_LSFT,        KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH,  KC_NO,   KC_RSFT, MO(1),  \
      KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                             TD(TD_MO), KC_RALT,  KC_NO,   KC_APP,  KC_RCTL),

  // 1: Function Layer
  LAYOUT_all(
      JU_GRV,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  RGB_TOG, RGB_MOD,\
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_UP,    KC_END,           KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_LEFT, KC_RGHT,  KC_TRNS,          KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_PGDN, KC_DOWN,  KC_TRNS, KC_TRNS, KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS),

  // 2: Function Layer
  LAYOUT_all(
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_UP,   KC_TRNS,\
      KC_TRNS,        KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_RGHT),

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


bool led_update_user(led_t led_state) {
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        led_state.caps_lock ? rgblight_enable() : rgblight_disable();
        caps_state = led_state.caps_lock;
    }
    return true;
}

// タップダンスの状態の型のグローバルインスタンス
static td_state_t td_state;

// 返却するタップダンス状態を特定します
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            return DOUBLE_HOLD;
        } else {
            return DOUBLE_TAP;
        }
    } else {
        return DOUBLE_HOLD + 1; 
    }
}

//--- TD_MO ---------------------------------------------------------------
void mo_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_ZKHK);
            break;
        case SINGLE_HOLD:
            layer_on(1);
            break;
        case DOUBLE_TAP:
            if (layer_state_is(2)) {
                layer_off(2);
            } else {
                layer_on(2);
            }
            break;
        case DOUBLE_HOLD:
            layer_on(1);
            break;
    }
}

void mo_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_ZKHK);
            break;
        case SINGLE_HOLD:
            layer_off(1);
            break;
        case DOUBLE_TAP:
            break;
        case DOUBLE_HOLD:
            layer_off(1);
            break;
    }
}
//------------------------------------------------------------------------------

// 各タップダンスキーコードの `ACTION_TAP_DANCE_FN_ADVANCED()` を定義し、`finished` と `reset` 関数を渡します
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mo_finished, mo_reset)
};
