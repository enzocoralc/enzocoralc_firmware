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

enum combos {
  MC_B,
  LC_J
};

const uint16_t PROGMEM mc_combo[] = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM lc_combo[] = {KC_L, KC_COMM, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [MC_B] = COMBO(mc_combo, KC_B),
  [LC_J] = COMBO(lc_combo, KC_J)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    ___,          KC_D,         KC_R,         KC_W,         KC_B,             KC_J,    KC_F,         KC_U,         KC_P,         ___,
    LGUI_T(KC_A), RALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), KC_G,             KC_Y,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_O), RGUI_T(KC_I),
    KC_Z,         KC_X,         KC_M,         KC_C,         KC_V,             KC_K,    KC_L,         KC_COMM,      KC_DOT,       KC_SLSH,
                            LT(1, KC_SPC), LT(3,KC_TAB), ___,             ___, ___, LT(2, KC_ENT)
  ),

  [1] = LAYOUT(
    ___,     ALT_TAB, CTRL_TAB, KC_LSFT, ___,             ___,     KC_7, KC_8, KC_9, ___,
    KC_LEFT, KC_UP,   KC_DOWN,  KC_RGHT, KC_BSPC,         KC_PSLS, KC_4, KC_5, KC_6, KC_0,
    KC_TAB,  ALT_F4,  CTRL_F4,  KC_RALT, KC_DEL,          KC_PAST, KC_1, KC_2, KC_3, KC_PDOT,
                      KC_TRNS, KC_TRNS, ___,          ___,  ___, KC_TRNS
  ),

  [2] = LAYOUT(
    ___,    KC_F9, KC_F10, KC_F11, ___,             ___,     KC_PGUP, KC_VOLU, KC_BSPC, ___,
    KC_F12, KC_F5, KC_F6,  KC_F7,  KC_F8,           KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_ESC, KC_F1, KC_F2,  KC_F3,  KC_F4,           KC_END,  KC_PGDN, KC_VOLD, KC_MUTE, KC_MPLY,
                KC_TRNS, KC_TRNS,   ___,             ___, ___, KC_TRNS
  ),

  [3] = LAYOUT(
    ___,     KC_GT,   KC_LBRC,  KC_RBRC, ___,        ___,     KC_HASH, KC_DLR,  KC_MINS, ___,
    KC_EXLM, KC_AT,   KC_LSPO,  KC_RAPC, ___,        KC_UNDS, KC_COLN, KC_QUES, KC_SCLN, KC_QUOT,
    KC_PERC, KC_CIRC, KC_LCBR,  KC_RCBR, ___,        ___,     KC_BSLS, KC_PIPE, KC_TILD, KC_DQUO,
                   KC_TRNS, KC_TRNS, ___,            ___, ___, KC_TRNS
  ),

};
