Map location(layout);
//Map location;
AStar mapping(&location);
ZoneNodes z(&location);
Cycle cycle(&location,&z,&mapping);
///Move to coordinates////////////////////////////////////////////
class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};
void moveAStar(int x, int y){
    if(reached(x,y,10,10)){WheelLeft=0;WheelRight=0;return;}
	FindNode* go = new CheckReached(x,y);
	mapping.getPath(PositionX,PositionY,go);
	moveTo(&location,mapping.path,10);
}

///Super Object Collection//////////////////////////////////////////////////////////////////////////////////////////////////////////
class FindFurthestPoint:public FindNode{
		private: int dist = 15;int xpos=0,ypos = 0;
		int pythagoreanDistance(int x1, int y1, int x2, int y2){
			return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
		}
		public:
			FindFurthestPoint(int x, int y, int d){dist = d;};
			 virtual bool operator() (int x, int y){return pythagoreanDistance(xpos,ypos,x,y)>dist && location.isWalkablePixel(x,y);};
	};

Timer SuperObjTimer;
Timer SuperCloseTimer;
int SuperObjX;//[20];
int SuperObjY;//[20];
int SuperTimeOut = 40;
int SuperCloseTimeOut = 2;
OneTime nearingSuper;
coordinates superAwayPoint;
void getAwayPoint(){
	FindNode* go = new FindFurthestPoint(SuperObjX,SuperObjY, 20);
		mapping.getPath(colorSensorX,colorSensorY,go);
		superAwayPoint = nodeSelect(&location,mapping.path,10);
		cout<<"["<<superAwayPoint.pos[0]<<","<<superAwayPoint.pos[1]<<"]";
}
bool superObjAStar(){
    if (SuperCloseTimer.timeout(SuperCloseTimeOut+5)){SuperCloseTimer.reset();cout<<"SuperCloseReset";}
	if (w2Obj.isCollectedSuper()){
		cycle.changeZone();
	}
    if (SuperObj_Num>0 && w2Obj.noSuperObj != SuperObj_Num){
            w2Obj.noSuperObj = SuperObj_Num;
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
		cout<<"("<<SuperObjX<<","<<SuperObjY<<")";
		SuperObjTimer.reset();
		SuperCloseTimer.reset();
        return true;
	}
	 else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,30,30) &&
             SuperCloseTimer.timeout(SuperCloseTimeOut) && !SuperCloseTimer.timeout(SuperCloseTimeOut+5)
        ){
		cout<<"AWAYGAME";
        if (nearingSuper.toRun()){
			getAwayPoint();
		}
		rotateToSuper(superAwayPoint.pos[0], superAwayPoint.pos[1]);
        return true;
	}
	///TODO: Add timeout, moveback, and moveback in functionality
	else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,30,30) &&
			(!SuperObjTimer.timeout(SuperTimeOut))){
		cout<<"SUPER+++!!!"<<endl;
		FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect(&location,mapping.path,10);
		rotateToSuper(node.pos[0], node.pos[1]);
		nearingSuper.reset();
        return true;
    }
	else if (w2Obj.noSuperObj>0 &&
			(!SuperObjTimer.timeout(SuperTimeOut))){
		cout<<"SUPER!!!"<<endl;
        FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect(&location,mapping.path,10);
		rotateToSuper(node.pos[0], node.pos[1]);
		SuperCloseTimer.reset();
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
