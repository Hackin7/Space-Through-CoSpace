class PrevInfo{
	private:
	int threshold = 6;
	public:
	deque <int> prevCompass;
	deque <coordinates> prevCoordinates;
	
	void addCompass(int val){prevCompass.push_back(val);}
	void addCoordinate(int x, int y){coordinates c; c.pos[0] = x; c.pos[1] = y; prevCoordinates.push_back(c);}
	
	void cycleOut(){
		if (prevCompass.size() > threshold){
			prevCompass.pop_front();
		}
		if (prevCoordinates.size() > threshold){
			prevCoordinates.pop_front();
		}
	}
	int currentCompass(){return Compass;}
	int currentPositionX(){return PositionX;}
	int currentPositionY(){return PositionY;}
	void update(){
		addCompass(currentCompass());
		addCoordinate(currentPositionX(),currentPositionY());
		cycleOut();
	}
	coordinates getPastCoordinate(int x){
		if (prevCoordinates.size() < threshold){
			coordinates empty;
			empty.pos[0] = PositionX;
			empty.pos[1] = PositionY;
			return empty;
		}
		if (x <= 0 || x > threshold){x=1;}
		return prevCoordinates[threshold - x];
	}
	int getPastCompass(int x){
		if (prevCompass.size() < threshold){return Compass;}
		if (x <= 0 || x > threshold){x=1;}
		return prevCompass[threshold - x];
	}
	int dx(){
		return currentPositionX() - getPastCoordinate(3).pos[0];
	}
	int dy(){
		return currentPositionY() - getPastCoordinate(3).pos[1];
	}
	double dPos(){
		return sqrt(pow(dx(),2)+pow(dy(),2));
	}
	bool posChange(){
		return dPos() < 1.41;
	}
};
PrevInfo prevInfo;

/////////////////////////////////////////////////////////////////
int unexploredcol=-1;
int unexfloorcol = -2;
int wallcol=location.wall;
int whitefloorcol=location.empty;
int redcol=location.red;
int cyancol=location.blue;
int blackcol=location.black;
int specialbluecol =-3;
int orangecol=location.deposit;
int graycol=location.slow;
int yellowcol=location.trapBorder;
int trapbluecol=location.trap;

/*
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
*/
// INIT MAP
//int location.map[360][270]={0};


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
        if (location.map[x][y]!=wallcol && location.map[x][y]!=unexploredcol && location.map[x][y]!=yellowcol)
        {location.map[x][y]=color;}
    }
}
}

