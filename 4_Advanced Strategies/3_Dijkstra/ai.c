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
void Game0(){}

////Trigonometry///////////////////////////////////////////////
//Calculate angle from current position to target location
double angle(int x, int y,int posX, int posY){
	double Ychange = (y-posY); double Xchange = (x-posX);
	if (Xchange == 0 && Ychange > 0){return 0;}
	if (Xchange == 0 && Ychange < 0){return 180;}

	//Basic angle
	int theta = abs(atan(Ychange/Xchange)/(2*3.14159265358979323846) * 360);

    //Convert theta to Degress format output by the compass:
    //        0 degrees upward, goes anticlockwise to 359 degrees
	//First quadrant
	if (Ychange>0 && Xchange>0){theta = 270+theta;}
	//Second quadrant
	else if (Ychange>=0 && Xchange<0){theta = 90-theta;}
	//Third quadrant
	else if (Ychange<0 && Xchange<0){theta = 90+theta;}
	//Fourth quadrant
	else if (Ychange<=0 && Xchange>0){theta = 270-theta;}
	return theta;
}
//Turn and move at target angle
void rotateRobot(double theta){
	double AngleDiff = abs(Compass-theta);

    if(AngleDiff>180){AngleDiff=360-AngleDiff;}

    //Set the degree to turn to
    int faster = 0, smaller = 0;
    if (AngleDiff<5){faster=4;smaller=4;} // Go Straight
    else if (AngleDiff<15){faster=4;smaller=3;}
    else if (AngleDiff<30){faster=4;smaller=2;}
    else if (AngleDiff<80){faster=3;smaller=1;}
    else if (AngleDiff<130){faster=3;smaller=-3;}
    else if (AngleDiff<180){faster=5;smaller=-4;}
    else{faster=4;smaller=0;} //Failsafe

    //turn to theta
    //step 1: determine clockwise and anti-clockwise angle difference
    double CWAngleDiff, ACWAngleDiff; //Clockwise, Anticlockwise
    if(Compass>theta){
        CWAngleDiff=Compass-theta;
        ACWAngleDiff=360-(Compass-theta);
    }else if(theta>Compass){
        ACWAngleDiff=theta-Compass;
        CWAngleDiff=360-(theta-Compass);
    }else{
        ACWAngleDiff=0;
        CWAngleDiff=0;
    }

    //step 2: determine if CWAngleDiff or ACWAngleDiff is lower
    if(CWAngleDiff<ACWAngleDiff || CWAngleDiff==180){//turn clockwise
        WheelLeft=faster;WheelRight=smaller;//clockwise(theta);
    }
    else if(ACWAngleDiff<CWAngleDiff){ //turn anti-clockwise
        WheelLeft=smaller;WheelRight=faster;//aclockwise(theta);
    }
}
//Wrapper Function
void rotateTo(int x, int y){
    rotateRobot(angle(x,y, PositionX,PositionY));
}

////Dijkstra //////////////////////////////////////////////////
#define MAX 22
int xval[MAX] = {0,113,166,228,305,45 ,169,169,305,48 ,137,213,305,36 ,97 ,142,167,214,305,67 ,303,338};
int yval[MAX] = {0,251,246,245,238,190,165,190,185,130,128,110,133,68 ,75 ,86 ,30 ,55 ,82 ,30 ,41 ,22};

int cost[MAX][MAX];
void setCostValues(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            cost[i][j] = 9999;
        }
    }
cost[1][1] = 1;
cost[1][5] = 2;
cost[1][2] = 1;
cost[2][3] = 1;
cost[3][4] = 1;
cost[4][8] = 1;
cost[8][12] = 1;
cost[12][18] = 1;
cost[18][20] = 1;
cost[20][21] = 1;
cost[5][9] = 1;
cost[9][13] = 1;
cost[13][14] = 1;
cost[13][19] = 1;
cost[14][19] = 1;
cost[14][15] = 1;
cost[10][15] = 1;
cost[11][15] = 3;
cost[6][10] = 1;
cost[6][7] = 1;
cost[6][11] = 1;
cost[11][17] = 1;
cost[16][17] = 1;
cost[15][16] = 1;
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
			//printf("\nDistance of %d = %d", i, distance[i]);
			pathCost = distance[i];

			for(int k=0;k< 1000;k++)
            {
                pathNodes[k] = 0;
            }

			//printf("\nPath = %d", i);
            pathLength = 0;
			pathNodes[pathLength] = i;
			j=i;
			do
			{
				j=pred[j];
				pathLength++;
				pathNodes[pathLength] = j;
				//printf(" <-%d", j);
			}
			while(j!=startnode);
		}
}

////////////////////////////////////////
int reached(int x, int y, int rangex, int rangey){
    return (x-rangex <= PositionX && PositionX <= x+rangex && y-rangey <= PositionY && PositionY <= y+rangey);
}

int pythagoreanDistance(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
}
int closestNode(int x,int y){
    int minDist = pythagoreanDistance(xval[0],yval[0],x,y);
    int startNode = 0;

    for (int i = 1; i<MAX;i++){
        int distance = pythagoreanDistance(xval[i],yval[i],x,y);
        //(coordinates[i][0]-x)*(coordinates[i][0]-x) + (coordinates[i][1]-y)*(coordinates[i][1]-y);
        if (distance < minDist){
            minDist = distance;
            startNode = i;
        }
    }
    return startNode;
}

void moveDijkstra(int endNode){
    setCostValues();
    int startNode = closestNode(PositionX,PositionY);
    if (closestNode == endNode){return;}
    dijkstra(cost,MAX,startNode,endNode);
    int nodeCounter = pathLength-1;
    if (!(nodeCounter < 0 || nodeCounter > MAX-1)){
        rotateTo(xval[pathNodes[nodeCounter]], yval[pathNodes[nodeCounter]]);
        printf("Startnode: %d, PathNode: %d, PathLength: %d\n", startNode, pathNodes[nodeCounter], nodeCounter);
    }
}

//C:\Users\zunmu\Documents\Stuff\Github\Space Through CoSpace\4_Advanced Strategies\Dijkstra\ai.c
void Game1(){moveDijkstra(21);}//rotateTo(100,100);}
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
        case 0: Game0();
        case 1: Game1();
        default:
            break;
    }
}

