
bool dijkstraStarted = false;
void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	//posInfoLost();
    //printf("Points %d",LoadedPoints);
	//Super Object
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;//LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2;//true;

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



	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	//else if (posInfoLost()){return;}
	else if (boundary()){}
	else if (LoadedObjects >= 4 || LoadedSuperObj > 0){
        if (!dijkstraStarted){depositDijkstra();dijkstraStarted=true;}
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);
    }
	else if (PositionX==0 && PositionY==0){
        WheelLeft=3;WheelRight=3;
	}
	else if (superObjDijkstra()){}

    else if (collectionDijkstra(false)){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}
}
