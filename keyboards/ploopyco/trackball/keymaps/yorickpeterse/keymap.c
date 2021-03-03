// Custom keymap for my Ploopy trackball

#include QMK_KEYBOARD_H

// safe range starts at `PLOOPY_SAFE_RANGE` instead.

#define LCLICK KC_BTN1
#define MCLICK KC_BTN3
#define RCLICK KC_BTN2
#define NEXT KC_BTN4
#define PREV KC_BTN5

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
        DPI_CONFIG
    )
};
