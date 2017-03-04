

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
    int currentFloor;
    pollAndSetFloor(&currentFloor);
    while(1){
          switch(state){
            case IDLE:
                elev_set_door_open_lamp(0);
                pollAndUpdateButtons();
                updateQueue(&currentOrder);
                if (!(currentOrder.isEnabled)){
                    fetchOrder(&currentOrder);
                }
                if(currentOrder.isEnabled){
                    state = MOVING;
                }
                else if(elev_get_stop_signal()){
                    state = STOP;
                }
                break;


            case MOVING:
                setMotorDirection(&currentFloor, &currentOrder);
                while(elev_get_floor_sensor_signal() != currentOrder.floor){
                    if (elev_get_stop_signal()){
                        state = STOP;
                        break;
                        }
                    pollAndUpdateButtons();
                    updateQueue(&currentOrder);
                    pollAndSetFloor(&currentFloor);
                    if ((temporaryOrdersExists(&currentFloor, getDirection())) && (elev_get_floor_sensor_signal() != -1)){
                        state = SERVICE;
                        break;
                    }
                }
                if (state != STOP){
                    state = SERVICE;
                }
                break;
            case SERVICE:
                elev_set_motor_direction(DIRN_STOP);
                pollAndSetFloor(&currentFloor);
                setDirection(-1);
                elev_set_door_open_lamp(1);
                startTimer();
                while(!(timeOut())){
                    clearOrdersOnCurrentFloor(currentFloor);
                    pollAndUpdateButtons();
                    updateQueue(&currentOrder);
                    if(elev_get_stop_signal()){
                        state = STOP;
                        break;
                        }
                }
                if(currentFloor == currentOrder.floor){
                    currentOrder.isEnabled = 0;
                }
                if (state != STOP){
                    state = IDLE;
                }
                break;
            case STOP:
                elev_set_motor_direction(DIRN_STOP);
                clearQueue();
                pollAndUpdateButtons();
                currentOrder.isEnabled = 0;
                if(!(elev_get_floor_sensor_signal() == -1)){
                    state = SERVICE;
                }
                else if(!(elev_get_stop_signal())){
                    state = IDLE;
                }
                break;
            default:
                printf("default\n");
        }

    }
    return 0;
}

void initialize(struct order *currentOrder){
    printf("INITIALISERER");
    currentOrder->isEnabled = 0;
    currentOrder->buttonType = -1;
    currentOrder->floor = -2;
    while (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_DOWN);
    }
    elev_set_motor_direction(DIRN_STOP);
}