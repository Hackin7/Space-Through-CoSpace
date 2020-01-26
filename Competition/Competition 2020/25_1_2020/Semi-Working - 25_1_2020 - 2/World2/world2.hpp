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

//#include <fstream>
//ofstream outfile;
ofstream mapFile;
ofstream pathFile;

int prevX; int prevY;
static void Game1()
{
    PositionX1 = PositionX;PositionY1 = PositionY;

	if (PositionX==0 || PositionY==0){
            //PositionX = prevX;PositionY=prevY;
            //WheelLeft=3;WheelRight=5;
    }
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
        mapFile.open("map.txt"); //Check the Robotics Dev Studio Folder
    }else{
        ///Map
        for (int i=width-1;i>=0;i--){
            for (int j=0;j<height;j++){
                mapFile<<location.getPixel(i,j);
                if(j!=0)mapFile<<" ";
            }mapFile<<endl;
        }
        //outfile<<data;
        mapFile.flush();
        mapFile.seekp(0, ios::beg);
    }
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

	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);

	bool collectBlue = w2Obj.LoadedObjects<6 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<6 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<6 && w2Obj.LoadedBlack<2;//true;
	bool deposit = true || w2Obj.LoadedObjects>=6 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;//true;


	//if (Time > 410){collectBlue=true;collectBlack=true;collectRed=true;cycle.zoneToCollect=4;cout<<"FAST Game";}

	//else

        //cycle.currZoneNo=max(cycle.currZoneNo,z.getZoneNo(PositionX1,PositionY1));
        //cout<<endl<<"ZoneNo: "<<PositionX1<<","<<PositionY1<<","<<z.getZoneNo(PositionX1,PositionY1)<<", ";

    if (w2Obj.Trap(avoid)){return;}
	else if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if ( US_Front < 15){WheelLeft=-2;WheelRight=-3;Duration=5;} //iMPROVE wORLD 2 Wall Avoiding
	//else if (colorCheck(w2Obj.slowarea,20) && Time>60){WheelLeft=-3;WheelRight=-4;Duration=2;}
    else if (boundary(10)){}
	else if (wallAvoiding(10)){}
	else if (PositionX==0 || PositionY==0){//cout<<"Nothing";}//}PositionX = prevX;PositionY=prevY;return;}//
	    WheelLeft=3;WheelRight=3;return;}
	else if (superObjAStar()){return;}
	//else if (w2Obj.LoadedObjects >=6 || (Time > 420 && (w2Obj.LoadedObjects >=3 ||w2Obj.LoadedSuperObj>0))){cout<<"D";cycle.moveDeposit();}
	//else
	//else if (PositionX==0 || PositionY==0){WheelLeft=3;WheelRight=3;return;}
    else cycle.collectObjects(!collectRed,!collectBlue, !collectBlack);

    //rotateTo(200,200);
    //moveAStar(310,45);

	prevX = PositionX;prevY=PositionY;
}
