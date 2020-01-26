template<typename T> static inline bool inRange(T a, T b, T c){return b<=a&&a<=c;}

int colorSensorX, colorSensorY;
static void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}
	posInfoLost();
	PositionX1 = PositionX;
	PositionY1 = PositionY;
	
	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	cout<<"_";//<<PositionX1<<","<<PositionY1<<"_"<<endl;

	//moveAStar(330, 190);
	collectObjects();
	
	bool collectBlue = LoadedObjects<=7;// && LoadedBlue<2;//true;
	bool collectRed = LoadedObjects<=7;// && LoadedRed<2;//true;
	bool collectBlack = LoadedObjects<=7;// && LoadedBlack<2;//true;
	bool deposit = true;//LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2|| LoadedSuperObj > 0;;//true;
	
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

    else if (wallAvoiding(10)){}
	/*
	else if (depositDijkstra(LoadedObjects >= 4 || LoadedSuperObj > 0)){}
	//else if (PositionX==0 && PositionY==0){WheelLeft=3;WheelRight=3;}
	else if (superObjDijkstra()){}
	else if (startTime < Time&&Time <startTime+60){
            printf("CHOPEBLACK");
        blackDijkstra();
	}
    else if (collectionDijkstra(false)){}
    //else if (collectionSuperObjectDijkstra()){}*/
	else { // Default Movement
		//WheelLeft=3;WheelRight=3;
	}
}