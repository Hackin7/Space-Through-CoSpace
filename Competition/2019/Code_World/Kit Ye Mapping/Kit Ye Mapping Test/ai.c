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
int t = 0;
int red = 0;
int cyan = 0;
int black = 0;
int trigofin = 0;
// INIT MAP
int map1[480][270]={0};
// printttt
int map0[180][240]={0};
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

void squarefill(int color, int x1,int x2,int y1,int y2)
{
  for (int x=x1; x <= x2; x++)
  {
    for (int y=y1; y<= y2; y++)
    {
      if (map1[x][y]!='b')
      {
        map1[x][y]=color;
      }
    }
  }
}
  void findarea(int color, int x1, int y1)
  {
    int x=x1;
    int y=y1;
    int visited[480][270]={0};
    int queue[480][270]={0};
    if (map1[x][y]==color)
    {

    }
    else{return 0;}
  }

bool colorLeftCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSLeft_R && CSLeft_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSLeft_G && CSLeft_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSLeft_B && CSLeft_B <= objBlue[2] + objRange
		);
}
int colorRightCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSRight_R && CSRight_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSRight_G && CSRight_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSRight_B && CSRight_B <= objBlue[2] + objRange
		);
}
bool colorCheck(int *objBlue, int objRange)
{return ( colorLeftCheck(objBlue, objRange) || colorRightCheck(objBlue, objRange));}

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
bool boundary(){
    if ((xreached(22,5) && 0<=Compass && Compass <180)||
        (xreached(343,5) && 180<=Compass && Compass <=360)||
        (yreached(22,5) && 90<=Compass && Compass <=270)||
        (yreached(250,5) && (Compass>270 || Compass <90))){
			WheelLeft=-5;WheelRight=5;
			Duration=2;
			return true;
			}
    return false;//quarrantine(10,335,10,250,5,5);
}

void clockwise(int theta1)
{
  if (!(Compass < (theta1 + 5)%360 && Compass > (theta1 - 5)%360))
  {
    WheelLeft=3;
    WheelRight=-2;
    if ((Compass < (theta1 + 45)%360 && Compass > (theta1 - 45)%360)) // smol angle
    {
      WheelLeft=4;
      WheelRight=2;
    }
  }

}

void aclockwise(int theta1)
{
  if (!(Compass < (theta1 + 5)%360 && Compass > (theta1 - 5)%360))
  {
    WheelLeft=-2;
    WheelRight=3;
    if ((Compass < (theta1 + 45)%360 && Compass > (theta1 - 45)%360)) // small angle
    {
      WheelLeft=2;
      WheelRight=4;
    }
  }

}

void turnto(int theta)
{
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
  else
  {
  	ACWAngleDiff=0;
  	CWAngleDiff=0;
  }

  //step 2: determine if CWAngleDiff or ACWAngleDiff is lower


  if(CWAngleDiff==180)
  {
  	//if AngleDiff is the same, it doesn't matter which way you turn
    clockwise(theta);

  }

  else if(CWAngleDiff<ACWAngleDiff)
  {
  	//turn clockwise
    clockwise(theta);
  }

  else if(ACWAngleDiff<CWAngleDiff)
  {
  	//turn anti-clockwise
    aclockwise(theta);
  }

  else // move forward
  {
  	WheelLeft = 5;
    WheelRight=5;
  }
}


void laser(int us, double uscomp)
{
  int ptx = (us-4)*cos(uscomp) + PositionX;
  int pty= (us-4)*sin(uscomp)+PositionY;
  if (ptx<0){ptx=0;}
  else if (ptx>480){ptx=480;}

  if (pty<0){pty=0;}
  else if (pty>270){pty=270;}
  map1[ptx][pty]= -1; //wall

  int leftx; int rightx;int downy; int upy;


  if (ptx==PositionX)
  {
    if (pty<PositionY){downy=pty;upy=PositionY;}
    else{downy=PositionY;upy=pty;}
    for (int y=downy;y<upy;y++)
    {
      map1[ptx][y]=1;
    }
  }

  else
  {
    double m = (pty-PositionY)/(ptx-PositionX); // y=mx+c but c is positionx,y


    if (ptx < PositionX){leftx = ptx; rightx = PositionX;}
    else{leftx = PositionX; rightx = ptx;}
    for (int x = leftx;  x < rightx; x++)
    {
      if (x==ptx){}
      else{
        int y=PositionY+m*x;
        map1[x][y]=1; // no wall
      }
    }
  }
  }
