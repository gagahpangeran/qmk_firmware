#include QMK_KEYBOARD_H

enum gpr_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _NAV,
};

enum gpr_keycodes {
  TD_LSFT_CAPS,
  TD_RSFT_CAPS,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define NV_SCLN LT(_NAV, KC_SCLN)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_QUO RCTL_T(KC_QUOT)
#define LSF_CPS TD(TD_LSFT_CAPS)
#define RSF_CPS TD(TD_RSFT_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NV_SCLN, CTL_QUO,
    LSF_CPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSF_CPS,
    KC_LCTL, _______, _______, KC_LGUI, KC_LALT, LOWER,   RAISE,   KC_SPC,  KC_ENT,  _______, _______, _______
  ),

  [_LOWER] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_HOME, KC_END,  _______,
    _______, RESET,   DEBUG,   _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  [_RAISE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Store the current modifier state in the variable for later reference
  mod_state = get_mods();

  switch (keycode) {
    // Shift+Esc for Delete
    // From https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete
    case KC_BSPC: {
      // Initialize a boolean variable that keeps track
      // of the delete key status: registered or not?
      static bool delkey_registered;
      if (record->event.pressed) {
        // Detect the activation of either shift keys
        if (mod_state & MOD_MASK_SHIFT) {
          // First temporarily canceling both shifts so that
          // shift isn't applied to the KC_DEL keycode
          del_mods(MOD_MASK_SHIFT);
          register_code(KC_DEL);

          // Update the boolean variable to reflect the status of KC_DEL
          delkey_registered = true;

          // Reapplying modifier state so that the held shift key(s)
          // still work even after having tapped the Backspace/Delete key.
          set_mods(mod_state);

          return false;
        }
      } else { // on release of KC_BSPC
        // In case KC_DEL is still being sent even after the release of KC_BSPC
        if (delkey_registered) {
          unregister_code(KC_DEL);
          delkey_registered = false;
          return false;
        }
      }
    }
    // Let QMK process the KC_BSPC keycode as usual outside of shift
    return true;
  }

  return true;
};
