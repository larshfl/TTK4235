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
	currentOrder->direction = queue[0].direction;
	currentOrder->floor = queue[0].floor;
	currentOrder->isEnabled = queue[0].isEnabled;
	for (int i = 0; i < 9; i++){
		queue[i].direction = queue[i+1].direction;
		queue[i].floor = queue[i+1].floor;
		queue[i].isEnabled = queue[i+1].isEnabled;
	}

		queue[10].isEnabled = 0;
}


void updateQueue(struct order *currentOrder){
	static int antallOrdre = 0;
	for(int direction = 0; direction < 3; direction++){
		for(int floorOrder = 0; floorOrder < 4; floorOrder++){
			if (BUTTONS[(direction*4) + floorOrder]){
				for(int i = 0; i < 10; i++){
					if ((queue[i].direction == direction && queue[i].floor == floorOrder && queue[i].isEnabled) || (currentOrder->direction == direction && currentOrder->floor == floorOrder && currentOrder->isEnabled == 1)){
						break;
					}
					else if (!(queue[i].isEnabled)){
						queue[i].direction = direction;
						queue[i].floor = floorOrder;
						queue[i].isEnabled = 1;
						antallOrdre++;
						printf("antall ordre er nå: %d \n", antallOrdre);
						break;
					}
				}
			}
		}
	}
}

void clearOrdersOnCurrentFloor(int currentFloor){
	for (int i = 0; i < 10; i++){
		if ((queue[i].floor == currentFloor)&& (queue[i].isEnabled)){
			for (int j = i; j < 9; j++){
					queue[j].floor = queue[j+1].floor;
					queue[j].direction = queue[j+1].direction;
					queue[j].isEnabled = queue[j+1].isEnabled;
			}
			queue[9].floor = -5; //settes til en ugyldig verdi;
			queue[9].direction = -5; //settes til en ugyldig verdi;
			queue[9].isEnabled = 0;

		}
	}
	BUTTONS[currentFloor] = 0;
	BUTTONS[4 + currentFloor] = 0;
	BUTTONS[8 + currentFloor] = 0;
}

int temporaryOrdersExists(int *currentFloor, int direction){
	for (int i = 0; i < 10; i++){
		if ((queue[i].floor == *currentFloor) && ((queue[i].direction == direction) || queue[i].direction == 2) && queue[i].isEnabled){
			return 1;
		}
	}
	return 0;
}