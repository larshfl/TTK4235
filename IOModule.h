#pragma once
#include "Queue.h"
#include "elev.h"

static int direction;//direction husker hvilken retning heisen kjørte sist, benyttes mhp stoppknapp

void pollFloorsAndSetLights(int *currentFloor); // pollFloorsAndSetLights
void pollAndUpdateButtonsAndLights();
void setMotorDirection (int *currentFloor, struct order *currentOrder);

// hjelpefunkjsoner for variabelen direction. 
int getDirection();
void setDirection(int dir); 