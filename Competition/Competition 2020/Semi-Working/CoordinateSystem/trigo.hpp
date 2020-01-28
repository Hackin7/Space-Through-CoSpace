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

// void rotateTo(int x, int y){trigo(x, y, PositionX, PositionY);}
// int colorSensorX = PositionX, colorSensorY = PositionY;
// void rotateToSuper(int x, int y){trigo(x, y, colorSensorX, colorSensorY);}


//////Samuel's Trigo/////////////////////////////////////////////////////////////////////
class SamuelTrigo{
	public:

 int minSpeed=5,maxSpeed=5;
 int theta=-1,AngleDiff,CWAngleDiff,ACWAngleDiff;
void speed(int left, int right){
	WheelLeft=left;WheelRight=right;
}
  void turnToAngle(int targetAngle)
{
	//must have set minSpeed AND maxSpeed BEFORE CALLING THIS FUNC
	if(Compass>=targetAngle)
	{
		CWAngleDiff=Compass-targetAngle;
		ACWAngleDiff=360-(Compass-targetAngle);
	}
	else //Compass<targetAngle
	{
		ACWAngleDiff=targetAngle-Compass;
		CWAngleDiff=360-(targetAngle-Compass);
	}

	if(CWAngleDiff<=ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
	else if(ACWAngleDiff<CWAngleDiff) speed(minSpeed,maxSpeed);//turn anti-clockwise
	else speed(maxSpeed,maxSpeed);//move forward
}

void reduceSpeeds(int& spd1, int& spd2)
{
	spd1 = spd1>=0 ? spd1/2+1 : spd1/2-1;
	spd2 = spd2>=0 ? spd2/2+1 : spd2/2-1;
}

  void calcTheta(int originX, int originY, int targetX, int targetY)
{
	const int deltaX = targetX - originX;
	const int deltaY = targetY - originY;
		 if (deltaX==0 && deltaY>0) theta = 0;
	else if (deltaX<0 && deltaY==0) theta = 90;
	else if (deltaX<0 && deltaY>0)  theta = 90 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX<0 && deltaY<0)  theta = 90 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX==0 && deltaY<0) theta = 180;
	else if (deltaX>0 && deltaY<0)  theta = 270 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX>0 && deltaY==0) theta = 270;
	else if (deltaX>0 && deltaY>0)  theta = 270 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
}
bool isOnSwamp(){
	return colorCheck(w2Obj.slowarea, 10);
}
 void trigo(int targetX, int targetY, int PositionX1, int PositionY1)
{
	calcTheta(PositionX1, PositionY1, targetX, targetY);
	AngleDiff=abs(Compass-theta);
	if(AngleDiff>180) AngleDiff=360-AngleDiff;
	if(AngleDiff>=130&&AngleDiff<=180)
	{
		minSpeed=-4;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=80&&AngleDiff<130)
	{
		minSpeed=-3;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=30&&AngleDiff<80)
	{
		minSpeed=1;//1
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=15&&AngleDiff<30)
	{
		minSpeed=2;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=5&&AngleDiff<15)
	{
		minSpeed=4;
		maxSpeed=5;
	}
	else if(AngleDiff<5)
	{
		minSpeed=5;
		maxSpeed=5;
		if (w2Obj.LoadedObjects >3){
			minSpeed=3;
			maxSpeed=3;
		}
	}
	else //failsafe
	{
		minSpeed=-3;
		maxSpeed=-3;
	}
	//if(US_Front<=FRONT_MOVE_BACK+10) reduceSpeeds(minSpeed,maxSpeed);
	turnToAngle(theta);
}
};
SamuelTrigo st;


void rotateTo(int x, int y){
    //if (!reached(x,y,5,5)){
    st.trigo(x, y, PositionX1, PositionY1);
    //}
	//else{WheelLeft=0;WheelRight=0;}
}
int colorSensorX = PositionX1, colorSensorY = PositionY1;
void rotateToSuper(int x, int y){
    //if(reached(x,y,10,10)){WheelLeft=0;WheelRight=0;}
    //else{
    st.trigo(x, y, PositionX1, PositionY1);
    //rotateTo(x,y);//
}//trigo(x, y, colorSensorX, colorSensorY);}
void rotateToFAST(int x, int y){st.trigo(x, y, PositionX1, PositionY1);}
