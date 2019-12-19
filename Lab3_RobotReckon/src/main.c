/*
 * This program is for EEE243 Lab 3-4. Once prompted, the 3pi will calibrate
 * itself on a straight line. It will measure a certain distance specified by
 * horizontal lines across the straight line. Afterwards, it will drive one of
 * the five distances specified by the user using input buttons.
 *
 * Authors: OCdt X. Lu 28297 and OCdt T. Tang 28296
 * Version: 09-10-2018
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
unsigned long calibrate();
void turn(int nat_right);
int confirm_end();
void follow();

unsigned int reflect_value[5];      // global array used in multiple functions

int main() {
    // 3pi is initialized and waits for user input
    lcd_init_printf();
    printf("Calibr");
    lcd_goto_xy(0,1);
    printf("Press B");
    wait_for_button(BUTTON_B);
    pololu_3pi_init(2000);

    unsigned long time_10 = calibrate();    // The calibration time value is
                                            // stored in time_10
    clear();
    printf("Ready");
    lcd_goto_xy(0, 1);
    printf("10");

    // This array stores the possible travel distances (divided by 10)
    int time_array[5]={1,3,6,9,15};
    // Variable i will be used as the index for time_array
    int i = 0;

    while (1) {
        // The following line immediately returns 0 unless a button has just
        // been pressed
        unsigned char button = get_single_debounced_button_press(ANY_BUTTON);

        if (button & BUTTON_A){
            // IF button A is pressed...
            i--;
            // The IF loops allows the index reference i to loop around
            if (i == -1) {
                i = 4;
            }
            clear();
            printf("Ready");
            lcd_goto_xy(0, 1);
            printf("%d", time_array[i]*10);
        }

        if (button & BUTTON_C){
            // IF button C is pressed...
            i++;
            // The IF loops allows the index reference i to loop around
            if (i == 5) {
                i = 0;
            }
            clear();
            printf("Ready");
            lcd_goto_xy(0, 1);
            printf("%d", time_array[i]*10);
        }

        if (button & BUTTON_B) {
            // IF button B is pressed...
            clear();
            printf("Driving");
            time_reset();

            // The WHILE loop allows the 3pi to follow a line for the
            // specified distance (time)
            while (get_ms() <= (time_10*time_array[i])) {
                follow();
            }
            set_motors(0, 0);
            play_frequency(NOTE_FREQ, NOTE_LENGTH, NOTE_VOLUME);

            // The loop is reset
            clear();
            printf("Ready");
            lcd_goto_xy(0,1);
            printf("10");
            i = 0;
        }


    }
    return 0;
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
 * Performs the calibration of 3pi robot. Drives from one set of black lines
 * to another set, storing and returning the time for the travel.
 */
unsigned long calibrate (){
    int line = 0;
    clear();
    printf("Calibr");
    lcd_goto_xy(0,1);
    printf("Driving");

    while(1) {
        // The first block of code allows the 3pi to drive forward and
        // auto-adjust to any deviations.
        set_motors(GO_SPEED, GO_SPEED);
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
        while (reflect_value[L_SOR] < TAPE){
            fix_self(1);
        }
        while (reflect_value[R_SOR] < TAPE) {
            fix_self(-1);
        }

        if (reflect_value[LL_SOR] >= TAPE && reflect_value[RR_SOR] >= TAPE){
            if (line) {
                // The second time through, this loop is accessed. This
                // stores the time to be returned. The time is divided by 12
                // to simulate the time needed to travel 10 metres, so it is
                // easier to use for the other specified distances.
                unsigned long time = get_ms()/12;
                set_motors(0,0);
                return time;
            } else {
                // The first time through, line is 0 and thus this loop is
                // entered. It will display the appropriate message, set line
                // to 1, and begin timing.
                clear();
                printf("Calibr");
                lcd_goto_xy(0, 1);
                printf("Timing");
                line = 1;
                time_reset();
                // Delay is added to allow the 3pi's far sensors to drive off
                // the black lines.
                delay(200);
            }
        }

    }
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
 * Edited slightly from "follow" program to avoid usage of "time_reset()"
 * which would interfere with this program's main function.
 *
 * Returns 1 for route to right, -1 for route to left, and 0 for confirmed end
 * of path.
 * As per the turn function, "delay(50)" is added to allow the 3pi to centre
 * itself better onto the tape.
 */
int confirm_end(){
    unsigned long start_time_1 = get_ms();
    while (reflect_value[M_SOR] < TAPE && (get_ms()-start_time_1) < CONF_TIME) {
        set_motors(GO_SPEED, (-1)* GO_SPEED);
        read_line_sensors(reflect_value, IR_EMITTERS_ON_AND_OFF);
    }
    if (reflect_value[M_SOR] >= TAPE){
        delay(50);
        set_motors(0,0);
        return 1;
    }

    unsigned long start_time_2 = get_ms();
    while (reflect_value[M_SOR] < TAPE &&
                    (get_ms()-start_time_2) < 2*CONF_TIME) {
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

/*
 * This function is pulled from part 3 of the lab, with the change that it is
 * no longer in an infinite loop. This allows the timing component to be used.
 */
void follow(){
    START:
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
            play_frequency(NOTE_FREQ, NOTE_LENGTH, NOTE_VOLUME);
            delay(NOTE_LENGTH);
            return 0;

        } else if (flag_left && !flag_right) {
            // Left path is available; therefore, left turn
            set_motors(GO_SPEED, GO_SPEED);
            delay(200);
            turn(-1);
            set_motors(0, 0);

        } else if (!flag_left && flag_right) {
            // Right path is available; therefore, right turn
            set_motors(GO_SPEED, GO_SPEED);
            delay(200);
            turn(1);
            set_motors(0, 0);

        } else {
            // Both paths are available; therefore, T-junc
            play_frequency(NOTE_FREQ, NOTE_LENGTH, NOTE_VOLUME);
            set_motors(GO_SPEED, -1 * GO_SPEED);
            delay(1200);
            turn(1);
        }
    }
}
