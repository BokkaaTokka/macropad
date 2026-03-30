#include QMK_KEYBOARD_H

enum layers { _BASE, _CAD };

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }

    return false;
}



bool encoder_button_state = false;

void matrix_scan_user(void) {
    bool state = gpio_read_pin(ENCODER_BTN_PIN);

    if (state && !encoder_button_state) {
        tap_code(KC_MUTE);
    }

    encoder_button_state = state;
}

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    oled_write_ln("Layer:", false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln("Base", false);
            break;

        case _CAD:
            oled_write_ln("CAD", false);
            break;
    }

    return false;
}

#endif




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(KC_7, KC_8, TG(_CAD), KC_4, KC_5, KC_6, KC_1, KC_2, KC_3),
    [_CAD]  = LAYOUT(KC_ESC, KC_UP, TG(_CAD), KC_LEFT, KC_ENT, KC_RIGHT, KC_PSCR, KC_DOWN, KC_DEL)

};
