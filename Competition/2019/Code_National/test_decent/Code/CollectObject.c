// #include <stdbool.h> for bool

bool colorLeftCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSLeft_R && CSLeft_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSLeft_G && CSLeft_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSLeft_B && CSLeft_B <= objBlue[2] + objRange
		);
}
bool colorRightCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSRight_R && CSRight_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSRight_G && CSRight_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSRight_B && CSRight_B <= objBlue[2] + objRange
		);
}
bool colorCheck(int *objBlue, int objRange)
{return ( colorLeftCheck(objBlue, objRange) || colorRightCheck(objBlue, objRange));}

int LoadedBlue = 0;
int LoadedRed = 0;
int LoadedBlack = 0;
int LoadedSuperObj = 0;
int LoadedPoints = 0;
int noSuperObj = 0;
int SuperObjX;//[20];
int SuperObjY;//[20];
bool objCollectDeposit(bool collectBlue,bool collectRed,bool collectBlack,bool deposit){
	int objBlue[3] = {29,249,255};
	int objRed[3] = {235,29,29};
	int objBlack[3] = {20,20,20};
	int specialZone[3]={20,171,235};

	int superObj[3] = {235,20,235};
	int depositOrange[3] = {215,175,20};

	int objRange=20;
	if (colorCheck(objBlue,objRange) && LoadedObjects < 6 && collectBlue)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedBlue++;

		LoadedPoints+=15;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=15;
		}
		printf("Blue_Object ");
	}
	else if (colorCheck(objRed,objRange) && LoadedObjects < 6 && collectRed)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedRed++;

		LoadedPoints+=10;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=10;
		}

		printf("Red_Object ");
	}
	else if (colorCheck(objBlack,objRange) && LoadedObjects < 6 && collectBlack)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedBlack++;

		LoadedPoints+=20;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=20;
		}

		printf("Black_Object ");
	}
	else if (colorCheck(superObj,objRange) && LoadedObjects < 6)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedSuperObj++;
		noSuperObj--;//SuperObj_Num--;

		LoadedPoints+=90;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=90;
		}

		printf("Super_Object ");
	}
	else if (LoadedObjects > 0 && colorCheck(depositOrange,objRange) && deposit)
	{
		//2 color sensors must be in orange
		if (! colorRightCheck(depositOrange,objRange)){ // Turn Right
			WheelLeft=0;WheelRight=3;
			Duration = 10;
			return true;
		}
		if (! colorLeftCheck(depositOrange,objRange)){ // Turn Left
			WheelLeft=3;WheelRight=0;
			Duration = 10;
			return true;
		}
		WheelLeft=0;WheelRight=0;
		LED_1 =2;
		Duration=60;
		LoadedObjects=0;
		LoadedPoints = 0;
		LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
		printf("Deposit ");
	}
	else
	{
		LED_1 =0;
		return false; // Nothing to collect
	}
	return true;
}
bool avoidTrap(bool avoid){
	int trapYellow[3] = {220,235,20};
	int trapBlue[3] = {20,20,235};
	int trapRange=20;
	if (colorCheck(trapBlue,trapRange)){
		LoadedObjects=0;
		LoadedPoints = 0;
		LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
	}
	else if (LoadedObjects > 0 && colorCheck(trapYellow,trapRange) && avoid){//objRange ) &&)){

	            WheelLeft=-3;WheelRight=-5; // Turn
            Duration=10;

		if (! colorRightCheck(trapYellow,trapRange*2)){ // Turn Right
			WheelLeft=3;WheelRight=-1;
			//Duration = 5;
		}
		else if (! colorLeftCheck(trapYellow,trapRange*2)){ // Turn Left
			WheelLeft=-1;WheelRight=3;
			//Duration = 5;
		}
		else{
            WheelLeft=-4;WheelRight=-5; // Turn
            Duration=10;
		}
		printf("Danger\n");
		return true;
		//Duration=41;
	}
	else{ return false;}
	return true;
}
