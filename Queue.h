#pragma once
#include "io.h"
#include <stdio.h>
#include <stdlib.h>


#define QUEUE_SIZE 10
#define BUTTON_SIZE 12
#define NUMBER_OF_FLOORS 4
#define BUTTON_TYPES 3

int BUTTONS[BUTTON_SIZE];

struct order {
	int floor;
	int buttonType;
	int isEnabled;
};

static struct order queue[QUEUE_SIZE];




void createOrdersAndUpdateQueue(struct order *currentOrder);
void clearQueueAndButtons();
void fetchOrder(struct order *currentOrder);
void clearOrdersOnCurrentFloor(int currentFloor);
int  ordersOnCurrentFloor(int *currentFloor, int direction);
int orderAlreadyExists(struct order *currentOrder, int buttonType, int floorOrder, int queueNumber);
void addOrder(int buttonType, int floor, struct order *currentOrder);