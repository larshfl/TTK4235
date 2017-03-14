#pragma once
#include "Queue.h"
#include "elev.h"

int previousDir; //RETNING I DET VI FORLOT FORRIGE ETASJE, BENYTTES MTP. STOPPKNAPP

int direction;

void pollFloorsAndSetLights(int *currentFloor);
void pollAndUpdateButtonsAndLights();
void setMotorDirection (int *currentFloor, struct order *currentOrder);
int getDirection();
void setDirection(int dir); 
