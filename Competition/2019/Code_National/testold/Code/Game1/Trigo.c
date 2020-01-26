
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
		WheelLeft=4;WheelRight=2; //Anticlockwise Turn
	}
	else {
		WheelLeft=2;WheelRight=4; //Clockwise Turn
	}
	//Duration = 1;
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
