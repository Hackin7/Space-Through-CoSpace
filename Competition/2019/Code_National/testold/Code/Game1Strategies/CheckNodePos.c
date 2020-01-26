bool dijkstraStarted = false;
void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	//posInfoLost();

	//Super Object
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2;//true;


	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	else if (PositionX==0 && PositionY==0){
        WheelLeft=3;WheelRight=3;
	}
	//else if (posInfoLost()){return;}
	else if (boundary()){}
    else if (collectionDijkstra(false)){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}
}
