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

///Movement Items////////////////////////////////////////////
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

class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};
const int threshold = 1;
int selectedNode=0;
coordinates prevCoordinates;
coordinates nodeSelect(){
	int i=threshold;/*
	for (;i < ( (int)mapping.path.size()-1<threshold ? (int)mapping.path.size()-1:threshold );i++){
		if (!reachable(PositionX, PositionY, mapping.path[i].pos[0], mapping.path[i].pos[1])){
			i--;break;
		}
	}*/
	i = (int)mapping.path.size()<threshold ? (int)mapping.path.size()-1:threshold;
	selectedNode = i;
	
	coordinates node =  mapping.path[(int)mapping.path.size()-1];
	
	FindNode* go = new CheckReached(node.pos[0],node.pos[1]);
	mapping.getPath(PositionX,PositionY,go);

	coordinates output = mapping.path[i];
	//for (int j=0;j < (int)mapping.path.size()-1;j++){
	//	cout<<"("<<mapping.path[j].pos[0]<<","<<mapping.path[j].pos[1]<<")";//<<endl;
	//}
	
	cout<<"("<<node.pos[0]<<","<<node.pos[1]<<")";//<<endl;
	cout<<output.pos[0]<<","<<output.pos[1];
	cout<<" "<<i<<" "<<mapping.path.size()<<endl;
	return output;
}
void moveTo(){
	coordinates node = nodeSelect();
	//if (selectedNode==0)return;
	// if (selectedNode < 3){
		// WheelLeft=3;WheelRight=3;
		// return;
	// }
	if (node.pos[0] < 0 || node.pos[0] > width-1)return;
	if (node.pos[1] < 0 || node.pos[1] > width-1)return;
	rotateTo(node.pos[0], node.pos[1]);
}

///Move to coordinates////////////////////////////////////////////

void moveAStar(int x, int y){
	FindNode* go = new CheckReached(x,y);
	mapping.getPath(PositionX,PositionY,go);
	moveTo();
}

///Move to Zones Nodes////////////////////////////////////////////
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
	Timer nodeTime;
	int posX=PositionX1, posY=PositionY1;
	class FindZone:public FindNode{
		private: int val = 4;
		public:
			FindZone(int v){val = v;};
			 virtual bool operator() (int x, int y){return (location.getPixel(x,y) == val);};
	};
public:
void moveZone(int val){
	if (location.getPixel(PositionX,PositionY) != val){
		FindNode* go = new FindZone(val);
		mapping.path=mapping.getPath(PositionX,PositionY,go);
		moveTo();
		if (!onetime.toRun()){onetime.reset();nodeTime.reset();}
		cout<<"Go Zone "<<val<<endl;
	}//Random Points
	else{
		if (onetime.toRun()){
			//cout<<"val";
			//posX = 0; posY = 0;
			coordinates c = randomNode(PositionX1, PositionY1, val, 0.8);
			posX = c.pos[0];
			posY = c.pos[1];
			cout<<posX<<","<<posY<<endl;
		}
		cout<<"Random Point "<<val<<endl;
		rotateTo(posX, posY);
		if (reached(posX, posY, 5, 5) || nodeTime.timeout(5)){onetime.reset();nodeTime.reset();}
	}
}
void moveRed(){moveZone(location.red);}
void moveBlue(){moveZone(location.blue);}
void moveBlack(){moveZone(location.black);}
void moveDeposit(){moveZone(location.deposit);}
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
int zoneToCollect = 2;
int AppropriateZone(){
	//Reset
	if (cycleFull()){
		//zoneToCollect = 4;
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

int timeToCollect = 18;
int consecutive = 0;
int additionalTime = 10;
public:
void changeZone(){
	zoneToCollect = AppropriateZone();
	consecutive = 0;
	Timing.reset();
	cout<<zoneToCollect<<endl;
}

void collectObjects(bool red, bool blue, bool black){
	//if (red&&blue&&black){zoneToCollect = 4;}
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
		case 4:
			moveDeposit();
			if (!red || !blue || !black){zoneToCollect=-1;}
			break;
			
	}
	if (w2Obj.collectedRed || w2Obj.collectedBlue || w2Obj.collectedBlack){consecutive++;}
	if (Timing.timeout(timeToCollect+consecutive*additionalTime) || zoneToCollect == -1){
		changeZone();
	}
	//cout<<zoneToCollect;
}

};

Cycle cycle;

//Move to Super Object////////////////////////////////////////////
class FindFurthestPoint:public FindNode{
		private: int dist = 4;int xpos=0,ypos = 0;
		int pythagoreanDistance(int x1, int y1, int x2, int y2){
			return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
		}
		public:
			FindFurthestPoint(int x, int y, int d){dist = d;};
			 virtual bool operator() (int x, int y){return pythagoreanDistance(xpos,ypos,x,y)>dist && location.isWalkablePixel(x,y);};
	};

