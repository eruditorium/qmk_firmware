/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 250 // 100

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT

#define TAPPING_TERM_PER_KEY

// https://precondition.github.io/home-row-mods
// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD  // make tap-then-hold _not_ do key auto repeat
#define TAPPING_FORCE_HOLD_PER_KEY  // ... but do it for some!

#define HOLD_ON_OTHER_KEY_PRESS  // obsolete my LT_NUM_BSPC
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY  // ... but not for mod-taps!

// source: https://jasoncarloscox.com/blog/combo-mods/
#define COMBO_TERM 25        // how quickly all combo keys must be pressed in succession to trigger
#define COMBO_MUST_HOLD_MODS // if a combo triggers a modifier, only trigger when the combo is held
#define COMBO_HOLD_TERM 175  // how long at least one of the combo keys must be held to trigger


#undef RGBLED_NUM
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17


// from pichfl
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_TRANSACTION_IDS_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSPORT_MIRROR

#define RGB_DISABLE_WHEN_USB_SUSPENDED

//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#undef OLED_FONT_H
#undef OLED_FONT_WIDTH
#undef OLED_FONT_HEIGHT
#undef OLED_FONT_END

#define OLED_FONT_H "keyboards/crkbd/keymaps/nico/glcdfont.c"
#define OLED_FONT_WIDTH 8
#define OLED_FONT_HEIGHT 8
#define OLED_FONT_END 0x9F

// Add these flags to your rules.mk file:
// This enables Link Time Optimization, saving a significant amount of space. Because the Macro and Function features are incompatible with Link Time Optimization, disable those features in config.h:
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION
// Drashna, on QMK issue 3224, paraphrased
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