int tmap=0; // fopr mapping bulshit
void Game1()
{

  tmap++;
  if (tmap==3)
  {
    for (int x=0; x<480; x++)
    {
      for (int y=0; y<270;y++)
      {
        printf("%d ", map1[x][y]);
      }
    }
  }
  int pi=3.1415926535;double usfcomp=0;double usrcomp=0;double uslcomp=0;
  int usfcomptemp=((Compass+90)%360);
  usfcomp=usfcomptemp;
  usrcomp=(usfcomptemp-45)%360;
  uslcomp=(usfcomptemp+45)%360;

  usfcomp=usfcomp*pi/180;
  usrcomp=usrcomp*pi/180;
  uslcomp=uslcomp*pi/180;

  laser(US_Front, usfcomp);
  laser(US_Left, uslcomp);
  laser(US_Right, usrcomp);

  if (t > 0)
  {
    t--;
    return;
  }
  LED_1 = 0;
  if (boundary()){return;}
  if (LoadedObjects == 0)
  {
    WheelRight = 5;
  	WheelLeft = 5;
  }
  else
  {
    WheelRight = 3;
  	WheelLeft = 3;
  }


// wall detection
  if (US_Front < 15) // wall front
	{
    if (LoadedObjects == 0)
    {
      WheelRight = 0;
    	WheelLeft = 5;
    }
    else
    {
      WheelLeft = 5; // turn right
      WheelRight = 0;
    }

    if (US_Left < 10 || US_Right < 10) // crap surrounded
    {
      t = 2;
      WheelLeft = -5; // turn left
      WheelRight = -3;
    }
    else // wall front only
    {
      if (LoadedObjects == 0)
      {
        WheelRight = 0;
      	WheelLeft = 5;
      }
      else
      {
        WheelLeft = 5; // turn right
        WheelRight = 0;
      }
    }
  }

  else if (US_Left < 13) // wall left
  {
    WheelRight = 4;
    WheelLeft = 5;
  }
  else if (US_Right < 13) // wall right
  {
    WheelLeft = 4;
    WheelRight = 5;
  }

// IT'S A TRAP!
  if (((CSRight_B < 50 && CSRight_G > 180 && CSRight_R > 180) || (CSLeft_B < 50 && CSLeft_G > 180 && CSLeft_R > 180)) && LoadedObjects > 0) // yellow
  {
    if ((CSRight_B < 50 && CSRight_G > 180 && CSRight_R > 180) && (CSLeft_B < 50 && CSLeft_G > 180 && CSLeft_R > 180))
    {
        t = 3;
        WheelLeft = -3; // turn right
        WheelRight = -5;
    }
    else if (US_Left < 20 || US_Front < 15) // wall left, backtrack and turn right
    {
      t = 3;
      WheelLeft = -3;
      WheelRight = -5;
    }
    else if (US_Right < 20 )// backtrack, left
    {
      t = 3;
      WheelLeft = -5;
      WheelRight = -3;
    }
    else if (!(CSRight_B < 50 && CSRight_G > 180 && CSRight_R > 180)) // no trap on right
    {
      WheelLeft = 3;
  		WheelRight = 0;
    }
    else if (!(CSLeft_B < 50 && CSLeft_G > 180 && CSLeft_R > 180)) // no trap on left
    {
      WheelLeft = 0;
  		WheelRight = 3;
    }

  }
  // blue
  if ((CSLeft_B > 180 && CSLeft_G < 70 && CSLeft_R < 70) || (CSRight_B > 180 && CSRight_G < 70 && CSRight_R < 70)) // did it screw up?
  {
    LED_1 = 1;
    LoadedObjects = 0;
    red = 0;
    cyan = 0;
    black = 0;
  }


// get dat loot
  if (((CSLeft_B < 50 && CSLeft_G < 50 && CSLeft_R > 190) || (CSRight_B < 50 && CSRight_G < 50 && CSRight_R > 190)) && red < 2) // red
  {
    if (LoadedObjects < 6)
    {

    }

  }
  else if (((CSLeft_B > 190 && CSLeft_G > 190 && CSLeft_R < 50) || (CSRight_B > 190 && CSRight_G > 190 && CSRight_R < 50)) && cyan < 2) // cyan
  {
    if (LoadedObjects < 6)
    {

    }

  }
  else if ((((CSLeft_B < 50 && CSLeft_G < 50 && CSLeft_R< 50) || (CSRight_B < 50 && CSRight_G < 50 && CSRight_R < 50))) && black < 2) // black
  {
    if (LoadedObjects < 6)
    {
      //t = 42;
      //WheelLeft = 0;
      //WheelRight = 0;
      //LED_1 = 1;
      //LoadedObjects++;
      //black ++;
    }
  }

  if (LoadedObjects > 5) // full inven
  {
    if ((CSLeft_B < 50 && CSLeft_G > 100 && CSLeft_G < 190 && CSLeft_R > 190) && (CSRight_B < 50 && CSRight_G > 100 && CSRight_G < 190 && CSRight_R > 190)) // both sense orange
    {
      t = 59;
      LoadedObjects = 0;
      red = 0;
      black = 0;
      cyan = 0;
      WheelLeft = 0;
      WheelRight = 0;
      LED_1 = 2;
    }
    else if (CSLeft_B < 50 && CSLeft_G > 100 && CSLeft_G < 190 && CSLeft_R > 190) // deposit left
    {
      WheelLeft = 0;
      WheelRight = 5;
    }
    else if (CSRight_B < 50 && CSRight_G > 100 && CSRight_G < 190 && CSRight_R > 190) // deposit right
    {
      WheelLeft = 5;
      WheelRight = 0;
    }
  }
  if (Time >= 180) // teleport to world 2
  {
    Teleport = 1;
  }
}