Timer SuperObjTimer;
int SuperObjX;//[20];
int SuperObjY;//[20];
int SuperTimeOut = 50;
OneTime nearingSuper;
coordinates superAwayPoint;
void getAwayPoint(){
	FindNode* go = new FindFurthestPoint(SuperObjX,SuperObjY, 20);
		mapping.getPath(colorSensorX,colorSensorY,go);
		superAwayPoint = nodeSelect();
		cout<<"["<<superAwayPoint.pos[0]<<","<<superAwayPoint.pos[1]<<"]";
}
bool superObjAStar(){
	if (w2Obj.isCollectedSuper()){
		cycle.changeZone();
	}
    if (SuperObj_Num>0 && w2Obj.noSuperObj != SuperObj_Num){
            w2Obj.noSuperObj = SuperObj_Num;
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
		cout<<"("<<SuperObjX<<","<<SuperObjY<<")";
		SuperObjTimer.reset();
        return true;
	}
	 else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,25,25) &&
	    (SuperObjTimer.timeout(SuperTimeOut-20)) && !(SuperObjTimer.timeout(SuperTimeOut-20+5))){\
		cout<<"AWAYGAME";
			if (nearingSuper.toRun()){
				getAwayPoint();
			}
		//coordinates node = nodeSelect();
		rotateToSuper(superAwayPoint.pos[0], superAwayPoint.pos[1]);
		
	}
	///TODO: Add timeout, moveback, and moveback in functionality
	else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,25,25) &&
			(!SuperObjTimer.timeout(SuperTimeOut))){
			//if (reachedSuperTime == 0)reachedSuperTime = Time;
		cout<<"SUPER+++!!!"<<endl;
		FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect();
		rotateToSuper(node.pos[0], node.pos[1]);
		//rotateToSuper(SuperObjX,SuperObjY);//node.pos[0], node.pos[1]);
        return true;
    }
	else if (w2Obj.noSuperObj>0 &&
			(!SuperObjTimer.timeout(SuperTimeOut))){
		//moveAStar(SuperObjX,SuperObjY);
		cout<<"SUPER!!!"<<endl;
        FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect();
		rotateToSuper(node.pos[0], node.pos[1]);
		nearingSuper.reset();
		return true;
	}
	else if (SuperObjTimer.timeout(SuperTimeOut)){
        w2Obj.noSuperObj = 0;
		SuperObjTimer.reset();
		nearingSuper.reset();
	}
	return false;
}

///Discover Locations////////////////////////////////////////////
class UndiscoveredNode:public FindNode{
	private: int val = 4;
	public:
		FindZone(){};
		virtual bool operator() (int x, int y){
			 return (!location.isVisited(x,y) && 
						(location.getPixel(x,y) != location.wall && location.getPixel(x,y) != location.border)
					);
		};
};

#include <fstream>
ofstream myfile;
int i=0;
void printLocation(){
	string data = "";
	if (!i<width){return;}
	//for (int i=0;i<width;i++){
		for (int j=0;i<height;j++){
			data += to_string(location.isVisited(i,j));
			data += ",";
		}
	//}
	i++;
	cout<<data;
	/*
	myfile.open("mapExample.txt");
	if (myfile.is_open())
	{
		myfile << data;
		myfile.close();
	}*/
}
int X=PositionX1, Y = PositionY1;
int mode = 1;
bool lock = false;
void discovery(){
	//if (Time >= 5){
	//	printLocation();
	//}
	//FindNode* go = new UndiscoveredNode();
	//mapping.getPath(PositionX1,PositionY1,go);
	//moveTo();
	
	//WheelLeft = 3;WheelRight = 3;
	//if (US_Front<20 || lock){moveAStar(PositionX1_40, PositionY1);}
	if (PositionX==0){mode = 1;lock = false;}
	if (!lock && PositionX !=0){
		cout<<"r";
		lock = true;
		switch (mode){
			case 1:
			case 3:
			X = PositionX1+40;
			Y = PositionY1;
			break;
			case 2:
			X = PositionX1;
			Y = PositionY1-40;
			break;
			case 4:
			X = PositionX1;
			Y = PositionY1+40;
			break;
			default:
			mode = 1;
			break;
		}
	}
	cout<<X<<','<<Y<<endl;
	moveAStar(X, Y);
	if (reached(X,Y,5,5)){mode++;lock = false;}
	
	if (!location.isVisited(PositionX1,PositionY1)){
		int colour = location.empty;
		if (colorCheck(w2Obj.objBlue,w2Obj.objRange)){
			colour = location.blue;
		}else if (colorCheck(w2Obj.objRed,w2Obj.objRange)){
			colour = location.red;
		}else if (colorCheck(w2Obj.objBlack,w2Obj.objRange)){
			colour = location.black;
		}
		else if (colorCheck(w2Obj.slowarea,w2Obj.objRange)){
			colour = location.slow;
		}else if (colorCheck(w2Obj.depositOrange,w2Obj.objRange)){
			colour = location.deposit;
		}else if (colorCheck(w2Obj.trapYellow,w2Obj.objRange)){
			colour = location.trap;
		}else if (colorCheck(w2Obj.trapBlue,w2Obj.objRange)){
			colour = location.trap;
		}
		location.squareFill(PositionX1,PositionY1,location.empty, 20);
	}
}