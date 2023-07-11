
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
KEY_OVERRIDE_ENABLE = yes

// no mousekeys
MOUSEKEY_ENABLE = no        # Mouse keys

// to reduce size of firmware
// https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
// Add these flags to your rules.mk file: EXTRAFLAGS += -flto
// Drashna, on QMK issue 3224, paraphrased
EXTRAFLAGS += -flto

COMBO_ENABLE = yes
