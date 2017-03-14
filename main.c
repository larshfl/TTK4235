#include "IOModule.h"
#include "Timer.h"




int BUTTONS[12] = {0}; //PRØV Å LEGG SOM ARRAY, SEND INN MED PEKER
					   //INKLUDER IO I QUEUE, INKLUDER QUEUE I MAIN


void initialize(struct order *currentOrder);

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    clearQueueAndButtons();
    typedef enum {MOVING, IDLE, SERVICE, STOP} STATE;
    STATE state = IDLE;
    struct order currentOrder;
    initialize(&currentOrder);
    int currentFloor;
    pollFloorsAndSetLights(&currentFloor);
    while(1){
          switch(state){
            case IDLE:
                elev_set_door_open_lamp(0);
                pollAndUpdateButtonsAndLights();
                createOrdersAndUpdateQueue(&currentOrder);
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
                    pollAndUpdateButtonsAndLights();
                    createOrdersAndUpdateQueue(&currentOrder);
                    pollFloorsAndSetLights(&currentFloor);
                    if ((ordersOnCurrentFloor(&currentFloor, getDirection())) && (elev_get_floor_sensor_signal() != -1)){
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
                pollFloorsAndSetLights(&currentFloor);
                setDirection(-1);
                elev_set_door_open_lamp(1);
                startTimer();
                while(!(timeOut())){
                    clearOrdersOnCurrentFloor(currentFloor);
                    pollAndUpdateButtonsAndLights();
                    createOrdersAndUpdateQueue(&currentOrder);
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
                clearQueueAndButtons();
                pollAndUpdateButtonsAndLights();
                currentOrder.isEnabled = 0;
                if(!(elev_get_floor_sensor_signal() == -1)){
                    state = SERVICE;
                }

                else if(!(elev_get_stop_signal())){
                    state = IDLE;
                }
                break;


            default:
                printf("INVALID STATE!\n");
        }

    }
    return 0;
}

void initialize(struct order *currentOrder){
    currentOrder->isEnabled = 0;
    currentOrder->buttonType = -5;
    currentOrder->floor = -5;
    while (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_DOWN);
    }
    elev_set_motor_direction(DIRN_STOP);
}