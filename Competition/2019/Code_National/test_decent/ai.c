// Time: 2019-04-05 10:29:43.978339
////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2016
//	Copyright (C) 2016 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif//The robot ID : It must be two char, such as '00','kl' or 'Cr'.
char AI_MyID[2] = {'0','2'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;

#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
    char info[1024];
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}

DLL_EXPORT char* GetTeamName()
{
     return "NYCasuals";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
///////////
void reverse(){
    if ((270 <= Compass && Compass < 360) ||
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=5;WheelRight=-5;//Turn Right
            }
        else{
            WheelLeft=-5;WheelRight=5;//Turn Left
        }
}


void wallAvoiding()
{
	if (US_Front < 25 && US_Left < 20 && US_Right < 20){
		reverse();//WheelLeft=5;WheelRight=-5; //Full Turn
		//printf("Corner");
	}
	else if (US_Left < 20){
		WheelLeft=3;WheelRight=0;
		//printf("Left");
	}
	else if (US_Right < 20){
		WheelLeft=0;WheelRight=3;
		//printf("Right");
	}
	else if (US_Front < 20){
        reverse();
            //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}
	else{return false;}// No need to run
	return true; //Ran
}
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

void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}

	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;

	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	else {
		WheelLeft=3;WheelRight=3;
	}

	if (Time > 180){
			Teleport = 1;
	}
}


//Angle to turn to
double angle(int x, int y){
	double Ychange = (y-PositionY); double Xchange = (x-PositionX);
	if (Xchange == 0 && Ychange > 0){
		return 0;
	}
	if (Xchange == 0 && Ychange < 0){
		return 180;
	}

	int theta = abs(atan(Ychange/Xchange)/(2*3.14159265358979323846) * 360); // Original arctan value

	//DEBUG///////////////////////////////////////////////////////////
    /*
	printf("PosX %d ",PositionX);
	printf("PositionY %d \n",PositionY);
	printf("Xchange %d ",Xchange);
	printf("Ychange %d \n",Ychange);
	//printf("atan%d = ",dabs(Ychange/Xchange));
	printf("%d\n ",theta);
    */
    ///////////////////////////////////////////////////////////////////

	//Process angle To turn to, 0 degress is north, goes anticlockwise
	//First quadrant
	if (Ychange>0 && Xchange>0){
		theta = 270+theta;
	}
	//Second quadrant
	else if (Ychange>0 && Xchange<0){
		theta = 90-theta;
	}
	//Third quadrant
	else if (Ychange<0 && Xchange<0){
		theta = 90+theta;
	}
	//Fourth quadrant
	else if (Ychange<0 && Xchange>0){
		theta = 270-theta;
	}
	//printf("New theta %d",theta);
	return theta;
}
//bool rotated = 0;

void clockwise(int theta1)
{
  if ((Compass < (theta1 + 5)%360 && Compass > (theta1 - 5)%360))
  {
      WheelLeft=5;
    WheelRight=5;
    return;
	}
	else if ((Compass < (theta1 + 10)%360 && Compass > (theta1 - 10)%360))
  {
      WheelLeft = 5;WheelRight=4;
    //WheelLeft=3;WheelRight=2;
    //WheelLeft=1;WheelRight=-1;
	}
  else
		{
      //WheelLeft=2;WheelRight=-2;
      WheelLeft=4;WheelRight=0;
    }

}

void aclockwise(int theta1)
{
	if ((Compass < (theta1 + 5)%360 && Compass > (theta1 - 5)%360))
  {
      WheelLeft=5;
    WheelRight=5;
    return;
	}
//ADD More Conditions and ranges
//Gradual Turning
  else if ((Compass < (theta1 + 10)%360 && Compass > (theta1 - 10)%360))
  {
    WheelLeft=4;WheelRight=5;
    //WheelLeft=-1;WheelRight=1;
	}
    else
    {
      //WheelLeft=-2; WheelRight=2;
     WheelLeft=0;WheelRight=4;
    }
  }
