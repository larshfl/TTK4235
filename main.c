

#include "IOModule.h"
#include "Timer.h"

int BUTTONS[12] = {0};

void initialize(struct order *currentOrder);


/*
stopp knapp fungerer ikke. Current ordre slettes ikke.





*/






int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    printf("Press STOP button to stop elevator and exit program.\n");
    clearQueue();
    typedef enum {MOVING, IDLE, SERVICE, STOP} STATE;
    STATE state = IDLE;
    struct order currentOrder;
    initialize(&currentOrder);
    printf("currentOrder = %d", currentOrder.isEnabled);
    int currentFloor;
    pollAndSetFloor(&currentFloor);
    while(1){
          switch(state){
            case IDLE:
                pollAndUpdateButtons();
                updateQueue(&currentOrder);
                fetchOrder(&currentOrder);
                if(currentOrder.isEnabled){
                    printf("Moving\n");
                    state = MOVING;
                }
                else if(elev_get_stop_signal()){
                    state = STOP;
                }
                break;


            case MOVING:
                if (elev_get_stop_signal()){
                    state = STOP;
                }
                else if (!(currentOrder.isEnabled)){
                    state = IDLE;
                }
                pollAndUpdateButtons();
                updateQueue(&currentOrder);
                pollAndSetFloor(&currentFloor);
                if (currentFloor > currentOrder.floor && currentOrder.isEnabled){
                    elev_set_motor_direction(DIRN_DOWN);
                }
                else if (currentFloor < currentOrder.floor && currentOrder.isEnabled){
                    elev_set_motor_direction(DIRN_UP);
                }
                else{
                    printf("RIKTIG ETASJE\n");
                    currentOrder.isEnabled = 0;
                    elev_set_motor_direction(DIRN_STOP);
                    state = SERVICE;
                    startTimer();
                }
                break;
            case SERVICE:
                clearOrdersOnCurrentFloor(currentFloor);
                pollAndUpdateButtons();
                updateQueue(&currentOrder);
                elev_set_door_open_lamp(1);
                if(timeOut() && !(elev_get_stop_signal())){
                    //exit(1);
                    printf("TIMEOUT\n");
                    elev_set_door_open_lamp(0);
                    state = IDLE;
                }
                else if(elev_get_stop_signal()){
                    clearQueue();
                    currentOrder.isEnabled = 0;
                    startTimer();
                }
                break;
            case STOP:
                elev_set_motor_direction(DIRN_STOP);
                clearQueue();
                currentOrder.isEnabled = 0;
                if(!(elev_get_floor_sensor_signal() == -1)){
                    state = SERVICE;
                    startTimer();
                }
                else if(!(elev_get_stop_signal())){
                    state = IDLE;
                }
                break;
            default:
                printf("default\n");
        }

    }
    /*
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
    */
    return 0;
}

void initialize(struct order *currentOrder){
    printf("INITIALISERER");
    currentOrder->isEnabled = 0;
    currentOrder->direction = -1;
    currentOrder->floor = -2;
    while (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_DOWN);
    }
    elev_set_motor_direction(DIRN_STOP);
}