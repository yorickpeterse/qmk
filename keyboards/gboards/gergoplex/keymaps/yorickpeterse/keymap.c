#include "gergoplex.h"
#include "print.h"

#define KC_SYM CTL_OR_SYM
#define KC_NUM MO(NUMBERS)
#define KC_EXT SHIFT_OR_EXT
#define KC_FUN OSL(FUNCTION)
#define KC_STAB LSFT(KC_TAB)

#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_CTL(KEY) LCTL(KC_##KEY)

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

enum custom_keycodes {
    CTL_OR_SYM = SAFE_RANGE,
    SHIFT_OR_EXT
};

enum layers {
    NORMAL,
    SYMBOLS,
    NUMBERS,
    EXTRA,
    FUNCTION
};

enum mod_tap_state {
    MOD_TAP_DISABLED,
    MOD_TAP_PENDING,
    MOD_TAP_PRESSED,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT_kc(
    // ,-----------------------------.      ,-------------------------------.
          Q  ,  W  ,  F  ,  P  ,  B  ,         J  ,  L  ,  U  ,  Y  ,   V   ,
    // |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
          A  ,  R  ,  S  ,  T  ,  G  ,         K  ,  N  ,  E  ,  I  ,   O   ,
    // |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
          Z  ,  X  , C   ,  D  , NUM ,        SYM ,  M  ,  H  , EXT ,  FUN  ,
    // '-----------------------------'      '-------------------------------'
    //        .------+------+--------.      .-----+------+--------.
                ____ , ____ , SPACE  ,        ENT , LALT ,  RALT  ),
    //        '------+------+--------'      '-----+------+--------'

    [SYMBOLS] = LAYOUT_kc(
    // ,-------------------------------------.      ,--------------------------------------.
          EXLM , QUES , LPRN , RPRN , BSLASH ,         COLN , MINUS , EQUAL , PLUS , ASTR  ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          PIPE , AT   , LCBR , RCBR , SLASH  ,        SCOLON, UNDS  , QUOTE , DQUO , GRAVE ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          ____ , HASH , LBRC , RBRC ,  ____  ,        ____  , AMPR  , COMMA , DOT  , ____  ,
    // '-------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .------+------+--------.
                          ____ , ____ , ____ ,        ____ , ____ , ____  ),
    //                  '------+------+------'      '------+------+--------'

    [NUMBERS] = LAYOUT_kc(
    // ,-------------------------------------.      ,--------------------------------------.
          ESC  , CIRC , LABK , RABK ,  TAB   ,        STAB  , DLR   , PERC  , TILD , ____  ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          1    , 2    , 3    , 4    , 5      ,        6     , 7     , 8     , 9    , 0     ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          ____ , ____ , ____ , ____ ,  ____  ,        ____  , BSPACE, DELETE, CAPS , INS   ,
    // '-------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .------+------+-------.
                          ____ , ____ , ____ ,        ____ , ____ , ____ ),
    //                  '------+------+------'      '------+------+-------'

    [EXTRA] = LAYOUT_kc(
    // ,-----------------------------------------.      ,--------------------------------------.
         ____   , ____   , UP     , ____  , ____ ,        ____  , ____  , ____  , ____ , ____  ,
    // |--------+--------+--------+-------+------|      |-------+-------+-------+------+-------|
         ____   , LEFT   , DOWN   , RIGHT , ____ ,        ____  , FULL  , LOCK  , ____ , ____  ,
    // |--------+--------+--------+-------+------|      |-------+-------+-------+------+-------|
         ____   , CTL(1) , CTL(2) , CTL(3), ____ ,        ____  , ____  , ____  , ____ , ____  ,
    // '-----------------------------------------'      '--------------------------------------'
    //                      .------+------+------.      .------+------+-------.
                              ____ , ____ , ____ ,        ____ , ____ , ____ ),
    //                      '------+------+------'      '------+------+-------'

    [FUNCTION] = LAYOUT_kc(
    // ,-------------------------------------.      ,--------------------------------------.
         ____  , ____ , ____ , ____ ,  ____  ,        ____  , ____  , ____  , ____ , ____  ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          F1   , F2   , F3   , F4   , F5     ,        F6    , F7    , F8    , F9   , F10   ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          ____ , ____ , ____ , ____ ,  ____  ,        ____  , ____  , ____  , ____ , ____  ,
    // '-------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .------+------+-------.
                          ____ , ____ , ____ ,        ____ , ____ , ____ ),
    //                  '------+------+------'      '------+------+-------'
};

static enum mod_tap_state sym_state = MOD_TAP_DISABLED;
static enum mod_tap_state ext_state = MOD_TAP_DISABLED;

void oneshot_modifier_or_layer(
    enum mod_tap_state *state,
    uint16_t modifier,
    int layer,
    keyrecord_t *record
) {
    int mod_bit = MOD_BIT(modifier);

    if (record->event.pressed) {
        if ((get_oneshot_mods() & mod_bit) == mod_bit) {
            *state = MOD_TAP_DISABLED;

            // Disable only the modifier that belongs to the same key that set
            // it. This ensures we can have multiple modifiers set, and only
            // unset the one we meant to; instead of unsetting all of them.
            set_oneshot_mods(get_oneshot_mods() & ~mod_bit);
        } else {
            *state = MOD_TAP_PENDING;
            layer_on(layer);
        }

        return;
    }

    layer_off(layer);

    if (*state == MOD_TAP_PENDING) {
        // No key was pressed, apply the modifier to the next key.
        set_oneshot_mods(get_oneshot_mods() | mod_bit);
    }

    *state = MOD_TAP_DISABLED;
}

void handle_pending_mod_tap(enum mod_tap_state *state) {
    if (*state == MOD_TAP_PENDING) {
        *state = MOD_TAP_PRESSED;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_OR_SYM:
            oneshot_modifier_or_layer(&sym_state, KC_LCTL, SYMBOLS, record);
            break;
        case SHIFT_OR_EXT:
            oneshot_modifier_or_layer(&ext_state, KC_LSHIFT, EXTRA, record);
            break;
        default:
            handle_pending_mod_tap(&sym_state);
            handle_pending_mod_tap(&ext_state);
    }

    return true;
}
