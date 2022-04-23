#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* QWERTY */
    KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I,    KC_O,   KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_QUOT,
    KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                    MO(1), KC_LSFT,     KC_SPACE, MO(2)
  ),

  [1] = LAYOUT( /* Numpad and symbols */
    KC_ESC, KC_LPRN, KC_RPRN, KC_AMPR, KC_ASTR,     KC_P7, KC_P8, KC_P9, KC_MINS, KC_BSPC,
    KC_TAB, KC_TRNS, KC_CIRC, KC_PERC, KC_DLR,      KC_P4, KC_P5, KC_P6, KC_PPLS, KC_ENT,
    KC_LALT, KC_TRNS, KC_HASH, KC_AT, KC_EXLM,      KC_P1, KC_P2, KC_P3, KC_EQL, KC_SCLN,
                            KC_TRNS, KC_LCTL,       KC_P0, MO(3)
  ),

  [2] = LAYOUT( /* Navigation and fancy symbols */
    KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_DEL,
    KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,        KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_BSLS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_HOME, KC_PGDN, KC_END, KC_TRNS, KC_GRV,
                                MO(3), KC_LSFT,         KC_LCTL, KC_TRNS
  ),

  [3] = LAYOUT( /* [> POWER <] */
    KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS,        KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS,
                               KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS
  )
};
