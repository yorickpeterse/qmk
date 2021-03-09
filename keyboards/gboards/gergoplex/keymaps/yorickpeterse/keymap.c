#include "gergoplex.h"

#define NORMAL 0
#define SYMBOLS 1
#define NUMBERS 2
#define FUNCTION 3
#define NAVIGATION 4
#define WINDOWS 5

#define KC_SYM MO(SYMBOLS)
#define KC_NUM MO(NUMBERS)
#define KC_FUN MO(FUNCTION)
#define KC_NAV MO(NAVIGATION)
#define KC_WINS MO(WINDOWS)
#define KC_FULL LALT(KC_F11)
#define KC_LOCK LCTL(LALT(KC_DEL))
#define KC_TAB_CTL MT(MOD_LCTL, KC_TAB)
#define KC_WIN(NUM) LCTL(KC_##NUM)
#define KC_SHIFT_ENT SHIFT_ENT
#define KC_ALT_TAB LALT(KC_TAB)

enum custom_keycodes {
    SHIFT_ENT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT_kc(
    // ,-------------------------------.      ,-------------------------------.
           Q   ,  W  ,  F  ,  P  ,  B  ,         J  ,  L  ,  U  ,  Y  ,   V   ,
    // |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
           A   ,  R  ,  S  ,  T  ,  G  ,         K  ,  N  ,  E  ,  I  ,   O   ,
    // |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
           Z   ,  X  ,  C  ,  D  , NUM ,        SYM ,  M  ,  H  , NAV , WINS  ,
    // '-------------------------------'      '-------------------------------'
    //       .------+---------+---------.      .-----+--------+--------.
               LALT , TAB_CTL ,  SPACE  ,        ENT , LSHIFT , RALT   ),
    //       '------+---------+---------'      '-----+--------+--------'

    [SYMBOLS] = LAYOUT_kc(
    // ,-------------------------------------.      ,--------------------------------------.
          EXLM , QUES , LPRN , RPRN , BSLASH ,         COLN , MINUS , EQUAL , PLUS , ASTR  ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          PIPE , AT   , LCBR , RCBR , SLASH  ,        SCOLON, UNDS  , QUOTE , DQUO , GRAVE ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          TRNS , HASH , LBRC , RBRC , TRNS   ,        TRNS  , AMPR  , COMMA , DOT  , TRNS  ,
    // '-------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .------+------+--------.
                          TRNS , TRNS , TRNS ,        TRNS , TRNS , TRNS  ),
    //                  '------+------+------'      '------+------+--------'

    [NUMBERS] = LAYOUT_kc(
    // ,-------------------------------------.      ,--------------------------------------.
          ESC  , CIRC , LABK , RABK , TRNS   ,        TRNS  , DLR   , PERC  , TILD , TRNS  ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          1    , 2    , 3    , 4    , 5      ,        6     , 7     , 8     , 9    , 0     ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          TRNS , TRNS , TRNS , TRNS , TRNS   ,        FUN   , BSPACE, DELETE, CAPS , INS   ,
    // '-------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .-----------+------+--------.
                          TRNS , TRNS , TRNS ,        SHIFT_ENT , TRNS , TRNS   ),
    //                  '------+------+------'      '-----------+------+--------'

    [FUNCTION] = LAYOUT_kc(
    // ,-------------------------------------.      ,--------------------------------------.
         TRNS  , TRNS , TRNS , TRNS , TRNS   ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          F1   , F2   , F3   , F4   , F5     ,        F6    , F7    , F8    , F9   , F10   ,
    // |-------+------+------+------+--------|      |-------+-------+-------+------+-------|
          TRNS , TRNS , TRNS , TRNS , TRNS   ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // '-------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .------+------+--------.
                          TRNS , TRNS , TRNS ,        TRNS , TRNS , TRNS  ),
    //                  '------+------+------'      '------+------+--------'

    [NAVIGATION] = LAYOUT_kc(
    // ,----------------------------------------.      ,--------------------------------------.
         TRNS   , TRNS   , UP     , TRNS , TRNS ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // |--------+--------+--------+------+------|      |-------+-------+-------+------+-------|
         TRNS   , LEFT   , DOWN   , RIGHT, TRNS ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // |--------+--------+--------+------+------|      |-------+-------+-------+------+-------|
          TRNS  , TRNS   , TRNS   , TRNS , TRNS ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // '----------------------------------------'      '--------------------------------------'
    //                  .------+------+------.      .------+------+--------.
                          TRNS , TRNS , TRNS ,        TRNS , TRNS , TRNS  ),
    //                  '------+------+------'      '------+------+--------'

    [WINDOWS] = LAYOUT_kc(
    // ,----------------------------------------.      ,--------------------------------------.
         TRNS   , TRNS   , TRNS   , TRNS , TRNS ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // |--------+--------+--------+------+------|      |-------+-------+-------+------+-------|
         WIN(1) , WIN(2) , WIN(3) , TRNS , TRNS ,        TRNS  , FULL  , LOCK  , TRNS , TRNS  ,
    // |--------+--------+--------+------+------|      |-------+-------+-------+------+-------|
          TRNS  , TRNS   , TRNS   , TRNS , TRNS ,        TRNS  , TRNS  , TRNS  , TRNS , TRNS  ,
    // '----------------------------------------'      '--------------------------------------'
    //                  .------+---------+------.      .------+------+--------.
                          TRNS , ALT_TAB , TRNS ,        TRNS , TRNS , TRNS  ),
    //                  '------+---------+------'      '------+------+--------'
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // Some programs such as Slack require the use of Shift+Enter to enter
        // newlines in text fields. This macro makes it easier to produce this
        // combination, as both Enter and Shift are next to each other on the
        // same hand.
        case SHIFT_ENT:
            if(record->event.pressed) {
                register_code(KC_LSHIFT);
                tap_code(KC_ENTER);
                unregister_code(KC_LSHIFT);
                break;
            }
    }

    return true;
}
