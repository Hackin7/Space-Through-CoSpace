// File: Game1Dijkstra/moveDijkstra.c

int pythagoreanDistance(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
}
int closestNode(int x,int y){
    int minDist = pythagoreanDistance(coordinates[0][0],coordinates[0][1],x,y);
    int startNode = 0;

    for (int i = 1; i<MAX;i++){
        int distance = pythagoreanDistance(coordinates[i][0],coordinates[i][1],x,y);
        //(coordinates[i][0]-x)*(coordinates[i][0]-x) + (coordinates[i][1]-y)*(coordinates[i][1]-y);
        if (distance < minDist){
            minDist = distance;
            startNode = i;
        }
    }
    return startNode;
}

int nodeCounter = 0;
int prevX,prevY;
void startDijkstra(int endNode){
    //Start Node
    setCostValues();
    int startNode = closestNode(PositionX,PositionY);

    dijkstra(cost,MAX,startNode,endNode);
    nodeCounter = pathLength;
    prevX=PositionX, prevY = PositionY;
    printf("\nStartNode: %d\t",startNode);
    printf("\nendNode: %d\t",endNode);
    printf("\nPathLength:%d\t",pathLength);
    printf("NodeCounter:%d\n",nodeCounter);
}

void startDijkstraStart(int startNode, int endNode){
    //Start Node
    setCostValues();

    dijkstra(cost,MAX,startNode,endNode);
    nodeCounter = pathLength;
    prevX=PositionX, prevY = PositionY;
    printf("\nStartNode: %d\t",startNode);
    printf("\nendNode: %d\t",endNode);
    printf("\nPathLength:%d\t",pathLength);
    printf("NodeCounter:%d\n",nodeCounter);
}
int prevNodeTime = 0;
void moveDijkstra(int x, int y){
    startDijkstra(pathNodes[0]);
    //Check for all nodes, so that able to relocate
    /*if  ((abs(prevX-PositionX)>100 || abs(prevY-PositionY)>100) && PositionX!=0 && PositionY!=0){
        startDijkstra(pathNodes[0]);
        prevX=PositionX, prevY = PositionY;
        return;

    }*/

        if (reached(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1],30,30)){
            nodeCounter--; prevNodeTime=Time;
            printf("Newnode %d %d, (%d,%d)\n",nodeCounter, pathNodes[nodeCounter],
                   coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);//startDijkstra(pathNodes[0]);

    if (nodeCounter<=-1){ //&& !reached(x-5,y-5,5,5)){
           // printf("Direct ");
        rotateTo(x, y);
        return;
        //startDijkstra(pathNodes[0]);
    }else{
        printf("Node:%d (%d,%d)\t",pathNodes[nodeCounter],coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);
        rotateTo(coordinates[pathNodes[nodeCounter]][0],
                    coordinates[pathNodes[nodeCounter]][1]);
    }

    if (Time - prevNodeTime > 20){
        if (nodeCounter == pathLength){
                startDijkstraStart(pathNodes[nodeCounter], pathNodes[0]);
        }
        else{
                startDijkstraStart(pathNodes[nodeCounter+1], pathNodes[0]);
        }
        prevNodeTime=Time;
    }
            //WheelLeft=0;WheelRight=0;
            //Duration=1;
    }


    prevX=PositionX, prevY = PositionY;

}