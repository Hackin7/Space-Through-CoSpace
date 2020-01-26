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
	}
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
	rotateTo(path[position].pos[0], path[position].pos[1]);
}