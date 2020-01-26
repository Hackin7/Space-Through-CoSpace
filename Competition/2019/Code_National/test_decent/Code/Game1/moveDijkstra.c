
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
int prevNodeTime = 0;

void moveDijkstra(int x, int y){
    //DEBUG/////////////////////////////////////////////////////////////
    /*printf("\nDijkstra On\n");
    printf("%d\n",nodeCounter);
    printf("At %d,%d: To(%d,%d)\n",
           nodeCounter,
           pathNodes[nodeCounter],
           coordinates[pathNodes[nodeCounter]][0],
           coordinates[pathNodes[nodeCounter]][1]);
    */
    ///////////////////////////////////////////////////////////////////////
    //Check for all nodes, so that able to relocate
if  ((abs(prevX-PositionX)>100 || abs(prevY-PositionY)>100) && PositionX!=0 && PositionY!=0){/*
        for (int i = 0; i< pathLength; i++){
        if (reached(coordinates[pathNodes[i]][0],
                coordinates[pathNodes[i]][1],15,15)){
            nodeCounter = i;
            printf("Newnode %d %d\n",nodeCounter, pathNodes[nodeCounter]);
        }
    }*/
    startDijkstra(pathNodes[0]);
    prevX=PositionX, prevY = PositionY;
    return;

}

    if (nodeCounter<=-1){ //&& !reached(x-5,y-5,5,5)){
            printf("Direct ");
        rotateTo(angle(x, y));
        return;
        //startDijkstra(pathNodes[0]);
    }else{
        printf("Node:%d (%d,%d)\t",pathNodes[nodeCounter],coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);
        rotateTo(angle(coordinates[pathNodes[nodeCounter]][0],
                    coordinates[pathNodes[nodeCounter]][1]));
    }

    if (reached(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1],15,15) || Time - prevNodeTime > 20){
            nodeCounter--; prevNodeTime=Time;
            printf("Newnode %d %d, (%d,%d)\n",nodeCounter, pathNodes[nodeCounter],
                   coordinates[pathNodes[nodeCounter]][0],
                   coordinates[pathNodes[nodeCounter]][1]);//startDijkstra(pathNodes[0]);
    }


    prevX=PositionX, prevY = PositionY;

}
