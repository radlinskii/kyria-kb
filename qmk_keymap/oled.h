#include <stdio.h>

#include "layer_names.h"

#define FRAMES_COUNT 2
#define FRAME_DURATION 350
#define FRAME_SIZE 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_frame = 0;

char wpm_str[14];

void render_animation(void) {
    static const char PROGMEM frames[FRAMES_COUNT][FRAME_SIZE] = {
        {
            0x3f, 0x1f, 0x9f, 0xcf, 0xc7, 0xe7, 0xe3, 0xe1, 0xf1, 0xf1, 0xc3, 0xc3, 0xe7, 0x0f, 0x1f, 0x1f,
            0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x03, 0x0f, 0x1f, 0x3f, 0x3f,
            0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x8f, 0x0d, 0x81, 0x83, 0x87,
            0x87, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xc7, 0xc7, 0xc3, 0xc1, 0xc0, 0xc0,
            0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x03, 0x07, 0x07,
            0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07,
            0x07, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x06, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
            0x0f, 0xef, 0x07, 0x03, 0xe9, 0xe9, 0xe9, 0xe3, 0xe7, 0xef, 0xcf, 0xdf, 0xdf, 0xdf, 0x1f, 0x0f,
            0x3e, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x3f, 0x7f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0,
            0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, 0x7f, 0xff, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80,
            0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x0f, 0x1f, 0x7f, 0xff, 0xff, 0xfc, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x80, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x70, 0x38, 0xfc, 0xf8, 0xc0, 0x00,
            0x00, 0x80, 0xf0, 0x7e, 0x3f, 0xfc, 0xf8, 0x10, 0x00, 0x6f, 0x67, 0x47, 0x43, 0x63, 0x60, 0x30,
            0x3c, 0x8c, 0xc6, 0xe4, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xfc,
            0xe0, 0x1f, 0x0c, 0x80, 0x87, 0x8f, 0xcf, 0xef, 0x0f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x80, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f,
            0x3f, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x3f, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0xf0, 0xfc,
            0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f,
            0x1e, 0x3f, 0x01, 0x00, 0x00, 0x80, 0x20, 0x18, 0x0c, 0x06, 0xf0, 0x3e, 0x8e, 0xf7, 0x0b, 0x0b,
            0xcb, 0x17, 0xff, 0xff, 0x81, 0x3c, 0xe6, 0x02, 0x32, 0xb2, 0x86, 0xf8, 0xc0, 0x60, 0x60, 0x20,
            0x20, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xc0, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0x7e, 0x1f, 0x03, 0x0f,
            0xff, 0xf8, 0xf8, 0x1e, 0x0f, 0x07, 0x3f, 0xff, 0xff, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x3f, 0xfe, 0x3f, 0x01,
            0x00, 0xff, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0xfc, 0x82, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xff, 0xfe, 0xf8, 0xf3, 0xf6, 0xf6,
            0xf6, 0xfa, 0xff, 0xff, 0xff, 0xef, 0xee, 0xe7, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1c, 0x18, 0x18,
            0x18, 0x08, 0x00, 0x0c, 0x83, 0xe0, 0xc0, 0x00, 0xe0, 0x7c, 0x1f, 0x07, 0x03, 0x0f, 0xce, 0xc0,
            0x80, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0xc0, 0x80, 0xa0, 0x78, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0f, 0x7f, 0xff, 0xfc, 0xe0, 0xe0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x01, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0xf8, 0x7f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x00, 0x7f, 0xff, 0x83, 0x3f, 0xf1, 0x87, 0x3f, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0xe0, 0xf8, 0xfe, 0x0f, 0x07, 0x0f, 0x0f, 0x33, 0x70, 0x78, 0xf8, 0xfc, 0x80, 0xbf, 0xbf,
            0xbf, 0xbf, 0xbf, 0x9f, 0x81, 0xc0, 0xec, 0xf4, 0xf3, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
            0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x7e, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x1c, 0x7c, 0x1f, 0x07, 0x00, 0x07, 0xff, 0x00, 0x08, 0x08, 0x08, 0x08,
            0x08, 0x08, 0x0b, 0x0f, 0x00, 0x01, 0x13, 0x3b, 0x38, 0xb9, 0xb3, 0x37, 0x26, 0x2d, 0x2b, 0xa8,
            0xe9, 0x29, 0x69, 0x09, 0x39, 0xf9, 0xc3, 0xc1, 0xd8, 0x3a, 0x07, 0x3e, 0x38, 0x30, 0x30, 0x00,
            0x00, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x06, 0xc4, 0xf4, 0xf4, 0xf4,
            0x05, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x7d, 0x79, 0x39, 0x9b,
            0xdb, 0xcb, 0xe3, 0xf3, 0x7b, 0xfb, 0xfd, 0xfc, 0xfe, 0x8e, 0x00, 0x9b, 0xdb, 0xeb, 0xf3, 0xfb,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x80, 0xe0,
            0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0xe0, 0x00, 0xc0, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x04, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x8f, 0xcf, 0xe7, 0xf3,
            0xfc, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x78, 0x7c, 0x3e, 0x1e, 0x0f, 0x07,
            0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x01
        },
        {
            0x0f, 0x0f, 0x8f, 0xc7, 0xc3, 0x81, 0x01, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f,
            0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x07, 0x07, 0x03, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
            0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x05, 0x03, 0x83, 0x07, 0x87, 0x8f, 0x8f,
            0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xcf, 0xc7, 0xc7, 0xc3, 0xc3, 0xc1, 0xc0, 0xc0, 0xc3, 0xc7, 0xc7,
            0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x0f,
            0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x07, 0x07, 0x03, 0x03, 0x03,
            0x03, 0x01, 0x01, 0x02, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x03,
            0x01, 0xe1, 0x01, 0x03, 0xe3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc7, 0xc7, 0xc7, 0xc7, 0x03, 0x01,
            0x3e, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0x7c, 0x7c, 0xfe, 0xfe, 0xfc, 0xf8, 0xe0,
            0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x81, 0xf1, 0xe1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, 0x7f, 0xff, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x3f, 0x3f, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x01, 0x07, 0x3f, 0xff, 0xff,
            0xff, 0xff, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xfc, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xe0, 0x70,
            0x7f, 0xfe, 0xf0, 0x1f, 0x1f, 0xff, 0xf8, 0x10, 0x00, 0x6f, 0x67, 0x47, 0x43, 0x63, 0x60, 0x30,
            0x3c, 0x8c, 0xc6, 0xe4, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfe, 0xe0, 0xc0, 0x00,
            0x00, 0x7f, 0xfc, 0x80, 0x87, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x80, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
            0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfe,
            0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x01, 0x03, 0x01, 0x03, 0x03, 0x00,
            0x00, 0x07, 0x00, 0x00, 0x00, 0x80, 0x20, 0x18, 0x0c, 0x06, 0xf0, 0x3e, 0x8e, 0xf7, 0x0b, 0x0b,
            0xcb, 0x17, 0xff, 0xff, 0x81, 0x3c, 0xe6, 0x02, 0x32, 0xb2, 0x86, 0xf8, 0xc0, 0x60, 0x60, 0x20,
            0x20, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x1f, 0x07, 0x07, 0x0f, 0x3f,
            0xfe, 0xf8, 0xf8, 0xfc, 0x7e, 0x3f, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xc0, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x3f, 0x7f, 0x7f, 0x1f, 0x07, 0x01, 0x00,
            0xfc, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x20, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0xfc, 0x82, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xff, 0xfe, 0xf8, 0xf3, 0xf6, 0xf6,
            0xf6, 0xfa, 0xff, 0xff, 0xff, 0xef, 0xee, 0xe7, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1c, 0x18, 0x18,
            0x18, 0x08, 0x00, 0x0c, 0x83, 0x00, 0x00, 0x80, 0xe0, 0x7c, 0x3f, 0x1f, 0x0f, 0x0f, 0xce, 0xc0,
            0x80, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0xc0, 0x80, 0xa0, 0x7b, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x03, 0x1f, 0xff, 0xff, 0xfe, 0xf8, 0xc0, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x00, 0x7f, 0xff, 0x83, 0x3f, 0xf1, 0x87, 0x3f, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0xfc, 0x3f, 0x1f, 0x0f, 0x0f, 0x33, 0x70, 0x78, 0xf8, 0xfc, 0x80, 0xbf, 0xbf,
            0xbf, 0xbf, 0xbf, 0x9f, 0x81, 0xc0, 0xec, 0xf4, 0xf3, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
            0xfc, 0xfc, 0xfe, 0xfe, 0x7e, 0x7e, 0x3e, 0x9e, 0x9e, 0x1e, 0x3e, 0xfc, 0xfe, 0xfe, 0xfe, 0x7e,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x78, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x08, 0x08, 0x08, 0x08,
            0x08, 0x08, 0x0b, 0x0f, 0x00, 0x01, 0x13, 0x3b, 0x38, 0xb9, 0xb3, 0x37, 0x26, 0x2d, 0x2b, 0xa8,
            0xe9, 0x29, 0x69, 0x09, 0x39, 0xf9, 0xc3, 0xc1, 0xd8, 0x3a, 0x07, 0x3e, 0x38, 0x30, 0x30, 0x00,
            0x00, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x06, 0x04, 0x04, 0xf4, 0xf4,
            0x05, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x89, 0xc1, 0xe3,
            0xf1, 0x79, 0x79, 0x3c, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x80, 0x80, 0xe3, 0xf1, 0xf9, 0xf8, 0xfc,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xa0, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x80, 0xe0,
            0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0xe0, 0x00, 0xc0, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x04, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0x00, 0xff, 0xff,
            0x80, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0e, 0x07, 0x03, 0x03, 0x01,
            0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00
        }
    };

    void render_frame(void) {
        oled_set_cursor(0, 0);
        current_frame = (current_frame + 1) % FRAMES_COUNT;
        oled_write_raw_P(frames[abs((FRAMES_COUNT-1)-current_frame)], FRAME_SIZE);
        oled_set_cursor(0, 4);
        oled_write_P(PSTR("this"), false);
        oled_set_cursor(0, 5);
        oled_write_P(PSTR("is"), false);
        oled_set_cursor(0, 6);
        oled_write_P(PSTR("fine."), false);
    }

    if(get_current_wpm() != 000) {
        oled_on();
        if(timer_elapsed32(anim_timer) > FRAME_DURATION) {
            anim_timer = timer_read32();
            render_frame();
        }
        anim_sleep = timer_read32();
    }
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
