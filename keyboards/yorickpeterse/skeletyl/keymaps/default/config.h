#pragma once

#undef IGNORE_MOD_TAP_INTERRUPT
#undef ONESHOT_TIMEOUT
#undef QMK_KEYS_PER_SCAN
#undef TAPPING_TERM
#undef DEBOUNCE

#define RETRO_TAPPING
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 3000
#define QMK_KEYS_PER_SCAN 4
#define TAPPING_TERM 200

#define COMBO_TERM 30

#define MK_KINETIC_SPEED
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MOVE_DELTA 30
#define MOUSEKEY_INITIAL_SPEED 100
#define MOUSEKEY_BASE_SPEED 2400
#define MOUSEKEY_DECELERATED_SPEED 200
#define MOUSEKEY_ACCELERATED_SPEED 2400

#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 32
#define MOUSEKEY_WHEEL_MAX_SPEED 4
#define MOUSEKEY_WHEEL_TIME_TO_MAX 80

#define DEBOUNCE 5
#define USB_POLLING_INTERVAL_MS 1
