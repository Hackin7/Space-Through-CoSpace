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
////////////////////////////////////////////////////////////////////////////////////////////////

class ObjectCollection{
	public:
	
int LoadedObjects=0;
int LoadedBlue = 0;
int LoadedRed = 0;
int LoadedBlack = 0;
int LoadedSuperObj = 0;
int LoadedPoints = 0;

int noSuperObj = 0;

int objBlue[3] = {29,249,255};
int objRed[3] = {235,29,29};
int objBlack[3] = {20,20,20};

int superObj[3] = {235,20,235};
int specialZone[3]={20,171,235};

int objRange=35;

int slowarea[3] = {143,151,197};
int depositOrange[3] = {235,147,20};
int depRange = 35;

int trapYellow[3] = {220,235,20};
int trapBlue[3] = {95,43,190};
int trapRange=20;

bool collectedRed = false;
bool collectedBlue = false;
bool collectedBlack = false;
bool collectedSuper = false;
	
void Collection(){
	WheelLeft=0;WheelRight=0;
	LED_1 =1;
	Duration=41;
	LoadedObjects++;
}
bool BlueObject(){
	if (colorCheck(objBlue,objRange))
	{
		Collection();
		LoadedBlue++;
		LoadedPoints+=15;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=15;
		}
	}
	else{return false;}
	return true;
}
bool RedObject(){
	if (colorCheck(objRed,objRange))
	{
		Collection();
		LoadedRed++;

		LoadedPoints+=10;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=10;
		}
	}
	else{return false;}
	return true;
}
bool BlackObject(){
	if (colorCheck(objBlack,objRange))
	{
		Collection();
		LoadedBlack++;

		LoadedPoints+=20;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=20;
		}
	}
	else{return false;}
	return true;
}
bool SuperObject(){
	if (colorCheck(superObj,objRange))
	{
		Collection();
		LoadedSuperObj++;
		noSuperObj--;//SuperObj_Num--;
		LoadedPoints+=90;
		if (colorCheck(specialZone,objRange)){
            LoadedPoints+=90;
		}
	}
	else{return false;}
	return true;
}
bool Deposit(){
	if (LoadedObjects > 0 && colorCheck(depositOrange,depRange))
	{
		//2 color sensors must be in orange
		if (! colorRightCheck(depositOrange,depRange)){ // Turn Right
			WheelLeft=0;WheelRight=3;
			return true;
		}
		if (! colorLeftCheck(depositOrange,depRange)){ // Turn Left
			WheelLeft=3;WheelRight=0;
			return true;
		}
		WheelLeft=0;WheelRight=0;
		LED_1 =2;
		Duration=60;
		LoadedObjects=0;
		LoadedPoints = 0;
		LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
	}
	else{return false;}
	return true;
}
bool Trap(bool avoid){
	
	if (colorCheck(trapBlue,trapRange)){
		LoadedObjects=0;
		LoadedPoints = 0;
		LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
	}
	else if (LoadedObjects > 0 && colorCheck(trapYellow,trapRange) && avoid){//objRange ) &&)){

	            WheelLeft=-3;WheelRight=-5; // Turn
            //Duration=5;

		if (! colorRightCheck(trapYellow,trapRange*2)){ // Turn Right
			WheelLeft=3;WheelRight=0;
			//Duration = 5;
		}
		else if (! colorLeftCheck(trapYellow,trapRange*2)){ // Turn Left
			WheelLeft=0;WheelRight=3;
			//Duration = 5;
		}
		else{
            WheelLeft=-2;WheelRight=-4; // Turn
            Duration=5;
		}
		printf("Danger\n");
		return true;
	}
		//Duration=41;
	else{ return false;}
	return true;
}

bool isCollectedBlue(){
	if (collectedBlue){
		collectedBlue = false;
		return true;
	}
	return false;
}
bool isCollectedRed(){
	if (collectedRed){
		collectedRed = false;
		return true;
	}
	return false;
}
bool isCollectedBlack(){
	if (collectedBlack){
		collectedBlack = false;
		return true;
	}
	return false;
}
bool isCollectedSuper(){
	if (collectedSuper){
		collectedSuper = false;
		return true;
	}
	return false;
}

bool isCollected(){
	return isCollectedBlue() || isCollectedRed() || isCollectedBlack();
}


bool objCollectDeposit(bool collectBlue,bool collectRed,bool collectBlack,bool deposit){
	LED_1 =0;
	if (LoadedObjects<6){
		if (collectBlue){ if (BlueObject()){ Duration+=5; collectedRed = true; return true;} }
		if (collectRed){ if (RedObject()){Duration+=5; collectedBlue = true; return true;} }
		if (collectBlack){ if (BlackObject()){Duration+=5; collectedBlack = true; return true;} }
		if (SuperObject()){Duration+=5;return true;}
	}
	if (deposit){if (Deposit()){return true;}}	
	return false;
}



};

ObjectCollection w1Obj;
ObjectCollection w2Obj;