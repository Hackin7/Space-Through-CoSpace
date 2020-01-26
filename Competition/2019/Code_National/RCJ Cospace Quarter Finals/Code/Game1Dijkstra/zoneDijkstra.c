int zoneDijkstra(int *points, int no){
    int minDist = 2147483647;//INT MAX
    int endNode = points[0];
       for (int i=0;i<no;i++){
            int toGo = pythagoreanDistance(PositionX,PositionY,coordinates[points[i]][0],coordinates[points[i]][1]);
            //dijkstra(cost, coordinates, MAX, startNode,depositNodes[i]);
            if (toGo < minDist){
                minDist = toGo;
                endNode = points[i];
            }
            printf("%d %dNode dist:%d\n",i,points[i],toGo);
        }
        //endNode=13;
    startDijkstra(endNode);
        return endNode;
}

bool dijkstraStarted = false;
int prevDepositTime = 0;
int depositNode = 13;
void depositDijkstra(){
    if (LoadedObjects >= 4 || LoadedSuperObj > 0){
        if (!dijkstraStarted){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            dijkstraStarted=true;
        }
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);

        if (Time - prevDepositTime > 10){
            depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
            prevDepositTime = Time;
        }

        /*if (reached(coordinates[depositNode][0],coordinates[depositNode][1],20,20) && LoadedObjects > 0 ){
                        int depositOrange[3] = {235,147,20};
                int objRange=20;
                if (! colorRightCheck(depositOrange,objRange) || ! colorLeftCheck(depositOrange,objRange)){
                    return;
                }
                WheelLeft=0;WheelRight=0;

            LED_1 =2;
            Duration=60;
            LoadedObjects=1;
            LoadedPoints = 0;
            LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
            printf("Deposit ");
        }*/

    }
    else{
            dijkstraStarted = false;
        }
}

