#include "elev.h"

void stopAtTop(){
	if(elev_get_floor_sensor_signal() == 3){
		elev_set_motor_direction(DIRN_STOP);
	}
}

