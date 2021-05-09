#include QMK_KEYBOARD_H

#define KC_____ KC_TRNS
#define KC_XXXX KC_TRNS
#define KC_NONE KC_NO
#define KC_SYM MO(SYMBOLS)
#define KC_NUM MO(NUMBERS)
#define KC_STAB LSFT(KC_TAB)
#define KC_ENT_OR_SHFT MT(MOD_LSFT, KC_ENT)
#define KC_OCTL ONESHOT_CONTROL
#define KC_OSHFT ONESHOT_SHIFT
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
    ONESHOT_CONTROL = SAFE_RANGE,
    ONESHOT_SHIFT
};

enum layer {
    NORMAL,
    SYMBOLS,
    NUMBERS,
    FUNCTION,
    EXTRA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
               Q   ,   W   ,   F   ,   P   ,   B   ,          J   ,   L   ,   U   ,   Y   , DELETE,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               A   ,   R   ,   S   ,   T   ,   G   ,          K   ,   N   ,   E   ,   I   ,   O   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               Z   ,   X   ,   C   ,   D   ,   V   ,          M   ,   H   , COMMA ,  DOT  , BSPACE,
        // '---------------------------------------'      '---------------------------------------'
        //         ,----------+---------+----------.      .-------+-------+-------.
                        NUM   ,  SPACE  ,   ROFI   ,        RALT  ,  ENT  ,  SYM
        //         '----------+---------+----------'      '-------+-------+-------'
    ),

    [SYMBOLS] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             EXLM  , QUES  , LPRN  , RPRN  , ____  ,        ____  , MINUS , EQUAL , PLUS  , ASTR  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             PIPE  , AT    , LCBR  , RCBR  , SLASH ,        SCOLON, UNDS  , QUOTE , DQUO  , GRAVE ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             CIRC  , HASH  , LBRC  , RBRC  , BSLASH,        COLN  , AMPR  , PERC  , TILD  ,  DLR  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+----------+---------.
                      ____   ,   ____   ,   ____   ,         ____   ,   ____   ,  XXXX
        //        '----------+----------+----------'      '---------+----------+---------'
    ),

    [NUMBERS] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
              ESC  , ____  , LABK  , RABK  ,  ____ ,        ____  , ____  , ____  , ____  , ____  ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
               1   ,  2    ,  3    ,  4    ,  5    ,         6    ,  7    ,  8    ,  9    ,  0    ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
              ____ , ____  , OCTL  , LALT  ,  TAB  ,        STAB  , ____  , OSHFT , ____  , INS   ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+--------+---------.
                      XXXX   ,   ____   ,   ____   ,         CAPS   , LSHIFT ,   EXTRA
        //        '----------+----------+----------'      '---------+--------+---------'
    ),

    [EXTRA] = LAYOUT(
        // ,---------------------------------------.      ,---------------------------------------.
             ____  , ____  , UP    , FULL  ,  LOCK ,        F1    , F2    , F3    , F4    , F5    ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , LEFT  , DOWN  , RIGHT , ____  ,        F6    , F7    , F8    , F9    , F10   ,
        // |-------+-------+-------+-------+-------|      |-------+-------+-------+-------+-------|
             ____  , CTL(1), CTL(2), CTL(3), ____  ,        ____  , ____  , ____  , ____  , ____  ,
        // '---------------------------------------'      '---------------------------------------'
        //        ,----------+----------+----------.      .---------+----------+---------.
                      ____   ,   ____   ,  RESET   ,         ____   ,   ____   ,   XXXX
        //        '----------+----------+----------'      '---------+----------+---------'
    ),
};

// A custom function for triggering one-shot modifiers.
//
// The OSH() macro built into QMK disables one-shot modifiers when exiting the
// layer they were triggered on, if no other key has been pressed (at least it
// appears that way). The implementation here keeps the modifier active until
// another key is pressed, or the modifier is disabled by pressing the same key
// again. This makes it easier to use the modifier when typing quickly.
void oneshot_modifier(uint16_t modifier, keyrecord_t *record) {
    int mod_bit = MOD_BIT(modifier);

    if (!record->event.pressed) {
        return;
    }

    if ((get_oneshot_mods() & mod_bit) == mod_bit) {
        // Disable only the modifier that belongs to the same key that set
        // it. This ensures we can have multiple modifiers set, and only
        // unset the one we meant to; instead of unsetting all of them.
        set_oneshot_mods(get_oneshot_mods() & ~mod_bit);
    } else {
        set_oneshot_mods(get_oneshot_mods() | mod_bit);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ONESHOT_CONTROL:
            oneshot_modifier(KC_LCTL, record);
            break;
        case ONESHOT_SHIFT:
            oneshot_modifier(KC_LSHIFT, record);
            break;
    }

    return true;
}
