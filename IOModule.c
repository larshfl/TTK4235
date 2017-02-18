#include "elev.h"
#include "IOModule.h"

void stopAtTop(){
	if(elev_get_floor_sensor_signal() == 3){
		elev_set_motor_direction(DIRN_STOP);
	}
}


void pollAndSetFloor(){
	switch(elev_get_floor_sensor_signal()){
	
		case -1:
			break;
		case 0:
			elev_set_floor_indicator(0);
			break;
		case 1:
			elev_set_floor_indicator(1);
			break;
		case 2:
			elev_set_floor_indicator(2);
			break;
		case 3:
			elev_set_floor_indicator(3);
			break;
	}
}

void pollAndUpdateButtons(){

		
		//COMMAND BUTTONS
		BUTTONS[0] = (BUTTONS[0] || elev_get_button_signal(2, 0));
		BUTTONS[1] = (BUTTONS[1] || elev_get_button_signal(2, 1));
		BUTTONS[2] = (BUTTONS[2] || elev_get_button_signal(2, 2));
		BUTTONS[3] = (BUTTONS[3] || elev_get_button_signal(2, 3));
		
		//DOWN BUTTONS
		BUTTONS[4] = (BUTTONS[4] || elev_get_button_signal(1, 1));
		BUTTONS[5] = (BUTTONS[5] || elev_get_button_signal(1, 2));
		BUTTONS[6] = (BUTTONS[6] || elev_get_button_signal(1, 3));
		
		//UP BUTTONS
		BUTTONS[7] = (BUTTONS[7] || elev_get_button_signal(0, 0));
		BUTTONS[8] = (BUTTONS[8] || elev_get_button_signal(0, 1));
		BUTTONS[9] = (BUTTONS[9] || elev_get_button_signal(0, 2));
		
	
		
		//SET LIGHTS
		elev_set_button_lamp(BUTTON_COMMAND, 0, BUTTONS[0]);
		elev_set_button_lamp(BUTTON_COMMAND, 1, BUTTONS[1]);
		elev_set_button_lamp(BUTTON_COMMAND, 2, BUTTONS[2]);
		elev_set_button_lamp(BUTTON_COMMAND, 3, BUTTONS[3]);
		
		elev_set_button_lamp(BUTTON_CALL_DOWN, 1, BUTTONS[4]);
		elev_set_button_lamp(BUTTON_CALL_DOWN, 2, BUTTONS[5]);
		elev_set_button_lamp(BUTTON_CALL_DOWN, 3, BUTTONS[6]);
		
		elev_set_button_lamp(BUTTON_CALL_UP, 0, BUTTONS[7]);
		elev_set_button_lamp(BUTTON_CALL_UP, 1, BUTTONS[8]);
		elev_set_button_lamp(BUTTON_CALL_UP, 2, BUTTONS[9]);
}











