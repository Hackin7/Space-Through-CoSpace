#include "core.hpp"

bool colorLeftCheck(int *color, int objRange)
{
	return (color[0] - objRange <= CSLeft_R && CSLeft_R <= color[0] + objRange &&
	      color[1] - objRange <= CSLeft_G && CSLeft_G <= color[1] + objRange &&
	      color[2] - objRange <= CSLeft_B && CSLeft_B <= color[2] + objRange
		);
}
bool colorRightCheck(int *color, int objRange)
{
	return (color[0] - objRange <= CSRight_R && CSRight_R <= color[0] + objRange &&
	      color[1] - objRange <= CSRight_G && CSRight_G <= color[1] + objRange &&
	      color[2] - objRange <= CSRight_B && CSRight_B <= color[2] + objRange
		);
}
bool colorCheck(int *color, int objRange)
{
    return ( colorLeftCheck(color, objRange) || colorRightCheck(color, objRange));
}

int depositOrange[3] = {235,148,0};

void Game0(){
    WheelLeft=5;WheelRight=5;
    if (colorCheck(depositOrange, 10)){
        WheelLeft=0;WheelRight=0;
    }
}
void Game1(){printf("hi2");}

