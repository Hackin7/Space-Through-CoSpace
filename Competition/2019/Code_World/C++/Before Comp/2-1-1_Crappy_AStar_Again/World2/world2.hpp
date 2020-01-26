#pragma once

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
int prevCompass=0;
static void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}
	PositionX1=PositionX,PositionY1=PositionY;
	//posInfoLost();
	/*
	if(!isInfoLost())
	{
		PositionX1 = PositionX;
		PositionY1 = PositionY;
	}*/
	if (PositionX1=0||PositionY1==0)
	{
		Vector2 bot;
		bot.setWheels(WheelLeft, WheelRight);
		pair <double, double> position;
		position = bot.rotate(PositionX1, PositionY1, prevCompass, Compass, isOnSwamp() ? 12 : 60);
		// int i = min(2, (int)path.size());
		// PositionX1=convFinalX(path[i]);
		// PositionY1=convFinalY(path[i]);
		PositionX1=(int)round(position.first);
		PositionY1=(int)round(position.second);
	}
	
	startAStar(330, 190);
	cout<<"_";//"["<<PositionX1<<","<<PositionY1<<"_";
	moveAStar();
	prevCompass = Compass;
}

static void Game1Legacy()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	posInfoLost();

	bool collectBlue = LoadedObjects<=7;// && LoadedBlue<2;//true;
	bool collectRed = LoadedObjects<=7;// && LoadedRed<2;//true;
	bool collectBlack = LoadedObjects<=7;// && LoadedBlack<2;//true;
	bool deposit = true;//LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2|| LoadedSuperObj > 0;;//true;


	//For SuperOBJ Collection
	//bool collectBlue = LoadedObjects<=7 && LoadedBlue<=2;//true;
	//bool collectRed = LoadedObjects<=7 && LoadedRed<=2;//true;
	//bool collectBlack = LoadedObjects<=7 && LoadedBlack<=2;//true;

int startTime = 183;
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
    //else if (US_Front < 20){WheelLeft=-3;WheelRight=-3;Duration=5;}
	else if (boundary()){}
	/*AvoidSlowArea*/
	else if (colorCheck(slowarea,20)){
          WheelLeft=-2;WheelRight=-4; // Turn
            //WheelLeft=5;WheelRight=5; // Turn
          Duration=5;
          }

    else if (wallAvoiding(15)){}
	else if (depositDijkstra(LoadedObjects >= 4 || LoadedSuperObj > 0)){}
	//else if (PositionX==0 && PositionY==0){WheelLeft=3;WheelRight=3;}
	else if (superObjDijkstra()){}
	else if (startTime < Time&&Time <startTime+60){
            printf("CHOPEBLACK");
        blackDijkstra();
	}
    else if (collectionDijkstra(false)){}
    //else if (collectionSuperObjectDijkstra()){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}

}