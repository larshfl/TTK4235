#include "Queue.h"

void clearQueueAndButtons(){
	for (int i = 0; i < QUEUE_SIZE; i++){
		queue[i].isEnabled = 0;
		BUTTONS[i] = 0;
	}
	BUTTONS[BUTTON_SIZE - 2] = 0;
	BUTTONS[BUTTON_SIZE - 1] = 0;

}


void fetchOrder(struct order *currentOrder){
	currentOrder->buttonType = queue[0].buttonType;
	currentOrder->floor = queue[0].floor;
	currentOrder->isEnabled = queue[0].isEnabled;
	for (int i = 0; i < (QUEUE_SIZE - 1); i++){
		queue[i] = queue[i+1];
	}
		queue[QUEUE_SIZE - 1].isEnabled = 0;
}



void createOrdersAndUpdateQueue(struct order *currentOrder){
	for(int buttonType = 0; buttonType < BUTTON_TYPES; buttonType++){
		for(int floor = 0; floor < NUMBER_OF_FLOORS; floor++){
			addOrder(buttonType, floor, currentOrder);
		}
	}
}
int orderAlreadyExists(struct order *currentOrder, int buttonType, int floor, int queueNumber){
	if ((queue[queueNumber].buttonType == buttonType && queue[queueNumber].floor == floor && queue[queueNumber].isEnabled)){ //SJEKKER OM ORDREN LIGGER I KØEN
		return 1;
	}
	else if ((currentOrder->buttonType == buttonType && currentOrder->floor == floor && currentOrder->isEnabled == 1)){ // SJEKKER OM ORDREN ER UNDER BEHANDLING
		return 1;
	}
	return 0;
}

void clearOrdersOnCurrentFloor(int currentFloor){
	for (int i = 0; i < QUEUE_SIZE; i++){
		if ((queue[i].floor == currentFloor)&& (queue[i].isEnabled)){
			for (int j = i; j < (QUEUE_SIZE - 1); j++){
					queue[j] = queue[j+1];
			}
			queue[QUEUE_SIZE - 1].floor = -1;
			queue[QUEUE_SIZE - 1].buttonType = -1;
			queue[QUEUE_SIZE - 1].isEnabled = 0;

		}
	}
	for (int i = 0; i < BUTTON_TYPES; i++){
		BUTTONS[NUMBER_OF_FLOORS * i + currentFloor] = 0;
	}
}

int ordersOnCurrentFloor(int *currentFloor, int direction){
	for (int i = 0; i < QUEUE_SIZE; i++){
		if ((queue[i].floor == *currentFloor) && ((queue[i].buttonType == direction) || queue[i].buttonType == 2) && queue[i].isEnabled){
			return 1;
		}
	}
	return 0;
}

void addOrder(int buttonType, int floor, struct order *currentOrder){
	if (BUTTONS[(buttonType * NUMBER_OF_FLOORS) + floor]){
		for(int i = 0; i < QUEUE_SIZE; i++){
			if (orderAlreadyExists(currentOrder, buttonType, floor, i)){
				break;
			}
			else if (!(queue[i].isEnabled)){
				queue[i].buttonType = buttonType;
				queue[i].floor = floor;
				queue[i].isEnabled = 1;
				break;
				}
			}
		}
}