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
#define KC_GUI(KEY) LGUI(KC_##KEY)
#define KC_RESET RESET
#define KC_OCTL ONESHOT_CTL
#define KC_OSHIFT ONESHOT_SHIFT
#define KC_OSCTL ONESHOT_SHIFT_CTL
#define KC_DCLICK DOUBLE_CLICK

#define KC_NRESET NANO_RESET
#define KC_NDPI NANO_DPI

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
  ONESHOT_SHIFT_CTL,
  DOUBLE_CLICK,
  NANO_RESET,
  NANO_DPI,
};

enum layer { NORMAL, SYMBOLS, NUMBERS, FUNCTION, EXTRA, MOUSE };

enum oneshot_state {
  ONESHOT_DISABLED,
  ONESHOT_TRIGGER,
  ONESHOT_HOLDING,
  ONESHOT_RELEASE_AFTER_HOLD,
  ONESHOT_RELEASE,
};

enum nano_command {
  NANO_CMD_DPI = 1,
  NANO_CMD_RESET = 2,
};

struct oneshot {
  enum oneshot_state state;
  uint16_t timer;
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
             PIPE  , AT    , LCBR  , RCBR  , SLASH ,        SCOLON, UNDS  , QUOTE , DQUO  , GRAVE ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             CIRC  , HASH  , LBRC  , RBRC  , BSLASH,        COLN  , AMPR  , PERC  , DLR   , TILD  ,
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
              ____ ,  LALT , OCTL  ,  TAB  ,  STAB ,         ____ , BSPACE, OSCTL ,  DEL  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      XXXX   ,   ____   ,   ____   ,         ____   ,  ENT   ,  EXTRA
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [EXTRA] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , GUI(W), UP    , FULL  , LOCK  ,        ____  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        ____  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDOWN,        ____  , LGUI  , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .--------+----------+---------.
                      ____   ,   ____   ,   ____   ,         ____  ,   ____   ,   ____
        //        '----------+----------+----------'      '--------+----------+---------'
    ),

    [FUNCTION] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ ,  ____ ,  ____ ,  ____ ,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  PSCR ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F1   ,  F2   ,  F3   ,  F4   ,  F5   ,         F6   ,  F7   ,  F8   ,  F9   ,  F10  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ ,  ____ ,  ____ ,  ____ ,  ____ ,         F11  ,  F12  ,  ____ ,  ____ ,  ____ ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      ____   ,   ____   ,   XXXX   ,         RESET  , NRESET ,   ____
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [MOUSE] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ , CTL(C), CTL(V), DCLICK,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              NDPI ,  BTN3 ,  BTN2 ,  BTN1 ,  WH_U ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , LSHIFT,  LCTL , ____  ,  WH_D ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+-------+---------.
                      ____   ,   ____   ,   XXXX   ,         ____   ,  ____ ,   ____
        //        '----------+----------+----------'      '---------+-------+---------'
    ),
};
// clang-format on

static struct oneshot shift_state = {
    .state = ONESHOT_DISABLED,
    .timer = 0,
    .modifier = KC_LSHIFT,
};

static struct oneshot ctl_state = {
    .state = ONESHOT_DISABLED,
    .timer = 0,
    .modifier = KC_LCTL,
};

bool oneshot_timer_expired(struct oneshot *state) {
  return state->timer > 0 &&
         (timer_elapsed(state->timer) > ONESHOT_MOD_TIMEOUT);
}

void oneshot_modifier(struct oneshot *state, keyrecord_t *record) {
  if (!record->event.pressed) {
    if (state->state == ONESHOT_HOLDING) {
      state->state = ONESHOT_TRIGGER;
    } else if (state->state == ONESHOT_RELEASE_AFTER_HOLD) {
      state->state = ONESHOT_DISABLED;

      unregister_code(state->modifier);
    }

    return;
  }

  // Pressing the key again disables it.
  if (state->state != ONESHOT_DISABLED) {
    state->state = ONESHOT_DISABLED;
    state->timer = 0;

    return;
  }

  state->state = ONESHOT_HOLDING;
  state->timer = timer_read();
}

void handle_oneshot_modifier(struct oneshot *state) {
  if (state->state == ONESHOT_HOLDING) {
    // We pressed a key while the modifier is still being held. In this case
    // we'll unregister the modifier when the modifier key is released.
    state->timer = 0;
    state->state = ONESHOT_RELEASE_AFTER_HOLD;

    register_code(state->modifier);
    return;
  }

  if (state->state == ONESHOT_TRIGGER) {
    // The modifier key was released before another key was pressed. In this
    // case we'll apply (if still valid) the modifier to the next key.
    if (oneshot_timer_expired(state)) {
      state->timer = 0;
      state->state = ONESHOT_DISABLED;

      return;
    }

    state->state = ONESHOT_RELEASE;

    register_code(state->modifier);
    return;
  }

  if (state->state == ONESHOT_RELEASE) {
    state->state = ONESHOT_DISABLED;

    unregister_code(state->modifier);
  }
}

void nano_command(keyrecord_t *record, enum nano_command cmd) {
  if (!record->event.pressed) {
    return;
  }

  for (uint16_t i = 0; i < (uint16_t)cmd; i++) {
    // Every pair, one tap is to enable the caps lock, and the other to disable
    // it.
    tap_code16(KC_CAPS_LOCK);
    tap_code16(KC_CAPS_LOCK);
  }
}

void double_click(keyrecord_t *record) {
  if (!record->event.pressed) {
    return;
  }

  tap_code16(KC_BTN1);

  // We need to wait a little between the taps, otherwise only one tap is
  // registered. I'm not sure if that's an OS or QMK issue.
  wait_ms(50);
  tap_code16(KC_BTN1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ONESHOT_SHIFT:
    oneshot_modifier(&shift_state, record);
    break;
  case ONESHOT_CTL:
    oneshot_modifier(&ctl_state, record);
    break;
  case ONESHOT_SHIFT_CTL:
    oneshot_modifier(&shift_state, record);
    oneshot_modifier(&ctl_state, record);
    break;
  case DOUBLE_CLICK:
    double_click(record);
    break;
  case KC_SYM:
  case KC_NUMS:
  case KC_EXTRA:
  case KC_MOUSE:
    break;
  case NANO_RESET:
    nano_command(record, NANO_CMD_RESET);
    break;
  case NANO_DPI:
    nano_command(record, NANO_CMD_DPI);
    break;
  default:
    handle_oneshot_modifier(&shift_state);
    handle_oneshot_modifier(&ctl_state);
  }

  return true;
}
