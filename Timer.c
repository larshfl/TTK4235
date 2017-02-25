#include "Timer.h"


void startTimer(){
	timestamp = time(0);
}

int timeOut(){
	//printf("timestamp = %d", timestamp);
	if ((time(0) - 3) > timestamp){
		return 1;
	}
	else{
		return 0;
	}
	//return ((time(0) - 3) > timestamp);
}
