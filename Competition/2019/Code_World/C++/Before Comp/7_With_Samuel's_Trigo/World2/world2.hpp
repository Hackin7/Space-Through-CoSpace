
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
	
	bool collectBlue = w2Obj.LoadedObjects<=7 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<=7 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<=7 && w2Obj.LoadedBlack<2;//true;
	bool deposit = true || w2Obj.LoadedObjects>=6 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;;//true;
	//discovery();
	
	if (w2Obj.Trap(avoid)){return;}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	//else if (boundary()){}
	else if (colorCheck(w2Obj.slowarea,20)){
          WheelLeft=-2;WheelRight=-4;
          }

    else if (wallAvoiding(12)){}
	//else if (depositDijkstra(LoadedObjects >= 4 || LoadedSuperObj > 0)){}
	else if (PositionX==0 && PositionY==0){WheelLeft=3;WheelRight=3;}
	else if (superObjAStar()){return;}
	else if (w2Obj.LoadedObjects >=6){cout<<"D";cycle.moveDeposit();}
	else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
}

/*
class PresetMovement{
	public:
	deque<pair<pair<int,int>,int> > steps;
	void addStep(int left, int right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=left;
		step.first.second=right;
		step.second=delay;
		steps.push_back(step);
	}
	bool run(){
		if (!steps.empty()){
			WheelLeft = steps[0].first.first;
			WheelRight = steps[0].first.second;
			Duration = steps[0].second;
			steps.pop_front();
			cout<<"Move Like An Idiot:"<<WheelLeft<<","<<WheelRight<<","<<Duration<<endl;
			return true;
		}
		return false;
	}
};
PresetMovement moveLikeAnIdiot;

class Discovery{
	public:
	int cornerMode = 4;
	Timer CornerTimer;
	
	void discoverCorner(){
		int posX = 90, posY = 203;
		switch (cornerMode){
			case 1:
			posX = 90;posY = 203;break;
			case 2:
			posX = 270;posY = 203;break;
			case 3:
			posX = 270;posY = 68;break;
			case 4:
			posX = 90;posY = 68;break;
			default:cornerMode=1;
		}
		rotateTo(posX, posY);//moveAStar(posX, posY);
		if (CornerTimer.timeout(20)){
			CornerTimer.reset();
			//cornerMode++;
		}
	}
	
	void discover(){
		discoverCorner();
	}
	
	void circleSurroundings(){
		moveLikeAnIdiot.addStep(1,-1,84);
	}
};
Discovery mapOut;
int tmap=0; // fopr mapping bulshit

int map_=0;
void Game1()
{
	PositionX1 = PositionX;
	PositionY1 = PositionY;
	
	mappingMode();
	
  if (map_==0)
  {
    for (int x=0;x<360;x++)
    {
      for (int y=0;y<270;y++)
      {location.map[x][y]=unexploredcol;}

	  }
	  map_=1;
	  printf("%d\n",unexfloorcol );
	  mapOut.circleSurroundings();
	  return;
	}
	
posInfoLost();
  tmap++;
  if (Time > 30 && map_ <2) // print map
  {
	  map_ = 2;
    for (int x=0; x<360; x++)
    {
      for (int y=0; y<270;y++)
      {
        printf("%d ", location.map[x][y]);
      }
    }
  }



//colormap(colorSensorX,colorSensorY);


  if (Duration > 0)
  {
    Duration--;
    return;
  }
  if (moveLikeAnIdiot.run()){return;};
  LED_1 = 0;
  
  
  mapOut.discover();
  //WheelLeft=3;WheelRight=-3;
  //WheelLeft=5;WheelRight=-5;return;
  if (boundary()){return;}
  else if (wallAvoiding(15)){return;}
  //WheelLeft = -1;WheelRight=1;
  
  // if (LoadedObjects == 0)
  // {
    // WheelRight = 4;
  	// WheelLeft = 4;
  // }
  // else if (colorCheck(w2Obj.slowarea,10)){WheelLeft=-4;WheelRight=-5;}
  // else
  // {
    // WheelRight = 3;
  	// WheelLeft = 3;
  // }
}

*/