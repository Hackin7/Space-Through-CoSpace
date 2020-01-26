int SuperObjTime = 0;
int SuperObjStartTime = 0;
bool superObjDijkstra(){
    if (SuperObj_Num>0 && noSuperObj != SuperObj_Num){
        //if (noSuperObj<SuperObj_Num){
            //Collect 1 superobject at a time
            noSuperObj = SuperObj_Num;
        //}
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;

        int endNode = 0;
        if (SuperObj_Num>0){
            endNode = closestNode(SuperObjX,SuperObjY);
            startDijkstra(endNode);
        }
        SuperObjStartTime = Time;
        return true;
	}
	else if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5,5)
          && Time - SuperObjStartTime  < 40){
            printf("SuperObj \t");

        //Recalculate if sidetracked
        if (SuperObjTime != Time){
            int endNode = 0;
            if (SuperObj_Num>0){
                endNode = closestNode(SuperObjX,SuperObjY);
                startDijkstra(endNode);
            }
        }
        SuperObjTime=Time;

		moveDijkstra(SuperObjX,SuperObjY);
        return true;
	}
	else if (Time - SuperObjStartTime  >= 40){
        noSuperObj = 0;
	}
	return false;
}

bool quarrantine(int x1, int x2, int y1, int y2, int rangex, int rangey){
    if (xreached(x1,rangex) && 0<=Compass && Compass <180){
            if (Compass < 90){
                WheelLeft=5;WheelRight=0;//reverse();
            }
            else{
                WheelLeft=0;WheelRight=5;//reverse();
            }
			return true;
	}
	else if (xreached(x2,rangex) && 180<=Compass && Compass <=360){
            if (Compass < 270){
                WheelLeft=5;WheelRight=0;//reverse();
            }
            else{
                WheelLeft=0;WheelRight=5;//reverse();
            }
        //WheelLeft=-5;WheelRight=5;//reverse();
		return true;
	}
	if (yreached(y1,rangey) && 90<=Compass && Compass <=270){
        reverse();
		return true;
		}
	else if (yreached(y2,rangey) && (Compass>270 || Compass <90)){
        reverse();
		return true;
	}
    return false;
}

int objectCollectionArea = 0;
int prevTime = 0;
int prevLoaded = -60;
bool reachedObjRegion = false;
bool setupCollectionDijkstra(int *objectPoints, int noPoints, bool moveon){
    int collectTime = 20;
    if ((Time - prevTime > collectTime  || LoadedObjects-prevLoaded >=2)  || moveon){
        prevTime = Time;
        objectCollectionArea++;
        prevLoaded = LoadedObjects;
            if (objectCollectionArea >= noPoints){
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
bool moveCollectionDijkstra(int *objectPoints){

    int sizex = objectPointsSize[objectCollectionArea][0];//25;
    int sizey = objectPointsSize[objectCollectionArea][1];//25;

    if (reached(coordinates[objectPoints[objectCollectionArea]][0],
                coordinates[objectPoints[objectCollectionArea]][1],sizex,sizey)){
                    //printf("Quarrantined %d\t",objectPoints[objectCollectionArea]);
                     printf("Quarrantined %d\t",objectPoints[objectCollectionArea]);
                 WheelLeft=5;WheelRight=5;
                 quarrantine(coordinates[objectPoints[objectCollectionArea]][0]-sizex,coordinates[objectPoints[objectCollectionArea]][0]+sizex,coordinates[objectPoints[objectCollectionArea]][1]-sizey,coordinates[objectPoints[objectCollectionArea]][1]+sizey,sizex, sizey);
                 //WheelLeft=0;WheelRight=0;
                 //LED_1 = 2;
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

int depositNode = 13;
void depositDijkstra(){depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);}
bool boundary(){
    if ((xreached(10,5) && 0<=Compass && Compass <180)||
        (xreached(340,5) && 180<=Compass && Compass <=360)||
        (yreached(10,5) && 90<=Compass && Compass <=270)||
        (yreached(250,5) && (Compass>270 || Compass <90))){
			WheelLeft=-3;WheelRight=3;
			return true;
			}
    return false;//quarrantine(10,335,10,250,5,5);
}

