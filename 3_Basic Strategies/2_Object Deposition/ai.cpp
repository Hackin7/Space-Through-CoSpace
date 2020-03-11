#include "core.hpp"

//Color Sensor Checking
bool colorLeftCheck(int *objBlue, int objRange){
	return (objBlue[0] - objRange <= CSLeft_R && CSLeft_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSLeft_G && CSLeft_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSLeft_B && CSLeft_B <= objBlue[2] + objRange
		);
}
bool colorRightCheck(int *objBlue, int objRange){
	return (objBlue[0] - objRange <= CSRight_R && CSRight_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSRight_G && CSRight_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSRight_B && CSRight_B <= objBlue[2] + objRange
		);
}
bool colorCheck(int *objBlue, int objRange){
    return ( colorLeftCheck(objBlue, objRange) || colorRightCheck(objBlue, objRange));
}

//Colors, Measured from the colour sensor
int objBlue[3] = {29,249,255};
int objRed[3] = {235,29,29};
int objBlack[3] = {20,20,20};
int superObj[3] = {235,20,235};
int depositOrange[3] = {235,148,0};
int objRange = 20;

int LoadedRed=0;

void Game0(){
    //Pause Code
    if (Duration){ //>0
		Duration--;
		WheelLeft=0;WheelRight=0;
		return;
	}
	LED_1=0; //Clear any LED State
	
	//Collecting Red Objects//////////////////////////
	if (colorCheck(objRed,objRange))	{
		WheelLeft=0;WheelRight=0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedRed++;
		return; //Exit out of the code
	}
	//Remeber to fill in for other colours
	//Deposit Code///////////////////////////////////
	if (colorLeftCheck(depositOrange,objRange)&&colorRightCheck(depositOrange,objRange))	{
		WheelLeft=0;WheelRight=0;
		LED_1 =2;
		Duration=41;
		LoadedObjects++;
		LoadedRed++;
		return; //Do not run anything else
	}
	//Normal Movement/////////////////////////////////
    WheelLeft=3;WheelRight=3;
}
void Game1(){}

