// File: Game1/PosInfoLost.c
double * angleToHorizontal(int speed){
	double angle=0, deltaX=0, deltaY=0;
	if (Compass > 270){
		angle = Compass - 270; //Anticlockwise Upward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (180< Compass && Compass < 270){
		angle = 270 - Compass;// Clockwise Downward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = -sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (90< Compass && Compass < 180){
		angle = Compass - 180;// Clockwise Downward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = -sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (Compass < 90){
		angle = 90 - Compass;//Clockwise upward
		deltaX = -cos(angle/(2*3.14159265358979323846) * 360);
		deltaY = sin(angle/(2*3.14159265358979323846) * 360);
	}
	else if (Compass == 0)//up
	{
		angle = 0;
		deltaX = 0;//speed * cos(angle);
		deltaY = 1 ;//* sin(angle);
	}
	else if (Compass == 180)//down
	{
		angle = 0;
		deltaX = 0;//speed * cos(angle);
		deltaY = -1 ;//* sin(angle);
	}
	else if (Compass == 90)//left
	{
		angle = 0;
		deltaX = -1 ;//* cos(angle);
		deltaY = 0;//speed * sin(angle);
	}
	else// if (Compass == 270) //right
	{
		angle = 0;
		deltaX = 1 ;//* cos(angle);
		deltaY = 0;//-speed * sin(angle);
	}
	/*printf("Compass %d ",Compass);
	printf("^X %f ",deltaX);
	//printf("sin60 %f ",sin(3.14159265358979323846/3));
	printf("^Y %f\n",deltaY);
	*/

    double output[3] = {angle, deltaX*speed/215, deltaY*speed};
	return output;
}

double tx=0,ty=0;
int icompass=0;
int speed;
void posInfoLost(){
    if (PositionX==0 && PositionY==0)
    {
			if ((WheelLeft<2 && WheelLeft>-2) || (WheelRight>-2 && WheelRight<2)) // can ignore i guess? since its probably turning
			{
				PositionX=tx;
				PositionY=tx;
				return;
			}
      speed=(WheelLeft+WheelRight)/3.48;
      tx = speed * cos((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + tx;
      ty =speed * sin((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + ty;
			PositionX=tx;
			PositionY=ty;
    }

icompass=Compass;
tx = PositionX;
ty = PositionY;
}

class Vector2 {
public:

	double x,y;
	bool reverse;

	void setWheels(int WL, int WR)
	{
		double coeff=215.0;
		reverse = WL<0 && WR<0;
		x = 0;
		y = abs(WL + WR)/coeff;
	}

	pair<double,double> rotate(double prevX, double prevY, double prevAngle, double currAngle, int numIT)
	{
		//convert degrees to radians
		currAngle*=0.0174532925199432958;
		prevAngle*=0.0174532925199432958;

		double rate_of_rotation = (currAngle - prevAngle)/numIT;
		pair<double,double> result = make_pair(prevX, prevY);

		for (int i=0; i<numIT; i++)
		{
			currAngle = prevAngle + rate_of_rotation*i;
			double sin_ = sin(currAngle);
			double cos_ = cos(currAngle);

			double tx = -sin_ * y;
			double ty = cos_ * y;

			if (!reverse)
			{
				result.first += tx;
				result.second += ty;
			}
			else
			{
				result.first -= tx;
				result.second -= ty;
			}

		}
		return result;
	}
} ;