#include "IOModule.h"

void pollFloorsAndSetLights(int *currentFloor){

	switch(elev_get_floor_sensor_signal()){
	
		case -1:
			break;
		case 0:
			*currentFloor = 0;
			elev_set_floor_indicator(0);
			previousDir = direction;
			break;
		case 1:
			*currentFloor = 1;
			elev_set_floor_indicator(1);
			previousDir = direction;
			break;
		case 2:
			*currentFloor = 2;
			elev_set_floor_indicator(2);
			previousDir = direction;
			break;
		case 3:
			*currentFloor = 3;
			elev_set_floor_indicator(3);
			previousDir = direction;
			break;
		default:
			printf("FLOOR SENSOR BROKEN\n");
	}
};

void pollAndUpdateButtonsAndLights(){

	for(int i = 0; i < BUTTON_TYPES; i++){
		for(int j = 0; j < NUMBER_OF_FLOORS; j ++){
			if (((i == 0) && (j == (NUMBER_OF_FLOORS - 1))) || ((i == 1) && (j == (0)))){ 
				BUTTONS[j + i*NUMBER_OF_FLOORS] = 0; //NED I FØRSTE OG OPP I ØVERSTE ETASJE EKSISTERER IKKE;
			}
			else{
				BUTTONS[j + i*NUMBER_OF_FLOORS] = (BUTTONS[j + i*NUMBER_OF_FLOORS] || elev_get_button_signal(i, j));
				if(elev_get_stop_signal()){
					elev_set_button_lamp(i, j, 0);
				}
				else{
					elev_set_button_lamp(i, j, BUTTONS[j + i*NUMBER_OF_FLOORS]);
				}
			}
		}
	}
		

	
};

void setMotorDirection(int *currentFloor, struct order *currentOrder){
	

	if(elev_get_floor_sensor_signal() != -1){
        if(*currentFloor < currentOrder->floor){
            elev_set_motor_direction(DIRN_UP);
            direction = 0;
        }
        else if(*currentFloor > currentOrder->floor){
            elev_set_motor_direction(DIRN_DOWN);
            direction = 1;
        }
        }
    else{
        if(currentOrder->floor > *currentFloor){
            elev_set_motor_direction(DIRN_UP);
           	direction = 0;
        }
       	else if (currentOrder->floor < *currentFloor){
           	elev_set_motor_direction(DIRN_DOWN);
           	direction = 1;
        }
       	else{
         	if (previousDir == 1){
                elev_set_motor_direction(DIRN_UP);
                direction = 0;
                }
           	else{
               	elev_set_motor_direction(DIRN_DOWN);
               	direction = 1;
             	}
        }
    }    

}

int getDirection(){
	return direction;
}
void setDirection(int dir){
	direction = dir;
}





