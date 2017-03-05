#include "Queue.h"
#include "elev.h"

static int direction;//direction husker hvilken retning heisen kjørte sist, benyttes mhp stoppknapp
static int buttonLights[1];
static int floorLights[1];

void pollAndSetFloor(int *currentFloor);
void pollAndUpdateButtonsAndLights();
void setMotorDirection (int *currentFloor, struct order *currentOrder);

int getDirection();
void setDirection(int dir); 