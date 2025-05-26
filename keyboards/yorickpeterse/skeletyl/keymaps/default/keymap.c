#include <stdint.h>
#include <sys/types.h>
#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_NONE KC_NO
#define KC_NORM TO(NORMAL)
#define KC_PRIM RIGHT_THUMB
#define KC_NAV OSL(NAV)
#define KC_SECON MO(SECONDARY)
#define KC_MOUSE TO(MOUSE)
#define KC_FUNC OSL(FUNCTION)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)
#define KC_ALT(KEY) LALT(KC_##KEY)
#define KC_RESET QK_BOOT
#define KC_OCTL ONESHOT_CTL
#define KC_CAPS CW_TOGG
#define KC_STAB LSFT(KC_TAB)

// For some reason using _just_ KC_LGUI on an OSL layer results in it not
// working as it should, resulting in e.g. Gnome's overview not focusing the
// search bar. This lets us work around that.
#define KC_SUPER LGUI(KC_NONE)

enum custom_keycodes {
  RIGHT_THUMB = SAFE_RANGE,
  ONESHOT_CTL,
};

enum layer { NORMAL, PRIMARY, SECONDARY, NAV, FUNCTION, MOUSE };

enum oneshot_status {
  OS_DISABLED,
  OS_HOLDING,
  OS_RELEASED,
  OS_OTHER_KEY_PRESSED,
  OS_DISABLE,
};

struct oneshot_state {
  enum oneshot_status status;
  uint16_t modifier;
  int layer;
};

struct oneshot_state shift_state = {
    .status = OS_DISABLED,
    .modifier = KC_LSFT,
    .layer = PRIMARY,
};

struct oneshot_state ctl_state = {
    .status = OS_DISABLED,
    .modifier = KC_LCTL,
    .layer = -1,
};

bool disable_primary_after_caps_word = false;

void oneshot(struct oneshot_state *state, bool pressed) {
  if (pressed && state->status == OS_DISABLED) {
    state->status = OS_HOLDING;

    if (state->layer == -1) {
      register_code(state->modifier);
    } else {
      layer_on(state->layer);
    }
  } else {
    switch (state->status) {
    // Nothing pressed after the key down, so schedule the modifier for the
    // next key.
    case OS_HOLDING:
      state->status = OS_RELEASED;

      if (state->layer >= -1) {
        register_code(state->modifier);
      }

      break;
    // Another key was pressed, so we treat the key as a normal modifier you
    // need to hold down.
    case OS_OTHER_KEY_PRESSED:
      state->status = OS_DISABLED;

      if (state->layer == -1) {
        unregister_code(state->modifier);
      }

      break;
    default:
      state->status = OS_DISABLED;
      unregister_code(state->modifier);
      break;
    }

    // If a layer is used on hold, we should always disable it when releasing
    // the button.
    if (state->layer >= 0) {
      layer_off(state->layer);
    }
  }
}

void after_oneshot(struct oneshot_state *state, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (state->status) {
    // If the modifier is held down, signal that another key is pressed.
    case OS_HOLDING:
      state->status = OS_OTHER_KEY_PRESSED;
      break;
    // If we are the first key down event after releasing the modifier (without
    // pressing another key), we'll be responsible for clearing the modifier.
    // This way the sequence `MOD -> A -> B` results in MOD only applying to A,
    // instead of applying to both A and B.
    case OS_RELEASED:
      state->status = OS_DISABLE;
      break;
    // If another key was pressed but is still held down, we need to disable the
    // modifier _first_ such that it only applies to the initially pressed key.
    case OS_DISABLE:
      state->status = OS_DISABLED;
      unregister_code(state->modifier);
    default:
      break;
    }
  } else {
    switch (state->status) {
    case OS_DISABLE:
      state->status = OS_DISABLED;
      unregister_code(state->modifier);
    default:
      break;
    }
  }
}

bool shift_space_action(bool pressed, void *state) {
  if (pressed) {
    layer_on(SECONDARY);
  } else {
    layer_off(SECONDARY);
  }

  return false;
}

const key_override_t override_shift_dot =
    ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_RALT);

const key_override_t override_shift_space = {
    .trigger_mods = MOD_BIT(KC_LSFT),
    .layers = ~0,
    .suppressed_mods = MOD_BIT(KC_LSFT),
    .options = ko_option_no_unregister_on_other_key_down,
    .negative_mod_mask = 0,
    .custom_action = shift_space_action,
    .context = NULL,
    .trigger = KC_SPACE,
    .replacement = KC_NO,
    .enabled = NULL,
};

const key_override_t *key_overrides[] = {
    &override_shift_space,
    &override_shift_dot,
};

const uint16_t PROGMEM combo_pf[] = {KC_P, KC_F, COMBO_END};
const uint16_t PROGMEM combo_cd[] = {KC_C, KC_D, COMBO_END};

