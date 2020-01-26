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

int random(int size){
	srand (Time);
	return (int) (rand()/RAND_MAX * size);
}

/// Movement Items
bool reachable(int x1, int y1, int x2, int y2){
	
	int dx = x1-x2;
	int dy = y1-y2;
	int signX = dx>0 ? 1:-1;
	int signY = dy>0 ? 1:-1;
	
	int i, j, j1,j2;
	for (int k=0; k<abs(dx); k++){
		i = x2 + signX*k;
		j = (int)y2 + signY*(dy/dx)*k;
		j1 = j-1;
		j2 = j+1;
		if (!location.isWalkablePixel(i,j) || !location.isWalkablePixel(i,j1) || !location.isWalkablePixel(i,j2)){
			return false;
		}
	}
	return true;
}
const int threshold = 50;
coordinates nodeSelect(){
	int i=2;
	for (;i < ( (int)mapping.path.size()<threshold ? (int)mapping.path.size():threshold );i++){
		if (!reachable(PositionX, PositionY, mapping.path[i].pos[0], mapping.path[i].pos[1])){
			i--;break;
		}
	}
	return mapping.path[i];
}
void moveTo(){
	coordinates node = nodeSelect();
	rotateTo(node.pos[0], node.pos[1]);
	//cout<<":"<<node.pos[0]<<","<<node.pos[1]<<"_";
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
///Move to Zones Nodes


class ZoneNodes:public coordinatesToNode{
private:
int convPosToNode(int from, int to){
	switch(to)
	{
		case 1: return from-width-1;
		case 2: return from-width;
		case 3: return from-width+1;
		case 4: return from-1;
		case 5: return from+1;
		case 6: return from+width-1;
		case 7: return from+width;
		case 8: return from+width+1;
	}
	assert(0);
	return 0;
}
bool closedList[v];

public:
	vector<int> nodesOfZone;
	
void zones(int start, int val){
		nodesOfZone.clear();
	for(int i=0; i<v; i++)
	{
		closedList[i] = false;
	}

	deque<int> openList;
	openList.push_back(start);

	int curr;
	while (!openList.empty())
	{
		curr = openList.front();
		openList.pop_front();
		if (getmap(curr) != val ) break;

		if(closedList[curr]) continue;
		closedList[curr] = true;

		for(int i=1; i<=8; i++)
		{
			if(conX(curr)==0&&(i==1||i==4||i==6)) continue;
			if(conX(curr)==width-1&&(i==3||i==5||i==8)) continue;
			if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
			if(conY(curr)==height-1&&(i==6||i==7||i==8)) continue;

			int next=convPosToNode(curr,i);
			//discard if out of w2map
			if(conX(next)<0||conX(next)>=width||conY(next)<0||conY(next)>=height) continue;

			//discard if already closedList
			if(!closedList[next] && getmap(next) == val)
			{
				openList.push_back(next);
				nodesOfZone.push_back(next);
			}
			
		}
	}
	}
	
	int pythagoreanDistance(int x1, int y1, int x2, int y2){
		return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
	}
	coordinates randomNode(int x, int y, int val, double percentage){
		zones(conv(x, y), val);
		int size = (int)nodesOfZone.size();
		int r = random((int)size*percentage) + (int)size*(1-percentage);
		//cout<<":"<<(int)nodesOfZone.size()<<":";
		return convCoordinates(nodesOfZone[r]);
	}

};
class Zoning:public ZoneNodes{
private:
	OneTime onetime;
	int posX=PositionX1, posY=PositionY1;
	class FindZone:public FindNode{
		private: int val = 4;
		public:
			FindZone(int v){val = v;};
			 virtual bool operator() (int x, int y){return (location.getPixel(x,y) == val);};
	};
public:
void moveZone(int val){
	if (location.getPixel(PositionX1,PositionY1) != val){
		FindNode* go = new FindZone(val);
		mapping.getPath(PositionX1,PositionY1,go);
		moveTo();
		if (!onetime.toRun()){onetime.reset();}
	}//Random Points
	else{
		if (onetime.toRun()){
			//cout<<"val";
			//posX = 0; posY = 0;
			coordinates c = randomNode(PositionX1, PositionY1, val, 0.5);
			posX = c.pos[0];
			posY = c.pos[1];
			cout<<posX<<","<<posY<<endl;
		}
		rotateTo(posX, posY);
		if (reached(posX, posY, 5, 5)){onetime.reset();}
	}
}
void moveRed(){moveZone(2);}
void moveBlue(){moveZone(3);}
void moveBlack(){moveZone(4);}
void moveDeposit(){moveZone(1);}
};
class Cycle:public Zoning{
private:
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

public:
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
};

Cycle cycle;

Timer SuperObjTimer;

int SuperObjX;//[20];
int SuperObjY;//[20];

bool superObjAStar(){
    if (SuperObj_Num>0 && w2Obj.noSuperObj != SuperObj_Num){
            w2Obj.noSuperObj = SuperObj_Num;
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
		SuperObjTimer.reset();
        return true;
	}
	/*
	else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,25,25)){
		cout<<"SUPER+++!!!"<<endl;
        FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect();
		rotateToSuper(node.pos[0], node.pos[1]);
        return true;
    }*/
	else if (w2Obj.noSuperObj>0 &&
			(
			(!reached(SuperObjX-5,SuperObjY-5,5,5)
			&& !SuperObjTimer.timeout(60)) || 
			!reached(SuperObjX-5,SuperObjY-5,25,25)
			)
		){
		//moveAStar(SuperObjX,SuperObjY);
		cout<<"SUPER!!!"<<endl;
        FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect();
		rotateToSuper(node.pos[0], node.pos[1]);
		
		return true;
	}
	else if (SuperObjTimer.timeout(60)){
        //w2Obj.noSuperObj = 0;
		SuperObjTimer.reset();
	}
	return false;
}