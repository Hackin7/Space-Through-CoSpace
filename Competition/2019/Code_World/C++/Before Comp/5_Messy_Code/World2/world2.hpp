

void moveStraight(int speed){
	WheelLeft=speed;WheelRight=speed;
}
void rotateangle(double angle){
	if (toCWM(angle)){
		WheelLeft=1;WheelRight=-1;
	}else{
		WheelLeft=-1;WheelRight=1;
	}
}
OneTime rotated;
int range = 15, sp = 5;
bool updir(){
	cout<< Compass<<endl;
	if (Compass < range|| Compass > 360-range){
		if (rotated.toRun()){
			moveLikeAnIdiot.addStep(0,0,2);
			moveLikeAnIdiot.addStep(sp,sp,5);
			//WheelLeft=0;WheelRight=0;
			//Duration = 2;
		}else{
		  moveStraight(sp);
		}
		return true;
	}
	else{
		rotated.reset();
		rotateangle(0);
		return false;
	}
}
bool downdir(){
	if (180-range < Compass & Compass < 180+range){
		if (rotated.toRun()){
			moveLikeAnIdiot.addStep(0,0,2);
			moveLikeAnIdiot.addStep(sp,sp,5);
		}else{
		  moveStraight(sp);
		}
		return true;
	}
	else{
		rotated.reset();
		rotateangle(180);
		return false;
	}
}
int m = 0;
bool rightdir(){
	if (270-range < Compass & Compass < 270+range){
		if (rotated.toRun()){
			moveLikeAnIdiot.addStep(0,0,2);
			moveLikeAnIdiot.addStep(sp,sp,5);
		}else{
		  moveStraight(sp);
		  Duration=5;
		  m++;
		}
		return true;
	}
	else{
		rotated.reset();
		rotateangle(270);
		return false;
	}
}
OneTime inb;
Timer awayFromBoundary;
void pathMove(){
	int X,Y;
	if ( (inBoundary() || colorCheck(w2Obj.slowarea,20) )&& inb.toRun() ){m++;}
	switch (m){
		case 0:
			if (updir() && US_Front < 25){m++;}
			if (awayFromBoundary.update(10))inb.reset();
			break;
		case 1:
		case 3:
			rightdir();
			break;
		case 2: 
			if (downdir() && US_Front < 25){m++;}
			if (awayFromBoundary.update(10))inb.reset();
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
	if (moveLikeAnIdiot.run()){return;};
	
	//pathMove();//downdir();//moveStraight(4);
	//cout<< Compass<<endl;
	/*
	bool collectBlue = w2Obj.LoadedObjects<=7 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<=7 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<=7 && w2Obj.LoadedBlack<2;//true;
	bool deposit = true || w2Obj.LoadedObjects>=6 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;;//true;
	if (w2Obj.Trap(true)){return;}
	else if (boundary()){}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding(20)){}
	else if (colorCheck(w2Obj.slowarea,20)){
		cout<<"SLOW!!!";
          //WheelLeft=-5;WheelRight=-5;
		  moveLikeAnIdiot.addStep(-5,-5,7);
		  if (downFromLeft()){moveLikeAnIdiot.addStep(-3,3,4);}
		  else if (downFromRight()){moveLikeAnIdiot.addStep(3,-3,4);}
		  else if (upFromLeft()){moveLikeAnIdiot.addStep(3,-3,4);}
		  else if (upFromLeft()){moveLikeAnIdiot.addStep(-3,3,4);}
		  else {moveLikeAnIdiot.addStep(-3,3,4);}
    }
	else{
		WheelLeft=5;WheelRight=5;
	}*/
	
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

    else if (wallAvoiding(5)){return;}
	//else if (depositDijkstra(LoadedObjects >= 4 || LoadedSuperObj > 0)){}
	else if (PositionX==0 && PositionY==0){WheelLeft=5;WheelRight=5;}
	else if (superObjAStar()){return;}
	else { // Default Movement
		//discovery();
		if (w2Obj.LoadedObjects >=6){cout<<"D";cycle.moveDeposit();}
		else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
	}
}