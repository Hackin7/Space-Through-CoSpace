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
     return "CoSpace Team";
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
void wallAvoiding()
{
	if (US_Front < 25 && US_Left < 20 && US_Right < 20){
		WheelLeft=5;WheelRight=-5; //Full Turn
		//printf("Corner");
	}
	else if (US_Left < 20){
		WheelLeft=3;WheelRight=-2;
		//printf("Left");
	}
	else if (US_Right < 20){
		WheelLeft=-2;WheelRight=3;
		//printf("Right");
	}
	else if (US_Front < 20){
		WheelLeft=-5;WheelRight=5;
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
int noSuperObj = 0;
int SuperObjX;//[20];
int SuperObjY;//[20];
bool objCollectDeposit(bool collectBlue,bool collectRed,bool collectBlack,bool deposit){
	int objBlue[3] = {29,249,255};
	int objRed[3] = {235,29,29};
	int objBlack[3] = {20,20,20};
	int superObj[3] = {235,20,235};
	int depositOrange[3] = {215,140,20};

	int objRange=20;
	if (colorCheck(objBlue,objRange) && LoadedObjects < 6 && collectBlue)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedBlue++;
		printf("Blue_Object ");
	}
	else if (colorCheck(objRed,objRange) && LoadedObjects < 6 && collectRed)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedRed++;
		printf("Red_Object ");
	}
	else if (colorCheck(objBlack,objRange) && LoadedObjects < 6 && collectBlack)
	{
		WheelLeft=0;WheelRight=-0;
		LED_1 =1;
		Duration=41;
		LoadedObjects++;
		LoadedBlack++;
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
bool avoidTrap(){
	int trapYellow[3] = {225,225,50};
	int trapBlue[3] = {20,20,235};
	if (LoadedObjects > 0 && colorCheck(trapYellow,50)){//objRange ) &&)){
		WheelLeft=-2;WheelRight=-5; // Turn
		Duration=10;
		printf("Danger\n");
		return true;
		//Duration=41;
	}
	else if (colorCheck(trapBlue,50)){
		LoadedObjects=0;
		LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
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

	if (avoidTrap()){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	else {
		WheelLeft=3;WheelRight=3;
	}

	if (Time > 180){
			Teleport = 1;
	}
}


double dabs(double i){
	if (i<0){return -i;}
	else{ return i;}
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

	printf("PosX %d ",PositionX);
	printf("PositionY %d \n",PositionY);
	printf("Xchange %d ",Xchange);
	printf("Ychange %d \n",Ychange);
	printf("atan%d = ",dabs(Ychange/Xchange));
	printf("%d\n ",theta);

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
	printf("New theta %d",theta);
	return theta;
}
//bool rotated = 0;
void rotateTo(double angle){
	//WheelLeft=-1;WheelRight=-1;
	if  (angle-5<= Compass && Compass <= angle+5){
		return;
	}

	int diffToACWM = (int)angle - Compass; // Angle antiClockwise of compass
	int diffToCWM = 360-abs(diffToACWM); // Other way
	if ( (diffToACWM < 0 && abs(diffToACWM) < diffToCWM) ||
	//Angle anticlockwise of compass and
		 (diffToACWM > 0 && abs(diffToACWM) > diffToCWM) )
	{
		WheelLeft=5;WheelRight=1; //Anticlockwise Turn
	}
	else {
		WheelLeft=1;WheelRight=5; //Clockwise Turn
	}
	//Duration = 1;
}

bool xreached(int x,int range){
	return (x-range<=PositionX && PositionX <= x+range);
}
bool yreached(int y,int range){
	return (y-range<=PositionY && PositionY <= y+range);
}
bool reached(int x,int y,int range){
	return ((x-range<=PositionX && PositionX <= x+range) &&
	    (y-range<=PositionY && PositionY <= y+range));
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


#define MAX 44

int coordinates[MAX][2] = { {11, 259}, {51, 261}, {88, 257}, {148, 260}, {210, 259}, {286, 258}, {336, 258}, {26, 223}, {145, 225}, {207, 226}, {248, 219}, {288, 224}, {334, 229}, {140, 198}, {13, 176}, {101, 176}, {249, 191}, {301, 193}, {320, 173}, {12, 138}, {72, 137}, {155, 124}, {216, 125}, {314, 134}, {17, 99}, {64, 99}, {107, 95}, {152, 95}, {198, 96}, {275, 105}, {16, 61}, {63, 59}, {113, 59}, {161, 62}, {201, 60}, {252, 60}, {342, 63}, {17, 23}, {66, 23}, {112, 24}, {184, 22}, {232, 21}, {289, 24}, {339, 22}};
int cost[MAX][MAX];
void setCostValues(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            cost[i][j] = 9999;
        }
    }
    cost[0][1] = 3;
cost[1][0] = 3;
cost[1][2] = 3;
cost[2][1] = 3;
cost[2][3] = 5;
cost[3][2] = 5;
cost[3][4] = 4;
cost[4][3] = 4;
cost[3][8] = 2;
cost[8][3] = 2;
cost[3][9] = 3;
cost[9][3] = 3;
cost[8][9] = 3;
cost[9][8] = 3;
cost[4][9] = 2;
cost[9][4] = 2;
cost[9][10] = 1;
cost[10][9] = 1;
cost[10][11] = 2;
cost[11][10] = 2;
cost[5][6] = 3;
cost[6][5] = 3;
cost[5][11] = 2;
cost[11][5] = 2;
cost[5][12] = 3;
cost[12][5] = 3;
cost[6][12] = 2;
cost[12][6] = 2;
cost[6][11] = 3;
cost[11][6] = 3;
cost[4][13] = 4;
cost[13][4] = 4;
cost[9][13] = 3;
cost[13][9] = 3;
cost[9][16] = 2;
cost[16][9] = 2;
cost[9][17] = 4;
cost[17][9] = 4;
cost[10][17] = 2;
cost[17][10] = 2;
cost[11][17] = 2;
cost[17][11] = 2;
cost[16][17] = 3;
cost[17][16] = 3;
cost[17][18] = 1;
cost[18][17] = 1;
cost[18][23] = 1;
cost[23][18] = 1;
cost[0][7] = 3;
cost[7][0] = 3;
cost[1][7] = 3;
cost[7][1] = 3;
cost[7][14] = 1;
cost[14][7] = 1;
cost[14][19] = 1;
cost[19][14] = 1;
cost[19][24] = 1;
cost[24][19] = 1;
cost[24][30] = 3;
cost[30][24] = 3;
cost[30][37] = 2;
cost[37][30] = 2;
cost[37][38] = 3;
cost[38][37] = 3;
cost[38][39] = 2;
cost[39][38] = 2;
cost[32][39] = 2;
cost[39][32] = 2;
cost[31][32] = 2;
cost[32][31] = 2;
cost[31][39] = 3;
cost[39][31] = 3;
cost[32][38] = 3;
cost[38][32] = 3;
cost[31][38] = 2;
cost[38][31] = 2;
cost[30][31] = 3;
cost[31][30] = 3;
cost[31][37] = 4;
cost[37][31] = 4;
cost[30][38] = 4;
cost[38][30] = 4;
cost[40][41] = 2;
cost[41][40] = 2;
cost[41][42] = 3;
cost[42][41] = 3;
cost[42][43] = 1;
cost[43][42] = 1;
cost[36][43] = 1;
cost[43][36] = 1;
cost[35][42] = 3;
cost[42][35] = 3;
cost[34][42] = 5;
cost[42][34] = 5;
cost[34][35] = 3;
cost[35][34] = 3;
cost[35][41] = 5;
cost[41][35] = 5;
cost[34][41] = 3;
cost[41][34] = 3;
cost[33][34] = 2;
cost[34][33] = 2;
cost[33][40] = 2;
cost[40][33] = 2;
cost[33][41] = 3;
cost[41][33] = 3;
cost[34][40] = 3;
cost[40][34] = 3;
cost[29][35] = 1;
cost[35][29] = 1;
cost[23][29] = 1;
cost[29][23] = 1;
cost[28][34] = 2;
cost[34][28] = 2;
cost[22][28] = 2;
cost[28][22] = 2;
cost[21][22] = 2;
cost[22][21] = 2;
cost[21][28] = 2;
cost[28][21] = 2;
cost[22][27] = 2;
cost[27][22] = 2;
cost[24][25] = 2;
cost[25][24] = 2;
cost[25][26] = 2;
cost[26][25] = 2;
cost[26][27] = 2;
cost[27][26] = 2;
cost[27][28] = 2;
cost[28][27] = 2;
cost[21][27] = 2;
cost[27][21] = 2;
cost[25][30] = 5;
cost[30][25] = 5;
cost[24][31] = 5;
cost[31][24] = 5;
cost[20][25] = 1;
cost[25][20] = 1;
cost[15][20] = 1;
cost[20][15] = 1;
cost[13][15] = 1;
cost[15][13] = 1;
cost[25][31] = 3;
cost[31][25] = 3;
cost[26][32] = 2;
cost[32][26] = 2;
cost[25][32] = 3;
cost[32][25] = 3;
cost[26][31] = 3;
cost[31][26] = 3;
cost[26][33] = 3;
cost[33][26] = 3;
cost[27][32] = 3;
cost[32][27] = 3;
cost[32][33] = 2;
cost[33][32] = 2;
cost[27][33] = 2;
cost[33][27] = 2;
cost[27][34] = 3;
cost[34][27] = 3;
cost[28][33] = 3;
cost[33][28] = 3;
cost[8][13] = 1;
cost[13][8] = 1;
cost[11][12] = 2;
cost[12][11] = 2;
cost[11][16] = 2;
cost[16][11] = 2;}

#define UINT_MAX 4294967295;
int pathLength;
int pathNodes[1000];
int pathCost = 0;
int dijkstra(int G[MAX][MAX],int n,int startnode, int endnode)
{
	int calcost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				calcost[i][j]=9999;//INFINITY;
			else
				calcost[i][j]=G[i][j];
	for(i=0;i<n;i++)
	{
		distance[i]=calcost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n-1)
	{
		mindistance=INFINITY;
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+calcost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+calcost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
	//print the path and distance of each node
	for(i=0;i<n;i++)
		if(i!=startnode && i==endnode)
		{

            printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);
            j=i;
			int c = 0;
            pathNodes[c] = j;
			do{
				j=pred[j];
				c++;
				printf("<-%d",j);
				pathNodes[c] = j;
			}while(j!=startnode);
			pathCost = distance[i];
            printf("\nPathLength%d=%d",i,c);
            pathLength = c;
            return;
	}
}

//////////////////////////////////////////
int pythagoreanDistance(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
}
int closestNode(int x,int y){
    int minDist = 10000000;int startNode = -1;
    int distances[MAX];
    for (int i = 0; i<MAX;i++){
        distances[i] = pythagoreanDistance(coordinates[i][0],coordinates[i][1],x,y);
        //(coordinates[i][0]-x)*(coordinates[i][0]-x) + (coordinates[i][1]-y)*(coordinates[i][1]-y);
        if (distances[i] < minDist){
            minDist = distances[i];
            startNode = i;
        }
    }
    return startNode;
}

int nodeCounter = 0;
int depositNode = 13;
void startDijkstra(bool deposit){
    //Start Node
    setCostValues();
    int startNode = closestNode(PositionX,PositionY);
    printf("\nStartNode: %d\n",startNode);
    //If Loaded
    int depositNodes[4] = {13, 20, 23, 35};
    int minDist = 2147483647;//INT MAX
    int endNode = depositNodes[0];
    if (deposit){
       for (int i=0;i<4;i++){
            int toDeposit = pythagoreanDistance(PositionX,PositionY,coordinates[depositNodes[i]][0],coordinates[depositNodes[i]][1]);
            //dijkstra(cost, coordinates, MAX, startNode,depositNodes[i]);
            if (toDeposit < minDist){
                minDist = toDeposit;
                endNode = depositNodes[i];
            }
            printf("%d %dNode dist:%d\n",i,depositNodes[i],toDeposit);
        }
        //endNode=13;
        depositNode = endNode;
    }
    else if (SuperObj_Num>0){
        endNode = closestNode(SuperObjX,SuperObjY);
    }

    printf("\nendNode: %d\n",endNode);
    dijkstra(cost,MAX,startNode,endNode);
    printf("\nPathLength:%d\n",pathLength);
    nodeCounter = pathLength;
    printf("NodeCounter:%d\n",nodeCounter);

}
void moveDijkstra(int x, int y){
    printf("\nDijkstra On\n");
    printf("%d\n",nodeCounter);

    if (nodeCounter==-1 && !reached(x-5,y-5,5)){
        rotateTo(angle(x, y));
        return;
    }
    printf("At %d,%d: To(%d,%d)\n",
           nodeCounter,
           pathNodes[nodeCounter],
           coordinates[pathNodes[nodeCounter]][0],
           coordinates[pathNodes[nodeCounter]][1]);
    rotateTo(angle(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1]));

    //Check for all nodes, so that able to relocate
    for (int i = 0; i< pathLength; i++){
        if (reached(coordinates[pathNodes[i]][0],
                coordinates[pathNodes[i]][1],15)){
            nodeCounter = i-1;
        }
    }

    if (reached(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1],15)){
            nodeCounter--;
    }

}
bool dijkstraStarted = false;
void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}
	//Game0();
	int depositOrange[3] = {215,140,20};

	if (colorCheck(depositOrange,20))
	{
	//	rotateTo(angle(100,100));
		//moveTo(100,100);
		//printf("%d",angle(0,100));
	}

	//Super Object
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;

	if (LoadedRed>=4 ||
	(LoadedObjects >=5 &&  LoadedRed > 0 &&(LoadedBlue==0 || LoadedBlack==0)))
	{collectRed = false;}
	else{collectRed = true;}

	if (LoadedBlack>=4 ||
	(LoadedObjects >=5 && LoadedBlack > 0 &&(LoadedBlue==0 || LoadedRed==0)))
	{collectBlack = false;}
	else{collectBlack = true;}

	if (LoadedBlue>=4 ||
	(LoadedObjects >=5 && LoadedBlue > 0 &&(LoadedRed==0 || LoadedBlack==0)))
	{collectBlue = false;}
	else{collectBlue = true;}

	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap()){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	//else if (posInfoLost()){return;}
	else {if (xreached(10,5) && 0<=Compass && Compass <180){
			printf("XLeftBoundary ");
			WheelLeft=-5;WheelRight=5;
			return;
		}
		else if (xreached(335,5) && 180<=Compass && Compass <=360){
			printf("XRightBoundary ");
			WheelLeft=-5;WheelRight=5;
			return;
		}
		if (yreached(10,5) && 90<=Compass && Compass <=270){
			printf("YBottomBoundary ");
			WheelLeft=-5;WheelRight=5;
			return;
			}
		else if (yreached(250,5) && (Compass>270 || Compass <90)){
			printf("YTopBoundary ");
			WheelLeft=-5;WheelRight=5;
			return;
			}
        else if (LoadedObjects >= 4){
            if (!dijkstraStarted){startDijkstra(true);dijkstraStarted=true;}
            printf("depositNode:%d",depositNode);
            moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);
        }
		else { // Default Movement
			WheelLeft=3;WheelRight=3;
		}
	}
	//Reach Point
	if (SuperObj_Num>0){
        if (noSuperObj<SuperObj_Num){
            noSuperObj = SuperObj_Num;
        }
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
        startDijkstra(false);
	}
	if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5)){
		moveDijkstra(SuperObjX,SuperObjY);
		//rotateTo(angle(SuperObjX,SuperObjY));
		//printf("SuperObjs %d \n",SuperObjs);
	}
	//else if ( reached(SuperObjX,SuperObj_Y,5)){
	//}
	//else{WheelLeft=0;WheelRight=0;}
	//moveTo(100,100);
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

