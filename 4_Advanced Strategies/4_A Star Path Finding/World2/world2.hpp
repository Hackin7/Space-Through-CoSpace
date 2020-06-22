ofstream outfile;
ofstream mapFile;
ofstream pathFile;

Map location(layout);
AStar mapping(&location);

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
	moveAStar(&mapping, &location, 174,190);
}
