bool started = false;

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
	int j=1;for (;j<threshold && j<pathSize;j++){
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
