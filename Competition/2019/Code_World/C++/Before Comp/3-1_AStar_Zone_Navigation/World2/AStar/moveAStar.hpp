bool started = false;
AStar mapping;

int PositionX1=98, PositionY1=130;
int CurrTime = 0;

class OneTime{
	private: bool ran = false;

	public:
	OneTime(){}
	bool toRun(){
		if (!ran){ran = true;}
		return (!ran);
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

bool canWalkHere(int x,int y, int val, int closed[width][height]){
    return (::map[x][y] == val && !closed[x][y]); //Walkable Tile Value
}
vector<coordinates> Neighbours(int x,int y, int val, int closed[width][height]){
    int North = y-1,
    South = y+1,
    East = x+1,
    West = x-1;
    bool NorthConnected = false,
    SouthConnected = false,
    EastConnected = false,
    WestConnected = false;
    if (North>-1){if (canWalkHere(x,North, val, closed)){NorthConnected = true;}}
    if (South<height){if (canWalkHere(x,South, val, closed)){SouthConnected = true;}}
    if (East<width){if (canWalkHere(East,y, val, closed)){EastConnected = true;}}
    if (West>-1){if (canWalkHere(West, y, val, closed)){WestConnected =  true;}}

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
        if(EastConnected && canWalkHere(East, North, val, closed))
        neighbours.push_back({East,North});
        if(WestConnected && canWalkHere(West, North, val, closed))
        neighbours.push_back({West,North});
    }
    if(SouthConnected){
        if(EastConnected && canWalkHere(East, South, val, closed))
        neighbours.push_back({East, South});
        if(WestConnected && canWalkHere(West, South, val, closed))
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
	//if (reached(mapping.path[mapping.path.size()-1].pos[0], 
	//			mapping.path[mapping.path.size()-1].pos[1],
	//			5, 5 )){
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
			for (int i=0; i< (int) (rand()/RAND_MAX *50 + 50) ; i++){
				vector<coordinates> neighbours = Neighbours(posX, posY, val, closed);
				r = (int) (rand()/RAND_MAX * neighbours.size());
				posX = neighbours[r].pos[0]; posY = neighbours[r].pos[1];
			}
		}
		cout<<"Collecting";
		rotateTo(posX, posY);
		if (reached(posX, posY, 5, 5)){onetime.reset();}
	}
}
void moveRed(){moveZone(2);}
void moveBlue(){moveZone(3);}
void moveBlack(){moveZone(4);}

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
void collectObjects(){
	switch(zoneToCollect){
		case 0: //Red
			moveRed();
			cycle[0] = true;
			break;
		case 1: //Blue
			moveBlue();
			cycle[1] = true;
			break;
		case 2: //Black
			moveBlack();
			cycle[2] = true;
			break;
	}
	if (Timing.timeout(10) || zoneToCollect == -1){
		zoneToCollect = AppropriateZone();
		Timing.reset();
		cout<<zoneToCollect<<endl;
	}
	//cout<<zoneToCollect;
}

