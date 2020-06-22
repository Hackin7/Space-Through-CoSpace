int PositionX1=0, PositionY1=0;

double dabs (double x){
    if (x<0){return -x;}
    return x;
}
bool xreached(int x,int range){
	return (x-range<=PositionX1 && PositionX1 <= x+range);
}
bool yreached(int y,int range){
	return (y-range<=PositionY1 && PositionY1 <= y+range);
}
bool reached(int x,int y,int rangex, int rangey){
	return ((x-rangex<=PositionX1 && PositionX1 <= x+rangex) &&
	    (y-rangey<=PositionY1 && PositionY1 <= y+rangey));
}

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

void rotateTo(int x, int y){
    //st.trigo(x, y, PositionX1, PositionY1);
    rotateRobot(angle(x,y, PositionX,PositionY));
}
int colorSensorX = PositionX1, colorSensorY = PositionY1;
void rotateToSuper(int x, int y){
    rotateRobot(angle(x,y, PositionX1,PositionY1));
}
void rotateToFAST(int x, int y){
    rotateRobot(angle(x,y, PositionX,PositionY));
}