double tx=0;
double ty=0;
double icompass=0;
double speed = 0;
int super = 0;
int superx=0;
int supery=0;

int gray[3]={140,150,190};

void Game0()
{
  int tx=0;
  int ty=0;


  if (t>0)
  {
    t--;
    return;
  }
  LED_1 = 0;
  WheelLeft=5;
  WheelRight=5;


  if (PositionX==0 && PositionY==0) // pos info lost
  {
    if (WheelLeft==WheelRight) // striaght
    {
      speed=WheelLeft*2/3.7;

      if (colorCheck(gray, 20)){speed*=0.1;}
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
        if (colorCheck(gray,20))
        {
          tx += 0.1*cos(((1/60)*(i*(w/2)))*(180/pi));
          ty += 0.1*sin(((1/60)*(i*(w/2)))*(180/pi));
        }
        else
        {
          tx += cos(((1/60)*(i*(w/2)))*(180/pi));
          ty += sin(((1/60)*(i*(w/2)))*(180/pi));
        }

      }
      PositionX = tx;
      PositionY = ty;
    }
    //printf("X: %d\n", PositionX);
    //printf("Y: %d\n", PositionY);
    }
  //else {printf("YAAAAA %d\n", PositionX); printf("YAAAAA %d\n", PositionY);}



  // avoid moving walls
  if (US_Left < 10 || US_Right < 10 || US_Front < 20)
  {
    WheelLeft = -5;
    WheelRight = -5;
  }


  // avoid world 2 border
  if (PositionX < 20)
  {
    turnto(270);
  }
  else if (PositionX > 340)
  {
    turnto(90);
  }
  if (PositionY < 20)
  {
    turnto(360);
  }
  else if (PositionY > 240)
  {
    turnto(180);
  }
  if (PositionX==0 && PositionY==0)
  {
    WheelLeft=5;
    WheelRight=5;
  }



  // IT'S A TRAP! // in case something goes wrong and it needs to avoid traps
    if (((CSRight_B < 50 && CSRight_G > 180 && CSRight_R > 180) || (CSLeft_B < 50 && CSLeft_G > 180 && CSLeft_R > 180)) && LoadedObjects > 0) // yellow
    {
      if ((CSRight_B < 50 && CSRight_G > 180 && CSRight_R > 180) && (CSLeft_B < 50 && CSLeft_G > 180 && CSLeft_R > 180))
      {
          t = 3;
          WheelLeft = -3; // turn right
          WheelRight = -5;
      }
      else if (US_Left < 20 || US_Front < 15) // wall left, backtrack and turn right
      {
        t = 3;
        WheelLeft = -3;
        WheelRight = -5;
      }
      else if (US_Right < 20 )// backtrack, left
      {
        t = 3;
        WheelLeft = -5;
        WheelRight = -3;
      }
      else if (!(CSRight_B < 50 && CSRight_G > 180 && CSRight_R > 180)) // no trap on right
      {
        WheelLeft = 3;
    		WheelRight = 0;
      }
      else if (!(CSLeft_B < 50 && CSLeft_G > 180 && CSLeft_R > 180)) // no trap on left
      {
        WheelLeft = 0;
    		WheelRight = 3;
      }

    }
    // blue
    if ((CSLeft_B > 180 && CSLeft_G < 70 && CSLeft_R < 70) || (CSRight_B > 180 && CSRight_G < 70 && CSRight_R < 70)) // did it screw up?
    {
      WheelLeft = -3;
      WheelRight = -5;
      LED_1 = 2;
      LoadedObjects = 0;
      red = 0;
      cyan = 0;
      black = 0;
    }


  // get dat loot
    if (((CSLeft_B < 50 && CSLeft_G < 50 && CSLeft_R > 190) || (CSRight_B < 50 && CSRight_G < 50 && CSRight_R > 190)) && red < 2) // red
    {
      if (LoadedObjects < 6)
      {
        t = 42;
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 1;
        LoadedObjects++;
        red++;
      }

    }
    else if (((CSLeft_B > 190 && CSLeft_G > 190 && CSLeft_R < 50) || (CSRight_B > 190 && CSRight_G > 190 && CSRight_R < 50)) && cyan < 2) // cyan
    {
      if (LoadedObjects < 6)
      {
        t = 42;
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 1;
        LoadedObjects++;
        cyan ++;
      }
    }
    else if ((((CSLeft_B < 50 && CSLeft_G < 50 && CSLeft_R< 50) || (CSRight_B < 50 && CSRight_G < 50 && CSRight_R < 50))) && black < 2) // black
    {
      if (LoadedObjects < 6)
      {
        t = 42;
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 1;
        LoadedObjects++;
        black ++;
      }

    }
    else if (((CSLeft_B > 150 && CSLeft_B < 240 && CSLeft_G > 100 && CSLeft_G < 190 && CSLeft_R > 110 && CSLeft_R < 180)  || (CSRight_B > 150 && CSRight_B < 240 && CSRight_G > 100 && CSRight_G < 190 && CSRight_R > 110 && CSRight_R < 180)))
    {
      LED_1=2;
      WheelLeft=0;
      WheelRight=0;
      t=45;
    }
    if (LoadedObjects > 5) // full inven
    {
      if ((CSLeft_B < 50 && CSLeft_G > 100 && CSLeft_G < 190 && CSLeft_R > 190) && (CSRight_B < 50 && CSRight_G > 100 && CSRight_G < 190 && CSRight_R > 190)) // both sense orange
      {
        t = 59;
        LoadedObjects = 0;
        red = 0;
        black = 0;
        cyan = 0;
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 2;
      }
      else if (CSLeft_B < 50 && CSLeft_G > 100 && CSLeft_G < 190 && CSLeft_R > 190) // deposit left
      {
        WheelLeft = 0;
        WheelRight = 5;
      }
      else if (CSRight_B < 50 && CSRight_G > 100 && CSRight_G < 190 && CSRight_R > 190) // deposit right
      {
        WheelLeft = 5;
        WheelRight = 0;
      }
    }
// superobjs
  if (((CSLeft_B > 190 && CSLeft_G < 60 && (CSLeft_R > 60)) || (CSRight_B > 190 && CSRight_G < 60 && (CSRight_R > 60))) && LoadedObjects<6)
  {
    t = 42;
    WheelLeft = 0;
    WheelRight = 0;
    LED_1 = 1;
    LoadedObjects++;
    super--;
  }

icompass=Compass;
tx = PositionX;
ty = PositionY;


turnto(0);
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
