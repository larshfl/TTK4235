#include "Queue.h"

void clearQueue(){
	for (int i = 0; i < 10; i++){
		queue[i].isEnabled = 0;
		BUTTONS[i] = 0;
	}
	BUTTONS[10] = 0;
	BUTTONS[11] = 0;

}


void fetchOrder(struct order *currentOrder){
	currentOrder->buttonType = queue[0].buttonType;
	currentOrder->floor = queue[0].floor;
	currentOrder->isEnabled = queue[0].isEnabled;
	for (int i = 0; i < 9; i++){
		queue[i] = queue[i+1];
	}
		queue[10].isEnabled = 0;
}


void updateQueue(struct order *currentOrder){
	static int antallOrdre = 0;
	for(int buttonType = 0; buttonType < 3; buttonType++){
		for(int floorOrder = 0; floorOrder < 4; floorOrder++){
			if (BUTTONS[(buttonType*4) + floorOrder]){
				for(int i = 0; i < 10; i++){
					if (alreadyExists(currentOrder, buttonType, floorOrder, i)){
						break;
					}
					else if (!(queue[i].isEnabled)){
						queue[i].buttonType = buttonType;
						queue[i].floor = floorOrder;
						queue[i].isEnabled = 1;
						antallOrdre++;
						break;
					}
				}
			}
		}
	}
}

int alreadyExists(struct order *currentOrder, int buttonType, int floorOrder, int queueNumber){
	if ((queue[queueNumber].buttonType == buttonType && queue[queueNumber].floor == floorOrder && queue[queueNumber].isEnabled)){ //SJEKKER OM ORDREN LIGGER I KØEN
		return 1;
	}
	else if ((currentOrder->buttonType == buttonType && currentOrder->floor == floorOrder && currentOrder->isEnabled == 1)){ // SJEKKER OM ORDREN ER UNDER BEHANDLING
		return 1;
	}
	return 0;
}

void clearOrdersOnCurrentFloor(int currentFloor){
	for (int i = 0; i < 10; i++){
		if ((queue[i].floor == currentFloor)&& (queue[i].isEnabled)){
			for (int j = i; j < 9; j++){
					queue[j] = queue[j+1];
			}
			queue[9].floor = -5; //settes til en ugyldig verdi;
			queue[9].buttonType = -5; //settes til en ugyldig verdi;
			queue[9].isEnabled = 0;

		}
	}
	BUTTONS[currentFloor] = 0;
	BUTTONS[4 + currentFloor] = 0;
	BUTTONS[8 + currentFloor] = 0;
}

int temporaryOrdersExists(int *currentFloor, int direction){
	for (int i = 0; i < 10; i++){
		if ((queue[i].floor == *currentFloor) && ((queue[i].buttonType == direction) || queue[i].buttonType == 2) && queue[i].isEnabled){
			return 1;
		}
	}
	return 0;
}