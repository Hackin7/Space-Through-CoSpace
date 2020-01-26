int pythagoreanDistance(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
}
int closestNode(int x,int y){
    int minDist = 10000000;int startNode = -1;
    int distances[MAX];
    for (int i = 0; i<MAX;i++){
        distances[i] = pythagoreanDistance(coordinates[i][0],coordinates[i][1],x,y);
        //(coordinates[i][0]-x)*(coordinates[i][0]-x) + (coordinates[i][1]-y)*(coordinates[i][1]-y);
        if (distances[i] < minDist){
            minDist = distances[i];
            startNode = i;
        }
    }
    return startNode;
}

int nodeCounter = 0;
void startDijkstra(int endNode){
    //Start Node
    setCostValues();
    int startNode = closestNode(PositionX,PositionY);

    dijkstra(cost,MAX,startNode,endNode);
    nodeCounter = pathLength;
    printf("\nStartNode: %d\t",startNode);
    printf("\nendNode: %d\t",endNode);
    printf("\nPathLength:%d\t",pathLength);
    printf("NodeCounter:%d\n",nodeCounter);
}
void moveDijkstra(int x, int y){


    if (nodeCounter==-1){ //&& !reached(x-5,y-5,5,5)){
        rotateTo(angle(x, y));
        return;
    }

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
    rotateTo(angle(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1]));
    //Check for all nodes, so that able to relocate
    for (int i = 0; i< pathLength; i++){
        if (reached(coordinates[pathNodes[i]][0],
                coordinates[pathNodes[i]][1],15,15)){
            nodeCounter = i-1;
        }
    }

    if (reached(coordinates[pathNodes[nodeCounter]][0],
                coordinates[pathNodes[nodeCounter]][1],15,15)){
            nodeCounter--;
    }

}