void multrectfill(int color, int x1,int x2,int y1,int y2) //objs
{
  for (int x=x1; x <= x2; x++)
  {
    for (int y=y1; y<= y2; y++)
      { if (location.map[x][y] >= 0 && location.map[x][y] !=yellowcol) // no unknown/wall, not already that color
      {if (location.map[x][y] == 0)
        {location.map[x][y]=color;}
        else
        {
          if (location.map[x][y] %color != 0)
          {location.map[x][y]*=color;}
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
    if (location.map[x][y]==color)
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
        if (location.map[x][y]==wallcol || location.map[x][y]==unexploredcol || location.map[x][y]==unexfloorcol) // dont go rewriting some other colors
        location.map[x][y]=color;
    }
  }
}

void colormap(int x, int y)
{
	int PositionX=x, PositionY=y;
  // unfixed location of the stuff, only probability, can coexist
  if (colorCheck(w2Obj.objRed,10)){multrectfill(redcol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}
  else if (colorCheck(w2Obj.objBlue,10)){multrectfill(cyancol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}
  else if (colorCheck(w2Obj.objBlack,10)){multrectfill(blackcol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}

  // fixed loc but can coexist
  else if (colorCheck(w2Obj.specialZone,10)){multrectfill(specialbluecol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}
  else if (colorCheck(w2Obj.slowarea,10)){multrectfill(graycol,findmax(PositionX-30,0),findmin(PositionX+30,360),findmax(PositionY-20,0),findmin(PositionY+20,270));}

  // only exists by themselves
  else if (colorCheck(w2Obj.trapYellow,20)){squarefill(yellowcol,PositionX,PositionY,7);}
  else if (colorCheck(w2Obj.depositOrange,20)){squarefill(orangecol,PositionX,PositionY,20);}
  else if (colorCheck(w2Obj.trapBlue,20)){squarefill(trapbluecol,PositionX,PositionY,3);}
  else {carmap(whitefloorcol,findmax(PositionX-5,0),findmin(PositionX+5,360),findmax(PositionY-3,0),findmin(PositionY+3,180));} // car area}
}
void addwall(int x, int y){
	int margin = 5;
	int wallval = wallcol, borderval = location.border;
	int size[] = {360,270};
	location.map[x][y] = redcol;
	for (int m=1; m<margin;m++){
		for (int n=1;n<margin;n++){
			if (x+m < size[0]){
				if (y+n < size[1]){
					if (location.map[x+m][y+n] != wallval)  location.map[x+m][y+n] = borderval;}
				if (y-n > 0){
					if (location.map[x+m][y-n] != wallval)  location.map[x+m][y-n] = borderval;}
			}
			if (x+m > 0){
				if (y+n < size[1]){
					if (location.map[x-m][y+n] != wallval)  location.map[x-m][y+n] = borderval;}
				if (y-n > 0){
					if (location.map[x-m][y-n] != wallval) location.map[x-m][y-n] = borderval;}
			}
		}
	}
}
void laser(int us, double uscomp)
{
	int x = PositionX + us*cos(uscomp);
	int y = PositionY + us*sin(uscomp);
	
	if (us < 186/2){
		addwall(x, y);
	}
	
	//squarefill(redcol,WallY,WallY,3);
}
void laserempty(int us, double uscomp){
	int WallX = PositionX + us*cos(uscomp);
	int WallY = PositionY + us*sin(uscomp);
	//location.map[WallX][WallY] = redcol;//
	//squarefill(redcol,WallY,WallY,3);
	
	int x1 = PositionX, x2 = WallX, y1 = PositionY, y2 = WallY;
	float dx = x1-x2;
	float dy = y1-y2;
	int signX = dx>0 ? 1:-1;
	int signY = dy>0 ? 1:-1;
	
	int i, j, j1,j2;
	if (dx == 0){
		for (int k=0;k<abs(dy);k++){
			i = x2;
			j = y2+signY*k;
			location.map[i][j] = unexfloorcol;
		}
	}
	else{
	for (int k=0; k<abs(dx); k++){
		//int k = (int)abs(dx)/2 + x2;
		i = x2 + signX*k;
		j = y2 + (int)(dy/dx)*signX*k;
		//j1 = j-1;
		//j2 = j+1;
		location.map[i][j] = unexfloorcol;
	}
	}
}
void laser1(int us, double uscomp)
{
	
	int l=1;
  int ptx = (us)*cos(uscomp) + PositionX;
  int pty= (us)*sin(uscomp)+PositionY;
  if (ptx<0){ptx=0;}
  else if (ptx>360){ptx=360;}

  if (pty<0){pty=0;}
  else if (pty>270){pty=270;}
  if (uscomp < 186) //{location.map[ptx][pty]= wallcol;} //wall squarerfll
	{
		for (int x = findmax(0,ptx-l); x<= findmin(ptx+l,360); x++)
	  {
	    for (int y=findmax(0,pty-l); y<= findmin(pty+l,270); y++)
	      {
	        location.map[x][y]=wallcol;
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
        if (location.map[ptx][y]==wallcol || location.map[ptx][y]==unexploredcol)
        {location.map[ptx][y]=0;}
      }
    }
    else
    {
      for (int y=PositionY;y<pty;y++)
      {
        if (location.map[ptx][y]==wallcol || location.map[ptx][y]==unexploredcol)
        {location.map[ptx][y]=unexfloorcol;}
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
          if (location.map[x][y]==wallcol || location.map[x][y]==unexploredcol){location.map[x][y]=0;}} // no wall but idk floor
      }
    }
  }
}
void mappingMode(){
	int Compass = prevInfo.getPastCompass(1);
	coordinates c = prevInfo.getPastCoordinate(1);
	int PositionX = c.pos[0];
	int PositionY = c.pos[1];
	
	
	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	double pi=3.1415926535;double usfcomp=0;double usrcomp=0;double uslcomp=0;
  int usfcomptemp=((Compass+90)%360);
  usfcomp=usfcomptemp;
  usrcomp=(usfcomptemp-45)%360;
  uslcomp=(usfcomptemp+45)%360;
// convert to rad
  usfcomp=usfcomp*pi/180;
  usrcomp=usrcomp*pi/180;
  uslcomp=uslcomp*pi/180;
  if (PositionX!=0 && PositionY!=0){
	  laser(US_Front, usfcomp);
	  laser(US_Left, uslcomp);
	  laser(US_Right, usrcomp);
	  //laserempty(US_Front, usfcomp);
	}
}