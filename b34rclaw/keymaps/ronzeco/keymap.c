// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "print.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum ferris_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _SYMBOLS,
  _NUMPAD,
  _MOUSE
};

enum custom_keycodes {
  ALT_TAB,
  CTRL_TAB,
  ALT_F4,
  CTRL_F4
};

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

#define CT_T LCTL_T(KC_T)
#define CT_E RCTL_T(KC_E)
#define SF_H LSFT_T(KC_H)
#define SF_N RSFT_T(KC_N)
#define CM_R GUI_T(KC_R)
#define CM_I GUI_T(KC_I)
#define RA_S RALT_T(KC_S)
#define RA_A RALT_T(KC_A)
#define SP_1 LT(1, KC_SPC)
#define EN_2 LT(2, KC_ENT)
#define TB_3 LT(3, KC_TAB)
#define BS_4 LT(4, KC_BSPC)
#define MT_5 LT(5, KC_MUTE)
#define TL KC_TRNS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* BASE */
    KC_W,  KC_C,    KC_D,    KC_F,    KC_B,            KC_X,    KC_L,  KC_U,    KC_O,   KC_Y,
    CM_R,  RA_S,    CT_T,    SF_H,    KC_K,            KC_J,    SF_N,  CT_E,    RA_A,   CM_I,
    KC_Q,  KC_G,    KC_M,    KC_P,    KC_V,            KC_Z,    KC_COMM,  KC_DOT, KC_QUOT, KC_SLSH,
                                SP_1, TB_3,            BS_4, EN_2
  ),

  [_LOWER] = LAYOUT( /* [> LOWER <] */
    KC_ESC,  ALT_TAB, CTRL_TAB, KC_VOLU,  KC_LSPO,       KC_MINS, KC_7,  KC_8,    KC_9,   KC_EQL,
    KC_LEFT, KC_UP,   KC_DOWN,  KC_RIGHT, KC_MPLY,       KC_PAST, KC_4,  KC_5,    KC_6,   KC_0,
    MT_5, ALT_F4,  CTRL_F4,  KC_VOLD,  KC_RAPC,       KC_PPLS, KC_1,  KC_2,    KC_3,   KC_PDOT,
                                           TL, TL,       TL, TL
  ),

  [_RAISE] = LAYOUT( /* [> RAISE <] */
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___,         ___, KC_HOME, KC_PGUP, ___,   KC_DEL,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   ___,         ___, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   ___,         ___, KC_END,  KC_PGDN, ___,   RESET,
                                     TL, TL,         TL, TL
  ),

  [_SYMBOLS] = LAYOUT( /* [> SYMBOLS <] */
    KC_GRV,  KC_PERC, KC_LBRC, KC_RBRC, KC_DEL,      KC_PLUS, KC_UNDS, KC_BSLS, KC_CIRC, KC_DLR,
    KC_EXLM, KC_AT,   KC_LSPO, KC_RAPC, KC_ENT,      KC_SCLN, KC_COLN, KC_QUES, KC_DQUO, KC_QUOT,
    KC_TILD, KC_HASH, KC_LCBR, KC_RCBR, KC_BSPC,     ___,     KC_AMPR, KC_PIPE, KC_LT,   KC_GT,
                                         TL, TL,     TL, TL
  ),

  [_NUMPAD] = LAYOUT( /* [> NUMPAD <] */
    KC_GRV,  KC_PERC, KC_LBRC, KC_RBRC, KC_DEL,      KC_PPLS, KC_P7, KC_P8, KC_P9, KC_PSLS,
    KC_EXLM, KC_AT,   KC_LSPO, KC_NLCK, KC_ENT,      KC_PMNS, KC_P4, KC_P5, KC_P6, KC_P0,
    KC_TILD, KC_HASH, KC_LCBR, KC_RCBR, KC_BSPC,     KC_PDOT, KC_P1, KC_P2, KC_P3, KC_PEQL,
                                         TL, TL,     TL, TL
  ),

  [_MOUSE] = LAYOUT( /* [> MOUSE <] */
    KC_ESC,  KC_PERC, KC_MS_WH_LEFT, KC_MS_WH_UP, KC_MS_BTN1,      KC_PPLS, KC_P7, KC_P8, KC_P9, KC_PSLS,
    KC_EXLM, KC_AT,   KC_LSPO, KC_NLCK, KC_MS_BTN3,      KC_PMNS, KC_P4, KC_P5, KC_P6, KC_P0,
    KC_TILD, KC_HASH, KC_MS_WH_RIGHT, KC_MS_WH_DOWN, KC_MS_BTN2,     KC_PDOT, KC_P1, KC_P2, KC_P3, KC_PEQL,
                                         TL, TL,     TL, TL
  )
};