const uint16_t PROGMEM combo_comma_h[] = {KC_COMMA, KC_H, COMBO_END};
const uint16_t PROGMEM combo_comma_dot[] = {KC_COMMA, KC_DOT, COMBO_END};

const uint16_t PROGMEM combo_lprn_plus[] = {KC_LPRN, KC_PLUS, COMBO_END};

combo_t key_combos[] = {
    // Left base layer
    COMBO(combo_pf, KC_ESC),
    COMBO(combo_cd, KC_OCTL),

    // Left symbol layer
    COMBO(combo_lprn_plus, KC_ESC),

    // Right
    COMBO(combo_comma_h, KC_ENTER),
    COMBO(combo_comma_dot, KC_NAV),
};

// clang-format off
#define LAYOUT( \
  L00, L01, L02, L03, L04,  R00, R01, R02, R03, R04, \
  L05, L06, L07, L08, L09,  R05, R06, R07, R08, R09, \
  L10, L11, L12, L13, L14,  R10, R11, R12, R13, R14, \
                      L15,  R15                      \
) LAYOUT_split_3x5_1( \
  KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04,     KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, \
  KC_##L05, KC_##L06, KC_##L07, KC_##L08, KC_##L09,     KC_##R05, KC_##R06, KC_##R07, KC_##R08, KC_##R09, \
  KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14,     KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, \
                                          KC_##L15,     KC_##R15                                          \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
               Q   ,   W   ,   F   ,   P   ,   B   ,          J   ,   L   ,   U   ,   Y   , BSPC  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               A   ,   R   ,   S   ,   T   ,   G   ,          M   ,   N   ,   E   ,   I   ,   O   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               Z   ,   X   ,   C   ,   D   ,   V   ,          K   ,   H   , COMMA ,  DOT  , CAPS  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             SPACE ,         PRIM
        //                                 '-------'      '--------'
    ),

    [PRIMARY] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ESC   , QUES  , LPRN  , PLUS  , AT    ,        BSLS  , EQUAL , RPRN  , EXLM  , ASTR  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             PIPE  , SLASH , LCBR  , MINUS , LABK  ,        RABK  , UNDS  , RCBR  , QUOTE , DLR   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             CIRC  , HASH  , LBRC  , SCLN  , AMPR  ,        TILD  , COLN  , RBRC  , DQUO  , PERC  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             SECON ,         ____
        //                                 '-------'      '--------'
    ),

    [SECONDARY] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , ____  , ____  , ____  ,        ____  , ____  , ____  , GRAVE , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             1     , 2     , 3     , 4     , 5     ,        6     , 7     , 8     , 9     , 0     ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LALT  , STAB  , TAB   , ____  ,        ____  , ____  , COMMA , DOT   , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             ____  ,         ____
        //                                 '-------'      '--------'
    ),

    [NAV] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , UP    , MOUSE , FULL  ,        LOCK  , FUNC  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        ____  ,CTL(F1),CTL(F2),CTL(F3),CTL(F4),
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDN  ,        ____  , SUPER , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             ____  ,         ____
        //                                 '-------'      '--------'
    ),

    [MOUSE] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ , CTL(C), CTL(V), NORM  ,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , BTN3  , BTN2  , BTN1  , WH_U  ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , LSFT  , LCTL  , ____  , WH_D  ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             ____  ,         ____
        //                                 '-------'      '--------'
    ),

    [FUNCTION] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ ,  ____ ,  ____ ,  ____ , ____  ,        ____  , PSCR  ,  ____ ,  ____ , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F1   ,  F2   ,  F3   ,  F4   ,  F5   ,         F6   ,  F7   ,  F8   ,  F9   ,  F10  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F11  ,  F12  ,  ____ ,  ____ ,  ____ ,        ____  , ____  ,  ____ ,  ____ , RESET ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             ____  ,         ____
        //                                 '-------'      '--------'
    ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case RIGHT_THUMB:
    // This ensures that enabling the primary layer while caps word is enabled
    // doesn't trigger an unregister of the shift key, disabling caps word in
    // the process.
    if (record->event.pressed && is_caps_word_on()) {
      layer_on(shift_state.layer);
      shift_state.status = OS_HOLDING;
      disable_primary_after_caps_word = true;
      return false;
    } else if (!record->event.pressed && disable_primary_after_caps_word) {
      // Allow disabling of caps word by tapping the right thumb.
      if (shift_state.status == OS_HOLDING) {
        caps_word_off();
      }

      shift_state.status = OS_DISABLED;
      layer_off(shift_state.layer);
      disable_primary_after_caps_word = false;
      return false;
    }

    oneshot(&shift_state, record->event.pressed);
    break;
  case ONESHOT_CTL:
    oneshot(&ctl_state, record->event.pressed);
    after_oneshot(&shift_state, record);
    break;
  case KC_FUNC:
    break;
  default:
    after_oneshot(&shift_state, record);
    after_oneshot(&ctl_state, record);
    break;
  }

  return true;
}
