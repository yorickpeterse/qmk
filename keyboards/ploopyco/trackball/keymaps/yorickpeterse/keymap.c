// Custom keymap for my Ploopy trackball

#include QMK_KEYBOARD_H

// safe range starts at `PLOOPY_SAFE_RANGE` instead.

#define LCLICK KC_BTN1
#define MCLICK KC_BTN3
#define RCLICK KC_BTN2
#define NEXT KC_BTN4
#define PREV KC_BTN5

enum custom_keycodes {
    SNIPER_BUTTON = PLOOPY_SAFE_RANGE
};

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
        SNIPER_BUTTON
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case SNIPER_BUTTON:
            if(record->event.pressed) {
                pmw_set_cpi(PLOOPY_DPI_SNIPER_VALUE);
            } else {
                pmw_set_cpi(PLOOPY_DPI_NORMAL_VALUE);
            }

            break;
    }

    return true;
}
