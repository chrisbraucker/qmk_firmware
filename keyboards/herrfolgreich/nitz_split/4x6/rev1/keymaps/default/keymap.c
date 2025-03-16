// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _DEFAULT,
    _1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Default Layer:

        ESC             1           2           3           4           5                                                               6           7           8           9           0           ß
        +/\*            Q           W           E           R           T                                                               Z           U           I           O           P           Ü
        #/'             A           S           D           F           G                                                               H           J           K           L           Ö           Ä
        LT(1,^)         Y           X           C           V           B                                                               N           M           ,           .           -           LT(1,´)
                                    M1          M2                      JS      LSFT_T(RET)     SPACE          SPACE        META        BCKSP                   XXX         XXX
                                                                                LCTRL           LALT           RSHIFT       RALT
     */
    [_DEFAULT] = LAYOUT(
        KC_ESC,         KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                                           KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
        KC_RBRC,        KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                                           KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
        KC_NUHS,        KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                                           KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        LT(_1, KC_GRV), KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                                                           KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    LT(_1,KC_EQL),
                                    MS_BTN1,    MS_BTN2,                        LSFT_T(KC_ENT), KC_SPC,         KC_SPC,     KC_RSFT,    KC_BSPC,                KC_PGDN,    KC_PGUP,
                                                                                KC_LCTL,        KC_LALT,        KC_RGUI,    KC_RALT
    ),
    /*
        Layer 1:

        F1              F2          F3          F4          F5          F6                                                              F7          F8          F9          F10         F11         F12
        TAB             _           BRI-        BRI+        _           SLEEP                                                           _           _           UP          _           _           _
        CAPS            PREV        STOP        PLAY        NEXT        _                                                               _           LEFT        DOWN        RIGHT       _           _
        _               <           VOL-        MUTE        VOL+        REBOOT                                                          _           _           _           _           _           _
                                    _           _                               _               _               INS         HOME        _                       XXX         XXX
                                                                                _               _               DEL         END
    */
    [_1] = LAYOUT(
        KC_F1,          KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                                                          KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
        KC_TAB,         _______,    KC_BRID,    KC_BRIU,    _______,    KC_SLEP,                                                        _______,    _______,    KC_UP,      _______,    _______,    _______,
        KC_CAPS,        KC_MPRV,    KC_MSTP,    KC_MPLY,    KC_MNXT,    KC_PWR,                                                         _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   _______,    _______,
        KC_TRNS,        KC_NUBS,    KC_VOLD,    KC_MUTE,    KC_VOLU,    _______,                                                        _______,    _______,    _______,    _______,    _______,    _______,
                                    _______,    _______,                        QK_RBT,         QK_BOOT,        KC_INS,     KC_HOME,    KC_DEL,                 _______,    _______,
                                                                                _______,        _______,        _______,    KC_END
    )
};


#ifdef OLED_ENABLE
bool oled_task_user(void) {

    oled_write_P(PSTR("Layer\n"), true);
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR(" Def\n"), false);
            break;
        case _1:
            oled_write_P(PSTR(" Fn\n"), false);
            break;
        default:
            oled_write_P(PSTR(" ???\n"), false);
    }

    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\nMods \n"), true);
    oled_write_P(led_state.caps_lock ? PSTR(">CAP<") : PSTR(" CAP\n"), false);
    return true;
}
#endif
