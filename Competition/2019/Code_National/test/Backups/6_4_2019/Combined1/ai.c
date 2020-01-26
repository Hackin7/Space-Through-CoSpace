// Time: 2019-04-06 11:13:17.478538
// File: TEMPLATE/TEMPLATE_START.c
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
// File: Movements/WallAvoiding.c
void world1wallAvoiding()
{
	if (US_Front < 15 && US_Left < 15 && US_Right < 15){
		WheelLeft=3;WheelRight=-3; //Full Turn
		//printf("Corner");
	}
	else if (US_Left < 15){
		WheelLeft=3;WheelRight=-1;
		//printf("Left");
	}
	else if (US_Right < 15){
		WheelLeft=-1;WheelRight=3;
		//printf("Right");
	}
	else if (US_Front < 15){
        if ((270 <= Compass && Compass < 360) &&
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=3;WheelRight=0;//Turn Left
            }
        else{
            WheelLeft=0;WheelRight=3;//Turn Right
        }
            //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}
	else{return false;}// No need to run
	return true; //Ran
}

void reverse(){
    if ((270 <= Compass && Compass < 360) ||
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=5;WheelRight=-5;//Turn Right
            }
        else{
            WheelLeft=-5;WheelRight=5;//Turn Left
        }
}


void wallAvoiding(int dist)
{
	if (US_Front < dist+10 && US_Left < dist && US_Right < dist){
		//reverse();
		WheelLeft=5;WheelRight=-5; //Full Turn
		//printf("Corner");
	}
	else if (US_Left < dist){
		WheelLeft=3;WheelRight=0;
		//printf("Left");
	}
	else if (US_Right < dist){
		WheelLeft=0;WheelRight=3;
		//printf("Right");
	}
	else if (US_Front < dist){
        reverse();
        //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}
	else{return false;}// No need to run
	return true; //Ran
}
// File: CollectObject.c
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

int slowarea[3] = {143,151,197};
bool objCollectDeposit(bool collectBlue,bool collectRed,bool collectBlack,bool deposit){
	int objBlue[3] = {29,249,255};
	int objRed[3] = {235,29,29};
	int objBlack[3] = {20,20,20};
	int specialZone[3]={20,171,235};

	int superObj[3] = {235,20,235};
	int depositOrange[3] = {235,147,20};

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
			return true;
		}
		if (! colorLeftCheck(depositOrange,objRange)){ // Turn Left
			WheelLeft=3;WheelRight=0;
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
// File: Movements/TrapAvoiding.c
bool avoidTrap(bool avoid){
	int trapYellow[3] = {220,235,20};
	int trapBlue[3] = {30,30,203};
	int trapRange=20;
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
// File: Movements/WallTracer.c
int timeout;
//only walltrace if walltrace = 1;
// wallfollowing
bool WallTracer_right(){
	timeout = 0;
	if (US_Right<30){
		WheelLeft = 0;
		WheelRight = 2;
		printf ("wall right");
		timeout++;
	}
	else if (US_Right>50){
		WheelLeft = 2;
		WheelRight = 0;
	}
	else if (timeout >= 100){
		return false;
	}
	return true;
}
// File: Game0.c
/*void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	int timeout = 0;

	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;


	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding(20)){}
	else if (WallTracer_right()){}
	else {
		WheelLeft=4;WheelRight=4;
	}

	if (Time > 180){
			Teleport = 1;
	}
}
*/

void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	/*
	if (Time<5)
	{
		printf("%d\n",Time );;
		if (Time<1){WheelLeft=5;WheelRight=-5;}
		else{WheelLeft=5;WheelRight=5;}
		return;
	}*/
	int zonewhite[3]={220,230,250};
	int zoneblue[3] = {0, 160,245};
	int zonebluerange=30;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	int color=0;
	int prevcolor=0;
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (world1wallAvoiding()){}
	else {
		if (LoadedObjects == 0)
		{
			WheelLeft=5; WheelRight = 5;
		}
		else{
			if (colorCheck(zoneblue, zonebluerange))
			{
				WheelLeft=5; WheelRight=5;/*
				color=2;
				if (LoadedObjects>-1 && prevcolor==1&&color==2&&Compass>245&&Compass<285)
				{//antic
					printf("'AAAAAAA'");
					Duration=2;
						WheelLeft=-5;WheelRight=5;
				}*/
			}
			else {
				WheelLeft=3;WheelRight=3;color=0;
				if (colorCheck(zonewhite, 30))
				{
					color=1;
				}
			}

			prevcolor=color;
				}
				}

	if (Time > 180){
			Teleport = 1;
	}
}
// File: Game1/Trigo.c
double dabs (double x){
    if (x<0){return -x;}
    return x;
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
	int theta = abs(atan(dabs(Ychange/Xchange))/(2*3.14159265358979323846) * 360); // Original arctan value
	//Process angle To turn to, 0 degress is north, goes anticlockwise

	//First quadrant
	if (Ychange>0 && Xchange>0){
            printf("1st");
		theta = 270+theta;
	}
	//Second quadrant
	else if (Ychange>=0 && Xchange<0){
            printf("2nd");
		theta = 90-theta;
	}
	//Third quadrant
	else if (Ychange<0 && Xchange<0){
            printf("3rd");
		theta = 90+theta;
	}
	//Fourth quadrant
	else if (Ychange<=0 && Xchange>0){
            printf("4th");
		theta = 270-theta;
	}
	//printf("New theta %d",theta);
/*
	//DEBUG///////////////////////////////////////////////////////////
	printf("\n\nPosX %d ",PositionX);
	printf("PositionY %d \n",PositionY);
	printf("Xchange %f ",Xchange);
	printf("Ychange %f \n",Ychange);
	printf("atan%d = ",dabs(Ychange/Xchange));
	printf("%d\n\n\n ",theta);
    ///////////////////////////////////////////////////////////////////
*/
	return theta;
}
//bool rotated = 0;
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

void rotateTo(int x, int y){
    double angl = angle(x,y);
	//WheelLeft=-1;WheelRight=-1;
	int range = 10;
	//printf("%d, %d, %d]\n",(int)angle-range, Compass,(int)angle+range);

    if (reached(x,y,10,10)){return;}

    double theta = angl;
	double CWAngleDiff;
  double ACWAngleDiff;
  double AngleDiff;
  AngleDiff = abs(Compass-theta);

  int faster = 0, smaller = 0;
    if (AngleDiff<=5)
    {faster=4;smaller=4;} //printf("10range");}
    else if (AngleDiff<=10)
    {faster=4;smaller=4;}// printf("10range");}
    else if (AngleDiff<=20)
    {faster=4;smaller=3;}//printf("20range");}
    else if (AngleDiff<=67)
    {faster=4;smaller=2;}// printf("45range");}
    else{faster=4;smaller=0;}//printf("SHIT");}

//    if (colorCheck(slowarea,20)){
          faster++;smaller++;
 //         }

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
  {//turn clockwise
    WheelLeft=faster;WheelRight=smaller;//clockwise(theta);
  }
  else if(ACWAngleDiff<CWAngleDiff)
  { //turn anti-clockwise
    WheelLeft=smaller;WheelRight=faster;//aclockwise(theta);
  }/*
	int diffToACWM = (int)angle - Compass; // Angle antiClockwise of compass
	int diffToCWM = 360-abs(diffToACWM); // Other way
	if ( (diffToACWM < 0 && abs(diffToACWM) < diffToCWM) ||
	//Angle anticlockwise of compass and
		 (diffToACWM > 0 && abs(diffToACWM) > diffToCWM) )
	{
		WheelLeft=4;WheelRight=5;//WheelLeft=4;WheelRight=2; //Anticlockwise Turn
	}
	else {
		WheelLeft=5;WheelRight=4; //Clockwise Turn
	}*/
}
// File: Game1/PosInfoLost.c
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
int speed;
bool posInfoLost(){
    if (PositionX==0 && PositionY==0)
    {
			if ((WheelLeft<2 && WheelLeft>-2) || (WheelRight>-2 && WheelRight<2)) // can ignore i guess? since its probably turning
			{
				PositionX=tx;
				PositionY=tx;
				return;
			}
      speed=(WheelLeft+WheelRight)/3.48;
      tx = speed * cos((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + tx;
      ty =speed * sin((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + ty;
			PositionX=tx;
			PositionY=ty;
    }

icompass=Compass;
tx = PositionX;
ty = PositionY;
}
// File: Game1/boundary.c
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
        WheelLeft=5;WheelRight=-4;
		return true;
		}
	else if (yreached(y2,rangey) && (Compass>270 || Compass <90)){
        WheelLeft=5;WheelRight=-4;
		return true;
	}
    return false;
}

bool boundary(){
    if ((xreached(22,5) && 0<=Compass && Compass <180)||
        (xreached(343,5) && 180<=Compass && Compass <=360)||
        (yreached(22,5) && 90<=Compass && Compass <=270)||
        (yreached(250,5) && (Compass>270 || Compass <90))){
			WheelLeft=-5;WheelRight=5;
			//Duration=2;
			return true;
			}
    return false;//quarrantine(10,335,10,250,5,5);
}

// File: Game1NodesANDCoordinates/2019RCJDay1.c
#define MAX 50
int coordinates[MAX][2] = {{66, 252}, {112, 241}, {149, 242}, {223, 244}, {259, 240}, {301, 252}, {343, 257}, {28, 215}, {77, 204}, {111, 217}, {149, 217}, {190, 216}, {227, 217}, {265, 219}, {312, 225}, {31, 169}, {74, 176}, {117, 165}, {150, 164}, {184, 165}, {226, 165}, {265, 182}, {28, 137}, {263, 142}, {321, 153}, {27, 104}, {69, 113}, {116, 110}, {149, 109}, {183, 108}, {223, 107}, {320, 120}, {266, 98}, {27, 57}, {79, 58}, {109, 59}, {149, 57}, {187, 57}, {228, 57}, {265, 58}, {68, 19}, {97, 31}, {150, 33}, {226, 31}, {268, 33}, {323, 46}, {304, 17}, {345, 13}};
#define DEPOSITNODES 1
int depositNodes[DEPOSITNODES] = {47};//,6};

#define OBJPOINTS 7
int objectPoints[OBJPOINTS] = {29,31, 1, 18, 20,41};
int objectPointsSize[OBJPOINTS][2] = {{25,25},{25,25},{12,12},{25,25},{25,25},{12,12}};
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
    }cost[15][16] = 1;
cost[16][15] = 1;
cost[16][17] = 1;
cost[17][16] = 1;
cost[15][22] = 1;
cost[22][15] = 1;
cost[22][25] = 1;
cost[25][22] = 1;
cost[25][26] = 1;
cost[26][25] = 1;
cost[25][33] = 1;
cost[33][25] = 1;
cost[33][34] = 1;
cost[34][33] = 1;
cost[33][40] = 1;
cost[40][33] = 1;
cost[34][40] = 1;
cost[40][34] = 1;
cost[40][41] = 1;
cost[41][40] = 1;
cost[41][42] = 2;
cost[42][41] = 2;
cost[0][8] = 2;
cost[8][0] = 2;
cost[7][8] = 2;
cost[8][7] = 2;
cost[0][1] = 1;
cost[1][0] = 1;
cost[1][2] = 1;
cost[2][1] = 1;
cost[46][47] = 1;
cost[47][46] = 1;
cost[44][46] = 1;
cost[46][44] = 1;
cost[43][44] = 1;
cost[44][43] = 1;
cost[45][46] = 1;
cost[46][45] = 1;
cost[45][47] = 1;
cost[47][45] = 1;
cost[26][27] = 1;
cost[27][26] = 1;
cost[39][45] = 3;
cost[45][39] = 3;
cost[32][39] = 1;
cost[39][32] = 1;
cost[32][45] = 4;
cost[45][32] = 4;
cost[31][32] = 2;
cost[32][31] = 2;
cost[24][31] = 1;
cost[31][24] = 1;
cost[23][31] = 2;
cost[31][23] = 2;
cost[23][24] = 2;
cost[24][23] = 2;
cost[23][32] = 1;
cost[32][23] = 1;
cost[21][23] = 1;
cost[23][21] = 1;
cost[13][21] = 1;
cost[21][13] = 1;
cost[3][4] = 1;
cost[4][3] = 1;
cost[4][5] = 1;
cost[5][4] = 1;
cost[5][6] = 1;
cost[6][5] = 1;
cost[5][14] = 1;
cost[14][5] = 1;
cost[6][14] = 1;
cost[14][6] = 1;
cost[13][14] = 1;
cost[14][13] = 1;
cost[14][21] = 3;
cost[21][14] = 3;
cost[12][13] = 1;
cost[13][12] = 1;
cost[11][12] = 1;
cost[12][11] = 1;
cost[9][10] = 1;
cost[10][9] = 1;
cost[10][11] = 1;
cost[11][10] = 1;
cost[17][18] = 1;
cost[18][17] = 1;
cost[18][19] = 1;
cost[19][18] = 1;
cost[19][20] = 1;
cost[20][19] = 1;
cost[27][28] = 1;
cost[28][27] = 1;
cost[35][36] = 1;
cost[36][35] = 1;
cost[36][37] = 1;
cost[37][36] = 1;
cost[37][38] = 1;
cost[38][37] = 1;
cost[38][39] = 1;
cost[39][38] = 1;
cost[28][29] = 1;
cost[29][28] = 1;
cost[29][30] = 1;
cost[30][29] = 1;
cost[30][32] = 1;
cost[32][30] = 1;
cost[23][30] = 1;
cost[30][23] = 1;
cost[20][21] = 1;
cost[21][20] = 1;
cost[20][23] = 1;
cost[23][20] = 1;
cost[9][17] = 2;
cost[17][9] = 2;
cost[27][35] = 2;
cost[35][27] = 2;
cost[17][27] = 2;
cost[27][17] = 2;
cost[10][18] = 2;
cost[18][10] = 2;
cost[18][28] = 2;
cost[28][18] = 2;
cost[28][36] = 3;
cost[36][28] = 3;
cost[29][37] = 2;
cost[37][29] = 2;
cost[30][38] = 2;
cost[38][30] = 2;
cost[19][29] = 2;
cost[29][19] = 2;
cost[20][30] = 2;
cost[30][20] = 2;
cost[11][19] = 2;
cost[19][11] = 2;
cost[12][20] = 2;
cost[20][12] = 2;
cost[9][18] = 2;
cost[18][9] = 2;
cost[10][17] = 2;
cost[17][10] = 2;
cost[10][19] = 2;
cost[19][10] = 2;
cost[11][20] = 2;
cost[20][11] = 2;
cost[12][21] = 2;
cost[21][12] = 2;
cost[11][18] = 2;
cost[18][11] = 2;
cost[12][19] = 2;
cost[19][12] = 2;
cost[13][20] = 2;
cost[20][13] = 2;
cost[17][28] = 2;
cost[28][17] = 2;
cost[18][29] = 2;
cost[29][18] = 2;
cost[19][30] = 2;
cost[30][19] = 2;
cost[18][27] = 2;
cost[27][18] = 2;
cost[19][28] = 2;
cost[28][19] = 2;
cost[20][29] = 2;
cost[29][20] = 2;
cost[27][36] = 2;
cost[36][27] = 2;
cost[28][37] = 2;
cost[37][28] = 2;
cost[29][38] = 2;
cost[38][29] = 2;
cost[20][32] = 2;
cost[32][20] = 2;
cost[30][39] = 2;
cost[39][30] = 2;
cost[28][35] = 2;
cost[35][28] = 2;
cost[29][36] = 2;
cost[36][29] = 2;
cost[30][37] = 2;
cost[37][30] = 2;
cost[32][38] = 2;
cost[38][32] = 2;
cost[0][7] = 1;
cost[7][0] = 1;
cost[7][15]=1;
cost[15][7]=1;
    }

// File: Game1Dijkstra/dijkstra.c
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

			for(int k=0;k< 1000;k++)
            {
                pathNodes[k] = 0;
            }

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
// File: Game1Dijkstra/moveDijkstra.c

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

void startDijkstraStart(int startNode, int endNode){
    //Start Node
    setCostValues();

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
    startDijkstra(pathNodes[0]);
    //Check for all nodes, so that able to relocate
    if  ((abs(prevX-PositionX)>100 || abs(prevY-PositionY)>100) && PositionX!=0 && PositionY!=0){
        startDijkstra(pathNodes[0]);
        prevX=PositionX, prevY = PositionY;
        return;

    }

        if (reached(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1],30,30)){
            nodeCounter--; prevNodeTime=Time;
            printf("Newnode %d %d, (%d,%d)\n",nodeCounter, pathNodes[nodeCounter],
                   coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);//startDijkstra(pathNodes[0]);

    if (nodeCounter<=-1){ //&& !reached(x-5,y-5,5,5)){
           // printf("Direct ");
        rotateTo(x, y);
        return;
        //startDijkstra(pathNodes[0]);
    }else{
        printf("Node:%d (%d,%d)\t",pathNodes[nodeCounter],coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);
        rotateTo(coordinates[pathNodes[nodeCounter]][0],
                    coordinates[pathNodes[nodeCounter]][1]);
    }

    if (Time - prevNodeTime > 20){
        if (nodeCounter == pathLength){
                startDijkstraStart(pathNodes[nodeCounter], pathNodes[0]);
        }
        else{
                startDijkstraStart(pathNodes[nodeCounter+1], pathNodes[0]);
        }
        prevNodeTime=Time;
    }
            //WheelLeft=0;WheelRight=0;
            //Duration=1;
    }


    prevX=PositionX, prevY = PositionY;

}
// File: Game1Dijkstra/superObjDijkstra.c
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
	else if (noSuperObj>0 && reached(SuperObjX,SuperObjY,22,22)){
        WheelLeft=3;WheelRight=3;
        quarrantine(SuperObjX-11,
                    SuperObjX+11,
                    SuperObjY-11,
                    SuperObjY+11,11, 11);
        return true;
    }
	else if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5,5)
          && Time - SuperObjStartTime  < 60){
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
// File: Game1Dijkstra/collectionDijkstra.c

int objectCollectionArea = 0;
int prevCollectionTime = 0;
int prevLoaded = -60;
bool reachedObjRegion = false;
bool setupCollectionDijkstra(int *objectPoints, int noPoints, bool moveon){
    int collectTime = 20;
    if (Time - prevCollectionTime > collectTime || moveon){//} || LoadedObjects-prevLoaded >=2){
        prevCollectionTime = Time;
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

double randomness[10][2] = {{0.6169011912620882, 0.41359524497141387}, {0.08755616375412689, 0.7009712280389377}, {0.7872038990460901, 0.4833193040772631}, {0.7350020616781006, 0.6070434995859642}, {0.14521003377638675, 0.07102237538339928}, {0.6808936060819739, 0.43353382884636915}, {0.5393546784424003, 0.4166507272523542}, {0.6348521888982387, 0.2724089257609801}, {0.740697955711559, 0.5928818961567596}, {0.9443143236809757, 0.1805145219031291}};
int random = 0;
bool moveCollectionDijkstra(int *objectPoints){

    int sizex = objectPointsSize[objectCollectionArea][0];//25;
    int sizey = objectPointsSize[objectCollectionArea][1];//25;

    if (reached(coordinates[objectPoints[objectCollectionArea]][0],
                coordinates[objectPoints[objectCollectionArea]][1],sizex,sizey)){
/*
                int cx = (int)(randomness[random][0]*sizex) + coordinates[objectPoints[objectCollectionArea]][0];
                int cy = (int)(randomness[random][1]*sizey) + coordinates[objectPoints[objectCollectionArea]][1];
                if (reached(cx,cy,8,8)){
                    random++;
                    if (random >= 10){random = 0;}
                }
                rotateTo(cx,cy);
                printf("Randomness (%d,%d)\t",cx,cy);

*/
                //Quarrantined
                printf("Quarrantined %d\t",objectPoints[objectCollectionArea]);
                WheelLeft=3;WheelRight=3;
                quarrantine(coordinates[objectPoints[objectCollectionArea]][0]-sizex,coordinates[objectPoints[objectCollectionArea]][0]+sizex,coordinates[objectPoints[objectCollectionArea]][1]-sizey,coordinates[objectPoints[objectCollectionArea]][1]+sizey,sizex, sizey);


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
// File: Game1Dijkstra/zoneDijkstra.c
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

bool dijkstraStarted = false;
int prevDepositTime = 0;
int depositNode = 13;
void depositDijkstra(){
    if (LoadedObjects >= 4 || LoadedSuperObj > 0){
        if (!dijkstraStarted){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            dijkstraStarted=true;
        }
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);

        if (Time - prevDepositTime > 10){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            prevDepositTime = Time;
        }
    }
    else{
            dijkstraStarted = false;
        }
}

// File: Game1Strategies/BASEStrategies.c
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

// File: Game1Strategies/GoToNode.c
void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	posInfoLost();
    //printf("Points %d",LoadedPoints);
	//Super Object
	bool collectBlue = LoadedObjects<=7;//true;
	bool collectRed = LoadedObjects<=7;//true;
	bool collectBlack = LoadedObjects<=7;//true;
	bool deposit = true;//LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2|| LoadedSuperObj > 0;;//true;
/*
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
*/


	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing

	//else if ((US_Front < 20)){WheelLeft=-3;WheelRight=-3;Duration=10;}

	//else if (posInfoLost()){return;}
	else if (boundary()){}
	/*AvoidSlowAres
	else if (colorCheck(slowarea,20)){
          WheelLeft=-1;WheelRight=-5; // Turn
            Duration=10;
          }
*/
    else if (wallAvoiding(15)){}
	else if (depositDijkstra()){}
	//else if (PositionX==0 && PositionY==0){WheelLeft=3;WheelRight=3;}
	else if (superObjDijkstra()){}

    else if (collectionDijkstra(false)){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}
}
// File: TEMPLATE/TEMPLATE_END.c

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

