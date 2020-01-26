/*static void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	//posInfoLost();
	PositionX1 = PositionX;
	PositionY1 = PositionY;

	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	//cout<<"_";//<<PositionX1<<","<<PositionY1<<"_"<<endl;

	if (w2Obj.isCollected()){
		location.squareFill(PositionX1,PositionY1,location.empty, 5);
	}

	bool collectBlue = w2Obj.LoadedObjects<=7 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<=7 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<=7 && w2Obj.LoadedBlack<2;//true;
	bool deposit = true || w2Obj.LoadedObjects>=6 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;;//true;
	//discovery();

	if (w2Obj.Trap(avoid)){return;}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	//else if (boundary()){}
	else if (colorCheck(w2Obj.slowarea,20)){
          WheelLeft=-2;WheelRight=-4;
          }

    else if (wallAvoiding(12)){}
	//else if (depositDijkstra(LoadedObjects >= 4 || LoadedSuperObj > 0)){}
	else if (PositionX==0 && PositionY==0){WheelLeft=2;WheelRight=3;}
	else if (superObjAStar()){}
	else { // Default Movement
		if (w2Obj.LoadedObjects >=6){cout<<"D";cycle.moveDeposit();}
		else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
	}
}
*/

int slowarea[3]={140,150,190};
int objBlue[3] = {29,249,255};
int objRed[3] = {235,29,29};
int objBlack[3] = {20,20,20};
int specialZone[3]={20,171,235};
int superObj[3] = {235,20,235};
int depositOrange[3] = {235,147,20};
int trapYellow[3] = {220,235,20};
int trapBlue[3] = {30,30,203};


int unexploredcol=-1;
int unexfloorcol = 0;
int wallcol=-2;
int whitefloorcol=1;
int redcol=2;
int cyancol=3;
int blackcol=5;
int specialbluecol =7;
int orangecol=11;
int graycol=13;
int yellowcol=17;
int trapbluecol=19;

// INIT MAP
int map1[360][270]={0};

// printttt
int map0[240][180]={0};

int findmax(int a, int b)
{
  if (a>b){return a;}
  else{return b;}
}

int findmin(int a,int b)
{
  if (a<b){return a;}
  else{return b;}
}

void rectfill(int color, int x1,int x2,int y1,int y2)// for trap/slowarea
{
  for (int x=x1; x <= x2; x++)
  {
    for (int y=y1; y<= y2; y++)
      {
        if (map1[x][y]!=wallcol && map1[x][y]!=unexploredcol && map1[x][y]!=yellowcol)
        {map1[x][y]=color;}
    }
}
}

void multrectfill(int color, int x1,int x2,int y1,int y2) //objs
{
  for (int x=x1; x <= x2; x++)
  {
    for (int y=y1; y<= y2; y++)
      { if (map1[x][y] >= 0 && map1[x][y] !=yellowcol) // no unknown/wall, not already that color
      {if (map1[x][y] == 0)
        {map1[x][y]=color;}
        else
        {
          if (map1[x][y] %color != 0)
          {map1[x][y]*=color;}
        }
      }
    }
}
}

void squarefill(int color, int x, int y, int len)
{
  int x1=x - len;
  int x2=x + len;
  int y1=y - len;
  int y2=y + len;
  if (x1 < 0){x1=0;}
  if (x2 > 480){x2=480;}
  if (y1 < 0){y1=0;}
  if (y2 > 270){y2=270;}
  rectfill(color,x1,x2,y1,y2);
}
void multsquarefill(int color, int x, int y, int len)
{
  int x1=x - len;
  int x2=x + len;
  int y1=y - len;
  int y2=y + len;
  if (x1 < 0){x1=0;}
  if (x2 > 480){x2=480;}
  if (y1 < 0){y1=0;}
  if (y2 > 270){y2=270;}
  multrectfill(color,x1,x2,y1,y2);
}


  int findarea(int color, int x1, int y1)
  {
    int x=x1;
    int y=y1;
    int visited[270][180]={0};
    int queue[270][180]={0};
    if (map1[x][y]==color)
    {

    }
    else{return 0;}
  }



void carmap(int color,int x1,int x2,int y1,int y2)// car area
{
  for (int x=x1; x <= x2; x++)
  {
    for (int y=y1; y<= y2; y++)
      {
        if (map1[x][y]==wallcol || map1[x][y]==unexploredcol || map1[x][y]==unexfloorcol) // dont go rewriting some other colors
        map1[x][y]=color;
    }
  }
}

