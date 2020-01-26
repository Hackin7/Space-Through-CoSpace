bool started = false;
AStar mapping;

int PositionX1=98, PositionY1=130;
int CurrTime = 0;

class OneTime{
	private: bool ran = false;

	public:
	OneTime(){}
	bool toRun(){
		if (!ran){ran = true;return true;}
		return false;
	}
	void reset(){ran = false;}
};

class Timer{
	private:
	int prevTime=0;

	public:
	Timer(){reset();}
	bool timeout(int diff){return Time-prevTime >= diff;}
	void reset(){prevTime = Time;}
	
	bool update(int diff){
		if (timeout(diff)){reset();}
		return timeout(diff);
	}
};

/// Movement Items
bool reachable(int x1, int y1, int x2, int y2){
	
	int dx = x1-x2;
	int dy = y1-y2;
	int signX = dx>0 ? 1:-1;
	int signY = dy>0 ? 1:-1;
	
	int i, j;
	for (int k=0; k<abs(dx); k++){
		i = x2 + signX*k;
		j = (int)y2 + signY*(dy/dx)*k;
		if (::map[i][j] != 0 || ::map[i][j] != 5 || ::map[i][j] != 6){
			return false;
		}
	}
	return true;
}
const int threshold = 100;
void moveTo(){
	int i=2;
	for (;i < ( (int)mapping.path.size()<threshold ? (int)mapping.path.size():threshold );i++){
		if (!reachable(PositionX, PositionY, mapping.path[i].pos[0], mapping.path[i].pos[1])){
			i--;break;
		}
	}
	rotateTo(mapping.path[i].pos[0], mapping.path[i].pos[1]);
	//cout<<i<<":"<<mapping.path[i].pos[0]<<","<<mapping.path[i].pos[1]<<"_";
}

///Move to coordinates
class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};
void moveAStar(int x, int y){
	FindNode* go = new CheckReached(x,y);
	mapping.getPath(PositionX1,PositionY1,go);
	moveTo();
}

///Move to Blue Nodes

class FindZone:public FindNode{
private: int val = 4;
public:
    FindZone(int v){val = v;};
     virtual bool operator() (int x, int y){return (::map[x][y] == val);};
};

int closed[width][height];
bool canWalkHere(int x,int y, int val){
    return (::map[x][y] == val && !closed[x][y]); //Walkable Tile Value
}
vector<coordinates> Neighbours(int x,int y, int val){
    int North = y-1,
    South = y+1,
    East = x+1,
    West = x-1;
    bool NorthConnected = false,
    SouthConnected = false,
    EastConnected = false,
    WestConnected = false;
    if (North>-1){if (canWalkHere(x,North, val)){NorthConnected = true;}}
    if (South<height){if (canWalkHere(x,South, val)){SouthConnected = true;}}
    if (East<width){if (canWalkHere(East,y, val)){EastConnected = true;}}
    if (West>-1){if (canWalkHere(West, y, val)){WestConnected =  true;}}

    vector<coordinates> neighbours;
    if (NorthConnected){
        neighbours.push_back({x,North});}
    if (SouthConnected){
        neighbours.push_back({x,South});}
    if (EastConnected){
        neighbours.push_back({East,y});}
    if (WestConnected){
        neighbours.push_back({West,y});}
    //For Diagonal movement

   if(NorthConnected){
        if(EastConnected && canWalkHere(East, North, val))
        neighbours.push_back({East,North});
        if(WestConnected && canWalkHere(West, North, val))
        neighbours.push_back({West,North});
    }
    if(SouthConnected){
        if(EastConnected && canWalkHere(East, South, val))
        neighbours.push_back({East, South});
        if(WestConnected && canWalkHere(West, South, val))
        neighbours.push_back({West, South});
    }
	return neighbours;
}

