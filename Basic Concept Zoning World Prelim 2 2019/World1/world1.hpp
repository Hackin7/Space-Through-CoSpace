Map location0(layout0);
AStar mapping0(&location0);

static void Game0(){
    w1posInfoLost();
    colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
    cout<<"X:"<<PositionX1<<" Y:"<<PositionY1<<endl;

    if (Duration){ //>0
		Duration--;
		return;
	}

	///File IO/////////////////////////////////////////////////////////////
	/*
    if (!mapFile.is_open()){
        mapFile.open("map.txt", ios::out | ios::trunc); //Check the Robotics Dev Studio Folder
    }else{
        ///Map
        for (int i=width0-1;i>=0;i--){
            //if (i!=0){
            mapFile<<endl;//}
            for (int j=0;j<height0;j++){
                //if (j!=0)
                mapFile<<" ";
                mapFile<<location0.getPixel(i,j);
            }
        }
        //outfile<<data;
        //mapFile.flush();
        //mapFile.seekp(0, ios::beg);
        mapFile.close();
    }
    cout<<mapping0.path.size()<<"] ";
    if (!pathFile.is_open()){
        pathFile.open("path.txt", ios::out | ios::trunc); //Check the Robotics Dev Studio Folder
    }else{
        for (auto i:mapping0.path){
            pathFile<<i.pos[0]<<" "<<i.pos[1]<<endl;
        }
        //outfile<<data;
        pathFile.close();//flush();
        //pathFile.seekp(0, ios::beg);
    }
    */
	/// ////////////////////////////////////////////////////////////////////////////////////////////

	bool collectBlue = w1Obj.LoadedObjects<6 && w1Obj.LoadedBlue<6;//true;
	bool collectRed = w1Obj.LoadedObjects<6 && w1Obj.LoadedRed<6;//true;
	bool collectBlack = w1Obj.LoadedObjects<6 && w1Obj.LoadedBlack<6;//true;
	bool deposit = true || w1Obj.LoadedObjects>6 ||  w1Obj.LoadedSuperObj > 0;//true;
	bool avoid = w1Obj.LoadedObjects>=2|| w1Obj.LoadedSuperObj > 0;//true;

	if (w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
    else if (w1Obj.Trap(avoid)){return;}
	else if (wallAvoiding(15)){}
    else {
        WheelLeft=3;WheelRight=3;
    }//cycle0.collectObjects(!collectRed,!collectBlue, !collectBlack);

	//moveAStar(&mapping0, &location0, 174,190);
    if (Time > 180){
			Teleport = 2;
			LoadedObjects=0;
	}
}
