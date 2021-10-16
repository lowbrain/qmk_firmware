#include <print.h>
#include QMK_KEYBOARD_H
#include "jtu_custom_keycodes.h"

bool SHIFT_PRESSED_L = false;
bool SHIFT_PRESSED_R = false;

bool convert_jtu(uint16_t code, uint16_t s_code, keyrecord_t *record) {
  if (record->event.pressed) {
    if (SHIFT_PRESSED_L || SHIFT_PRESSED_R) {
      if (SHIFT_PRESSED_L) unregister_code(KC_LSFT);
      if (SHIFT_PRESSED_R) unregister_code(KC_RSFT);
      register_code16(s_code);
    } else {
      register_code16(code);
    }
  } else {
    unregister_code16(s_code);
    unregister_code16(code);
    if (SHIFT_PRESSED_L) register_code(KC_LSFT);
    if (SHIFT_PRESSED_R) register_code(KC_RSFT);
  }
  return false;
}

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_LSFT:
      if (record->event.pressed) {
        SHIFT_PRESSED_L = true;
      } else {
        SHIFT_PRESSED_L = false;
      }
      break;
    case KC_RSFT:
      if (record->event.pressed) {
        SHIFT_PRESSED_R = true;
      } else {
        SHIFT_PRESSED_R = false;
      }
      break;
    case JU_CAPS:
      if (record->event.pressed) {
        register_code16(S(KC_CAPS));
        unregister_code16(S(KC_CAPS));
      }
      return false;
    case JU_GRV:
      if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
        if (record->event.pressed) {
          register_code(KC_GRV);
          unregister_code(KC_GRV);
          return false;
        }
      } else {
        return convert_jtu(S(KC_LBRC), S(KC_EQL), record);
      }
    case JU_2:    return convert_jtu(KC_2,       KC_LBRC,    record);
    case JU_6:    return convert_jtu(KC_6,       KC_EQL,     record);
    case JU_7:    return convert_jtu(KC_7,       S(KC_6),    record);
    case JU_8:    return convert_jtu(KC_8,       S(KC_QUOT), record);
    case JU_9:    return convert_jtu(KC_9,       S(KC_8),    record);
    case JU_0:    return convert_jtu(KC_0,       S(KC_9),    record);
    case JU_MINS: return convert_jtu(KC_MINS,    S(KC_INT1), record);
    case JU_EQL:  return convert_jtu(S(KC_MINS), S(KC_SCLN), record);
    case JU_LBRC: return convert_jtu(KC_RBRC,    S(KC_RBRC), record);
    case JU_RBRC: return convert_jtu(KC_NUHS,    S(KC_NUHS), record);
    case JU_BSLS: return convert_jtu(KC_INT1,    S(KC_INT3), record);
    case JU_SCLN: return convert_jtu(KC_SCLN,    KC_QUOT,    record);
    case JU_QUOT: return convert_jtu(S(KC_7),    S(KC_2),    record);
  }
  return true;
}
