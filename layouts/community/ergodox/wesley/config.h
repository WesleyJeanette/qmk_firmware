#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

#define LSPO_KEY KC_9
#define RSPC_KEY KC_0

#define LEADER_TIMEOUT 500 // leader key sequence timeout in millis

#define TAPPING_TOGGLE  1

#undef TAPPING_TERM
#define TAPPING_TERM    300
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling
//combos (zx) with keys that convert to other keys on hold (z becomes ctrl
//when you hold it, and when this option isn't enabled, z rapidly followed by
//x actually sends Ctrl-x. That's bad.)

#endif

