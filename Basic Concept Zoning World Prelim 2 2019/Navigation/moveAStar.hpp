///Movement Items////////////////////////////////////////////
bool reachable(Map *currlocation, int x1, int y1, int x2, int y2){
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
		if (!currlocation->isWalkablePixel(i,j) || !currlocation->isWalkablePixel(i,j1) || !currlocation->isWalkablePixel(i,j2)){
			return false;
		}
	}
	return true;
}
coordinates nodeSelect(Map *currlocation,vector<coordinates> path, int threshold){
	//Choose node in direct sight
	int pathSize = path.size();
	int j=1;for (;j<threshold+5 && j<pathSize;j++){
        if (!reachable(currlocation,PositionX1,PositionY1,path[j].pos[0],path[j].pos[1])){
            j--;break;
        }
	}
	if (j==pathSize){j--;}
	coordinates output = path[j];
	return output;
}
void moveTo(Map *currlocation,vector<coordinates> path,int th){
	coordinates node = nodeSelect(currlocation,path,th);
	if (node.pos[0] < 0 || node.pos[0] > width-1)return;
	if (node.pos[1] < 0 || node.pos[1] > width-1)return;
	rotateTo(node.pos[0], node.pos[1]);
}

///Move to coordinates////////////////////////////////////////////
class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};
void moveAStar(AStar *mapping, Map *location, int x, int y){
    if(reached(x,y,10,10)){WheelLeft=0;WheelRight=0;return;}
	FindNode* go = new CheckReached(x,y);
	mapping->getPath(PositionX,PositionY,go);
	moveTo(location,mapping->path,1);
}
