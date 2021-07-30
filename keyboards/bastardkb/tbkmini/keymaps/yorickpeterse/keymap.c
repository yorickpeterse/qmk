#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_XXXX KC_TRNS
#define KC_NONE KC_NO
#define KC_SYM MO(SYMBOLS)
#define KC_NUM MO(NUMBERS)
#define KC_STAB LSFT(KC_TAB)
#define KC_FUN OSL(FUNCTION)
#define KC_EXTRA MO(EXTRA)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)
#define KC_RESET RESET
#define KC_OCTL ONESHOT_CTL
#define KC_OSHIFT ONESHOT_SHIFT

// The firmware I'm using is based on the TBK Mini keyboard, which has 6 columns
// instead of 5.
#define LAYOUT( \
    k00, k01, k02, k03, k04,       k05, k06, k07, k08, k09, \
    k10, k11, k12, k13, k14,       k15, k16, k17, k18, k19, \
    k20, k21, k22, k23, k24,       k25, k26, k27, k28, k29, \
              k30, k31, k32,       k33, k34, k35  \
) LAYOUT_split_3x6_3( \
    KC_NO, KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04,       KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_NO, \
    KC_NO, KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14,       KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_NO, \
    KC_NO, KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24,       KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_NO, \
                               KC_##k30, KC_##k31, KC_##k32,       KC_##k33, KC_##k34, KC_##k35  \
)

enum custom_keycodes {
    ONESHOT_SHIFT = SAFE_RANGE,
    ONESHOT_CTL,
};

enum layer {
    NORMAL,
    SYMBOLS,
    NUMBERS,
    FUNCTION,
    EXTRA
};

enum oneshot_state {
    ONESHOT_DISABLED,
    ONESHOT_TRIGGER,
    ONESHOT_HOLDING,
    ONESHOT_RELEASE_AFTER_HOLD,
    ONESHOT_RELEASE,
};

struct oneshot {
    enum oneshot_state state;
    uint16_t timer;
    uint16_t modifier;
};

// The time (in milliseconds) after which a mod-tap modifier is disabled.
const static uint16_t ONESHOT_MOD_TIMEOUT = 1500;

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
                            NUM  ,  SPACE  ,  FUN  ,         CAPS  ,  OSHIFT  ,  SYM
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
              ____ , ____  , OCTL  , LALT  ,  TAB  ,        STAB  , BSPACE,  ENT  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      XXXX   ,   ____   ,   ____   ,         ____   ,  ____  ,  EXTRA
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [EXTRA] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , UP    , FULL  , LOCK  ,        ____  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        ____  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDOWN,        ____  , ____  , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+----------+---------.
                      ____   ,   ____   ,  RESET   ,         ____   ,   ____   ,   ____
        //        '----------+----------+----------'      '---------+----------+---------'
    ),

    [FUNCTION] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ____ ,  ____ ,  ____ ,  ____ ,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              F1   ,  F2   ,  F3   ,  F4   ,  F5   ,         F6   ,  F7   ,  F8   ,  F9   ,  F10  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ ,  ____ ,  ____ ,  ____ ,  ____ ,         ____ ,  ____ ,  ____ ,  ____ ,  ____ ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      ____   ,   ____   ,   XXXX   ,         ____   ,  ____  ,   ____
        //        '----------+----------+----------'      '---------+--------+---------'
    ),
};

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
    return state->timer > 0 && (timer_elapsed(state->timer) > ONESHOT_MOD_TIMEOUT);
}

void oneshot_modifier(struct oneshot *state, keyrecord_t *record) {
    if (!record->event.pressed) {
        if (state->state == ONESHOT_HOLDING) {
            state->state = ONESHOT_TRIGGER;
        }
        else if (state->state == ONESHOT_RELEASE_AFTER_HOLD) {
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ONESHOT_SHIFT:
            oneshot_modifier(&shift_state, record);
            break;
        case ONESHOT_CTL:
            oneshot_modifier(&ctl_state, record);
            break;
        case KC_SYM:
        case KC_NUM:
        case KC_EXTRA:
            break;
        default:
            handle_oneshot_modifier(&shift_state);
            handle_oneshot_modifier(&ctl_state);
    }

    return true;
}
