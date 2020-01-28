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
PresetMovement moveFixed;

int prevX; int prevY;
static void Game1()
{
    PositionX1 = PositionX;PositionY1 = PositionY;
    posInfoLost();
    colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
    cout<<"X:"<<PositionX1<<" Y:"<<PositionY1<<" TX:"<<tx<<" TY:"<<ty<<endl;

	if (Duration){ //>0
		Duration--;
		return;
	}if (moveFixed.run()){return;};

	///File IO/////////////////////////////////////////////////////////////
	if (!outfile.is_open()){
        outfile.open("CoSpace_Output.txt"); //Check the Robotics Dev Studio Folder
    }else{
        outfile<<"Time:"<<Time<<endl;
        outfile<<cycle.zoneToCollect;
        //outfile<<data;
        outfile.flush();
        outfile.seekp(0, ios::beg);
    }
    if (!mapFile.is_open()){
        mapFile.open("map.txt", ios::out | ios::trunc); //Check the Robotics Dev Studio Folder
    }else{
        ///Map
        for (int i=width-1;i>=0;i--){
            //if (i!=0){
            mapFile<<endl;//}
            for (int j=0;j<height;j++){
                //if (j!=0)
                mapFile<<" ";
                mapFile<<location.getPixel(i,j);
            }
        }
        //outfile<<data;
        //mapFile.flush();
        //mapFile.seekp(0, ios::beg);
        mapFile.close();
    }
    z.fileOut();
    if (!pathFile.is_open()){
        pathFile.open("path.txt"); //Check the Robotics Dev Studio Folder
    }else{
        for (auto i:mapping.path){
            pathFile<<i.pos[0]<<" "<<i.pos[1]<<endl;
        }
        //outfile<<data;
        pathFile.flush();
        pathFile.seekp(0, ios::beg);
    }
    /// //////////////////////////////////////////////////////////////////////

	bool collectBlue = w2Obj.LoadedObjects<6 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<6 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<6 && w2Obj.LoadedBlack<2;//true;
	bool deposit = w2Obj.LoadedObjects>=6 || Time > 450 || w2Obj.LoadedObjects>=1;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;//true;

    //mappingMode();

    if (w2Obj.Trap(avoid)){return;}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if ( US_Front < 15){
	    if (US_Left<US_Right){WheelLeft=-2;WheelRight=-4;}
	    else if (US_Left>US_Right){WheelLeft=-4;WheelRight=-2;}
	    else{WheelLeft=-3;WheelRight=-3;}
        Duration=10;} //iMPROVE wORLD 2 Wall Avoiding
	//else if (colorCheck(w2Obj.slowarea,20) && Time>10){WheelLeft=-3;WheelRight=-4;Duration=2;}
    else if (PositionX1==0 || PositionY1==0){posInfoLost();WheelLeft=3;WheelRight=3;return;}
    else if (boundary(15)){}
	else if (wallAvoiding(10)){}
	//else if (PositionX==0 || PositionY==0){WheelLeft=3;WheelRight=3;return;}
	else if (superObjAStar()){return;}
	//else if (w2Obj.LoadedObjects >=6 || (Time > 420 && (w2Obj.LoadedObjects >=3 ||w2Obj.LoadedSuperObj>0))){cout<<"D";cycle.moveDeposit();}
	//else

    else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);
    //else{WheelLeft=2;WheelRight=-2;}
    //else{WheelLeft=0;WheelRight=0;}

    //rotateTo(200,200);
    //moveAStar(310,45);

	prevX = PositionX;prevY=PositionY;
}
