
int objectCollectionArea = -1;
int prevCollectionTime = 0;
int prevLoaded = -60;
bool reachedObjRegion = false;
bool setupCollectionDijkstra(int *objectPoints, int noPoints, bool moveon){
    int collectTime = 15;
    if (Time - prevCollectionTime > collectTime || moveon){//} || LoadedObjects-prevLoaded >=2){
        prevCollectionTime = Time;
        objectCollectionArea++;
        prevLoaded = LoadedObjects;
            if (objectCollectionArea >= noPoints ||objectCollectionArea<0){
                objectCollectionArea = 0;
            }

        printf("Change Collection Area to %d\n",objectPoints[objectCollectionArea]);
        startDijkstra(objectPoints[objectCollectionArea]);
    }
    if (LoadedObjects < prevLoaded){ //Deposited
        prevLoaded = LoadedObjects;
        startDijkstra(objectPoints[objectCollectionArea]);
        printf("Refresh\n");
    }
}

double randomness[10][2] = {{0.6169011912620882, 0.41359524497141387}, {0.08755616375412689, 0.7009712280389377}, {0.7872038990460901, 0.4833193040772631}, {0.7350020616781006, 0.6070434995859642}, {0.14521003377638675, 0.07102237538339928}, {0.6808936060819739, 0.43353382884636915}, {0.5393546784424003, 0.4166507272523542}, {0.6348521888982387, 0.2724089257609801}, {0.740697955711559, 0.5928818961567596}, {0.9443143236809757, 0.1805145219031291}};
int random = 0;
bool moveCollectionDijkstra(int *objectPoints){

    int sizex = objectPointsSize[objectCollectionArea][0];//25;
    int sizey = objectPointsSize[objectCollectionArea][1];//25;

    if (reached(coordinates[objectPoints[objectCollectionArea]][0],
                coordinates[objectPoints[objectCollectionArea]][1],sizex,sizey)){
/*
                int cx = (int)(randomness[random][0]*sizex) + coordinates[objectPoints[objectCollectionArea]][0];
                int cy = (int)(randomness[random][1]*sizey) + coordinates[objectPoints[objectCollectionArea]][1];
                if (reached(cx,cy,8,8)){
                    random++;
                    if (random >= 10){random = 0;}
                }
                rotateTo(cx,cy);
                printf("Randomness (%d,%d)\t",cx,cy);

*/
                //Quarrantined
                printf("Quarrantined %d\t",objectPoints[objectCollectionArea]);
                WheelLeft=3;WheelRight=3;
                quarrantine(coordinates[objectPoints[objectCollectionArea]][0]-sizex,coordinates[objectPoints[objectCollectionArea]][0]+sizex,coordinates[objectPoints[objectCollectionArea]][1]-sizey,coordinates[objectPoints[objectCollectionArea]][1]+sizey,sizex, sizey);


            return true;
    }else{
        //printf("Travel to obj region %d\t",objectPoints[objectCollectionArea]);
        moveDijkstra(coordinates[objectPoints[objectCollectionArea]][0],
                     coordinates[objectPoints[objectCollectionArea]][1]);
        //rotateTo(angle(coordinates[objectPoints[objectCollectionArea]][0],
        //             coordinates[objectPoints[objectCollectionArea]][1]));
        //reachedObjRegion = false;
        //LED_1=0;
        return true;
    }
    return false;
}
bool collectionDijkstra(bool moveon){
    //int allPoints[MAX] = {0,1,2,3,4,5,6};
    //setupCollectionDijkstra(allPoints, MAX, moveon);
    setupCollectionDijkstra(objectPoints, OBJPOINTS, moveon);
    moveCollectionDijkstra(objectPoints);
}
