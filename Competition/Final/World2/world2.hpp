int prevX; int prevY;
static void Game1()
{
	if (PositionX==0 || PositionY==0){PositionX = prevX;PositionY=prevY;}
	cout<<PositionX<<","<<PositionY<<",";
	if (Duration){ //>0
		Duration--;
		return;
	}

	//posInfoLost();
	PositionX1 = PositionX;
	PositionY1 = PositionY;

	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	//cout<<"_";//<<PositionX1<<","<<PositionY1<<"_"<<endl;

	//if (w2Obj.isCollected()){
	//	location.squareFill(PositionX1,PositionY1,location.empty, 5);
	//}
	//if (colorCheck(w2Obj.ignorePurple,30)){cout<<"Purple";return;}

	bool collectBlue = w2Obj.LoadedObjects<=7 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<=7 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<=7 && w2Obj.LoadedBlack<2;//true;
	bool deposit = true || w2Obj.LoadedObjects>=6 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;//true;
	//discovery();

	if (w2Obj.Trap(avoid)){return;}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (boundary(3)){}
	else if (colorCheck(w2Obj.slowarea,20)){
          //WheelLeft=-2;WheelRight=-4;
          }

    else if (wallAvoiding(15)){}
	//else if (PositionX==0 || PositionY==0){//cout<<"Nothing";}//}PositionX = prevX;PositionY=prevY;return;}//
	//WheelLeft=3;WheelRight=3;return;}
	else if (superObjAStar()){return;}
	else if (w2Obj.LoadedObjects >=6 || (Time > 420 && (w2Obj.LoadedObjects >=3 ||w2Obj.LoadedSuperObj>0))){cout<<"D";cycle.moveDeposit();}
	else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
	prevX = PositionX;prevY=PositionY;
}
