#include <stdint.h>
#include <sys/types.h>
#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_XXXX KC_TRNS
#define KC_NONE KC_NO
#define KC_NORM TO(NORMAL)
#define KC_PRIM OSL(PRIMARY)
#define KC_SECON MO(SECONDARY)
#define KC_MOUSE TO(MOUSE)
#define KC_FUN MO(FUNCTION)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)
#define KC_ALT(KEY) LALT(KC_##KEY)
#define KC_GUI(KEY) LGUI(KC_##KEY)
#define KC_RESET QK_BOOT
#define KC_OCTL ONESHOT_CTL
#define KC_CAPS CW_TOGG
#define KC_OSFT ONESHOT_SFT

enum custom_keycodes {
  ONESHOT_SFT = SAFE_RANGE,
  ONESHOT_CTL,
};

enum layer { NORMAL, PRIMARY, SECONDARY, FUNCTION, MOUSE };

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
};

// clang-format off
const uint16_t PROGMEM combo_xc[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_dot_comma[] = {KC_DOT, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo_fp[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_ul[] = {KC_U, KC_L, COMBO_END};
const uint16_t PROGMEM combo_st[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_en[] = {KC_E, KC_N, COMBO_END};
const uint16_t PROGMEM combo_cd[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_comma_h[] = {KC_COMMA, KC_H, COMBO_END};
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo_mn[] = {KC_M, KC_N, COMBO_END};
const uint16_t PROGMEM combo_kh[] = {KC_K, KC_H, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM combo_bp[] = {KC_B, KC_P, COMBO_END};
const uint16_t PROGMEM combo_vd[] = {KC_V, KC_D, COMBO_END};
const uint16_t PROGMEM combo_rs[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM combo_ie[] = {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM combo_wf[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_yu[] = {KC_Y, KC_U, COMBO_END};

combo_t key_combos[] = {
  // Left hand
  COMBO(combo_wf, KC_HASH),
  COMBO(combo_rs, KC_AT),
  COMBO(combo_xc, KC_LABK),
  COMBO(combo_fp, KC_LPRN),
  COMBO(combo_st, KC_LCBR),
  COMBO(combo_cd, KC_LBRC),
  COMBO(combo_bp, KC_BSLS),
  COMBO(combo_gt, KC_SLASH),
  COMBO(combo_vd, KC_PIPE),

  // Right hand
  COMBO(combo_yu, KC_AMPR),
  COMBO(combo_ie, KC_DLR),
  COMBO(combo_dot_comma, KC_RABK),
  COMBO(combo_ul, KC_RPRN),
  COMBO(combo_en, KC_RCBR),
  COMBO(combo_comma_h, KC_RBRC),
  COMBO(combo_jl, KC_GRAVE),
  COMBO(combo_mn, KC_QUOTE),
  COMBO(combo_kh, KC_DQUO),
};
// clang-format on

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
             ESC   , ASTR  , PLUS  , MINUS , PERC  ,        CIRC  , UNDS  , EQUAL , TILD  , QUES  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             1     , 2     , 3     , 4     , 5     ,        6     , 7     , 8     , 9     , 0     ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             RALT  , LALT  , OCTL  , TAB   , SCLN  ,        COLN  , ENTER , OSFT  , LGUI  , EXLM  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             SECON ,         XXXX
        //                                 '-------'      '--------'
    ),

    [SECONDARY] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , UP    , MOUSE , FULL  ,        LOCK  , ____  , ____  , ____  , PSCR  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        ____  ,CTL(F1),CTL(F2),CTL(F3),CTL(F4),
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDN  ,        ____  , ____  , ____  , LGUI  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             ____  ,         FUN
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
              ____ ,  ____ ,  ____ ,  ____ ,  ____ ,        ____  , ____  ,  ____ ,  ____ , RESET ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F1   ,  F2   ,  F3   ,  F4   ,  F5   ,         F6   ,  F7   ,  F8   ,  F9   ,  F10  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F11  ,  F12  ,  ____ ,  ____ ,  ____ ,        ____  , ____  ,  ____ ,  ____ , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //                                 ,-------.      .--------.
                                             ____  ,         ____
        //                                 '-------'      '--------'
    ),
};
// clang-format on

struct oneshot_state shift_state = {
    .status = OS_DISABLED,
    .modifier = KC_LSFT,
};

struct oneshot_state ctl_state = {
    .status = OS_DISABLED,
    .modifier = KC_LCTL,
};

void oneshot(struct oneshot_state *state, keyrecord_t *record) {
  if (record->event.pressed) {
    state->status = OS_HOLDING;
    register_code(state->modifier);
  } else {
    switch (state->status) {
    // Nothing pressed after the key down, so schedule the modifier for the
    // next key.
    case OS_HOLDING:
      state->status = OS_RELEASED;
      break;
    // Another key was pressed, so we treat the key as a normal modifier you
    // need to hold down.
    case OS_OTHER_KEY_PRESSED:
      state->status = OS_DISABLED;
      unregister_code(state->modifier);
      break;
    default:
      break;
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

void reset_oneshot(struct oneshot_state *state) {
  if (state->status == OS_DISABLED || state->status == OS_HOLDING) {
    return;
  }

  state->status = OS_DISABLED;
  unregister_code(state->modifier);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_PRIM:
  case KC_SECON:
    return true;
  default:
    return false;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ONESHOT_SFT:
    oneshot(&shift_state, record);
    break;
  case ONESHOT_CTL:
    oneshot(&ctl_state, record);
    break;
  case KC_PRIM:
  case KC_SECON:
  case KC_MOUSE:
  case KC_FUN:
    break;
  case KC_ESC:
    reset_oneshot(&shift_state);
    reset_oneshot(&ctl_state);
    break;
  default:
    after_oneshot(&shift_state, record);
    after_oneshot(&ctl_state, record);
    break;
  }

  return true;
}