void rotateTo(double angle){
	//WheelLeft=-1;WheelRight=-1;
	int range = 10;
	//printf("%d, %d, %d]\n",(int)angle-range, Compass,(int)angle+range);
	/*
	if  ((int)angle-range <= Compass && Compass <= (int)angle+range){
            //printf("YES\n");
		WheelLeft=4;WheelRight=4;
		LED_1=1;
		return;
	}*/

	double theta = angle;
	double CWAngleDiff;
  double ACWAngleDiff;
  double AngleDiff;

  AngleDiff = abs(Compass-theta);

  if(AngleDiff>180)
  {
  	AngleDiff=360-AngleDiff;
  }

  //turn to theta

  //step 1: determine clockwise and anti-clockwise angle differences
  if(Compass>theta)
  {
  	CWAngleDiff=Compass-theta;
  	ACWAngleDiff=360-(Compass-theta);
  }
  else if(theta>Compass)
  {
  	ACWAngleDiff=theta-Compass;
  	CWAngleDiff=360-(theta-Compass);
  }
  else{
    ACWAngleDiff=0;
  	CWAngleDiff=0;
  }
  //step 2: determine if CWAngleDiff or ACWAngleDiff is lower
  if(CWAngleDiff<ACWAngleDiff || CWAngleDiff==180)
  {
  	//turn clockwise
    clockwise(theta);
  }

  else if(ACWAngleDiff<CWAngleDiff)
  {
  	//turn anti-clockwise
    aclockwise(theta);
  }


/*
	int diffToACWM = (int)angle - Compass; // Angle antiClockwise of compass
	int diffToCWM = 360-abs(diffToACWM); // Other way
	if ( (diffToACWM < 0 && abs(diffToACWM) < diffToCWM) ||
	//Angle anticlockwise of compass and
		 (diffToACWM > 0 && abs(diffToACWM) > diffToCWM) )
	{
		WheelLeft=-2;WheelRight=2;//WheelLeft=4;WheelRight=2; //Anticlockwise Turn
	}
	else {
		WheelLeft=2;WheelRight=-2; //Clockwise Turn
	}
	//Duration = 1;*/
}

