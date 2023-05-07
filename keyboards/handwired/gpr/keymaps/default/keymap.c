#include QMK_KEYBOARD_H

enum gpr_layers {
  _BASE,
  _SYMBOL,
  _FN,
  _NAV,
};

enum gpr_keycodes {
  TD_CUT,
  TD_COPY,
  TD_PASTE,
  TD_SFT_NAV,
};

#define SYMBOL TT(_SYMBOL)
#define FN TT(_FN)
#define NAV TT(_NAV)

#define NV_SCLN LT(_NAV, KC_SCLN)

#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_ENT RCTL_T(KC_ENT)

#define SYM_GUI LM(_SYMBOL, MOD_LGUI)
#define SYM_SPC LT(_SYMBOL, KC_SPC)

tap_dance_action_t tap_dance_actions[] = {
    [TD_CUT] = ACTION_TAP_DANCE_DOUBLE(C(KC_X), C(S(KC_X))),
    [TD_COPY] = ACTION_TAP_DANCE_DOUBLE(C(KC_C), C(S(KC_C))),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(C(KC_V), C(S(KC_V))),
    [TD_SFT_NAV] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RSFT, _NAV),
};

#define CUT TD(TD_CUT)
#define COPY TD(TD_COPY)
#define PASTE TD(TD_PASTE)
#define SFT_NAV TD(TD_SFT_NAV)

#define WRD_PRV C(KC_LEFT)
#define WRD_NXT C(KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NV_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    KC_F13,  FN,      SYM_GUI, KC_LGUI, KC_LALT, SYMBOL,  SYM_SPC, CTL_ENT, SFT_NAV, CUT,     COPY,    PASTE
  ),

  [_SYMBOL] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_MINS, KC_EQL,  KC_UNDS, KC_PLUS, _______, _______, _______, KC_CAPS,
    QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_FN] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    _______, _______, _______, _______, KC_PSCR, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_F11,  KC_F12,
    _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, _______,
    _______, _______, _______, _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT
  ),

  [_NAV] = LAYOUT(
    _______, _______, WRD_NXT, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_END,  _______, _______,
    _______, _______, KC_PGDN, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, WRD_PRV, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_ALT, KC_BSPACE, KC_DELETE);

// const key_override_t **key_overrides = (const key_override_t *[]){
//     &delete_key_override,
//     NULL
// };
