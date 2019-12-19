/*
* This program is for EEE243 Lab 3-3. When prompted, the 3pi will follow the
* path on the ground according to instructions per lab.
*
* Authors: OCdt X. Lu 28297 and OCdt T. Tang 28296
* Version: 25-09-2018
*/

#include <stdio.h>
#include <pololu/3pi.h>

#define GO_SPEED 25
#define SPEED_OFFSET 8  // used for "fix_self" function
#define RIGHT_COMPEN 2  // added due to problems with right motor; extra
                        // speed to account for right lag in turns

#define TAPE 1000       // cutoff for darkness
#define LL_SOR 0        // far left sensor
#define L_SOR 1         // middle left sensor
#define M_SOR 2         // middle sensor
#define R_SOR 3         // middle right sensor
#define RR_SOR 4        // far right sensor

#define CONF_TIME 1200  // used for "confirm_end" function; delay allows 3pi
                        // to turn more than 90 degrees to check for paths

#define NOTE_FREQ 400
#define NOTE_LENGTH 800
#define NOTE_VOLUME 8

void fix_self(int nat_right);
void turn(int nat_right);
int confirm_end();

unsigned int reflect_value[5];      // global array used in multiple functions

int main() {
    // 3pi is initialized and waits for user input
    lcd_init_printf();
    printf("Follow");
    lcd_goto_xy(0, 1);
    printf("Press B");
    wait_for_button(BUTTON_B);
    pololu_3pi_init(2000);


    while (1) {
        // 3pi travels forwards while displaying "Onward!:
        START:
        clear();
        printf("Onward!");
        set_motors(GO_SPEED, GO_SPEED);
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);

        // Provides correction to 3pi path, staying on the tape
        while (reflect_value[L_SOR] < TAPE && reflect_value[M_SOR] >= TAPE) {
            fix_self(1);
        }
        while (reflect_value[R_SOR] < TAPE && reflect_value[M_SOR] >= TAPE) {
            fix_self(-1);
        }

        // Triggered if 3pi encounters: sharp turns, T-junc, end of path
        // IF loop entered when all three sensors drive off tape
        if (reflect_value[M_SOR] < TAPE && reflect_value[L_SOR] < TAPE &&
            reflect_value[R_SOR] < TAPE) {
            set_motors(0, 0);
            read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);

            // Left and right flags are 1 based on far sensors if they detect
            // tape; else, they are 0
            int flag_left = 0;
            int flag_right = 0;
            if (reflect_value[LL_SOR] >= TAPE) {
                flag_left = 1;
            }
            if (reflect_value[RR_SOR] >= TAPE) {
                flag_right = 1;
            }

            // Set of loops determining behaviour based on flags
            if (!flag_left && !flag_right) {
                // Both left and right are 0; therefore, end of path

                // Use of confirm_end() was used due to some problems seen
                // during the testing of the robot; it can re-route the
                // program to an available turn
                if (confirm_end()) {
                    goto START;
                }
                clear();
                printf("End");
                play_frequency(NOTE_FREQ, NOTE_LENGTH, NOTE_VOLUME);
                delay(NOTE_LENGTH);
                return 0;

            } else if (flag_left && !flag_right) {
                // Left path is available; therefore, left turn
                clear();
                printf("Turn");
                set_motors(GO_SPEED, GO_SPEED);
                delay(200);
                turn(-1);
                set_motors(0, 0);

            } else if (!flag_left && flag_right) {
                // Right path is available; therefore, right turn
                clear();
                printf("Turn");
                set_motors(GO_SPEED, GO_SPEED);
                delay(200);
                turn(1);
                set_motors(0, 0);

            } else {
                // Both paths are available; therefore, T-junc
                clear();
                printf("T-Junc");
                play_frequency(NOTE_FREQ, NOTE_LENGTH, NOTE_VOLUME);
                set_motors(GO_SPEED, -1 * GO_SPEED);
                delay(1200);
                turn(1);
            }
        }

    }
}

/*
 * Allows for 3pi to correct its path when it starts to go slightly off. If
 * it slants off one side, it will correct by driving at a slight curve
 * towards the side it's slanting off.
 * The speed of the motors is the regular speed with an offset of positive or
 * negative, depending on whether nat_right is 1 or -1.
 *
 * nat_right: When 1, function will correct 3pi towards the right. When -1,
 * left.
 */
void fix_self(int nat_right) {
    set_motors(GO_SPEED+nat_right*SPEED_OFFSET,
               GO_SPEED+(-1)*nat_right*SPEED_OFFSET+(nat_right+1)*RIGHT_COMPEN);
    read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
}

/*
 * 3pi will turn in a direction until it senses that it is back on the line.
 * The delay is added at the end to allow it to centre itself better on the
 * line, as it would have stopped the turn as soon as the middle sensor
 * detected tape.
 *
 * nat_right: When 1, function will turn 3pi towards the right. When -1, left.
 */
void turn(int nat_right) {
    while (reflect_value[M_SOR] < TAPE) {
        set_motors(nat_right*GO_SPEED, (-1)*nat_right* GO_SPEED);
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
    }
    delay(50);
}

/*
 * Function was added to counteract some problems detected in testing process
 * There would be some occasions when the far left and right sensors could
 * not detect possible routes to the side. Therefore, this function causes
 * the 3pi to turn both left and right to use its middle sensor to manually
 * check for a possible left or right route.
 *
 * Returns 1 for route to right, -1 for route to left, and 0 for confirmed end
 * of path.
 * As per the turn function, "delay(50)" is added to allow the 3pi to centre
 * itself better onto the tape.
 */
int confirm_end(){
    time_reset();
    while (reflect_value[M_SOR] < TAPE && get_ms() < CONF_TIME) {
        set_motors(GO_SPEED, (-1)* GO_SPEED);
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
    }
    if (reflect_value[M_SOR] >= TAPE){
        delay(50);
        set_motors(0,0);
        return 1;
    }

    time_reset();
    while (reflect_value[M_SOR] < TAPE && get_ms() < 2*CONF_TIME) {
        set_motors((-1)* GO_SPEED, GO_SPEED);
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
    }
    if (reflect_value[M_SOR] >= TAPE){
        delay(50);
        set_motors(0,0);
        return 1;
    }

    set_motors(0,0);
    return 0;
}