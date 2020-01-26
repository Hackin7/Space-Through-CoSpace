void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	posInfoLost();
    //printf("Points %d",LoadedPoints);
	//Super Object
	bool collectBlue = LoadedObjects<=7;//true;
	bool collectRed = LoadedObjects<=7;//true;
	bool collectBlack = LoadedObjects<=7;//true;
	bool deposit = true;//LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2|| LoadedSuperObj > 0;;//true;
/*
	if (LoadedRed>=4 ||
	(LoadedObjects >=5 &&  LoadedRed > 0 &&(LoadedBlue==0 || LoadedBlack==0)))
	{collectRed = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectRed = true;}

	if (LoadedBlack>=4 ||
	(LoadedObjects >=5 && LoadedBlack > 0 &&(LoadedBlue==0 || LoadedRed==0)))
	{collectBlack = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectBlack = true;}

	if (LoadedBlue>=4 ||
	(LoadedObjects >=5 && LoadedBlue > 0 &&(LoadedRed==0 || LoadedBlack==0)))
	{collectBlue = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectBlue = true;}
*/


	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing

	//else if ((US_Front < 20)){WheelLeft=-3;WheelRight=-3;Duration=10;}

	//else if (posInfoLost()){return;}
	else if (boundary()){}
	/*AvoidSlowArea*/
	else if (colorCheck(slowarea,20)){
          WheelLeft=-1;WheelRight=-5; // Turn
            Duration=10;
          }

    else if (wallAvoiding(15)){}
	else if (depositDijkstra()){}
	//else if (PositionX==0 && PositionY==0){WheelLeft=3;WheelRight=3;}
	else if (superObjDijkstra()){}

    else if (collectionDijkstra(false)){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}
}
