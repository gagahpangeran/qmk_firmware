#include QMK_KEYBOARD_H

enum gpr_layers {
  _BASE,
  _SYMBOL,
  _FN,
  _NAV,
};

#define SYMBOL TT(_SYMBOL)
#define FN TT(_FN)
#define NV_SCLN LT(_NAV, KC_SCLN)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_QUO RCTL_T(KC_QUOT)
#define ALT_TAB A(KC_TAB)
#define ALS_TAB LSA(KC_TAB)
#define SYM_GUI LM(_SYMBOL, MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NV_SCLN, CTL_QUO,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, FN,      SYM_GUI, KC_LGUI, KC_LALT, SYMBOL,  _______, KC_SPC,  KC_ENT,  _______, _______, _______
  ),

  [_SYMBOL] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
    _______, _______, _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_MINS, KC_EQL,  KC_UNDS, KC_PLUS, KC_PIPE,
    RESET,   DEBUG,   _______, _______, _______, _______, _______, ALS_TAB, ALT_TAB, _______, _______, _______
  ),

  [_FN] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT
  ),

  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL
};

enum combo_events {
  SFT_CAPS,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM shift_combo[] = { KC_LSFT, KC_RSFT, COMBO_END };

combo_t key_combos[] = {
  [SFT_CAPS] = COMBO(shift_combo, KC_CAPS),
};
