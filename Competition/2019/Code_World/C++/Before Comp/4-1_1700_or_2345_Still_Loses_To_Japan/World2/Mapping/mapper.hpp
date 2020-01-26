class Map{
	private:
	
	const int empty = 0;
	const int deposit = 1;
	const int red = 2;
	const int blue = 3;
	const int black = 4;
	const int wall = 5;
	const int slow = 6;
	const int trap = 7;
	const int border = 8;
	//Negative values for unconfirmed
	
	public:
	int map[width][height];
	Map(){
		for (int i=0; i<width; i++){
			for (int y=0;j<width; j++)
				map[i][j] = empty;
		}
	}
	////Getter////////////////////////////////////////////////////
	int getMap(int i, int j){return map[i][j];}
	bool isVal(int i, int j, int val){return map[i][j] == val;}
	
	////Setter////////////////////////////////////////////////////
	void rectfill(int color, int x1,int x2,int y1,int y2)
	{
		for (int x=x1; x <= x2; x++){
			for (int y=y1; y<= y2; y++){
			map1[x][y]=color;
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
	
	
}


	void laser(int us, double uscomp)
	{
	  int ptx = (us)*cos(uscomp) + PositionX;
	  int pty= (us)*sin(uscomp)+PositionY;
	  if (ptx<0){ptx=0;}
	  else if (ptx>360){ptx=360;}
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
	  
	  void laserSensors(){
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
		  laser(US_Left, uslcomp);
		  laser(US_Right, usrcomp);
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



void mapOut(){
  tmap++;
  if (tmap==1200)
  {
    for (int x=0; x<360; x++)
    {
      for (int y=0; y<270;y++)
      {
        printf("%d ", map1[x][y]);
      }
    }
  }
  

squarefill(1,PositionX,PositionY,1);
}