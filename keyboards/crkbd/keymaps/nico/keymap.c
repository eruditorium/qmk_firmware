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

#include QMK_KEYBOARD_H
#include <stdio.h> // ??

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                  │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                       │
// └─────────────────────────────────────────────────┘
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y c o d e s                   │
// └─────────────────────────────────────────────────┘
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    SNAP,
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   c o m b o   n a m e s             │
// └─────────────────────────────────────────────────┘

enum combos {
    COMBO_HOME,
    COMBO_ENDE,
    COMBO_WORDBSPC,
    COMBO_WORDDEL,
    COMBO_LENGTH // nifty trick to avoid manually specifying how many combos you have
};

uint16_t COMBO_LEN = COMBO_LENGTH; // nifty trick continued

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s               │
// └─────────────────────────────────────────────────┘

// LEFT HAND HOME ROW MODS QWERTY ├──────────────────
#define SHT_F MT(MOD_LSFT, KC_F)

// RIGHT HAND HOME ROW MODS QWERTY ├─────────────────┐
#define SHT_J MT(MOD_RSFT, KC_J)

#define DEL_ALTGR MT(MOD_RALT, KC_DEL)
#define BSPC_ALT MT(MOD_LALT, KC_BACKSPACE)
#define ENTER_CTL MT(MOD_LCTL, KC_ENTER)

#define LOWER LT(_LOWER, KC_ESC)
#define RAISE LT(_RAISE, KC_TAB)
#define ADJUST MO(_ADJUST)

//#define RAISE MO(_RAISE)
//#define LOWER MO(_LOWER)
#define SFTAB LSFT_T(KC_TAB)
#define GUIEI LGUI_T(KC_PGUP)
#define ALTKN RALT_T(KC_PGDN)

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
    KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    SFTAB,    KC_A,    KC_S,    KC_D,    SHT_F,    KC_G,                      KC_H,    SHT_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                         GUIEI,    RAISE,   KC_ENT,  KC_SPC,  LOWER,   ALTKN
  ),

/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ l o w e r                                       │
   └─────────────────────────────────────────────────┘
*/
  [_LOWER] = LAYOUT_split_3x6_3(
    KC_ESC,  XXXXXXX  KC_HOME, KC_UP,   KC_PGUP,  KC_LCBR,                   KC_RCBR,   KC_7,   KC_8,   KC_9,   KC_PPLS,  KC_BSPC,
    SFTAB,   XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,  KC_LBRC,                   KC_RBRC,   KC_4,   KC_5,   KC_6,   KC_MINS,  XXXXXXX,
    KC_LCTL, XXXXXXX, KC_END,  XXXXXXX, KC_PGDN,  KC_LPRN,                   KC_RPRN,   KC_1,   KC_2,   KC_3,   KC_PAST,  KC_EQL,
                                        _______,  ADJUST, _______,  _______, _______,   KC_0
  ),

/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ r a i s e                                       │
   └─────────────────────────────────────────────────┘
   */
  [_RAISE] = LAYOUT_split_3x6_3(
    _______, KC_EXLM, KC_AT,   KC_UP,   KC_DLR,  KC_PERC,                   XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12,  KC_BSPC,
    _______, KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSLS,                   XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,  XXXXXXX,
    _______, KC_VOLD, KC_AMPR, KC_HASH, KC_CIRC, KC_GRV,                    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10,  XXXXXXX,
                                        _______, _______, _______, _______, ADJUST,  _______

  ),

/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ a d j u s t                                     │
   └─────────────────────────────────────────────────┘
   */
  [_ADJUST] = LAYOUT_split_3x6_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _______, _______, _______, _______, _______, _______
  )
};
/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸*/

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ M A C R O S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

