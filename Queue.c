#include "Queue.h"

void clearQueue(){
	for (int i = 0; i < 10; i++){
		queue[i].isEnabled = 0;
	}
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


