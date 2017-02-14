#include "elev.h"

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