bool xreached(int x,int range){
	return (x-range<=PositionX && PositionX <= x+range);
}
bool yreached(int y,int range){
	return (y-range<=PositionY && PositionY <= y+range);
}
bool reached(int x,int y,int rangex, int rangey){
	return ((x-rangex<=PositionX && PositionX <= x+rangex) &&
	    (y-rangey<=PositionY && PositionY <= y+rangey));
}
double * angleToHorizontal(int speed){
	double angle=0, deltaX=0, deltaY=0;
	if (Compass > 270){
		angle = Compass - 270; //Anticlockwise Upward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (180< Compass && Compass < 270){
		angle = 270 - Compass;// Clockwise Downward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = -sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (90< Compass && Compass < 180){
		angle = Compass - 180;// Clockwise Downward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = -sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (Compass < 90){
		angle = 90 - Compass;//Clockwise upward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (Compass == 0)//up
	{
		angle = 0;
		deltaX = 0;//speed * cos(angle);
		deltaY = 1 ;//* sin(angle);
	}
	else if (Compass == 180)//down
	{
		angle = 0;
		deltaX = 0;//speed * cos(angle);
		deltaY = -1 ;//* sin(angle);
	}
	else if (Compass == 90)//left
	{
		angle = 0;
		deltaX = -1 ;//* cos(angle);
		deltaY = 0;//speed * sin(angle);
	}
	else// if (Compass == 270) //right
	{
		angle = 0;
		deltaX = 1 ;//* cos(angle);
		deltaY = 0;//-speed * sin(angle);
	}
	/*printf("Compass %d ",Compass);
	printf("^X %f ",deltaX);
	//printf("sin60 %f ",sin(3.14159265358979323846/3));
	printf("^Y %f\n",deltaY);
	*/

    double output[3] = {angle, deltaX*speed/215, deltaY*speed};
	return output;
}
/*
double ActualX=0;double ActualY = 0;

bool posInfoLost(){
	if (PositionX==0 || PositionY==0){
		double *output = angleToHorizontal(min(WheelLeft,WheelRight));
		double deltaX=output[1];double deltaY=output[2];
		ActualX += deltaX;
		ActualY += deltaY;
		//WheelLeft=-4;WheelRight=5;
		printf("X %f ",ActualX);
	printf("Y %f",ActualY);
	printf("Compass %d ",Compass);
	printf("^X %f ",deltaX);
	printf("^Y %f\n",deltaY);
	}
	else{
		ActualX = (double)PositionX;
		ActualY = (double)PositionY;

		printf("X %f ",ActualX);
		printf("Y %f ",ActualY);
		printf("X %d ",PositionX);
		printf("Y %d\n",PositionY);
		return false;
	}

	return true;
}
*/

double tx=0,ty=0;
int icompass=0;
bool posInfoLost(){
    if (PositionX==0 && PositionY==0)
    {
    if (WheelLeft==WheelRight) // striaght
    {
      double speed=WheelLeft*2/3.25;
      PositionX = speed * cos((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + tx;
      PositionY =speed * sin((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + ty;
    }
    else // turn
    {
      double w;
      double pi;
      pi = 3.1415926535897932384626433832795;
      w = (1/60)* (Compass - icompass); // angle
      for (int i=0; i < 60; i++)
      {
        tx += cos(((1/60)*(i*(w/2)))*(180/pi));
        ty += sin(((1/60)*(i*(w/2)))*(180/pi));
      }
      PositionX = tx;
      PositionY = ty;
    }/*
    printf("X: %d\t", PositionX);
    printf("Y: %d\n", PositionY);*/
}

icompass=Compass;
tx = PositionX;
ty = PositionY;
}
#define MAX 43
int coordinates[MAX][2] = {{33, 245}, {80, 246}, {148, 253}, {199, 253}, {284, 258}, {317, 243}, {58, 210}, {147, 216}, {200, 221}, {250, 240}, {98, 211}, {333, 208}, {32, 175}, {61, 150}, {121, 146}, {178, 148}, {239, 157}, {328, 155}, {31, 124}, {74, 108}, {125, 101}, {186, 100}, {233, 116}, {296, 131}, {269, 97}, {299, 96}, {26, 71}, {272, 61}, {329, 59}, {23, 25}, {85, 46}, {124, 48}, {169, 45}, {202, 48}, {301, 63}, {85, 22}, {125, 21}, {171, 18}, {202, 19}, {239, 17}, {262, 19}, {336, 22}};

#define DEPOSITNODES 2
int depositNodes[DEPOSITNODES] = {29,41};

#define OBJPOINTS 4
int objectPoints[OBJPOINTS] = {0,7,22,33};
int objectPointsSize[OBJPOINTS][2] = {{50,25},{25,25},{50,50},{50,50}};
/*
#define REDPOINTS 2
int redNodes[REDPOINTS] = {9,18};
#define BLUEPOINTS 3
int blueNodes[BLUEPOINTS] = {32, 43, 29};
#define BLACKPOINTS 1
int blackNodes[BLACKPOINTS] = {33};
*/
int cost[MAX][MAX];
void setCostValues(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            cost[i][j] = 9999;
        }
    }
cost[32][33] = 1;
cost[33][32] = 1;
cost[37][38] = 1;
cost[38][37] = 1;
cost[32][37] = 1;
cost[37][32] = 1;
cost[33][38] = 1;
cost[38][33] = 1;
cost[0][1] = 1;
cost[1][0] = 1;
cost[0][6] = 1;
cost[6][0] = 1;
cost[1][6] = 1;
cost[6][1] = 1;
cost[13][19] = 2;
cost[19][13] = 2;
cost[6][13] = 3;
cost[13][6] = 3;
cost[19][20] = 2;
cost[20][19] = 2;
cost[13][20] = 3;
cost[20][13] = 3;
cost[14][19] = 3;
cost[19][14] = 3;
cost[13][14] = 2;
cost[14][13] = 2;
cost[14][20] = 2;
cost[20][14] = 2;
cost[20][21] = 2;
cost[21][20] = 2;
cost[21][22] = 1;
cost[22][21] = 1;
cost[22][24] = 1;
cost[24][22] = 1;
cost[22][23] = 2;
cost[23][22] = 2;
cost[23][24] = 2;
cost[24][23] = 2;
cost[14][15] = 2;
cost[15][14] = 2;
cost[15][16] = 2;
cost[16][15] = 2;
cost[15][21] = 2;
cost[21][15] = 2;
cost[14][21] = 3;
cost[21][14] = 3;
cost[15][20] = 3;
cost[20][15] = 3;
cost[16][21] = 3;
cost[21][16] = 3;
cost[15][22] = 3;
cost[22][15] = 3;
cost[16][22] = 2;
cost[22][16] = 2;
cost[2][3] = 2;
cost[3][2] = 2;
cost[7][8] = 2;
cost[8][7] = 2;
cost[2][7] = 1;
cost[7][2] = 1;
cost[3][8] = 1;
cost[8][3] = 1;
cost[2][8] = 3;
cost[8][2] = 3;
cost[3][7] = 3;
cost[7][3] = 3;
cost[6][10] = 2;
cost[10][6] = 2;
cost[7][10] = 2;
cost[10][7] = 2;
cost[6][12] = 2;
cost[12][6] = 2;
cost[12][13] = 1;
cost[13][12] = 1;
cost[13][18] = 2;
cost[18][13] = 2;
cost[18][19] = 2;
cost[19][18] = 2;
cost[12][18] = 2;
cost[18][12] = 2;
cost[19][26] = 3;
cost[26][19] = 3;
cost[26][29] = 2;
cost[29][26] = 2;
cost[31][36] = 1;
cost[36][31] = 1;
cost[30][35] = 1;
cost[35][30] = 1;
cost[30][31] = 1;
cost[31][30] = 1;
cost[35][36] = 1;
cost[36][35] = 1;
cost[20][31] = 1;
cost[31][20] = 1;
cost[39][40] = 3;
cost[40][39] = 3;
cost[27][40] = 3;
cost[40][27] = 3;
cost[38][39] = 3;
cost[39][38] = 3;
cost[31][32] = 1;
cost[32][31] = 1;
cost[36][37] = 1;
cost[37][36] = 1;
cost[31][37] = 1;
cost[37][31] = 1;
cost[32][36] = 1;
cost[36][32] = 1;
cost[28][41] = 2;
cost[41][28] = 2;
cost[24][27] = 1;
cost[27][24] = 1;
cost[24][25] = 1;
cost[25][24] = 1;
cost[27][34] = 1;
cost[34][27] = 1;
cost[25][34] = 1;
cost[34][25] = 1;
cost[24][34] = 1;
cost[34][24] = 1;
cost[25][27] = 1;
cost[27][25] = 1;
cost[28][34] = 1;
cost[34][28] = 1;
cost[17][23] = 1;
cost[23][17] = 1;
cost[11][17] = 2;
cost[17][11] = 2;
cost[5][11] = 1;
cost[11][5] = 1;
cost[4][5] = 1;
cost[5][4] = 1;
cost[4][9] = 1;
cost[9][4] = 1;
cost[8][9] = 2;
cost[9][8] = 2;
cost[3][9] = 2;
cost[9][3] = 2;

    }

#define UINT_MAX 4294967295;
int pathLength;
int pathNodes[1000];
int pathCost = 0;
void dijkstra(int G[MAX][MAX], int n, int startnode, int endnode)
{
    int infinity = 9999;
	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i,j;
	for(i=0;i < n;i++)
		for(j=0;j < n;j++)
			if(G[i][j]==0)
				cost[i][j]=infinity;
			else
				cost[i][j]=G[i][j];

	for(i=0;i< n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count < n-1){
		mindistance=infinity;
		for(i=0;i < n;i++)
			if(distance[i] < mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
		visited[nextnode]=1;
		for(i=0;i < n;i++)
			if(!visited[i])
				if(mindistance+cost[nextnode][i] < distance[i])
				{
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}
			count++;
	}

	for(i=0;i < n;i++)
		if(i!=startnode && i==endnode)
		{
			printf("\nDistance of %d = %d", i, distance[i]);
			pathCost = distance[i];

			printf("\nPath = %d", i);
            pathLength = 0;
			pathNodes[pathLength] = i;
			j=i;
			do
			{
				j=pred[j];
				pathLength++;
				pathNodes[pathLength] = j;
				printf(" <-%d", j);
			}
			while(j!=startnode);
		}
}

int pythagoreanDistance(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
}
int closestNode(int x,int y){
    int minDist = pythagoreanDistance(coordinates[0][0],coordinates[0][1],x,y);
    int startNode = 0;

    for (int i = 1; i<MAX;i++){
        int distance = pythagoreanDistance(coordinates[i][0],coordinates[i][1],x,y);
        //(coordinates[i][0]-x)*(coordinates[i][0]-x) + (coordinates[i][1]-y)*(coordinates[i][1]-y);
        if (distance < minDist){
            minDist = distance;
            startNode = i;
        }
    }
    return startNode;
}

int nodeCounter = 0;
int prevX,prevY;
void startDijkstra(int endNode){
    //Start Node
    setCostValues();
    int startNode = closestNode(PositionX,PositionY);

    dijkstra(cost,MAX,startNode,endNode);
    nodeCounter = pathLength;
    prevX=PositionX, prevY = PositionY;
    printf("\nStartNode: %d\t",startNode);
    printf("\nendNode: %d\t",endNode);
    printf("\nPathLength:%d\t",pathLength);
    printf("NodeCounter:%d\n",nodeCounter);
}
int prevNodeTime = 0;

void moveDijkstra(int x, int y){
    //DEBUG/////////////////////////////////////////////////////////////
    /*printf("\nDijkstra On\n");
    printf("%d\n",nodeCounter);
    printf("At %d,%d: To(%d,%d)\n",
           nodeCounter,
           pathNodes[nodeCounter],
           coordinates[pathNodes[nodeCounter]][0],
           coordinates[pathNodes[nodeCounter]][1]);
    */
    ///////////////////////////////////////////////////////////////////////
    //Check for all nodes, so that able to relocate
if  ((abs(prevX-PositionX)>100 || abs(prevY-PositionY)>100) && PositionX!=0 && PositionY!=0){/*
        for (int i = 0; i< pathLength; i++){
        if (reached(coordinates[pathNodes[i]][0],
                coordinates[pathNodes[i]][1],15,15)){
            nodeCounter = i;
            printf("Newnode %d %d\n",nodeCounter, pathNodes[nodeCounter]);
        }
    }*/
    startDijkstra(pathNodes[0]);
    prevX=PositionX, prevY = PositionY;
    return;

}

    if (nodeCounter<=-1){ //&& !reached(x-5,y-5,5,5)){
            printf("Direct ");
        rotateTo(angle(x, y));
        return;
        //startDijkstra(pathNodes[0]);
    }else{
        printf("Node:%d (%d,%d)\t",pathNodes[nodeCounter],coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);
        rotateTo(angle(coordinates[pathNodes[nodeCounter]][0],
                    coordinates[pathNodes[nodeCounter]][1]));
    }

    if (reached(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1],15,15) || Time - prevNodeTime > 20){
            nodeCounter--; prevNodeTime=Time;
            printf("Newnode %d %d, (%d,%d)\n",nodeCounter, pathNodes[nodeCounter],
                   coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);//startDijkstra(pathNodes[0]);
    }


    prevX=PositionX, prevY = PositionY;

}
int SuperObjTime = 0;
int SuperObjStartTime = 0;
bool superObjDijkstra(){
    if (SuperObj_Num>0 && noSuperObj != SuperObj_Num){
        //if (noSuperObj<SuperObj_Num){
            //Collect 1 superobject at a time
            noSuperObj = SuperObj_Num;
        //}
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;

        int endNode = 0;
        if (SuperObj_Num>0){
            endNode = closestNode(SuperObjX,SuperObjY);
            startDijkstra(endNode);
        }
        SuperObjStartTime = Time;
        return true;
	}
	else if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5,5)
          && Time - SuperObjStartTime  < 40){
            printf("SuperObj \t");

        //Recalculate if sidetracked
        if (SuperObjTime != Time){
            int endNode = 0;
            if (SuperObj_Num>0){
                endNode = closestNode(SuperObjX,SuperObjY);
                startDijkstra(endNode);
            }
        }
        SuperObjTime=Time;

		moveDijkstra(SuperObjX,SuperObjY);
        return true;
	}
	else if (Time - SuperObjStartTime  >= 40){
        noSuperObj = 0;
	}
	return false;
}

bool quarrantine(int x1, int x2, int y1, int y2, int rangex, int rangey){
    if (xreached(x1,rangex) && 0<=Compass && Compass <180){
            if (Compass < 90){
                WheelLeft=5;WheelRight=0;//reverse();
            }
            else{
                WheelLeft=0;WheelRight=5;//reverse();
            }
			return true;
	}
	else if (xreached(x2,rangex) && 180<=Compass && Compass <=360){
            if (Compass < 270){
                WheelLeft=5;WheelRight=0;//reverse();
            }
            else{
                WheelLeft=0;WheelRight=5;//reverse();
            }
        //WheelLeft=-5;WheelRight=5;//reverse();
		return true;
	}
	if (yreached(y1,rangey) && 90<=Compass && Compass <=270){
        reverse();
		return true;
		}
	else if (yreached(y2,rangey) && (Compass>270 || Compass <90)){
        reverse();
		return true;
	}
    return false;
}

int objectCollectionArea = 0;
int prevTime = 0;
int prevLoaded = -60;
bool reachedObjRegion = false;
bool setupCollectionDijkstra(int *objectPoints, int noPoints, bool moveon){
    int collectTime = 20;
    if ((Time - prevTime > collectTime  || LoadedObjects-prevLoaded >=2)  || moveon){
        prevTime = Time;
        objectCollectionArea++;
        prevLoaded = LoadedObjects;
            if (objectCollectionArea >= noPoints){
                objectCollectionArea = 0;
            }

        printf("Change Collection Area to %d\n",objectPoints[objectCollectionArea]);
        startDijkstra(objectPoints[objectCollectionArea]);
    }
    if (LoadedObjects < prevLoaded){ //Deposited
        prevLoaded = LoadedObjects;
        startDijkstra(objectPoints[objectCollectionArea]);
        printf("Refresh\n");
    }
}
bool moveCollectionDijkstra(int *objectPoints){

    int sizex = objectPointsSize[objectCollectionArea][0];//25;
    int sizey = objectPointsSize[objectCollectionArea][1];//25;

    if (reached(coordinates[objectPoints[objectCollectionArea]][0],
                coordinates[objectPoints[objectCollectionArea]][1],sizex,sizey)){
                    //printf("Quarrantined %d\t",objectPoints[objectCollectionArea]);
                     printf("Quarrantined %d\t",objectPoints[objectCollectionArea]);
                 WheelLeft=5;WheelRight=5;
                 quarrantine(coordinates[objectPoints[objectCollectionArea]][0]-sizex,coordinates[objectPoints[objectCollectionArea]][0]+sizex,coordinates[objectPoints[objectCollectionArea]][1]-sizey,coordinates[objectPoints[objectCollectionArea]][1]+sizey,sizex, sizey);
                 //WheelLeft=0;WheelRight=0;
                 //LED_1 = 2;
            return true;
    }else{
        //printf("Travel to obj region %d\t",objectPoints[objectCollectionArea]);
        moveDijkstra(coordinates[objectPoints[objectCollectionArea]][0],
                     coordinates[objectPoints[objectCollectionArea]][1]);
        //rotateTo(angle(coordinates[objectPoints[objectCollectionArea]][0],
        //             coordinates[objectPoints[objectCollectionArea]][1]));
        //reachedObjRegion = false;
        //LED_1=0;
        return true;
    }
    return false;
}
bool collectionDijkstra(bool moveon){
    //int allPoints[MAX] = {0,1,2,3,4,5,6};
    //setupCollectionDijkstra(allPoints, MAX, moveon);
    setupCollectionDijkstra(objectPoints, OBJPOINTS, moveon);
    moveCollectionDijkstra(objectPoints);
}

int zoneDijkstra(int *points, int no){
    int minDist = 2147483647;//INT MAX
    int endNode = points[0];
       for (int i=0;i<no;i++){
            int toGo = pythagoreanDistance(PositionX,PositionY,coordinates[points[i]][0],coordinates[points[i]][1]);
            //dijkstra(cost, coordinates, MAX, startNode,depositNodes[i]);
            if (toGo < minDist){
                minDist = toGo;
                endNode = points[i];
            }
            printf("%d %dNode dist:%d\n",i,points[i],toGo);
        }
        //endNode=13;
    startDijkstra(endNode);
        return endNode;
}

int depositNode = 13;
void depositDijkstra(){depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);}
bool boundary(){
    if ((xreached(10,5) && 0<=Compass && Compass <180)||
        (xreached(340,5) && 180<=Compass && Compass <=360)||
        (yreached(10,5) && 90<=Compass && Compass <=270)||
        (yreached(250,5) && (Compass>270 || Compass <90))){
			WheelLeft=-3;WheelRight=3;
			return true;
			}
    return false;//quarrantine(10,335,10,250,5,5);
}


