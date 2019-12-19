/*
 * This program is for EEE243 Lab 3-2. Once prompted, the 3pi will display
 * the reflectance value read by its sensors and play a note. This note will
 * vary based on the reflectance.
 *
 * Authors: OCdt X. Lu 28297 and OCdt T. Tang 28296
 * Version: 18-09-2018
 */

#include <stdio.h>
#include <pololu/3pi.h>

#define MIDDLE_SENSOR 2
#define RESCAN 30           // delay for 30ms before rescanning
#define NOTE_LENGTH 50      // set longer than rescan, thus continuous sound
#define NOTE_VOLUME 8

// these are the highest sensor values allowed for the greyscale reading
#define TOP_ZERO 350
#define TOP_TEN 425
#define TOP_TWENTY 525
#define TOP_THIRTY 650
#define TOP_FORTY 750
#define TOP_FIFTY 1000
#define TOP_SIXTY 1500
#define TOP_SEVENTY 2000
#define TOP_EIGHTY 2900
#define TOP_NINETY 4250
#define TOP_HUNDRED 5000

// frequencies for the greyscale reading notes
#define FREQ_ZERO 466
#define FREQ_TEN 440
#define FREQ_TWENTY 415
#define FREQ_THIRTY 392
#define FREQ_FORTY 370
#define FREQ_FIFTY 350
#define FREQ_SIXTY 330
#define FREQ_SEVENTY 311
#define FREQ_EIGHTY 294
#define FREQ_NINETY 277
#define FREQ_HUNDRED 262

int main() {
    // 3pi is initialized and waits for user input
    unsigned int reflect_value[5];
    lcd_init_printf();
    printf("Sing");
    lcd_goto_xy(0, 1);
    printf("Press B");
    wait_for_button(BUTTON_B);
    pololu_3pi_init(2000);

    while (!button_is_pressed(BUTTON_A)) { // auto-exit when button A is pressed
        clear();
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
        printf("%d", reflect_value[MIDDLE_SENSOR]);

        // loop to determine which note is played, depending on reflectance
        // value read
        if (reflect_value[MIDDLE_SENSOR] > 0 && reflect_value[3] <= TOP_ZERO) {
            play_frequency(FREQ_ZERO, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_TEN) {
            play_frequency(FREQ_TEN, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_TWENTY) {
            play_frequency(FREQ_TWENTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_THIRTY) {
            play_frequency(FREQ_THIRTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_FORTY) {
            play_frequency(FREQ_FORTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_FIFTY) {
            play_frequency(FREQ_FIFTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_SIXTY) {
            play_frequency(FREQ_SIXTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_SEVENTY) {
            play_frequency(FREQ_SEVENTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_EIGHTY) {
            play_frequency(FREQ_EIGHTY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_NINETY) {
            play_frequency(FREQ_NINETY, NOTE_LENGTH, NOTE_VOLUME);
        } else if (reflect_value[MIDDLE_SENSOR] <= TOP_HUNDRED) {
            play_frequency(FREQ_HUNDRED, NOTE_LENGTH, NOTE_VOLUME);
        }
        delay(RESCAN);
    }

    // stops note when scanning is stopped
    stop_playing();

    return 0;
}