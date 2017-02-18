#include <stdio.h>

#include "elev.h"
#include "IOModule.h"
#include "Queue.h"
#include "Timer.h"
#include "BUTTONS.h"


int BUTTONS[10] = {0};


int main() {
	
		clearQueue();
		
	
	
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
    
    
    
    	pollAndUpdateButtons();
    	
    	pollAndSetFloor();
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
			startTimer();
			while(!timeOut()){
				elev_set_motor_direction(DIRN_STOP);
			}
			while(elev_get_floor_sensor_signal() == N_FLOORS - 1){
				elev_set_motor_direction(DIRN_DOWN);
				}
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
