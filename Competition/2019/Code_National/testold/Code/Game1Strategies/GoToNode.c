

void superObjDijkstra(){
    int endNode = 0;
    if (SuperObj_Num>0){
        endNode = closestNode(SuperObjX,SuperObjY);
        startDijkstra(endNode);
    }
}


bool quarrantine(int x1, int x2, int y1, int y2, int rangex, int rangey){
    if (xreached(x1,rangex) && 0<=Compass && Compass <180){
        WheelLeft=-5;WheelRight=5;//reverse();
			return true;
	}
	else if (xreached(x2,rangex) && 180<=Compass && Compass <=360){
        WheelLeft=-5;WheelRight=5;//reverse();
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
#define OBJPOINTS 6
int objectPoints[OBJPOINTS] = {9,32,33,43,18,29};
#define REDPOINTS 2
int redNodes[REDPOINTS] = {9,18};
#define BLUEPOINTS 3
int blueNodes[BLUEPOINTS] = {32, 43, 29};
#define BLACKPOINTS 1
int blackNodes[BLACKPOINTS] = {33};


int objectCollectionArea = 0;
int prevTime = 0;
int prevLoaded = -60;
bool reachedObjRegion = false;
bool collectionDijkstra(int collectTime, bool dontmoveon, bool moveon, int sizex, int sizey){
    //if (dontmoveon){}
    //else
    if ((Time - prevTime > collectTime  || LoadedObjects-prevLoaded >=2)  || moveon){
        prevTime = Time;
        objectCollectionArea++;
        prevLoaded = LoadedObjects;
            if (objectCollectionArea > OBJPOINTS){
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

    if (reached(coordinates[objectPoints[objectCollectionArea]][0],
                coordinates[objectPoints[objectCollectionArea]][1],sizex*0.5,sizey*0.5)){
        reachedObjRegion = true;
    }
    if (reached(coordinates[objectPoints[objectCollectionArea]][0],
                coordinates[objectPoints[objectCollectionArea]][1],sizex,sizey)
        && reachedObjRegion){
                    printf("Quarrantined\t");
                 WheelLeft=4;WheelRight=4;
            /*quarrantine(coordinates[objectPoints[objectCollectionArea]][0]-sizex,
                coordinates[objectPoints[objectCollectionArea]][0]+sizex,
                coordinates[objectPoints[objectCollectionArea]][1]-sizey,
                coordinates[objectPoints[objectCollectionArea]][1]+sizey,
                     sizex, sizey);*/
            return true;
    }else{
        printf("Travel to obj region %d\t",objectPoints[objectCollectionArea]);
        moveDijkstra(coordinates[objectPoints[objectCollectionArea]][0],
                     coordinates[objectPoints[objectCollectionArea]][1]);
        reachedObjRegion = false;
        return true;
    }



    return false;
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
void depositDijkstra(){
    depositNode = zoneDijkstra(depositNodes,DEPOSITNODES);
}
bool boundary(){
    return quarrantine(10,335,10,250,5,5);
}

bool dijkstraStarted = false;
void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}

	posInfoLost();

	//Super Object
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = LoadedObjects>=3 || LoadedSuperObj > 0;//true;
	bool avoid = LoadedObjects>=2;//true;

	if (LoadedRed>=4 ||
	(LoadedObjects >=5 &&  LoadedRed > 0 &&(LoadedBlue==0 || LoadedBlack==0)))
	{collectRed = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectRed = true;}

	if (LoadedBlack>=4 ||
	(LoadedObjects >=5 && LoadedBlack > 0 &&(LoadedBlue==0 || LoadedRed==0)))
	{collectBlack = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectBlack = true;}

	if (LoadedBlue>=4 ||
	(LoadedObjects >=5 && LoadedBlue > 0 &&(LoadedRed==0 || LoadedBlack==0)))
	{collectBlue = false;}//collectionDijkstra(20, false,true, 50, 40);}
	else{collectBlue = true;}



	if (LoadedObjects==0){
        dijkstraStarted=false;
	}
	//Boundary
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	//else if (posInfoLost()){return;}
	else if (boundary()){}
	else if (SuperObj_Num>0){
        if (noSuperObj<SuperObj_Num){
            noSuperObj = SuperObj_Num;
        }
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
        superObjDijkstra();
	}
	else if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5,5)){
            printf("SuperObj \t");
        superObjDijkstra();
		moveDijkstra(SuperObjX,SuperObjY);
		//rotateTo(angle(SuperObjX,SuperObjY));
		//printf("SuperObjs %d \n",SuperObjs);
	}
    else if (LoadedObjects >= 4 || LoadedSuperObj > 0){
        if (!dijkstraStarted){depositDijkstra();dijkstraStarted=true;}
        printf("depositNode:%d\t",depositNode);
        moveDijkstra(coordinates[depositNode][0],coordinates[depositNode][1]);
    }
    else if (collectionDijkstra(40,false, false, 50, 40)){}
	else { // Default Movement
		WheelLeft=3;WheelRight=3;
	}
	printf("End\n");
}
