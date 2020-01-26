bool started = false;
AStar mapping;

int PositionX1=98, PositionY1=130;
int CurrTime = 0;

bool reachable(int x1, int y1, int x2, int y2){
	
	int dx = x1-x2;
	int dy = y1-y2;
	int signX = dx>0 ? 1:-1;
	int signY = dy>0 ? 1:-1;
	
	int i, j;
	for (int k=0; k<abs(dx); k++){
		i = x2 + signX*k;
		j = (int)y2 + signY*(dy/dx)*k;
		if (::map[i][j] != 0 || ::map[i][j] != 3){
			return false;
		}
	}
	return true;
}
const int threshold = 100;
void moveTo(){
	int i=2;
	for (;i < ( mapping.path.size()<threshold ? mapping.path.size():threshold );i++){
		if (!reachable(PositionX, PositionY, mapping.path[i].pos[0], mapping.path[i].pos[1])){
			i--;break;
		}
	}
	
	rotateTo(mapping.path[i].pos[0], mapping.path[i].pos[1]);
	cout<<i<<":"<<mapping.path[i].pos[0]<<","<<mapping.path[i].pos[1]<<"_";
	/*
    if (reached(mapping.path[position].pos[0],mapping.path[position].pos[1],5,5)){
		//position++;
		//cout<<position<<":"<<mapping.path[position].pos[0]<<","<< mapping.path[position].pos[1]<<":"<<::map[mapping.path[position].pos[0]][mapping.path[position].pos[1]];
        //nodeCounter--; prevNodeTime=Time;
        //printf("Newnode %d %d, (%d,%d)\n",nodeCounter, pathNodes[nodeCounter],
        //       coordinates[pathNodes[nodeCounter]][0],
        //       coordinates[pathNodes[nodeCounter]][1]);//startDijkstra(pathNodes[0]);
	}*/
	//trigo(path[position].pos[0], path[position].pos[1]);*/
}

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
class FindBlue:public FindNode{
public:
    FindBlue(){};
     virtual bool operator() (int x, int y){return (::map[x][y] == 3);};
};
bool reachedBlue = false;
coordinates endBlue = {-1,-1};
void moveBlue(){
	FindNode* go = new FindBlue();
	mapping.getPath(PositionX1,PositionY1,go);
	if (!reachedBlue){
		endBlue.pos[0] = mapping.path[mapping.path.size()-1].pos[0];
		endBlue.pos[1] = mapping.path[mapping.path.size()-1].pos[1];
	}
	moveTo();
	if (reached(endBlue.pos[0], endBlue.pos[1], 5,5)){
		WheelLeft = 0; WheelRight = 0;
	}

}