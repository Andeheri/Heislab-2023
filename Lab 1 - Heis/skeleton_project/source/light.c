
#include "light.h"
#include "driver/elevio.h"

void toggleButtonLamp(int current_floor, int floor, ButtonType button, MotorDirection *hall_button_lights){
    if (current_floor != floor){
        switch (button)
        {
        case BUTTON_HALL_UP:
            if (hall_button_lights[floor] == DIRN_STOP){
                elevio_buttonLamp(floor, button, 1);
                hall_button_lights[floor] = DIRN_UP;
            }
            break;
        case BUTTON_HALL_DOWN:
            if (hall_button_lights[floor] == DIRN_STOP){
                elevio_buttonLamp(floor, button, 1);
                hall_button_lights[floor] = DIRN_DOWN;
            } 
            break;
        default:
            break;
        }
    }
}

void reset_lights(){
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                elevio_buttonLamp(f, b, 0);
            }
    }
}