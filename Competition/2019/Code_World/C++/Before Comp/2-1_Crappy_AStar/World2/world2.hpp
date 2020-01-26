
static void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	posInfoLost();
	
	startAStar(319, 190);
	cout<<"_";
	moveAStar();
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