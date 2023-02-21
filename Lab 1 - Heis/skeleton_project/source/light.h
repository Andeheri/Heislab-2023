
#pragma once
#include "driver/elevio.h"

void reset_lights();
void toggleButtonLamp(int current_floor, int floor, ButtonType button, MotorDirection *hall_button_lights);