void colormap()
{
  // unfixed location of the stuff, only probability, can coexist
  if (colorCheck(objRed,10)){multrectfill(redcol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}
  else if (colorCheck(objBlue,10)){multrectfill(cyancol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}
  else if (colorCheck(objBlack,10)){multrectfill(blackcol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}

  // fixed loc but can coexist
  else if (colorCheck(specialZone,10)){multrectfill(specialbluecol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}
  else if (colorCheck(slowarea,10)){multrectfill(graycol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}

  // only exists by themselves
  else if (colorCheck(trapYellow,20)){squarefill(yellowcol,PositionX,PositionY,7);}
  else if (colorCheck(depositOrange,20)){squarefill(orangecol,PositionX,PositionY,20);}
  else if (colorCheck(trapBlue,20)){squarefill(trapbluecol,PositionX,PositionY,3);}
  else {carmap(whitefloorcol,findmax(PositionX-5,0),findmin(PositionX+5,360),findmax(PositionY-3,0),findmin(PositionY+3,180));} // car area}
}


void laser(int us, double uscomp)
{
	int l=1;
  int ptx = (us)*cos(uscomp) + PositionX;
  int pty= (us)*sin(uscomp)+PositionY;
  if (ptx<0){ptx=0;}
  else if (ptx>360){ptx=360;}

  if (pty<0){pty=0;}
  else if (pty>270){pty=270;}
  if (us < 186)
	{
		for (int x = findmax(0,ptx-l); x<= findmin(ptx+l,360); x++)
	  {
	    for (int y=findmax(0,pty-l); y<= findmin(pty+l,270); y++)
	      {
	        map1[x][y]=wallcol;
	    }
	}
	}

  int leftx; int rightx;int downy; int upy;


  if (ptx==PositionX)
  {
    if (pty<PositionY)
    {
      for (int y=pty+1;y<PositionY;y++)
      {
        if (map1[ptx][y]==wallcol || map1[ptx][y]==unexploredcol)
        {map1[ptx][y]=0;}
      }
    }
    else
    {
      for (int y=PositionY;y<pty;y++)
      {
        if (map1[ptx][y]==wallcol || map1[ptx][y]==unexploredcol)
        {map1[ptx][y]=unexfloorcol;}
      }
    }
  }

  else
  {
    double m = (pty-PositionY)/(ptx-PositionX); // y=mx+c but c is positionx,y
    if (ptx < PositionX){leftx = ptx; rightx = PositionX;}
    else{leftx = PositionX; rightx = ptx;}
    for (int x = leftx+1;  x < rightx; x++)
    {
      if (x==ptx){}
      else{
        {int y=PositionY+m*x;
          if (map1[x][y]==wallcol || map1[x][y]==unexploredcol){map1[x][y]=0;}} // no wall but idk floor
      }
    }
  }
}

int tmap=0; // print map after t frames



int map_=0;
void Game1()
{
  // initialize as -1
  if (map_==0)
  {
    for (int x=0;x<360;x++)
    {
      for (int y=0;y<270;y++)
      {map1[x][y]=unexploredcol;}

  }
  map_=1;
  printf("%d\n",unexfloorcol );
}
posInfoLost();
  tmap++;
  if (tmap==2000) // print map
  {
    for (int x=0; x<360; x++)
    {
      for (int y=0; y<270;y++)
      {
        printf("%d ", map1[x][y]);
      }
    }
  }
  double pi=3.1415926535;double usfcomp=0;double usrcomp=0;double uslcomp=0;
  int usfcomptemp=((Compass+90)%360);
  usfcomp=usfcomptemp;
  usrcomp=(usfcomptemp-45)%360;
  uslcomp=(usfcomptemp+45)%360;
// convert to rad
  usfcomp=usfcomp*pi/180;
  usrcomp=usrcomp*pi/180;
  uslcomp=uslcomp*pi/180;

  laser(US_Front, usfcomp);
  laser(US_Left, uslcomp);
  laser(US_Right, usrcomp);

colormap();


  if (Duration > 0)
  {
    Duration--;
    return;
  }
  LED_1 = 0;
  //WheelLeft=3;WheelRight=-3;
  //WheelLeft=5;WheelRight=-5;return;
  if (boundary()){return;}
  if (wallAvoiding(15)){return;}
  if (LoadedObjects == 0)
  {
    WheelRight = 4;
  	WheelLeft = 4;
  }
  else if (colorCheck(slowarea,10)){WheelLeft=5;WheelRight=5;}
  else
  {
    WheelRight = 3;
  	WheelLeft = 3;
  }
}
