#include <stdint.h>
#include <sys/types.h>
#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_XXXX KC_TRNS
#define KC_NONE KC_NO
#define KC_NORM TO(NORMAL)
#define KC_PRIM MO(PRIMARY)
#define KC_SECON MO(SECONDARY)
#define KC_MOUSE TO(MOUSE)
#define KC_STAB LSFT(KC_TAB)
#define KC_FUN OSL(FUNCTION)
#define KC_NAV MO(NAV)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)
#define KC_ALT(KEY) LALT(KC_##KEY)
#define KC_GUI(KEY) LGUI(KC_##KEY)
#define KC_RESET QK_BOOT
#define KC_OCTL ONESHOT_CTL
#define KC_OSHIFT ONESHOT_SHIFT
#define KC_CAPS CW_TOGG

enum custom_keycodes {
  ONESHOT_SHIFT = SAFE_RANGE,
  ONESHOT_CTL,
};

enum layer { NORMAL, PRIMARY, SECONDARY, FUNCTION, NAV, MOUSE };

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

const uint16_t PROGMEM ctl_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_DOT, KC_COMMA, COMBO_END};

combo_t key_combos[] = {
    COMBO(ctl_combo, ONESHOT_CTL),
    COMBO(esc_combo, KC_ESC),
};

// clang-format off
#define LAYOUT( \
  L00, L01, L02, L03, L04,  R00, R01, R02, R03, R04, \
  L05, L06, L07, L08, L09,  R05, R06, R07, R08, R09, \
  L10, L11, L12, L13, L14,  R10, R11, R12, R13, R14, \
            L15, L16, L17,  R15, R16, R17            \
) LAYOUT_split_3x5_3( \
  KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04,     KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, \
  KC_##L05, KC_##L06, KC_##L07, KC_##L08, KC_##L09,     KC_##R05, KC_##R06, KC_##R07, KC_##R08, KC_##R09, \
  KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14,     KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, \
                      KC_##L15, KC_##L16, KC_##L17,     KC_##R15, KC_##R16, KC_##R17                      \
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
        //               ,-------+---------+-------.      .--------+----------+-------.
                           SECON ,  SPACE  , ____  ,          FUN  ,  OSHIFT  , PRIM
        //               '-------+---------+-------'      '--------+----------+-------'
    ),

    [PRIMARY] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             EXLM  , QUES  , LPRN  , RPRN  , LABK  ,        RABK  , MINUS , EQUAL , PLUS  , ASTR  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             PIPE  , AT    , LCBR  , RCBR  , SLASH ,        SCLN  , UNDS  , QUOTE , DQUO  , GRAVE ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             AMPR  , HASH  , LBRC  , RBRC  , BSLS  ,        COLN  , ENTER , TAB   , LALT  , RALT  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+----------+---------.
                      ____   ,   ____   ,   ____   ,         ____   ,   ____   ,  XXXX
        //        '----------+----------+----------'      '---------+----------+---------'
    ),

    [SECONDARY] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , ____  , MOUSE ,  ____ ,         ____ , ____  , ____  , ____  ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               1   ,  2    ,  3    ,  4    ,  5    ,         6    ,  7    ,  8    ,  9    ,  0    ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , ____  , ____  , ____  , ____  ,         ____ ,  CIRC ,  PERC ,  DLR  ,  TILD ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      XXXX   ,   ____   ,   ____   ,         ____   ,  ____  ,   NAV
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [NAV] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , UP    , ____  , FULL  ,        LOCK  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        ____  ,CTL(F1),CTL(F2),CTL(F3),CTL(F4),
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDN  ,        ____  , LGUI  , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .--------+----------+---------.
                      ____   ,   ____   ,   ____   ,         ____  ,   ____   ,   ____
        //        '----------+----------+----------'      '--------+----------+---------'
    ),

    [MOUSE] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ , CTL(C), CTL(V), NORM  ,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , BTN3  , BTN2  , BTN1  , WH_U  ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , LSFT  , LCTL  , ____  , WH_D  ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+-------+---------.
                      ____   ,   ____   ,   ____   ,         ____   ,  ____ ,   ____
        //        '----------+----------+----------'      '---------+-------+---------'
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ONESHOT_SHIFT:
    oneshot(&shift_state, record);
    break;
  case ONESHOT_CTL:
    oneshot(&ctl_state, record);
    break;
  case KC_PRIM:
  case KC_SECON:
  case KC_NAV:
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
