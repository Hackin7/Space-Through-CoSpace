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
	//cout<<"_";//<<PositionX1<<","<<PositionY1<<"_"<<endl;

	if (w2Obj.isCollected()){
		location.squareFill(PositionX1,PositionY1,location.empty, 5);
	}
	
	bool collectBlue = w2Obj.LoadedObjects<=;//7 && (w2Obj.LoadedBlue)<3;//true;
	bool collectRed = w2Obj.LoadedObjects<=7;// && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<=7;// && w2Obj.LoadedBlack<2;//true;
	bool deposit = true;//true;
	bool avoid = w2Obj.LoadedObjects>=2;//true;
	//discovery();
	
	if (w2Obj.Trap(avoid)){return;}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	//else if (boundary()){}
	else if (colorCheck(w2Obj.slowarea,20)){
          WheelLeft=-2;WheelRight=-4;
          }

    else if (wallAvoiding(12)){}
	//else if (depositDijkstra(LoadedObjects >= 4 || LoadedSuperObj > 0)){}
	else if (PositionX==0 && PositionY==0){WheelLeft=2;WheelRight=3;}
	else if (superObjAStar()){}
	else { // Default Movement
		if (w2Obj.LoadedObjects >=5){cout<<"D";cycle.moveDeposit();}
		else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
	}
}