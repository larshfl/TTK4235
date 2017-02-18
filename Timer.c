#include "Timer.h"


void startTimer(){
	timestamp = time(0);
}

int timeOut(){
	return ((time(0) - 3) > timestamp);
}
