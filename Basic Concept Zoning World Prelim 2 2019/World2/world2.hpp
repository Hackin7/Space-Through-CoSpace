class FindColour:public FindNode{
    private:
        int val = 1;
        Map *currlocation;
    public:
        FindColour(Map *c, int v){
            val = v;
            currlocation = c;
        };
         virtual bool operator() (int x, int y){
             bool condition = currlocation->getPixel(x,y) == val;
             return condition;
        };
};
bool moveDeposit(AStar *mapping, Map *location){
    int deposit = location->deposit;
    FindNode* go = new FindColour(location, deposit);
    mapping->getPath(PositionX,PositionY,go);
    moveTo(location,mapping->path,1);
    return true;
}
///////////////////////////////////////////////////////////////////////////////////
int pointX=-1;int pointY=-1;
void randomSelectZonePoint(int node){
    // Or randomly select node
    int counting=0;
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            if (zones[i][j] == node){counting++;}
        }
    }
    int pointNo = rand() % counting;
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            if (zones[i][j] == node){
                pointNo--;if (pointNo==0){pointX=i;pointY=j;}
            }
        }
    }

    printf("Random point chosen %d,%d\n", pointX, pointY);
}

class FindZone:public FindNode{
    private:
        Map *currlocation;
        int nodeval;
    public:
        FindZone(Map *c, int zones[width][height], int node){
            nodeval = node;
            currlocation = c;
        };
         virtual bool operator() (int x, int y){
             bool condition = (zones[x][y] == nodeval);
             return condition;
        };
};

const int numberOfZones = 5;
int zoneCycle[numberOfZones][2] =  {
    {10, 3},
    {13, 2},
    {11, 0},
    {4, 1},
    {1, 1}
};
int zoneNo = 0;
Timer Timing;
bool cycle(AStar *mapping, Map *location, bool blue, bool red, bool black){
    bool bluebypass = (!blue && zoneCycle[zoneNo][1] == 0);
    bool redbypass = (!red && zoneCycle[zoneNo][1] == 1);
    bool blackbypass = (!black && zoneCycle[zoneNo][1] == 2);
    bool bypass = bluebypass || redbypass || blackbypass;
    if (bluebypass&&redbypass&&blackbypass){bypass=false;}

    if (Timing.timeout(20) || bypass){
        Timing.reset();
        zoneNo++;
        if (zoneNo>=numberOfZones){zoneNo=0;}
    }
    int node = zoneCycle[zoneNo][0];
    //printf("Bypass blue:%d, red:%d, black:%d, total:%d\t", bluebypass,redbypass,blackbypass,bypass);
    printf("ZoneNo %d %d\n", zoneNo, node);

    if ( zones[PositionX1][PositionY1] == node){
        /*
        int choice = rand() % 7;
        //printf("Choice: %d\n",choice);
        switch(choice){
            case 0:WheelLeft=3;WheelRight=3;break;
            case 1:WheelLeft=3;WheelRight=4;break;
            case 2:WheelLeft=4;WheelRight=3;break;
            case 3:WheelLeft=2;WheelRight=4;break;
            case 4:WheelLeft=4;WheelRight=2;break;
            case 5:WheelLeft=-3;WheelRight=3;break;
            case 6:WheelLeft=3;WheelRight=-3;break;
            //default:WheelLeft=3;WheelRight=3;break;
        }*/
        if (reached(pointX,pointY,10,10) ||
            (pointX==-1 && pointY==-1) || //invalid
            zones[pointX][pointY] != node){
            randomSelectZonePoint(node);
        }
        moveAStar(mapping, location, pointX,pointY);
        return true;
    }
    else{
        FindNode* go = new FindZone(location, zones, node);
        mapping->getPath(PositionX,PositionY,go);
        moveTo(location,mapping->path,1);
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////////////////////
ofstream outfile;
ofstream mapFile;
ofstream pathFile;

void boxOut(int box, int x, int y){
    for(int j=max(0,x-box);j<x;j++){
        for(int k=max(0,y-box);k<y;k++){
            pathFile<<j<<" "<<k<<"\n";//count++;
    }}
}

static void Game1(){
    PositionX1 = PositionX;PositionY1 = PositionY;
    posInfoLost();
    colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	if (PositionX1 == 0 || PositionY1 == 0){PositionX1=tx;PositionY1=ty;}
    //cout<<"X:"<<PositionX1<<" Y:"<<PositionY1<<" TX:"<<tx<<" TY:"<<ty<<endl;

    if (Duration){ //>0
		Duration--;
		return;
	}

	///File IO/////////////////////////////////////////////////////////////

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
        mapFile.flush();
        mapFile.seekp(0, ios::beg);
    }
    if (!pathFile.is_open()){
        pathFile.open("path.txt"); //Check the Robotics Dev Studio Folder
    }else{
        for (auto i:mapping.path){
            //boxOut(5,i.pos[0],i.pos[1]);
            pathFile<<i.pos[0]<<" "<<i.pos[1]<<endl;
        }
        //outfile<<data;
        pathFile.flush();
        pathFile.seekp(0, ios::beg);
    }

    /////////////////////////////////////////////////////////////////////////

    bool collectBlue = w2Obj.LoadedObjects<6 && (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w2Obj.LoadedObjects<6 && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w2Obj.LoadedObjects<6 && w2Obj.LoadedBlack<2;//true;
	bool deposit = w2Obj.LoadedObjects>=3 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w2Obj.LoadedObjects>=2|| w2Obj.LoadedSuperObj > 0;//true;

	if (w2Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	if (w2Obj.Trap(w2Obj.LoadedObjects > 0)){return;}
	//else if (colorCheck(w2Obj.slowarea,20) && Time>60){WheelLeft=-3;WheelRight=-4;Duration=2;}
    //else if ( US_Front < 15){WheelLeft=-2;WheelRight=-3;Duration=5;} //iMPROVE wORLD 2 Wall Avoiding
    else if (boundary(12)){}
	else if ( US_Front < 9){
        WheelLeft=-2;WheelRight=-2;//Duration=2;
    }
    else if (superObjAStar()){return;}
    else if (w2Obj.LoadedObjects >=6 || (Time > 420 && (w2Obj.LoadedObjects >=3 ||w2Obj.LoadedSuperObj>0))){
        //printf("D");
        moveDeposit(&mapping, &location);
    }
    else{
        cycle(&mapping, &location, collectBlue, collectRed, collectBlack);//moveAStar(&mapping, &location, 174,190);
    }
}
