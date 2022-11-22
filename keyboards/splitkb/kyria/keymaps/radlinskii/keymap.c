// Copyright 2022 Ignacy Radliński (@radlinskii)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdio.h>

#include QMK_KEYBOARD_H
#include "light_layers.h"
#include "oled_animation.h"

char wpm_str[14];

enum my_layers {
    _COLEMAK,
    _QWERTY,
    _NUM,
    _SYM,
    _NAV,
    _MOUSE,
    _MEDIA_FN,
};

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY
};

// COLEMAK
#define LALT_KA LALT_T(KC_A)
#define LCTL_KR LCTL_T(KC_R)
#define LGUI_KS LGUI_T(KC_S)
#define LSFT_KT LSFT_T(KC_T)
#define RSFT_KN RSFT_T(KC_N)
#define RGUI_KE RGUI_T(KC_E)
#define RCTL_KI RCTL_T(KC_I)
#define RALT_KO RALT_T(KC_O)

// QWERTY
// #define LALT_KA LALT_T(KC_A)
#define LCTL_KS LCTL_T(KC_S)
#define LGUI_KD LGUI_T(KC_D)
#define LSFT_KF LSFT_T(KC_F)
#define RSFT_KJ RSFT_T(KC_J)
#define RGUI_KK RGUI_T(KC_K)
#define RCTL_KL RCTL_T(KC_L)
#define RA_SCLN RALT_T(KC_SCLN)

// NUM
#define LALT_K1 LALT_T(KC_1)
#define LCTL_K2 LCTL_T(KC_2)
#define LGUI_K3 LGUI_T(KC_3)
#define LSFT_K4 LSFT_T(KC_4)
#define RSFT_K7 RSFT_T(KC_7)
#define RGUI_K8 RGUI_T(KC_8)
#define RCTL_K9 RCTL_T(KC_9)
#define RALT_K0 RALT_T(KC_0)

// SYM
#define LAL_GRV LALT_T(KC_GRV)
#define LSF_QT LSFT_T(KC_QUOT)
#define RSF_MIN RSFT_T(KC_MINS)
#define RAL_EQL RALT_T(KC_EQL)

// MISC
#define KC_CAPW LGUI(LSFT(KC_3)) // capture the whole screen on MacOS
#define KC_CAPP LGUI(LSFT(KC_5)) // capture portion of the screen on MacOS

// LAYERS
#define MO_SYM MO(_SYM)
#define MO_NAV MO(_NAV)
#define MS_ENT LT(_MOUSE, KC_ENT)
#define NUM_SPC LT(_NUM, KC_SPC)
#define MF_TAB LT(_MEDIA_FN, KC_TAB)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                                          KC_J,    KC_L,    KC_U,   KC_Y , KC_SCLN, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, LALT_KA, LCTL_KR, LGUI_KS, LSFT_KT,    KC_G,                                                          KC_M, RSFT_KN, RGUI_KE, RCTL_KI, RALT_KO, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V, XXXXXXX, KC_CAPS,                   KC_CAPW, KC_CAPP,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   XXXXXXX, KC_BSPC,  MO_NAV,  MS_ENT,  KC_DEL,                    KC_ESC, NUM_SPC,  MO_SYM,  MF_TAB, XXXXXXX
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_QWERTY] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                          KC_Y,    KC_U,   KC_I,     KC_O,    KC_P, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, LALT_KA, LCTL_KS, LGUI_KD, LSFT_KF,    KC_G,                                                          KC_H, RSFT_KJ, RGUI_KK, RCTL_KL, RA_SCLN, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, XXXXXXX, KC_CAPS,                   KC_CAPW, KC_CAPP,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   XXXXXXX, KC_BSPC,  MO_NAV,  MS_ENT,  KC_DEL,                    KC_ESC, NUM_SPC,  MO_SYM,  MF_TAB, XXXXXXX
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_NUM] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, LALT_K1, LCTL_K2, LGUI_K3, LSFT_K4,    KC_5,                                                          KC_6, RSFT_K7, RGUI_K8, RCTL_K9, RALT_K0, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_SYM] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC,                                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE, KC_BSLS, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, LAL_GRV, KC_LCTL, KC_LGUI,  LSF_QT,  KC_DQT,                                                       KC_UNDS, RSF_MIN, KC_RGUI, KC_RCTL, RAL_EQL, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX,KC_TILDE, KC_LABK, KC_LPRN, KC_LCBR, KC_LBRC, _______, _______,                   _______, _______, KC_RBRC, KC_RCBR, KC_RPRN, KC_RABK, KC_PLUS, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_NAV] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, _______, _______, _______, _______, _______,                                                       _______, KC_PGDN, KC_UP,   KC_PGUP, _______, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, _______,                                                       KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_MOUSE] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, _______, _______, _______, _______, _______,                                                       _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, _______,                                                       KC_WH_R, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_L, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, _______, _______, _______, _______, _______,   RESET, _______,                   _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, _______, _______, _______,                   _______, KC_BTN1, KC_BTN2, KC_BTN3, _______
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
    ),

    [_MEDIA_FN] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                                     ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX, KC_MPLY, KC_MNXT, KC_VOLU, KC_BRIU, _______,                                                       _______, _______, _______,  KC_F11,  KC_F12, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                                                     ├────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐                 ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_MUTE, KC_MPRV, KC_VOLD, KC_BRID, _______,   RESET, QWERTY,                   COLEMAK,   RESET,  _______, _______, _______, _______, _______, XXXXXXX,
    //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤                 ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                   _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______
    //                           └────────┴────────┴────────┴────────┴────────┘                 └────────┴────────┴────────┴────────┴────────┘
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
    }
    return true;
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
    rgblight_set_layer_state(_NUM, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(_SYM, layer_state_cmp(state, _SYM));
    rgblight_set_layer_state(_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_MOUSE, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(_MEDIA_FN, layer_state_cmp(state, _MEDIA_FN));

    return state;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

void render_status(void) {
    oled_write_P(PSTR(" Layer: "), false);

    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("COLEMAK\n\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("NUM\n\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("SYM\n\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("NAV\n\n"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("MOUSE\n\n"), false);
            break;
        case _MEDIA_FN:
            oled_write_P(PSTR("MEDIA / FN\n\n"), false);
            break;
        default:
            oled_write_P(PSTR("UNDEFINED\n\n"), false);
    }

    sprintf(wpm_str, "   WPM: %03d\n\n", get_current_wpm());
    oled_write(wpm_str, false);

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.caps_lock   ? PSTR("      * CAPSLOCK \n\n") : PSTR("                 \n\n"), false);

    oled_set_cursor(0, 7);
    oled_write_P(PSTR("        Kyria rev2.1\n"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_status();
    } else {
        render_animation();
    };

    return false;
}
