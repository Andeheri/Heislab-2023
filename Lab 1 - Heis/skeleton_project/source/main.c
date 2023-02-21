#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "light.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    // Reset lights
    reset_lights();

    // -1: Ingen knapp trykt, 0: Opp, 1: Ned, 
    MotorDirection hall_button_lights[4] = {DIRN_STOP, DIRN_STOP, DIRN_STOP, DIRN_STOP}; 

    //                  Up   Down   Cab
    int queue[4][3] = {{0,   0,     0},  // 0th floor
                       {0,   0,     0},  // 1st floor
                       {0,   0,     0},  // 2nd floor
                       {0,   0,     0}}; // 3rd floor

    while(1){
        MotorDirection direction = DIRN_STOP;
        int floor = elevio_floorSensor();

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if(btnPressed){
                    printf("floor: %d, button: %d \n", f, b);
                    toggleButtonLamp(floor, f, b, hall_button_lights);
                }
                
                //elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
