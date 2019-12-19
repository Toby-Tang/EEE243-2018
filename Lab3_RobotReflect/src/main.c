/*
 * This program is for EEE243 Lab 3-1. Once prompted, the 3pi displays the
 * reflectance value read by its sensors.
 *
 * Authors: OCdt X. Lu 28297 and OCdt T. Tang 28296
 * Version: 18-09-2018
 */

#include <stdio.h>
#include <pololu/3pi.h>

int main() {
    // 3pi is initialized and waits for user input
    unsigned int reflect_value[5];
    lcd_init_printf();
    printf("Reflect");
    lcd_goto_xy(0,1);
    printf("Press B");
    wait_for_button(BUTTON_B);
    pololu_3pi_init(2000);

    do {
        // this loop reads and displays reflectance value on middle sensor
        // every time button B is pressed
        clear();
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
        printf("%d", reflect_value[2]);
        lcd_goto_xy(0,1);
        print("Press B");
    } while(wait_for_button(BUTTON_B));

    return 0;
}