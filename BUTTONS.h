#include <stdio.h>
#include <stdlib.h>
extern int BUTTONS[12];

struct order {
	int floor;
	int direction; // 0 = up, 1 = down, 2 = command!
	int isEnabled;
};