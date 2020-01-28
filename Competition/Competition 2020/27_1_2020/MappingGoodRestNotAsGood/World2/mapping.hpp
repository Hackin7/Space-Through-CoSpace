 class PrevInfo{
	private:
	int threshold = 6;
	public:
	deque <int> prevCompass;
	deque <coordinates> prevCoordinates;

	void addCompass(int val){prevCompass.push_back(val);}
	void addCoordinate(int x, int y){coordinates c; c.pos[0] = x; c.pos[1] = y; prevCoordinates.push_back(c);}

	void cycleOut(){
		if ((int)prevCompass.size() > threshold){
			prevCompass.pop_front();
		}
		if ((int)prevCoordinates.size() > threshold){
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
		if (prevCoordinates.size() < threshold){return true;}
		return dPos() > 1.5;
	}
};
PrevInfo prevInfo;

/////////////////////////////////////////////////////////////////
int unexploredcol=location.unexplored;
int unexfloorcol = location.predictedEmpty;
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
int border = location.border;

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
void addwall(int x, int y, int wallval, int borderval){
	int margin = 5;
	//int wallval = wallcol, borderval = location.border;
	int size[] = {360,270};
	location.setPixel(x,y,wallval);
	if (location.map[x][y] == wallval){
		for (int m=0; m<margin;m++){
			for (int n=0;n<margin;n++){
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
}

void laser1(int us, double uscomp)
{

	int l=1;
    int ptx = (us+5)*cos(uscomp) + PositionX1;
    int pty= (us+5)*sin(uscomp)+PositionY1;
    if (ptx<0){ptx=0;}
    else if (ptx>360){ptx=360;}

    if (pty<0){pty=0;}
    else if (pty>270){pty=270;}
    if (uscomp < 90){ //{location.map[ptx][pty]= wallcol;} //wall squarerfll
        for (int x = findmax(0,ptx-l); x<= findmin(ptx+l,360); x++){
	    for (int y=findmax(0,pty-l); y<= findmin(pty+l,270); y++){
	        addwall(x, y, wallcol, location.border);
			//location.map[x][y]=wallcol;
	    }
		}
	}


  int leftx; int rightx;int downy; int upy;


  if (ptx==PositionX1)
  {
    if (pty<PositionY1)
    {
      for (int y=pty+1;y<PositionY1;y++)
      {
        if (location.map[ptx][y]==wallcol || location.map[ptx][y]==unexploredcol)
        {location.map[ptx][y]=0;}
      }
    }
    else
    {
      for (int y=PositionY1;y<pty;y++)
      {
        if (location.map[ptx][y]==wallcol || location.map[ptx][y]==unexploredcol)
        {
			location.map[ptx][y]=unexfloorcol;
		}
      }
    }
  }

  else{
    double m = (pty-PositionY1)/(ptx-PositionX1); // y=mx+c but c is positionx,y
    if (ptx < PositionX1){leftx = ptx; rightx = PositionX1;}
    else{leftx = PositionX1; rightx = ptx;}
    for (int x = leftx+1;  x < rightx; x++)
    {
      if (x==ptx){}
      else{
        int y=PositionY1+m*x;
          if (location.map[x][y]==wallcol || location.map[x][y]==unexploredcol){
			  location.map[x][y]=0;
			}
		 // no wall but idk floor
      }
    }
  }
}

int sensorVal(){
    if (colorCheck(w2Obj.objRed, w2Obj.objRange)){return location.red;}
    else if (colorCheck(w2Obj.objBlue, w2Obj.objRange)){return location.blue;}
    else if (colorCheck(w2Obj.objBlack, w2Obj.objRange)){return location.black;}
    else if (colorCheck(w2Obj.slowarea,30)){return location.wall;}
    else if (colorCheck(w2Obj.trapYellow,w2Obj.trapRange)){return location.trapBorder;}
    else if (colorCheck(w2Obj.depositOrange,w2Obj.depRange)){return location.deposit;}
    else{return location.empty;}
}

void lineDrawer(int x1, int y1, int x2, int y2, int val, int width){
    double dx = x2-x1;
	double dy = y2-y1;
	int signX = dx>0 ? 1:-1;
	int signY = dy>0 ? 1:-1;

	int i=x1, j=y1;
	if (dx==0){
        for (int k=0;k<abs(dy);k++){
			//i = x2;
			j += signY;
			location.squareFill(i,j,val,width);
			//location.map[i][j] = unexfloorcol;
		}
    }else if (signX != signY){ //For Different Directions
	    for (int k=0; k<abs(dx); k++){
            i += signX;
            j = (int)y1 + -signY*(dy/dx)*k;
            location.squareFill(i,j,val,width);
        }
	}else{ //For Same Directions
	    for (int k=0; k<abs(dx); k++){
            i += signX;
            j = (int)y1 + signY*(dy/dx)*k;
            location.squareFill(i,j,val,width);
        }
	}
}
void lineDrawerDriver(){
    lineDrawer(100,100,200,100,location.empty,1); //Horizontal Test
    lineDrawer(200,50,100,50,location.empty,1); //Horizontal Test
    lineDrawer(100,0,100,100,location.empty,1); //Vertical Test
    lineDrawer(200,100,200,0,location.empty,1); //Vertical Test

    lineDrawer(0,0,180,200,location.red,1); //Steep Gradient Testing
    lineDrawer(0,0,269,269,location.black,1); // Negative Gradient Testing
    lineDrawer(0,0,359,269,location.blue,1); // Gentle Gradient Testing

    lineDrawer(300,269,0,0,location.red,1); //Negative x Direction Test

    lineDrawer(50,269,100,150,location.red,1); // Negative Gradient Testing
    lineDrawer(50,100,310,50,location.wall,1); // Negative Gradient Testing
    lineDrawer(310,100,50,150,location.blue,1); // Negative Gradient and dx Testing
    lineDrawer(310,0,50,50,location.black,1); // Negative Gradient and dx Testing
}
bool inRange(int a,int b,int c){
    if (b<a){return a;}
    else if (b>c){return c;}
    else{return b;}
}
void laser(int us, double uscomp){
	int x = PositionX1 + (us+5)*cos(uscomp); //Offset
	int y = PositionY1 + (us+5)*sin(uscomp);
    int x1 = PositionX1 + (us)*cos(uscomp); //Offset
	int y1 = PositionY1 + (us)*sin(uscomp);

	if (us < (int)186/3*2){ //Sensor cannot sense >180
		lineDrawer(PositionX1,PositionY1,x1,y1,location.empty,1);
		location.squareFill(x,y,location.wall,3);
	}
	//
}
void mappingMode(){
	//int Compass = prevInfo.getPastCompass(1);
	//coordinates c = prevInfo.getPastCoordinate(1);
	//int PositionX = c.pos[0];
	//int PositionY = c.pos[1];

	  double pi=3.1415926535;double usfcomp=0;double usrcomp=0;double uslcomp=0;
      int usfcomptemp=((Compass+90)%360);
      usfcomp=usfcomptemp;
      uslcomp=(usfcomptemp-40)%360;
      usrcomp=(usfcomptemp+40)%360;
    // convert to rad
      usfcomp=usfcomp*pi/180;
      usrcomp=usrcomp*pi/180;
      uslcomp=uslcomp*pi/180;
      laser(US_Front, usfcomp);
      //laser(US_Left, uslcomp);
      //laser(US_Right, usrcomp);
      //laser(US_Left, uslcomp);
      //laser(US_Right, usrcomp);

    //location.squareFill(colorSensorX,colorSensorY,location.red,7);
    //laserEmpty(US_Front, Compass);
    //laser(US_Left, uslcomp);
    //laser(US_Right, usrcomp);
    //colormap(colorSensorX,colorSensorY);
    //cout<<"Sensor Map:"<<sensorVal()<<endl;
    location.squareFill(colorSensorX,colorSensorY,sensorVal(),5);

    //lineDrawerDriver();
}
