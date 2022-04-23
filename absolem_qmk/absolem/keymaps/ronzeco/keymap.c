#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "print.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define ___ KC_NO


enum custom_keycodes {
  DEFAULT = SAFE_RANGE,
  ALT_TAB,
  CTRL_TAB,
  ALT_F4,
  CTRL_F4,
  CTRL_V
};


// alt + tab

bool is_alt_tab_active = false;
bool is_ctrl_tab_active = false;
uint16_t alt_tab_timer = 0;
uint16_t ctrl_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(is_alt_tab_active && record->event.pressed && keycode!=ALT_TAB && keycode!=KC_LALT && keycode!=KC_LSFT && keycode!=KC_RSFT)
  {
        unregister_code(KC_LALT);
        is_alt_tab_active=false;
  }
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case CTRL_TAB:
      if (record->event.pressed) {
        if (!is_ctrl_tab_active) {
          is_ctrl_tab_active = true;
          register_code(KC_LCTL);
        }
        ctrl_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case ALT_F4:
      if (record->event.pressed) {
        register_code(KC_LALT);
        register_code(KC_F4);
      } else {
        unregister_code(KC_F4);
        unregister_code(KC_LALT);
      }
      break;
    case CTRL_F4:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_F4);
      } else {
        unregister_code(KC_F4);
        unregister_code(KC_LCTL);
      }
      break;
    case CTRL_V:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_V);
      } else {
        unregister_code(KC_V);
        unregister_code(KC_LCTL);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_ctrl_tab_active) {
    if (timer_elapsed(ctrl_tab_timer) > 500) {
      unregister_code(KC_LCTL);
      is_ctrl_tab_active = false;
    }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_Q,         KC_D,         KC_R,         KC_W,         KC_B,             KC_J,    KC_F,         KC_U,         KC_P,         KC_BSPC,
    LGUI_T(KC_A), RALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), KC_G,             KC_Y,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_O), RGUI_T(KC_I),
    KC_Z,         KC_X,         KC_M,         KC_C,         KC_V,             KC_K,    KC_L,         KC_COMM,      KC_DOT,       ___,
                            LT(1, KC_SPC), LT(3,KC_TAB), KC_LALT,             TO(4),   KC_RSFT, LT(2, KC_ENT)
  ),

  [1] = LAYOUT(
    KC_ESC,  ALT_TAB, CTRL_TAB, KC_LSFT, KC_DEL,          KC_MINS, KC_7, KC_8, KC_9, KC_EQL,
    KC_LEFT, KC_UP,   KC_DOWN,  KC_RGHT, KC_BSPC,         KC_PSLS, KC_4, KC_5, KC_6, KC_0,
    KC_TAB,  ALT_F4,  CTRL_F4,  KC_RALT, KC_ENT,          KC_PAST, KC_1, KC_2, KC_3, KC_PDOT,
                      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT(
    KC_ESC,  KC_F9, KC_F10, KC_F11, KC_F12,          KC_HOME, KC_PGUP, KC_VOLU, KC_MUTE, KC_MPLY, 
    KC_LSFT, KC_F5, KC_F6,  KC_F7,  KC_F8,           KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, 
    KC_LCTL, KC_F1, KC_F2,  KC_F3,  KC_F4,           KC_MPRV, KC_PGDN, KC_VOLD, KC_MNXT, ___, 
                KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [3] = LAYOUT(
    KC_LT,   KC_GT,   KC_LBRC,  KC_RBRC, ___,        KC_UNDS, KC_HASH, KC_DLR,  KC_MINS, KC_GRV, 
    KC_EXLM, KC_AT,   KC_LSPO,  KC_RAPC, ___,        KC_SLSH, KC_COLN, KC_QUES, KC_SCLN, KC_QUOT, 
    KC_PERC, KC_CIRC, KC_LCBR,  KC_RCBR, ___,        KC_DQUO, KC_BSLS, KC_PIPE, KC_TILD, ___, 
                   KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [4] = LAYOUT(
    KC_ESC,  KC_Q, KC_D, KC_R, KC_W,           KC_J, KC_F, KC_U,    KC_P,   KC_BSPC,
    KC_LSFT, KC_A, KC_S, KC_H, KC_T,           KC_Y, KC_N, KC_E,    KC_O,   KC_I,
    KC_LCTL, KC_Z, KC_X, KC_M, KC_C,           KC_K, KC_L, KC_COMM, KC_DOT, ___,
           KC_TRNS, KC_SPC, KC_TRNS,           TO(0), KC_TRNS, KC_ENT
  ),

};