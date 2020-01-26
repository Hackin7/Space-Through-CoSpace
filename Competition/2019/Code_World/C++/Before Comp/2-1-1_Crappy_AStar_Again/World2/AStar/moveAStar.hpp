vector<coordinates> path;
bool started = false;
AStar mapping;

int position = 0;
void startAStar(int x, int y){
	if (!started){
		//path = mapping.calculatePath({PositionX, PositionY},{x,y});
		//srand(12345);
		//generateMap();
		path = mapping.calculatePath({PositionX, PositionY},{x,y});
		//position = 0;
		//cout<<PositionX<<","<<PositionY<<"_"<<x<<","<<y<<"_"<<::map[x][y]<<"_"<<path.size();
		//cout<<path.size();
		
		started = true;
	}else{started = false;}
}
static int minSpeed=5,maxSpeed=5;
static int PositionX1=-1,PositionY1=-1,colorSensorX=-1,colorSensorY=-1;
static inline bool isOnSwamp() {return false;}
static int theta=-1,AngleDiff,CWAngleDiff,ACWAngleDiff;
static constexpr int FRONT_MOVE_BACK = 12;
void move(int left, int right){
	WheelLeft = left;WheelRight = right;
}
void reduceSpeeds(int& spd1, int& spd2)
{
	spd1 = spd1>=0 ? spd1/2+1 : spd1/2-1;
	spd2 = spd2>=0 ? spd2/2+1 : spd2/2-1;
}

static inline void turnToAngle(int targetAngle)
{
	//must have set minSpeed AND maxSpeed BEFORE CALLING THIS FUNC
	if(Compass>=targetAngle)
	{
		CWAngleDiff=Compass-targetAngle;
		ACWAngleDiff=360-(Compass-targetAngle);
	}
	else //Compass<targetAngle
	{
		ACWAngleDiff=targetAngle-Compass;
		CWAngleDiff=360-(targetAngle-Compass);
	}

	if(CWAngleDiff<=ACWAngleDiff) move(maxSpeed,minSpeed);//turn clockwise
	else if(ACWAngleDiff<CWAngleDiff) move(minSpeed,maxSpeed);//turn anti-clockwise
	else move(maxSpeed,maxSpeed);//move forward
}
static inline void calcTheta(int originX, int originY, int targetX, int targetY)
{
	const int deltaX = targetX - originX;
	const int deltaY = targetY - originY;
		 if (deltaX==0 && deltaY>0) theta = 0;
	else if (deltaX<0 && deltaY==0) theta = 90;
	else if (deltaX<0 && deltaY>0)  theta = 90 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX<0 && deltaY<0)  theta = 90 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX==0 && deltaY<0) theta = 180;
	else if (deltaX>0 && deltaY<0)  theta = 270 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX>0 && deltaY==0) theta = 270;
	else if (deltaX>0 && deltaY>0)  theta = 270 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
}

static inline void trigo(int targetX, int targetY)
{
	calcTheta(PositionX1, PositionY1, targetX, targetY);
	AngleDiff=abs(Compass-theta);
	if(AngleDiff>180) AngleDiff=360-AngleDiff;
	if(AngleDiff>=130&&AngleDiff<=180)
	{
		minSpeed=-4;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=80&&AngleDiff<130)
	{
		minSpeed=-3;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=30&&AngleDiff<80)
	{
		minSpeed=1;//1
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=15&&AngleDiff<30)
	{
		minSpeed=2;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=5&&AngleDiff<15)
	{
		minSpeed=4;
		maxSpeed=5;
	}
	else if(AngleDiff<5)
	{
		minSpeed=5;
		maxSpeed=5;
	}
	else //failsafe
	{
		minSpeed=-3;
		maxSpeed=-3;
	}
	if(US_Front<=FRONT_MOVE_BACK+10) reduceSpeeds(minSpeed,maxSpeed);
	turnToAngle(theta);
}
void moveAStar(){
    if (reached(path[position].pos[0],path[position].pos[1],5,5)){\
		position++;
		cout<<position<<":"<<path[position].pos[0]<<","<< path[position].pos[1]<<":"<<::map[path[position].pos[0]][path[position].pos[1]];
        //nodeCounter--; prevNodeTime=Time;
        //printf("Newnode %d %d, (%d,%d)\n",nodeCounter, pathNodes[nodeCounter],
        //       coordinates[pathNodes[nodeCounter]][0],
        //       coordinates[pathNodes[nodeCounter]][1]);//startDijkstra(pathNodes[0]);
	}
	
	if (position >= path.size()){
        //rotateTo(x, y);
		WheelLeft = 0; WheelRight = 0;
        return;
    }
	/*else{
        printf("Node:%d (%d,%d)\t",pathNodes[nodeCounter],coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);
        rotateTo(coordinates[pathNodes[nodeCounter]][0],
                    coordinates[pathNodes[nodeCounter]][1]);
    }*/
	//rotateTo(path[position].pos[0], path[position].pos[1]);
	trigo(path[position].pos[0], path[position].pos[1]);
}