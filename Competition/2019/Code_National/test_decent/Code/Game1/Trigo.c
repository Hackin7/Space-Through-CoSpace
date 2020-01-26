
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
