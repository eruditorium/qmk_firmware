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
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
    // 'Astronaut', 32x128px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x1f, 0x00, 0x00, 0x00, 0x6a, 0xc0,
    0x00, 0x01, 0x91, 0x70, 0x00, 0x02, 0x00, 0xa8, 0x00, 0x02, 0x40, 0x18, 0x00, 0x04, 0x01, 0x0c,
    0x00, 0x04, 0x92, 0x04, 0x00, 0x0a, 0x3c, 0x16, 0x00, 0x08, 0x1a, 0x82, 0x00, 0x0c, 0x5d, 0x12,
    0x00, 0x0a, 0x23, 0xa2, 0x00, 0x0c, 0x55, 0x56, 0x00, 0x06, 0xfb, 0x8c, 0x00, 0x05, 0x79, 0x44,
    0x00, 0x02, 0xae, 0xe8, 0x00, 0x03, 0x55, 0x58, 0x00, 0x01, 0xaa, 0xb0, 0x20, 0x00, 0x75, 0xc0,
    0x71, 0x00, 0x1f, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0xc0, 0x00, 0x00, 0x1c, 0xf0, 0x00, 0x00, 0x0c, 0x38, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x21, 0x80, 0x10, 0x00, 0x00, 0xe0, 0x00, 0x00,
    0x00, 0x30, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x80, 0x03, 0x18, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x0c, 0xe0, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x30, 0x00, 0x18, 0x00, 0x30, 0x00,
    0x0c, 0x00, 0x00, 0x10, 0x06, 0x00, 0x00, 0x38, 0x06, 0x00, 0x00, 0x10, 0x0c, 0x00, 0x00, 0x00,
    0x1c, 0x1c, 0x00, 0x00, 0x38, 0x12, 0x00, 0x00, 0x70, 0x2f, 0x00, 0x00, 0x60, 0x44, 0x80, 0x00,
    0xc0, 0xc6, 0x40, 0x00, 0xc0, 0xef, 0xfc, 0x00, 0x81, 0x3c, 0x06, 0x00, 0x82, 0x7b, 0xf9, 0x80,
    0x84, 0xe4, 0x06, 0x40, 0x89, 0xd9, 0x81, 0xa0, 0xd1, 0xa3, 0x80, 0xa0, 0x63, 0x43, 0x00, 0x50,
    0x67, 0x40, 0x00, 0x50, 0x7a, 0x80, 0x00, 0x28, 0xf2, 0x80, 0x00, 0x28, 0x06, 0x80, 0x00, 0x2e,
    0xd6, 0x80, 0x00, 0xa9, 0xba, 0x80, 0x00, 0x59, 0xd7, 0x40, 0x00, 0x5d, 0xef, 0xa0, 0x01, 0x5f,
    0xff, 0x58, 0x2a, 0xb1, 0xfe, 0xdd, 0x55, 0x73, 0xf9, 0xae, 0xab, 0x66, 0xe7, 0x77, 0xde, 0xe6,
    0x1f, 0xb9, 0xfd, 0xcc, 0x3c, 0xde, 0x13, 0xd4, 0xf3, 0xee, 0xef, 0xb2, 0xe1, 0xf1, 0xdf, 0xbc,
    0xdc, 0x7d, 0xba, 0x5c, 0xae, 0x7f, 0xbf, 0xd8, 0xd6, 0xfd, 0x7f, 0xc0, 0xed, 0xfd, 0x67, 0xa0,
    0xf3, 0xfd, 0x5f, 0xe0, 0xa5, 0xfb, 0xb9, 0xe0, 0x62, 0xfb, 0xa6, 0x60, 0xf1, 0x77, 0x9f, 0xe0,
    0xb9, 0x8f, 0x38, 0xc0, 0xd8, 0xfe, 0x37, 0x40, 0xac, 0x7e, 0x6e, 0x80, 0x6e, 0x7c, 0x5d, 0x80,
    0xf6, 0x3c, 0xdb, 0x00, 0xcb, 0x18, 0xb7, 0x00, 0xea, 0xd1, 0xcc, 0x00, 0xdd, 0xf1, 0xfe, 0x00};
    oled_write_P(crkbd_logo, false);
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

bool oled_task_user(void) {
    update_log();
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
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
