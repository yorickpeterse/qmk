// Custom keymap for my Ploopy trackball
//
// safe range starts at `PLOOPY_SAFE_RANGE` instead.

#include QMK_KEYBOARD_H

#define LCLICK KC_BTN1
#define MCLICK KC_BTN3
#define RCLICK KC_BTN2
#define SHIFT KC_LSHIFT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        // Bottom left
        LCLICK,
        // Middle left
        MCLICK,
        // Top left
        RCLICK,
        // Top right
        MCLICK,
        // Bottom right
        SHIFT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
