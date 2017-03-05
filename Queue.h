#pragma once
#include "io.h"
#include <stdio.h>
#include <stdlib.h>


int BUTTONS[12];

struct order {
	int floor;
	int buttonType; // 0 = up, 1 = down, 2 = command!
	int isEnabled;
};

static struct order queue[10]; //kun 10 knapper, worst case scenario 10 aktive ordre.




void createOrdersAndUpdateQueue(struct order *currentOrder); // endre? // verste funkjsonsbody?
void clearQueueAndButtons();
void fetchOrder(struct order *currentOrder);
void clearOrdersOnCurrentFloor(int currentFloor);
int  ordersOnCurrentFloor(int *currentFloor, int direction);
int orderAlreadyExists(struct order *currentOrder, int buttonType, int floorOrder, int queueNumber);
