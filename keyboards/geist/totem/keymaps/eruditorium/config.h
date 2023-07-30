#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

//#define MASTER_LEFT
#define MASTER_RIGHT

// source: https://www.reddit.com/r/ErgoMechKeyboards/comments/tiejpp/home_row_mods_what_works_for_you
#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200 // 250 // 100
#define TAPPING_TERM_PER_KEY
// https://precondition.github.io/home-row-mods
#define TAPPING_FORCE_HOLD  // make tap-then-hold _not_ do key auto repeat
#define TAPPING_FORCE_HOLD_PER_KEY  // ... but do it for some!
#define HOLD_ON_OTHER_KEY_PRESS  // obsolete my LT_NUM_BSPC
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY  // ... but not for mod-taps!
//#define IGNORE_MOD_TAP_INTERRUPT  // obsolete
#define PERMISSIVE_HOLD  // I don't think this works for me, hence I rolled my own implementation.

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// source: https://jasoncarloscox.com/blog/combo-mods/
// #define COMBO_TERM 25        // how quickly all combo keys must be pressed in succession to trigger
// #define COMBO_MUST_HOLD_MODS // if a combo triggers a modifier, only trigger when the combo is held
// #define COMBO_HOLD_TERM 175  // how long at least one of the combo keys must be held to trigger

// Add these flags to your rules.mk file:
// This enables Link Time Optimization, saving a significant amount of space. Because the Macro and Function features are incompatible with Link Time Optimization, disable those features in config.h:
// Drashna, on QMK issue 3224, paraphrased
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// Activate CAPS WORD by pressing Left Shift + Right Shift
// https://docs.qmk.fm/#/feature_caps_word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// Activate by double tapping Left Shift:
// alternative:
//#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