OneTime onetime;
int posX=PositionX1, posY=PositionY1;
void moveZone(int val){
	if (::map[PositionX1][PositionY1] != val){
		FindNode* go = new FindZone(val);
		mapping.getPath(PositionX1,PositionY1,go);
		moveTo();
		if (!onetime.toRun()){onetime.reset();}
	}//Random Points
	else{
		if (onetime.toRun()){
			int closed[width][height];
			for (int i=0;i<width;i++){
				for (int j=0;j<height;j++){
					closed[i][j] = false;
				}
			}
			posX = PositionX1; posY = PositionY1;
			closed[posX][posY] = true;
			int r = 0;
			//Threshold needs to be large enough
			for (int i=0; i< (int) (rand()/RAND_MAX *100 + 100) ; i++){
				vector<coordinates> neighbours = Neighbours(posX, posY, val);
				r = (int) (rand()/RAND_MAX * neighbours.size());
				posX = neighbours[r].pos[0]; posY = neighbours[r].pos[1];
			}
		}
		cout<<posX<<","<<posY<<endl;
		rotateTo(posX, posY);
		if (reached(posX, posY, 5, 5)){onetime.reset();}
	}
}
void moveRed(){moveZone(2);}
void moveBlue(){moveZone(3);}
void moveBlack(){moveZone(4);}
void moveDeposit(){moveZone(1);}


Timer Timing;


bool cycle[3] = {false, false, false};
bool cycleFull(){
	for (int i=0; i<3; i++){
		if (!cycle[i])return false; 
	}
	return true;
}
void cycleReset(){
	for (int i=0; i<3; i++){
		cycle[i] = false; 
	}
}
int AppropriateZone(){
	//Reset
	if (cycleFull()){
		cycleReset();
	}
	moveRed();
	int redPath = (int)mapping.path.size();
	moveBlue();
	int bluePath = (int)mapping.path.size();
	moveBlack();
	int blackPath = (int)mapping.path.size();
	
	int zone = 2;//Black
	int minPath = blackPath;
	if ( (bluePath <= minPath && !cycle[1]) || cycle[2]){minPath = bluePath;zone = 1;}//Blue
	if ( (redPath <= minPath && !cycle[0]) || (zone == 3 && cycle[1])){minPath = redPath;zone = 0;}//Red
	return zone;
}
int zoneToCollect = -1;
void collectObjects(bool red, bool blue, bool black){
	switch(zoneToCollect){
		case 0: //Red
			moveRed();
			cycle[0] = true;
			if (red) zoneToCollect = -1;
			break;
		case 1: //Blue
			moveBlue();
			cycle[1] = true;
			if (blue) zoneToCollect = -1;
			break;
		case 2: //Black
			moveBlack();
			cycle[2] = true;
			if (black) zoneToCollect = -1;
			break;
	}
	if (Timing.timeout(40) || zoneToCollect == -1){
		zoneToCollect = AppropriateZone();
		Timing.reset();
		cout<<zoneToCollect<<endl;
	}
	//cout<<zoneToCollect;
}

Timer SuperObjTimer;
bool superObjAStar(){
    if (SuperObj_Num>0 && noSuperObj != SuperObj_Num){
        //if (noSuperObj<SuperObj_Num){
            //Collect 1 superobject at a time
            noSuperObj = SuperObj_Num;
        //}
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
		SuperObjTimer.reset();
        return true;
	}
	else if (noSuperObj>0 && reached(SuperObjX,SuperObjY,25,25)){
        WheelLeft=3;WheelRight=3;
        quarrantine(SuperObjX-11,
                    SuperObjX+11,
                    SuperObjY-11,
                    SuperObjY+11,11, 11);
        return true;
    }
	else if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5,5)
          && !SuperObjTimer.timeout(60)){
		moveAStar(SuperObjX,SuperObjY);
        return true;
	}
	else if (SuperObjTimer.timeout(40)){
        noSuperObj = 0;
		SuperObjTimer.reset();
	}
	return false;
}