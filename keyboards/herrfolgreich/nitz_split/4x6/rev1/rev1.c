#include "quantum.h"

#ifdef OLED_ENABLE

bool oled_logo_cleared = false;
uint16_t startup_timer;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return rotation;
    }
    startup_timer = timer_read();
    return OLED_ROTATION_270;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x81, 0x82, 0x83, 0x84,
        0x20, 0xA1, 0xA2, 0xA3, 0xA4,
        0x20, 0xC1, 0xC2, 0xC3, 0xC4,
        0x20, 0x20, 0x20, 0x20, 0x20,
        0x85, 0x86, 0x87, 0x88, 0x89,
        0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
        0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
        0x20, 0x20, 0x20, 0x20, 0x20,
    };
    oled_set_cursor(0, 2);
    oled_write_P(qmk_logo, false);
}

bool oled_task_kb(void) {
    if (!is_keyboard_master()) {
        return false;
    }

    oled_clear();

    if ((timer_elapsed(startup_timer) < 3000) || !oled_logo_cleared) {
        render_logo();
    } else {
        return oled_task_user();
    }

    return false;
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    #ifdef OLED_ENABLE
    if (!oled_logo_cleared && record->event.pressed) {
        oled_logo_cleared = true;
    }
    #endif

    if (record->event.pressed) {
    }

    return process_record_user(keycode, record);
}