bool dijkstraStarted = false;
void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	//posInfoLost();
    //printf("Points %d",LoadedPoints);
	//Super Object
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;//LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2;//true;

	if (LoadedRed>=4 ||
	(LoadedObjects >=5 &&  LoadedRed > 0 &&(LoadedBlue==0 || LoadedBlack==0)))
	{collectRed = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectRed = true;}

	if (LoadedBlack>=4 ||
	(LoadedObjects >=5 && LoadedBlack > 0 &&(LoadedBlue==0 || LoadedRed==0)))
	{collectBlack = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectBlack = true;}

	if (LoadedBlue>=4 ||
	(LoadedObjects >=5 && LoadedBlue > 0 &&(LoadedRed==0 || LoadedBlack==0)))
	{collectBlue = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectBlue = true;}



	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	//else if (posInfoLost()){return;}
	else if (boundary()){}
	else if (LoadedObjects >= 4 || LoadedSuperObj > 0){
        if (!dijkstraStarted){depositDijkstra();dijkstraStarted=true;}
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);
    }
	else if (PositionX==0 && PositionY==0){
        WheelLeft=3;WheelRight=3;
	}
	else if (superObjDijkstra()){}

    else if (collectionDijkstra(false)){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}
}

DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        case 0:
            Game0();
            break;
		case 1:
            Game1();
            break;
        default:
            break;
    }
}

