#include QMK_KEYBOARD_H

#define LED_CMD_TIMEOUT 25
#define CURSOR_TIMEOUT 500

typedef struct {
  bool reset;
  uint8_t count;
} cmd_window_state_t;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{KC_NO}}};

static bool reset_state = false;
static bool cursor = false;
static uint16_t cursor_timer = 0;

void keyboard_post_init_user(void) {
  reset_state = host_keyboard_led_state().caps_lock;

  // The default DPI of the Ploopy is a bit too high, so I have it turned down
  // a notch.
  pointing_device_set_cpi(1000);
}

bool led_update_user(led_t led_state) {
  if (led_state.caps_lock != reset_state) {
#ifdef CONSOLE_ENABLE
    print("Entering bootloader mode\n");
#endif
    reset_keyboard();
  }

  reset_state = led_state.caps_lock;
  return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t report) {
  if (report.x || report.y) {
    cursor_timer = timer_read();

    if (!cursor) {
      cursor = true;
      tap_code16(KC_NUMLOCK);
    }
  } else if (cursor && timer_elapsed(cursor_timer) > CURSOR_TIMEOUT) {
    cursor = false;
    tap_code16(KC_NUMLOCK);
  }

  return report;
}
