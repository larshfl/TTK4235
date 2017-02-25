#include "Queue.h"
#include "elev.h"

static int direction;
static int buttonLights[1];
static int floorLights[1];

void pollAndSetFloor(int *currentFloor);
void pollAndUpdateButtons();
