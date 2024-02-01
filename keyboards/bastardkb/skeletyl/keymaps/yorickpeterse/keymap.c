#include "action.h"
#include "action_util.h"
#include <sys/types.h>
#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_XXXX KC_TRNS
#define KC_NONE KC_NO
#define KC_SYM MO(SYMBOLS)
#define KC_NUMS MO(NUMBERS)
#define KC_MOUSE TG(MOUSE)
#define KC_STAB LSFT(KC_TAB)
#define KC_FUN OSL(FUNCTION)
#define KC_EXTRA MO(EXTRA)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)
#define KC_ALT(KEY) LALT(KC_##KEY)
#define KC_GUI(KEY) LGUI(KC_##KEY)
#define KC_RESET QK_BOOT
#define KC_OCTL ONESHOT_CTL
#define KC_OSHIFT ONESHOT_SHIFT
#define KC_CSPC COMMA_SPACE

// The firmware I'm using is based on the TBK Mini keyboard, which has 6 columns
// instead of 5.
// clang-format off
#define LAYOUT( \
    k00, k01, k02, k03, k04,     k44, k43, k42, k41, k40, \
    k10, k11, k12, k13, k14,     k54, k53, k52, k51, k50, \
    k20, k21, k22, k23, k24,     k64, k63, k62, k61, k60, \
              k32, k33, k30,     k70, k73, k72            \
) LAYOUT_split_3x5_3( \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04,     KC_##k44, KC_##k43, KC_##k42, KC_##k41, KC_##k40, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14,     KC_##k54, KC_##k53, KC_##k52, KC_##k51, KC_##k50, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24,     KC_##k64, KC_##k63, KC_##k62, KC_##k61, KC_##k60, \
                        KC_##k32, KC_##k33, KC_##k30,     KC_##k70, KC_##k73, KC_##k72            \
)
// clang-format on

enum custom_keycodes {
  ONESHOT_SHIFT = SAFE_RANGE,
  ONESHOT_CTL,
  COMMA_SPACE,
};

enum layer { NORMAL, SYMBOLS, NUMBERS, FUNCTION, EXTRA, MOUSE };

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

// The time (in milliseconds) after which a mod-tap modifier is disabled.
const static uint16_t ONESHOT_MOD_TIMEOUT = 1500;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
               Q   ,   W   ,   F   ,   P   ,   B   ,          J   ,   L   ,   U   ,   Y   , RALT  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               A   ,   R   ,   S   ,   T   ,   G   ,          M   ,   N   ,   E   ,   I   ,   O   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               Z   ,   X   ,   C   ,   D   ,   V   ,          K   ,   H   , COMMA ,  DOT  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //               ,-------+---------+-------.      .--------+----------+-------.
                            NUMS ,  SPACE  , MOUSE ,          FUN  ,  OSHIFT  ,  SYM
        //               '-------+---------+-------'      '--------+----------+-------'
    ),

    [SYMBOLS] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             EXLM  , QUES  , LPRN  , RPRN  , LABK  ,        RABK  , MINUS , EQUAL , PLUS  , ASTR  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             PIPE  , AT    , LCBR  , RCBR  , SLASH ,        SCLN  , UNDS  , QUOTE , DQUO  , GRAVE ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             CIRC  , HASH  , LBRC  , RBRC  , BSLS  ,        COLN  , AMPR  , PERC  , DLR   , TILD  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+----------+---------.
                      ____   ,   ____   ,   ____   ,         ____   ,   ____   ,  XXXX
        //        '----------+----------+----------'      '---------+----------+---------'
    ),

    [NUMBERS] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ESC  , ____  , ____  , ____  ,  ____ ,        INS   , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               1   ,  2    ,  3    ,  4    ,  5    ,         6    ,  7    ,  8    ,  9    ,  0    ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ ,  LALT , OCTL  ,  TAB  ,  STAB ,         ____ , BSPC  ,  CSPC ,  ____ ,  DEL  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      XXXX   ,   ____   ,   ____   ,         ____   ,  ENT   ,  EXTRA
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [EXTRA] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , GUI(W), UP    , FULL  , LOCK  ,        ____  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        ____  ,CTL(F1),CTL(F2),CTL(F3),CTL(F4),
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDN  ,        ____  , LGUI  , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .--------+----------+---------.
                      ____   ,   ____   ,   ____   ,         ____  ,   ____   ,   ____
        //        '----------+----------+----------'      '--------+----------+---------'
    ),

    [FUNCTION] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ ,  ____ ,  ____ ,  ____ ,  ____ ,        RESET , ____  ,  ____ ,  ____ ,  PSCR ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F1   ,  F2   ,  F3   ,  F4   ,  F5   ,         F6   ,  F7   ,  F8   ,  F9   ,  F10  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F11  ,  F12  ,  ____ ,  ____ ,  ____ ,        ____  , ____  ,  ____ ,  ____ , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      ____   ,   ____   ,   XXXX   ,         ____   ,  ____  ,   ____
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [MOUSE] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ , CTL(C), CTL(V), ____  ,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ ,  BTN3 ,  BTN2 ,  BTN1 ,  WH_U ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , LSFT  ,  LCTL , ____  ,  WH_D ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+-------+---------.
                      ____   ,   ____   ,   XXXX   ,         ____   ,  ____ ,   ____
        //        '----------+----------+----------'      '---------+-------+---------'
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
  state->status = OS_DISABLED;
  unregister_code(state->modifier);
}

void comma_space(keyrecord_t *record) {
  if (record->event.pressed) {
    tap_code(KC_COMMA);
    tap_code(KC_SPC);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case COMMA_SPACE:
    comma_space(record);
    break;
  case ONESHOT_SHIFT:
    oneshot(&shift_state, record);
    break;
  case ONESHOT_CTL:
    oneshot(&ctl_state, record);
    break;
  case KC_SYM:
  case KC_NUMS:
  case KC_EXTRA:
  case KC_MOUSE:
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
