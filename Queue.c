#include "Queue.h"
#include "BUTTONS.h"

void clearQueue(){
	
	for(int i = 0; i < 10; i++){
		queue[i] = 0;
		}
}


int fetchOrder(){ 

	int order = queue[0];

		for(int i = 0; i < 8; i++){
		queue[i] = queue[i + 1];
		}
	
		queue[9] = 0;


	return order; 

}


void updateQueue(){
	for(int i = 0; i < 9; i++){
		if(BUTTONS[i]){
			for(int j = 0; j < 9; j++){        //GÅR GJENNOM ARRAY BUTTONS, DERSOM KNAPP TRYKKET INN SJEKKES KØEN FOR IDENTISKE ORDRE
				if(i+1 == queue[j]){
					break;
					}
				else if(queue[j] == 0){
					queue[j] = i+1;
					}
				}
			}
	}
}
