#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#define CMD_TIMEOUT 25
#define CURSOR_TIMEOUT 500

#define DPI_LOW 350
#define DPI_HIGH 1000

enum caps_command {
  CMD_DPI = 1,
  CMD_RESET = 2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{KC_NO}}};

static bool caps_waiting = false;
static bool caps_state = false;
static uint16_t caps_count = 0;

// Ploopy's cycle_dpi() seems a bit dodgy and defaults to an inconsistent value.
// Perhaps I wrote the wrong value to the EEPROM at some point, but I haven't
// been able to figure this out.
//
// To work around this we'll handle DPI switching ourselves. We track the
// current DPI here as pointing_device_get_dpi() always returns 2000 for the
// Nano.
static uint16_t current_dpi = DPI_HIGH;

void keyboard_post_init_user(void) {
  caps_state = host_keyboard_led_state().caps_lock;

  pointing_device_set_cpi(current_dpi);
}

void swap_dpi(void) {
  uint16_t new_dpi = DPI_HIGH;

  if (current_dpi == new_dpi) {
    new_dpi = DPI_LOW;
  }

#ifdef CONSOLE_ENABLE
  uprintf("Changing DPI from %u to %u\n", current_dpi, new_dpi);
#endif

  current_dpi = new_dpi;
  pointing_device_set_cpi(new_dpi);
}

uint32_t command_timeout(uint32_t trigger_time, void *_) {
  // The keyboard triggers a tap, which results in two LED state changes, but
  // what we want is the number of taps.
  uint16_t taps = caps_count / 2;

#ifdef CONSOLE_ENABLE
  uprintf("Caps lock taps: %u\n", taps);
#endif

  switch (taps) {
  case CMD_DPI:
    swap_dpi();
    break;
  case CMD_RESET:
    reset_keyboard();
    break;
  default:
    break;
  }

  caps_waiting = false;
  caps_count = 0;

  return 0;
}

bool led_update_user(led_t led_state) {
  if (led_state.caps_lock != caps_state) {
#ifdef CONSOLE_ENABLE
    print("Received caps lock state change\n");
#endif

    caps_count++;

    if (!caps_waiting) {
      caps_waiting = true;
      defer_exec(CMD_TIMEOUT, command_timeout, NULL);
    }
  }

  caps_state = led_state.caps_lock;
  return true;
}