// ┌─────────────────────────────────────────────────┐
// │ c o m b o s                                     │
// └─────────────────────────────────────────────────┘
// define keys that make up combos
const uint16_t PROGMEM qa_combo[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM ps_combo[] = {KC_P, KC_SCLN, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM fd_combo[] = {KC_S, KC_D, COMBO_END};


// map combo names to their keys and the key they trigger
combo_t key_combos[] = {
    [COMBO_HOME] = COMBO(qa_combo, KC_HOME),
    [COMBO_ENDE] = COMBO(ps_combo, KC_END),
    [COMBO_WORDDEL] = COMBO(fd_combo, LCTL(KC_BSPC)),
    [COMBO_WORDBSPC] = COMBO(jk_combo, LCTL(KC_DEL)),
};

/*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸*/

// ┌─────────────────────────────────────────────────┐
// │ o l e d                                         │
// └─────────────────────────────────────────────────┘
// this part is from pichfl's great animation for the aurora lily58
// https://github.com/pichfl/qmk_firmware/tree/lily58-mission-control
#ifdef OLED_ENABLE
static const char PROGMEM shuttle[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 12, 2, 1, 1, 2, 12, 112, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 112, 176, 79, 128, 64, 32, 16, 16, 32, 64, 128, 79, 176, 112, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 85, 170, 253, 3, 248, 222, 205, 205, 222, 248, 3, 253, 170, 85, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 85, 10, 193, 0, 255, 255, 255, 255, 255, 255, 0, 193, 10, 85, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 160, 208, 239, 248, 254, 255, 0, 127, 127, 255, 255, 127, 127, 0, 255, 254, 248, 239, 208, 160, 64, 128, 0, 0, 0, 0,
};

static const char PROGMEM launch_1[] = {
    0, 0, 6, 9, 14, 15, 15, 239, 23, 151, 31, 192, 63, 31, 32, 127, 127, 32, 31, 63, 192, 31, 151, 23, 239, 15, 15, 14, 9, 6, 0, 0, 254, 255, 255, 246, 224, 128, 64, 226, 126, 206, 62, 254, 30, 128, 254, 30, 236, 254, 128, 30, 254, 102, 158, 254, 226, 192, 0, 0, 176, 248, 252, 252, 131, 65, 161, 67, 131, 6, 29, 122, 61, 26, 157, 27, 180, 59, 117, 235, 212, 171, 245, 58, 21, 26, 29, 59, 245, 58, 13, 7, 3, 1, 1, 3, 10, 21, 42, 85, 42, 21, 10, 20, 170, 85, 170, 85, 170, 21, 10, 0, 143, 71, 160, 84, 170, 84, 168, 64, 128, 64, 168, 84, 170, 85, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 1, 2, 1, 0, 0, 0, 1, 0, 1, 2, 5, 10, 5, 2, 1, 0, 0, 0, 0,
};

static const char PROGMEM launch_2[] = {
    0, 128, 134, 137, 14, 15, 15, 239, 23, 151, 31, 192, 63, 31, 32, 127, 127, 32, 31, 63, 192, 31, 151, 23, 239, 15, 15, 14, 9, 6, 0, 0, 127, 127, 255, 247, 227, 128, 64, 226, 190, 110, 156, 254, 30, 128, 254, 62, 206, 126, 128, 30, 254, 78, 182, 126, 98, 192, 0, 0, 156, 254, 254, 252, 160, 80, 160, 3, 15, 30, 125, 250, 245, 122, 53, 59, 124, 123, 245, 235, 212, 171, 245, 122, 61, 59, 61, 122, 245, 234, 127, 115, 33, 0, 0, 1, 10, 21, 42, 85, 42, 20, 40, 84, 170, 84, 170, 85, 138, 4, 128, 65, 163, 81, 160, 80, 168, 84, 168, 81, 161, 64, 160, 80, 168, 84, 170, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 2, 1, 2, 5, 10, 5, 10, 5, 10, 5, 2, 1, 0, 0,
};

static const char PROGMEM launch_3[] = {
    0, 0, 6, 9, 14, 15, 15, 239, 23, 151, 31, 192, 63, 31, 32, 127, 127, 32, 31, 63, 192, 31, 151, 23, 239, 15, 15, 14, 9, 6, 0, 0, 120, 60, 60, 124, 248, 176, 64, 226, 254, 110, 158, 254, 30, 128, 254, 62, 204, 254, 128, 30, 254, 78, 182, 254, 226, 192, 24, 190, 255, 127, 63, 62, 128, 64, 134, 30, 63, 62, 125, 250, 253, 123, 61, 59, 116, 123, 245, 235, 212, 251, 245, 122, 53, 59, 61, 122, 245, 234, 223, 255, 112, 32, 0, 0, 42, 85, 170, 85, 170, 20, 8, 20, 40, 84, 42, 84, 136, 4, 128, 65, 163, 81, 160, 80, 168, 80, 160, 65, 129, 0, 128, 0, 136, 84, 170, 84, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 5, 2, 1, 2, 1, 2, 1, 2, 5,
};

static const char PROGMEM launch_4[] = {
    0, 0, 6, 9, 14, 15, 15, 239, 23, 151, 31, 192, 63, 31, 32, 127, 127, 32, 31, 63, 192, 31, 151, 23, 239, 15, 15, 14, 9, 6, 0, 0, 248, 248, 240, 240, 224, 128, 64, 226, 62, 206, 62, 254, 30, 128, 254, 174, 94, 254, 128, 30, 254, 28, 230, 126, 226, 192, 0, 192, 240, 248, 252, 252, 129, 64, 128, 0, 25, 62, 117, 234, 245, 122, 117, 107, 116, 107, 253, 251, 244, 235, 117, 58, 21, 27, 125, 234, 245, 234, 215, 255, 103, 35, 1, 1, 170, 85, 170, 81, 160, 64, 160, 80, 168, 84, 40, 80, 160, 64, 160, 81, 171, 81, 168, 84, 168, 64, 128, 64, 129, 0, 0, 20, 170, 84, 170, 84, 0, 1, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 5, 10, 5, 10, 5, 2, 1, 2, 5, 2, 5, 10, 5, 2, 1,
};

static const char PROGMEM launch_5[] = {
    0, 0, 6, 9, 14, 15, 15, 239, 23, 151, 31, 192, 63, 31, 32, 127, 127, 32, 31, 63, 192, 31, 151, 23, 239, 15, 15, 14, 9, 6, 0, 0, 254, 254, 252, 240, 224, 128, 64, 226, 254, 52, 206, 254, 30, 128, 254, 158, 108, 254, 128, 30, 254, 182, 78, 126, 226, 128, 0, 0, 128, 192, 240, 248, 1, 0, 128, 0, 25, 62, 127, 234, 213, 123, 52, 43, 52, 123, 245, 251, 214, 233, 245, 122, 53, 59, 52, 107, 212, 235, 125, 63, 15, 7, 3, 3, 42, 85, 42, 85, 170, 84, 40, 80, 40, 84, 42, 85, 170, 68, 128, 9, 135, 67, 160, 80, 168, 64, 128, 64, 128, 64, 160, 80, 168, 84, 42, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 5, 2, 1, 0, 0, 0, 1, 2, 1, 2, 5, 2, 1, 0, 0, 0, 0,
};

static const char* launch_frames[] = {
    launch_1, launch_2, launch_3, launch_4, launch_5,
};

static const char PROGMEM space_1[] = {
    0, 0,   8, 0, 0,  0, 0, 0, 0, 96, 96,  0,   0,   0,  0,  0,  0,   128, 128, 64,  192, 64, 192, 64, 128, 128, 0,   4,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 0,  0,   0,   224, 152, 38,  1,   17,  132, 32,  241, 224, 160, 80, 137, 66, 1,  3,  165, 14, 56,  224, 0,   0, 0,   128, 0,   0,  0,   0,   0,   0,   0,   0,   0,   3,   14,  53, 104, 84, 174, 221, 174, 92,  178, 85,  175, 213, 186, 81,  98,  52, 14,  3,   0,   0,   1,   3,   1,  0,   4,   0,   1,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   1,   1,   1,   1,   1,   0,   0,   0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0, 0, 0,   0,   32, 112, 32,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   128, 0,   0,   16,  0,  0,   0,  0,  0,   0, 0, 0, 0, 0,
    0, 128, 0, 0, 32, 0, 0, 8, 0, 0,  0,   0,   0,   0,  0,  0,  0,   0,   0,   1,   0,   0,  0,   0,  0,   128, 6,   6,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   6,  76,  12, 24, 16, 48,  96, 192, 128, 128, 0, 0,   0,   0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0,  0,   3,  7,   6,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  32,  0,   1,   3,   134, 252, 56, 0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   240, 248, 12,  6,  6,   12,  12,  12,  7,   3,   0,   0,   0,   0, 0, 192, 192, 0,  0,   0,   0,  1,   0,   0,   0,   0,   0,   0,   0,   0,   192, 224, 112, 57,  31,  6,   0,   0,   128, 64,  48,  80, 208, 96, 64, 128, 0, 0, 0, 0, 0,
    0, 0,   0, 0, 2,  7, 2, 0, 0, 0,  127, 195, 128, 64, 32, 16, 136, 228, 115, 187, 94,  44, 46,  23, 203, 234, 106, 11, 10, 10, 10, 22, 20, 40, 104, 144, 96, 128, 0, 0, 0, 0,  244, 215, 167, 118, 162, 217, 255, 193, 190, 65,  128, 0,   0,  0,   0,  0,  0,  0,   0,  0,   0,   0,   0, 128, 16,  225, 30, 225, 254, 200, 136, 240, 207, 207, 239, 119, 55, 59,  91, 221, 246, 235, 220, 187, 119, 110, 108, 154, 220, 218, 85, 186, 221, 218, 237, 246, 249, 62, 207, 227, 144, 188, 78, 3, 191, 221, 250, 149, 11, 47, 86, 184, 124, 255, 255, 255, 127, 159, 226, 255, 227, 28, 111, 183, 183, 222, 223, 190, 190, 247, 248, 3, 3, 1,   0,   0,  247, 250, 93, 147, 239, 156, 120, 161, 195, 206, 158, 254, 63,  31,  7,   193, 240, 220, 167, 187, 221, 238, 182, 58, 13,  3,  0,  0,   0, 0, 0, 0,
};

static const char PROGMEM space_2[] = {
    0, 0,   8, 0, 0,  0, 0, 0,  32, 112, 32,  0,   0,   0,  0,  0,  0,   128, 128, 64,  192, 64, 192, 64, 128, 128, 0,   12, 12, 0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 0,  0,   0,   224, 152, 38,  1,   17,  132, 32,  241, 224, 160, 80, 137, 66, 1,  3,  165, 14, 56,  224, 0,   0, 0,   0,  0,   0,  0,   0,   0,   0,   0,   0,   0,   3,   14,  53, 104, 84, 174, 221, 174, 92,  178, 85,  175, 213, 186, 81,  98,  52, 14,  3,   0,   0,   0,   1,   2,  0,   4,   0,   1,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   1,   1,   1,   1,   1,   0,   0,   0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0, 0,  0,   0,  32, 112, 32,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   128, 0,   0,   16,  0,  0,   0,  0,  0,   0, 0, 0, 0, 0,
    0, 128, 0, 0, 32, 0, 0, 24, 24, 0,   0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,  0,   0,  0,   131, 7,   6,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   6,  76,  12, 24, 16, 48,  96, 192, 128, 128, 0, 0,   0,  0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0,  0,   0,  2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  32,  0,   1,   3,   134, 252, 56, 0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   240, 248, 12,  6,  6,   12,  12,  12,  7,   3,   0,   0,   0,   0, 64, 224, 64, 0,  0,   0,   0,  1,   0,   0,   0,   0,   0,   0,   0,   0,   192, 224, 112, 57,  31,  6,   0,   0,   128, 64,  48,  80, 208, 96, 64, 128, 0, 0, 0, 0, 0,
    0, 0,   0, 0, 2,  7, 2, 0,  0,  0,   127, 195, 128, 64, 32, 16, 136, 228, 115, 187, 94,  44, 46,  23, 203, 234, 106, 11, 10, 10, 10, 22, 20, 40, 104, 144, 96, 128, 0, 0, 0, 0,  244, 215, 167, 118, 162, 217, 255, 193, 190, 65,  128, 0,   0,  0,   0,  0,  0,  0,   0,  0,   0,   0,   0, 128, 16, 225, 30, 225, 254, 200, 136, 240, 207, 207, 239, 119, 55, 59,  91, 221, 246, 235, 220, 187, 119, 110, 109, 154, 220, 218, 85, 186, 220, 218, 237, 246, 249, 62, 207, 227, 144, 188, 78, 3, 191, 221, 250, 149, 11, 47, 86, 184, 124, 255, 255, 255, 127, 159, 226, 255, 227, 28, 111, 183, 183, 222, 223, 190, 190, 247, 248, 3, 3,  1,   0,  0,  247, 250, 93, 147, 239, 156, 120, 161, 195, 206, 158, 254, 63,  31,  7,   193, 240, 220, 167, 187, 221, 238, 182, 58, 13,  3,  0,  0,   0, 0, 0, 0,
};

static const char PROGMEM space_3[] = {
    0, 0,   8, 0, 0,  0, 0,  0,  0,  32, 64,  0,   0,   0,  0,  0,  0,   128, 128, 64,  192, 64, 192, 64, 128, 128, 4,   14, 4,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 0,  0,   0,   224, 152, 38,  1,   17,  132, 32,  241, 224, 160, 80, 137, 66, 1,  3,  165, 14, 56,  224, 0,   0, 0,   0,  0,   0,  0,   0,   0,   0,   0,   0,   0,   3,   14,  53, 104, 84, 174, 221, 174, 92,  178, 85,  175, 213, 186, 81,  98,  52, 14,  3,   0,   0,   0,   1,   0,  0,   12,  12,  1,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   1,   1,   1,   1,   1,   0,   0,   0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0, 0, 0,  0,   32, 112, 32,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   128, 0,   0,   16,  0,  0,   0,  0,  0,   0, 0, 0, 0, 0,
    0, 128, 0, 0, 32, 0, 12, 28, 24, 0,  0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,  0,   0,  0,   128, 2,   4,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   6,  76,  12, 24, 16, 48,  96, 192, 128, 128, 0, 0,   0,  0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0,  0,   2,  7,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  96,  96,  1,   3,   134, 252, 56, 0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   240, 248, 12,  6,  6,   12,  12,  12,  7,   3,   0,   0,   0,   0, 0, 64, 128, 0,  0,   0,   0,  1,   0,   0,   0,   0,   0,   0,   0,   0,   192, 224, 112, 57,  31,  6,   0,   0,   128, 64,  48,  80, 208, 96, 64, 128, 0, 0, 0, 0, 0,
    0, 0,   0, 0, 2,  7, 2,  0,  0,  0,  127, 195, 128, 64, 32, 16, 136, 228, 115, 187, 94,  44, 46,  23, 203, 234, 106, 75, 10, 10, 10, 22, 20, 40, 104, 144, 96, 128, 0, 0, 0, 0,  244, 215, 167, 118, 162, 217, 255, 193, 190, 65,  128, 0,   0,  0,   0,  1,  0,  0,   0,  128, 0,   0,   0, 128, 16, 225, 30, 225, 254, 200, 136, 240, 207, 207, 239, 119, 55, 59,  91, 221, 246, 235, 220, 187, 119, 110, 109, 154, 220, 218, 85, 186, 221, 218, 237, 246, 249, 62, 207, 227, 144, 188, 78, 3, 191, 221, 250, 149, 11, 47, 86, 184, 124, 255, 255, 255, 127, 159, 226, 255, 227, 28, 111, 183, 183, 222, 223, 190, 190, 247, 248, 3, 3, 1,  0,   0,  247, 250, 93, 147, 239, 156, 120, 161, 195, 206, 158, 254, 63,  31,  7,   193, 240, 220, 167, 187, 221, 238, 182, 58, 13,  3,  0,  0,   0, 0, 0, 0,
};

static const char PROGMEM space_4[] = {
    0, 8,   28, 8, 0,  0, 0, 0, 0,  32, 0,   0,   0,   0,  0,  0,  0,   128, 128, 64,  192, 64, 192, 64, 128, 128, 0,   4,  8,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 0,  0,   0,   224, 152, 38,  1,   17,  132, 32,  241, 224, 160, 80, 137, 66, 1,  3,  165, 14, 56,  224, 0,   0, 0,   0, 0,   0,  0,   0,   0,   0,   0,   0,   0,   3,   14,  53, 104, 84, 174, 221, 174, 92,  178, 85,  175, 213, 186, 81,  98,  52, 14,  3,   0,   0,   0,   1,   0,  4,   14,  4,   1,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   1,   1,   1,   1,   1,   0,   0,   0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0, 0, 0,  0, 32, 112, 32,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   128, 128, 0,   16,  0,  0,   0,  0,  0,   0, 0, 0, 0, 0,
    0, 128, 0,  0, 32, 0, 0, 8, 16, 0,  0,   0,   0,   0,  0,  0,  0,   0,   1,   1,   0,   0,  0,   0,  0,   128, 2,   0,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   6,  76,  12, 24, 16, 48,  96, 192, 128, 128, 0, 0,   0, 0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0,  0,   2,  7,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   48, 112, 96,  1,   3,   134, 252, 56, 0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   240, 248, 12,  6,  6,   12,  12,  12,  7,   3,   0,   0,   0,   0, 0, 64, 0, 0,  0,   0,   0,  1,   0,   0,   0,   0,   0,   0,   0,   0,   192, 224, 112, 57,  31,  6,   0,   0,   128, 64,  48,  80, 208, 96, 64, 128, 0, 0, 0, 0, 0,
    0, 0,   0,  0, 2,  7, 2, 0, 0,  0,  127, 195, 128, 64, 32, 16, 136, 228, 115, 187, 94,  44, 46,  87, 203, 250, 106, 75, 10, 74, 10, 22, 20, 40, 104, 144, 96, 128, 0, 0, 0, 0,  244, 215, 167, 118, 162, 217, 255, 193, 190, 65,  128, 0,   0,  0,   2,  1,  0,  0,   0,  0,   0,   0,   0, 128, 0, 225, 30, 225, 254, 200, 136, 240, 207, 207, 239, 119, 55, 59,  91, 221, 246, 235, 220, 187, 119, 110, 108, 152, 220, 216, 84, 186, 220, 218, 237, 246, 249, 62, 207, 227, 144, 188, 78, 3, 191, 221, 250, 149, 11, 47, 86, 184, 124, 255, 255, 255, 127, 159, 226, 255, 227, 28, 111, 183, 183, 222, 223, 190, 190, 247, 248, 3, 3, 1,  0, 0,  247, 250, 93, 147, 239, 156, 120, 161, 195, 206, 158, 254, 63,  31,  7,   193, 240, 220, 167, 187, 221, 238, 182, 58, 13,  3,  0,  0,   0, 0, 0, 0,
};

static const char PROGMEM space_5[] = {
    0, 0,   8, 0, 0,  0, 0, 0, 0, 32, 0,   0,   0,   0,  0,  0,  0,   128, 128, 64,  192, 64, 192, 64, 128, 128, 0,   4,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 0,  0,   0,   224, 152, 38,  1,   17,  132, 32,  241, 224, 160, 80, 137, 66, 1,  3,  165, 14, 56,  224, 0,   0, 0,   0,  0,   0,  0,   0,   0,   0,   0,   0,   0,   3,   14,  53, 104, 84, 174, 221, 174, 92,  178, 85,  175, 213, 186, 81,  98,  52, 14,  3,   0,   0,   0,   1,   0,  0,   4,   8,   1,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   1,   1,   1,   1,   1,   0,   0,   0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0, 0, 0, 0, 32, 112, 32,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   128, 192, 128, 0,   16,  0,  0,   0,  0,  0,   0, 0, 0, 0, 0,
    0, 128, 0, 0, 32, 0, 0, 8, 0, 0,  0,   0,   0,   0,  0,  0,  0,   0,   1,   0,   0,   0,  0,   0,  0,   128, 2,   0,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,   0, 0, 0, 32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   6,  76,  12, 24, 16, 48,  96, 192, 128, 128, 0, 0,   0,  0,   0,  0,   0,   0,   64,  0,   0,   0,   0,   0,   0,  0,   0,  2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  32,  64,  1,   3,   134, 252, 56, 0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   240, 248, 12,  6,  6,   12,  12,  12,  7,   3,   0,   0,   0,   0, 0, 0, 0, 0,  0,   0,   0,  1,   0,   0,   0,   0,   0,   0,   0,   0,   192, 224, 112, 57,  31,  6,   0,   0,   128, 64,  48,  80, 208, 96, 64, 128, 0, 0, 0, 0, 0,
    0, 0,   0, 0, 2,  7, 2, 0, 0, 0,  127, 195, 128, 64, 32, 16, 136, 228, 115, 187, 94,  44, 46,  23, 203, 234, 106, 11, 10, 10, 10, 22, 20, 40, 104, 144, 96, 128, 0, 0, 0, 0,  244, 215, 167, 118, 162, 217, 255, 193, 190, 65,  128, 0,   0,  0,   0,  0,  0,  0,   0,  0,   0,   0,   0, 128, 16, 225, 30, 225, 254, 200, 136, 240, 207, 207, 239, 119, 55, 59,  91, 221, 246, 235, 220, 187, 119, 110, 109, 154, 220, 216, 84, 186, 220, 218, 237, 246, 249, 62, 207, 227, 144, 188, 78, 3, 191, 221, 250, 149, 11, 47, 86, 184, 124, 255, 255, 255, 127, 159, 226, 255, 227, 28, 111, 183, 183, 222, 223, 190, 190, 247, 248, 3, 3, 1, 0, 0,  247, 250, 93, 147, 239, 156, 120, 161, 195, 206, 158, 254, 63,  31,  7,   193, 240, 220, 167, 187, 221, 238, 182, 58, 13,  3,  0,  0,   0, 0, 0, 0,
};

static const char* space_frames[] = {
    space_1, space_2, space_3, space_4, space_5,
};

static const char PROGMEM mod_gui_off_1[] = {
    0, 56, 124, 108, 252, 248, 96, 96, 96, 248, 252, 108, 124, 56, 0, 0,
};

static const char PROGMEM mod_gui_off_2[] = {
    0, 56, 124, 108, 127, 63, 12, 12, 12, 63, 127, 108, 124, 56, 0, 0,
};

static const char PROGMEM mod_gui_on_1[] = {
    252, 198, 130, 146, 2, 6, 158, 158, 158, 6, 2, 146, 130, 198, 252, 0,
};

static const char PROGMEM mod_gui_on_2[] = {
    127, 199, 131, 147, 128, 192, 243, 243, 243, 192, 128, 147, 131, 199, 127, 0,
};

static const char PROGMEM mod_alt_off_1[] = {
    0, 0, 0, 24, 24, 24, 120, 240, 192, 0, 24, 24, 24, 24, 0, 0,
};

static const char PROGMEM mod_alt_off_2[] = {
    0, 0, 0, 0, 0, 0, 0, 1, 7, 31, 60, 48, 48, 48, 0, 0,
};

static const char PROGMEM mod_alt_on_1[] = {
    0, 252, 254, 230, 230, 230, 134, 14, 62, 254, 230, 230, 230, 230, 254, 252,
};

static const char PROGMEM mod_alt_on_2[] = {
    0, 127, 255, 255, 255, 255, 255, 254, 248, 224, 195, 207, 207, 207, 255, 127,
};

static const char PROGMEM mod_ctrl_off_1[] = {
    0, 0, 128, 192, 224, 112, 56, 24, 56, 112, 224, 192, 128, 0, 0, 0,
};

static const char PROGMEM mod_ctrl_off_2[] = {
    0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0,
};

static const char PROGMEM mod_ctrl_on_1[] = {
    252, 254, 126, 62, 30, 142, 198, 230, 198, 142, 30, 62, 126, 254, 252, 0,
};

static const char PROGMEM mod_ctrl_on_2[] = {
    127, 254, 252, 254, 255, 255, 255, 255, 255, 255, 255, 254, 252, 254, 127, 0,
};

static const char PROGMEM mod_shift_off_1[] = {
    0, 0, 0, 128, 192, 224, 112, 56, 24, 56, 112, 224, 192, 128, 0, 0,
};

static const char PROGMEM mod_shift_off_2[] = {
    0, 0, 3, 7, 7, 62, 126, 96, 96, 96, 126, 62, 7, 7, 3, 0,
};

static const char PROGMEM mod_shift_on_1[] = {
    0, 252, 254, 126, 62, 30, 142, 198, 230, 198, 142, 30, 62, 126, 254, 252,
};

static const char PROGMEM mod_shift_on_2[] = {
    0, 127, 252, 248, 248, 193, 129, 159, 159, 159, 129, 193, 248, 248, 252, 127,
};

void fp_render_mod_status_gui_alt(uint8_t modifiers) {
    oled_set_cursor(0, 14);
    if (modifiers & MOD_MASK_GUI && modifiers & MOD_MASK_ALT) {
        oled_write_raw_P(mod_gui_on_1, sizeof(mod_gui_on_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_alt_on_1, sizeof(mod_alt_on_1));
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_raw_P(mod_gui_on_1, sizeof(mod_gui_on_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_alt_off_1, sizeof(mod_alt_off_1));
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_raw_P(mod_gui_off_1, sizeof(mod_gui_off_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_alt_on_1, sizeof(mod_alt_on_1));
    } else {
        oled_write_raw_P(mod_gui_off_1, sizeof(mod_gui_off_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_alt_off_1, sizeof(mod_alt_off_1));
    }

    oled_set_cursor(0, 15);

    if (modifiers & MOD_MASK_GUI && modifiers & MOD_MASK_ALT) {
        oled_write_raw_P(mod_gui_on_2, sizeof(mod_gui_on_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_alt_on_2, sizeof(mod_alt_on_2));
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_raw_P(mod_gui_on_2, sizeof(mod_gui_on_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_alt_off_2, sizeof(mod_alt_off_2));
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_raw_P(mod_gui_off_2, sizeof(mod_gui_off_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_alt_on_2, sizeof(mod_alt_on_2));
    } else {
        oled_write_raw_P(mod_gui_off_2, sizeof(mod_gui_off_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_alt_off_2, sizeof(mod_alt_off_2));
    }
}

void fp_render_mod_status_ctrl_shift(uint8_t modifiers) {
    oled_set_cursor(0, 14);

    if (modifiers & MOD_MASK_CTRL && modifiers & MOD_MASK_SHIFT) {
        oled_write_raw_P(mod_ctrl_on_1, sizeof(mod_ctrl_on_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_shift_on_1, sizeof(mod_shift_on_1));
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_raw_P(mod_ctrl_on_1, sizeof(mod_ctrl_on_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_shift_off_1, sizeof(mod_shift_off_1));
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_raw_P(mod_ctrl_off_1, sizeof(mod_ctrl_off_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_shift_on_1, sizeof(mod_shift_on_1));
    } else {
        oled_write_raw_P(mod_ctrl_off_1, sizeof(mod_ctrl_off_1));
        oled_set_cursor(2, 14);
        oled_write_raw_P(mod_shift_off_1, sizeof(mod_shift_off_1));
    }

    oled_set_cursor(0, 15);

    if (modifiers & MOD_MASK_CTRL && modifiers & MOD_MASK_SHIFT) {
        oled_write_raw_P(mod_ctrl_on_2, sizeof(mod_ctrl_on_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_shift_on_2, sizeof(mod_shift_on_2));
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_raw_P(mod_ctrl_on_2, sizeof(mod_ctrl_on_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_shift_off_2, sizeof(mod_shift_off_2));
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_raw_P(mod_ctrl_off_2, sizeof(mod_ctrl_off_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_shift_on_2, sizeof(mod_shift_on_2));
    } else {
        oled_write_raw_P(mod_ctrl_off_2, sizeof(mod_ctrl_off_2));
        oled_set_cursor(2, 15);
        oled_write_raw_P(mod_shift_off_2, sizeof(mod_shift_off_2));
    }
}

static const char PROGMEM layer_default[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 56, 56, 56, 56, 56, 56, 16, 0, 0, 0, 0, 0, 0, 0, 0, 16, 56, 56, 56, 56, 56, 56, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

static const char PROGMEM layer_raise[] = {
    0, 224, 240, 224, 0, 0, 0, 0, 0, 0, 0, 0, 224, 240, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 240, 224, 0, 0, 199, 239, 199, 16, 56, 56, 56, 56, 56, 56, 16, 199, 239, 199, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 199, 239, 199, 0, 0, 15, 31, 15, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 15, 0,
};

static const char PROGMEM layer_lower[] = {
    0, 224, 240, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 240, 224, 8, 28, 28, 28, 28, 28, 28, 8, 224, 240, 224, 0, 0, 199, 239, 199, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 199, 239, 199, 0, 0, 0, 0, 0, 0, 0, 0, 199, 239, 199, 0, 0, 15, 31, 15, 32, 112, 112, 112, 112, 112, 112, 32, 0, 0, 0, 0, 0, 15, 31, 15, 32, 112, 112, 112, 112, 112, 112, 32, 15, 31, 15, 0,
};

static const char PROGMEM layer_adjust[] = {
    0, 224, 240, 224, 8, 28, 28, 28, 28, 28, 28, 8, 224, 240, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 240, 224, 0, 0, 199, 239, 199, 16, 56, 56, 56, 56, 56, 56, 16, 199, 239, 199, 0, 0, 192, 224, 192, 16, 56, 56, 56, 56, 56, 56, 16, 199, 239, 199, 0, 0, 15, 31, 15, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 15, 0, 0, 15, 31, 15, 32, 112, 112, 112, 112, 112, 112, 32, 15, 31, 15, 0,
};

static const char PROGMEM layer_play[] = {
    0, 224, 240, 224, 8, 28, 28, 28, 28, 28, 28, 8, 224, 240, 224, 0, 0, 224, 240, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 199, 239, 199, 16, 56, 56, 56, 56, 56, 56, 16, 7, 15, 7, 0, 0, 199, 239, 199, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 15, 32, 112, 112, 112, 112, 112, 112, 32, 0, 0, 0, 0,
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}


void fp_render_layer_state(void) {
    oled_set_cursor(0, 11);

    if (layer_state_is(_ADJUST)) {
        oled_write_raw_P(layer_play, sizeof(layer_play));
    } else if (layer_state_is(_ADJUST)) {
        oled_write_raw_P(layer_adjust, sizeof(layer_adjust));
    } else if (layer_state_is(_LOWER)) {
        oled_write_raw_P(layer_lower, sizeof(layer_lower));
    } else if (layer_state_is(_RAISE)) {
        oled_write_raw_P(layer_raise, sizeof(layer_raise));
    } else {
        oled_write_raw_P(layer_default, sizeof(layer_default));
    }
}

void fp_render_modifier_state(void) {
    uint8_t modifiers = get_mods() | get_oneshot_mods();

    oled_set_cursor(0, 15);
    // oled_write_char(shift, modifiers & MOD_MASK_SHIFT);
    // oled_set_cursor(1, 15);
    // oled_write_char(control, modifiers & MOD_MASK_CTRL);
    // oled_set_cursor(2, 15);
    // oled_write_char(option, modifiers & MOD_MASK_ALT);
    // oled_set_cursor(3, 15);
    // oled_write_char(command, modifiers & MOD_MASK_GUI);

    oled_write_P(PSTR("C"), modifiers & MOD_MASK_CTRL);
    oled_write_P(PSTR("O"), modifiers & MOD_MASK_ALT);
    oled_write_P(PSTR("S"), modifiers & MOD_MASK_SHIFT);
    oled_write_P(PSTR("M"), modifiers & MOD_MASK_GUI);
}

#define FRAME_TIME 350

uint8_t         current_frame     = -1;
static uint32_t frame_timer       = 0;
static uint32_t animation_timeout = 0;

static void render_animation(const char** frames, size_t frame_size, const uint8_t frames_length, const uint8_t col, const uint8_t line) {
    if (timer_elapsed32(animation_timeout) > OLED_TIMEOUT) {
        // Stop animating so display can go to sleep
        oled_off();
        return;
    }

    if (timer_elapsed32(frame_timer) < FRAME_TIME) {
        return;
    }

    current_frame = (current_frame + 1) % frames_length;
    frame_timer   = timer_read32();

    oled_set_cursor(col, line);
    oled_write_raw_P(frames[current_frame], frame_size);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        animation_timeout = timer_read32();
        frame_timer       = timer_read32();
        oled_on();
    }

    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_raw_P(shuttle, sizeof(shuttle));
        render_animation(launch_frames, sizeof(launch_1), 5, 0, 5);
        fp_render_layer_state();
        fp_render_modifier_state();
    } else {
        render_animation(space_frames, sizeof(space_1), 5, 0, 0);
    }

    return false;
}

bool should_process_keypress(void) {
    return true;
}

// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// // This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
//     &delete_key_override,
//     NULL // Null terminate the array of overrides!
// };

#endif
/*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸*/
