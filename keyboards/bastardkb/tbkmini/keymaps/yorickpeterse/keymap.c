#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_XXXX KC_TRNS
#define KC_NONE KC_NO
#define KC_CANCEL CANCEL_MODIFIERS
#define KC_SYM SYM_OR_SHIFT
#define KC_NUM NUM_OR_CTL
#define KC_STAB LSFT(KC_TAB)
#define KC_ENT_OR_SHFT MT(MOD_LSFT, KC_ENT)
#define KC_FUN MO(FUNCTION)
#define KC_EXTRA MO(EXTRA)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)
#define KC_ROFI LCTL(KC_ENTER)
#define KC_RESET RESET

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
    SYM_OR_SHIFT = SAFE_RANGE,
    NUM_OR_CTL,
    CANCEL_MODIFIERS
};

enum layer {
    NORMAL,
    SYMBOLS,
    NUMBERS,
    FUNCTION,
    EXTRA
};

enum mod_tap_state {
    MOD_TAP_DISABLED,
    MOD_TAP_PENDING,
    MOD_TAP_TRIGGER,
    MOD_TAP_RELEASE,
};

struct mod_tap {
    // The mod-tap state.
    enum mod_tap_state state;

    // The time the modifier was activated on.
    uint16_t timer;

    // The one-shot modifier to apply when the button is tapped.
    uint16_t modifier;

    // The layer to activate when the button is held down.
    int layer;
};

// The time (in milliseconds) after which a mod-tap modifier is disabled.
const static uint16_t MOD_TAP_TIMEOUT = 1500;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
               Q   ,   W   ,   F   ,   P   ,   B   ,          J   ,   L   ,   U   ,   Y   , RALT  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               A   ,   R   ,   S   ,   T   ,   G   ,          K   ,   N   ,   E   ,   I   ,   O   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               Z   ,   X   ,   C   ,   D   ,   V   ,          M   ,   H   , COMMA ,  DOT  , CANCEL,
        // '---------------------------------------'      '---------------------------------------'
        //         ,----------+---------+----------.      .-------+-------+-------.
                        NUM   ,  SPACE  ,   ROFI   ,        CAPS  ,  ENT  ,  SYM
        //         '----------+---------+----------'      '-------+-------+-------'
    ),

    [SYMBOLS] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             EXLM  , QUES  , LPRN  , RPRN  , ____  ,        ____  , MINUS , EQUAL , PLUS  , ASTR  ,
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
              ESC  , ____  , LABK  , RABK  ,  ____ ,        INS   , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               1   ,  2    ,  3    ,  4    ,  5    ,         6    ,  7    ,  8    ,  9    ,  0    ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , ____  , LCTL  , LALT  ,  TAB  ,        STAB  , BSPACE, DELETE, ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      XXXX   ,   ____   ,   ____   ,         ____   ,  ____  ,  EXTRA
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [EXTRA] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , UP    , FULL  ,  LOCK ,        F1    , F2    , F3    , F4    , F5    ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , PGUP  ,        F6    , F7    , F8    , F9    , F10   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), PGDOWN,        ____  , ____  , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+----------+---------.
                      ____   ,   ____   ,  RESET   ,         ____   ,   ____   ,   XXXX
        //        '----------+----------+----------'      '---------+----------+---------'
    ),
};

static struct mod_tap sym_state = {
    .state = MOD_TAP_DISABLED,
    .timer = 0,
    .modifier = KC_LSHIFT,
    .layer = SYMBOLS,
};

static struct mod_tap num_state = {
    .state = MOD_TAP_DISABLED,
    .timer = 0,
    .modifier = KC_LCTL,
    .layer = NUMBERS,
};

bool oneshot_timer_expired(struct mod_tap *state) {
    return state->timer > 0 && (timer_elapsed(state->timer) > MOD_TAP_TIMEOUT);
}

void reset_all_oneshot_modifiers(void) {
    sym_state.state = MOD_TAP_DISABLED;
    sym_state.timer = 0;

    num_state.state = MOD_TAP_DISABLED;
    num_state.timer = 0;
}

// Enables a layer or toggles a oneshot modifier key.
//
// This uses custom logic instead of QMK's built-in functions for enabling
// oneshot modifiers. This makes it possible to enable a oneshot modifier using
// key A, then press key A again to activate a layer, then tap something on that
// layer and have the modifier applied.
//
// When using QMK, _any_ key press after enabling a oneshot modifier will have
// the "down" event of the modifier applied to it. This makes it impossible to
// use the modifiers for any keys on the layer.
//
// In addition, the setup here simply gives us more control; at the cost of a
// bit of extra code. Peraps there's an easier way of achieving all this, but I
// haven't found it yet :<
void oneshot_modifier_or_layer(struct mod_tap *state, keyrecord_t *record) {
    if (record->event.pressed) {
        if (state->state == MOD_TAP_DISABLED) {
            // We only overwrite the disabled state to allow for modifiers for
            // keys on the layer. If we always set the state to "pending", this
            // wouldn't be possible.
            state->state = MOD_TAP_PENDING;
            state->timer = 0;
        }

        layer_on(state->layer);

        return;
    }

    // The code that follows runs when the key is released.
    layer_off(state->layer);

    if (state->state == MOD_TAP_PENDING) {
        // No key was pressed, apply the modifier to the next key.
        state->timer = timer_read();
        state->state = MOD_TAP_TRIGGER;

        return;
    }
}

void handle_pending_mod_tap(struct mod_tap *state, keyrecord_t *record) {
    if (state->state == MOD_TAP_PENDING) {
        // The layer is still active, and we pressed a key on that layer. In
        // this case we don't enable any one-shot keys.
        state->state = MOD_TAP_DISABLED;

        return;
    }

    if (state->state == MOD_TAP_TRIGGER) {
        // A oneshot key is enabled. Only trigger it if the timeout didn't
        // expire.
        if (oneshot_timer_expired(state)) {
            state->timer = 0;
            state->state = MOD_TAP_DISABLED;

            return;
        }

        register_code(state->modifier);
        state->state = MOD_TAP_RELEASE;

        return;
    }

    if (state->state == MOD_TAP_RELEASE) {
        // A oneshot key has been registered, and we need to unregister it.
        unregister_code(state->modifier);

        state->state = MOD_TAP_DISABLED;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYM_OR_SHIFT:
            oneshot_modifier_or_layer(&sym_state, record);
            break;
        case NUM_OR_CTL:
            oneshot_modifier_or_layer(&num_state, record);
            break;
        case KC_EXTRA:
            // Don't apply modifiers to this layer key.
            return true;
        case CANCEL_MODIFIERS:
            reset_all_oneshot_modifiers();
            break;
        default:
            handle_pending_mod_tap(&sym_state, record);
            handle_pending_mod_tap(&num_state, record);
    }

    return true;
}
