void moveStraight(int speed){
	WheelLeft=speed;WheelRight=speed;
}
OneTime rotated;
int range = 10, sp = 4;
bool updir(){
	cout<< Compass<<endl;
	if (Compass < range|| Compass > 360-range){
		if (rotated.toRun()){
			WheelLeft=0;WheelRight=0;
			Duration = 2;
		}else{
		  moveStraight(sp);
		}
		return true;
	}
	else{
		rotated.reset();
		WheelLeft = 1; WheelRight=-1;
		return false;
	}
}
bool downdir(){
	if (180-range < Compass & Compass < 180+range){
		if (rotated.toRun()){
			WheelLeft=0;WheelRight=0;
			Duration = 2;
		}else{
		  moveStraight(sp);
		}
		return true;
	}
	else{
		rotated.reset();
		WheelLeft = 1; WheelRight=-1;
		return false;
	}
}
int m = 0;
bool rightdir(){
	if (270-range < Compass & Compass < 270+range){
		if (rotated.toRun()){
			WheelLeft=0;WheelRight=0;
			Duration = 2;
		}else{
		  moveStraight(sp);
		  Duration=5;
		  m++;
		}
		return true;
	}
	else{
		rotated.reset();
		WheelLeft = 1; WheelRight=-1;
		return false;
	}
}
OneTime inb;
void pathMove(){
	int X,Y;
	if (inBoundary() && inb.toRun()){m++;}
	else{inb.reset();}
	switch (m){
		case 0:
			if (updir() && US_Front < 15){m++;}
			break;
		case 1:
		case 3:
			rightdir();
			break;
		case 2: 
			if (downdir() && US_Front < 15){m++;}
			break;
		default: m = 0;break;
	}
	cout<<m<<",";
}
static void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}
	pathMove();//downdir();//moveStraight(4);
	cout<< Compass<<endl;
	if (w2Obj.Trap(true)){return;}
	else if (boundary()){}
	//else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	//else if (wallAvoiding(12)){}
	/*
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
	else if (PositionX==0 && PositionY==0){WheelLeft=2;WheelRight=3;}
	else if (superObjAStar()){}
	else { // Default Movement
		if (w2Obj.LoadedObjects >=6){cout<<"D";cycle.moveDeposit();}
		else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
	}*/
}