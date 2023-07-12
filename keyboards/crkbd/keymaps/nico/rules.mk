
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
KEY_OVERRIDE_ENABLE = yes

MOUSEKEY_ENABLE = no        # Mouse keys
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6

RGB_MATRIX_ENABLE = yes

# to reduce size of firmware
# https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
# Add these flags to your rules.mk file: EXTRAFLAGS += -flto
# Drashna, on QMK issue 3224, paraphrased
EXTRAFLAGS += -flto

DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = no
EXTRAKEY_ENABLE = yes