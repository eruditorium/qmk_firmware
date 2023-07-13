MOUSEKEY_ENABLE = no        # Mouse keys
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6

# to reduce size of firmware
# https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
# Add these flags to your rules.mk file: EXTRAFLAGS += -flto
# Drashna, on QMK issue 3224, paraphrased
EXTRAFLAGS += -flto

DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = no
EXTRAKEY_ENABLE = yes

# https://docs.qmk.fm/#/feature_caps_word
# make sure COMMAN_ENABLE = no
CAPS_WORD_ENABLE = yes

SRC += features/select_word.c
