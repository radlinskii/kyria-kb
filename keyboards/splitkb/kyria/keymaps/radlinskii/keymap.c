// Copyright 2022 Ignacy Radliński (@radlinskii)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "light_layers.h"

#include <stdio.h>
char wpm_str[14];

enum my_layers {
    _COLEMAK,
    _QWERTY,
    _NUM_SYM,
    _NAV,
    _MOUSE,
    _MEDIA_MISC,
};

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY,
    DEFAULT
};

#define LALT_KA LALT_T(KC_A)
#define LCTL_KS LCTL_T(KC_S)
#define LGUI_KD LGUI_T(KC_D)
#define LSFT_KF LSFT_T(KC_F)
#define RSFT_KJ RSFT_T(KC_J)
#define RGUI_KK RGUI_T(KC_K)
#define RCTL_KL RCTL_T(KC_L)
#define RA_SCLN RALT_T(KC_SCLN)

#define LALT_K1 LALT_T(KC_1)
#define LCTL_K2 LCTL_T(KC_2)
#define LGUI_K3 LGUI_T(KC_3)
#define LSFT_K4 LSFT_T(KC_4)
#define RSFT_K7 RSFT_T(KC_7)
#define RGUI_K8 RGUI_T(KC_8)
#define RCTL_K9 RCTL_T(KC_9)
#define RALT_K0 RALT_T(KC_0)

#define LCTL_KR LCTL_T(KC_R)
#define LGUI_KS LGUI_T(KC_S)
#define LSFT_KT LSFT_T(KC_T)
#define RSFT_KN RSFT_T(KC_N)
#define RGUI_KE RGUI_T(KC_E)
#define RCTL_KI RCTL_T(KC_I)
#define RALT_KO RALT_T(KC_O)

#define LGUI_BS LGUI_T(KC_BSPC)
#define RALT_TB RALT_T(KC_TAB)

#define TT_N_S TT(_NUM_SYM)
#define TT_NAV TT(_NAV)
#define TO_QWRT TO(_QWERTY)
#define TO_N_S TO(_NUM_SYM)
#define TO_NAV TO(_NAV)
#define TO_MOUSE TO(_MOUSE)
#define TO_M_M TO(_MEDIA_MISC)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX , KC_Q   ,  KC_W  ,  KC_F  ,   KC_P ,   KC_B ,                                                          KC_J  ,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX , LALT_KA, LCTL_KR, LGUI_KS, LSFT_KT,   KC_G ,                                                           KC_M , RSFT_KN, RGUI_KE, RCTL_KI, RALT_KO, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────── ─┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX , KC_Z   ,  KC_X  ,  KC_C  ,   KC_D ,   KC_V , KC_DEL, KC_CAPS,                      _______, KC_ESC, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, KC_BSPC,  TT_N_S, KC_ENT , _______,                   _______, KC_SPC ,  TT_NAV,  KC_TAB, KC_QUOT
                              // └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_QWERTY] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,  KC_Q  ,  KC_W  ,  KC_E  ,   KC_R ,   KC_T ,                                                          KC_Y,   KC_U ,  KC_I  ,   KC_O ,   KC_P , XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX , LALT_KA, LCTL_KS, LGUI_KD, LSFT_KF,   KC_G ,                                                          KC_H, RSFT_KJ, RGUI_KK, RCTL_KL, RA_SCLN, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,  KC_DEL, KC_CAPS,                    _______, KC_ESC,     KC_N,   KC_M , KC_COMM, KC_DOT , KC_SLSH, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, KC_BSPC, TT_N_S,  KC_ENT , _______,                   _______, KC_SPC ,  TT_NAV, KC_TAB , KC_QUOT
                              // └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_NUM_SYM] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_PLUS, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, LALT_K1, LCTL_K2, LGUI_K3, LSFT_K4,    KC_5,                                                          KC_6, RSFT_K7, RGUI_K8, RCTL_K9, RALT_K0, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_QUOT, KC_GRV,  KC_LPRN, KC_LCBR, KC_LBRC, _______, _______,                   _______, _______, KC_RBRC, KC_RCBR, KC_RPRN,  KC_MINS, KC_EQL, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, DEFAULT, _______, _______,                   _______, _______, TO_NAV,  _______, KC_BSLS
                              // └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_NAV] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, _______, _______, _______, _______, _______,                                                       _______, KC_PGDN, KC_UP,   KC_PGUP, _______, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______,                                                       KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────── ─┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, DEFAULT, _______, _______,                   _______, _______,TO_MOUSE, _______, _______
                              // └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_MOUSE] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, _______, _______, _______, _______, _______,                                                       _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______,                                                       KC_WH_R, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_L, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────── ─┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, DEFAULT, KC_BTN2, _______,                   _______, KC_BTN1, TO_NAV , KC_BTN2, TO_M_M
                              // └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_MEDIA_MISC] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, _______, _______, KC_MUTE, _______,  QWERTY,                                                       COLEMAK, _______, _______, _______, _______, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_MPLY, KC_MNXT, KC_VOLU, KC_BRIU, _______,                                                      RGB_TOG , RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────── ─┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_MSTP, KC_MPRV, KC_VOLD, KC_BRID, _______, _______, _______,                   _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD,RGB_RMOD, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, DEFAULT, _______, _______,                  _______, _______, DEFAULT, _______, _______
                              // └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
                layer_move(_COLEMAK);
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
                layer_move(_QWERTY);
            }
            return false;
        case DEFAULT:
            if (record->event.pressed) {
                if (layer_state_cmp(default_layer_state, _COLEMAK)) {
                    layer_move(_COLEMAK);
                } else if (layer_state_cmp(default_layer_state, _QWERTY)) {
                    layer_move(_QWERTY);
                }
            }
            return false;
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_left()) {

        // Host Keyboard Layer Status
        oled_write_P(PSTR(" Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _COLEMAK:
                oled_write_P(PSTR("COLEMAK\n\n"), false);
                break;
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n\n"), false);
                break;
            case _NUM_SYM:
                oled_write_P(PSTR("NUM / SYM\n\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("NAV\n\n"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("MOUSE\n\n"), false);
                break;
            case _MEDIA_MISC:
                oled_write_P(PSTR("MEDIA\n\n"), false);
                break;
            default:
                oled_write_P(PSTR("UNDEFINED\n\n"), false);
        }

        sprintf(wpm_str, "   WPM: %03d\n\n", get_current_wpm());  // edit the string to change wwhat shows up, edit %03d to change how many digits show up
        oled_write(wpm_str, false);                       // writes wpm on top left corner of string

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.caps_lock   ? PSTR("      * CAPSLOCK \n\n") : PSTR("                 \n\n"), false);

        oled_set_cursor(0, 7);
        oled_write_P(PSTR("        Kyria rev2.1\n"), false);
    } else {
        oled_write_P(PSTR("TODO:\n\n"), false);
        oled_write_P(PSTR("- find a job\n"), false);
        oled_write_P(PSTR("- learn rust\n"), false);
        oled_write_P(PSTR("- add oled animation\n\n"), false);

    };

    return false;
}


void keyboard_post_init_user(void) {
    rgblight_layers = MY_LIGHT_LAYERS;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_COLEMAK, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(_QWERTY, layer_state_cmp(state, _QWERTY));

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_NUM_SYM, layer_state_cmp(state, _NUM_SYM));
    rgblight_set_layer_state(_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_MOUSE, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(_MEDIA_MISC, layer_state_cmp(state, _MEDIA_MISC));

    return state;
}
