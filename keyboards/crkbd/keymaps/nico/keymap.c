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


#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define CTLTB CTL_T(KC_TAB)
#define GUIEI GUI_T(KC_LNG2)
#define ALTKN ALT_T(KC_LNG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTLTB,   KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                        GUIEI,    LOWER,   KC_SPC,  KC_ENT,  RAISE,   ALTKN
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    CTLTB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
    KC_LSFT, KC_F11,  KC_F12,  KC_F13,  KC_F14,   KC_F15,                    KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  XXXXXXX,
                                        GUIEI,    LOWER,   KC_SPC,  KC_ENT,  RAISE,   ALTKN
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    CTLTB,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
                                        GUIEI,   LOWER,   KC_SPC,  KC_ENT,  RAISE,   ALTKN

  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        GUIEI,   LOWER,   KC_SPC,  KC_ENT,  RAISE,   ALTKN
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_90;
    }
}


#    define KEYLOG_LEN 5
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_mod_status(get_mods());
    render_bootmagic_status();

    render_keylogger_status();
}

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


bool oled_task_user(void) {
    update_log();
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        //render_crkbd_logo();
        render_animation(space_frames, sizeof(space_1), 5, 0, 0);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}
#endif
