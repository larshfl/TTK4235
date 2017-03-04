#include "io.h"
#include "BUTTONS.h"

static struct order queue[10]; //kun 10 knapper, worst case scenario 10 aktive ordre.



void updateQueue(struct order *currentOrder);
void clearQueue();
void fetchOrder(struct order *currentOrder);
void clearOrdersOnCurrentFloor(int currentFloor);
 	
