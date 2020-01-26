// File: Game1/Trigo.c
double dabs (double x){
    if (x<0){return -x;}
    return x;
}
//Angle to turn to
double angle(int x, int y, int originX, int originY){
	double Ychange = (y-originY); double Xchange = (x-originX);
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
            //printf("1st");
		theta = 270+theta;
	}
	//Second quadrant
	else if (Ychange>=0 && Xchange<0){
            //printf("2nd");
		theta = 90-theta;
	}
	//Third quadrant
	else if (Ychange<0 && Xchange<0){
            //printf("3rd");
		theta = 90+theta;
	}
	//Fourth quadrant
	else if (Ychange<=0 && Xchange>0){
            //printf("4th");
		theta = 270-theta;
	}
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
bool toCWM(double theta){
	int range = 10;

	double CWAngleDiff;
	double ACWAngleDiff;
	double AngleDiff;
	AngleDiff = abs(Compass-theta);

  //int faster = 0, smaller = 0;
  if(AngleDiff>180)
  {AngleDiff=360-AngleDiff;}
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
    return true;//WheelLeft=faster;WheelRight=smaller;//clockwise(theta);
  }
  else if(ACWAngleDiff<CWAngleDiff)
  { //turn anti-clockwise
    return false;//WheelLeft=smaller;WheelRight=faster;//aclockwise(theta);
  }
}

void trigo(int x, int y, int originX, int originY){
    double angl = angle(x,y, originX, originY);
	//WheelLeft=-1;WheelRight=-1;
	int range = 10;
	//printf("%d, %d, %d]\n",(int)angle-range, Compass,(int)angle+range);

    //if (reached(x,y,10,10)){return;}

    double theta = angl;
  double AngleDiff;
  AngleDiff = abs(Compass-theta);

  int faster = 0, smaller = 0;

    if (AngleDiff<=5)
    {faster=5;smaller=5;} //printf("10range");}
    else if (AngleDiff<=10)
    {faster=4;smaller=3;}// printf("10range");}
    else if (AngleDiff<=20)
    {faster=3;smaller=1;}//printf("20range");}
    else if (AngleDiff<=67)
    {faster=3;smaller=0;}// printf("45range");}
    else{faster=2;smaller=-2;}//printf("SHIT");}

/*
    if (colorCheck(slowarea,20)){
          faster++;smaller++;
         }
*/
  if(toCWM(theta))
  {//turn clockwise
    WheelLeft=faster;WheelRight=smaller;//clockwise(theta);
  }
  else
  { //turn anti-clockwise
    WheelLeft=smaller;WheelRight=faster;//aclockwise(theta);
  }
}
void rotateTo(int x, int y){trigo(x, y, PositionX, PositionY);}

int colorSensorX = PositionX, colorSensorY = PositionY;
void rotateToSuper(int x, int y){trigo(x, y, colorSensorX, colorSensorY);}
