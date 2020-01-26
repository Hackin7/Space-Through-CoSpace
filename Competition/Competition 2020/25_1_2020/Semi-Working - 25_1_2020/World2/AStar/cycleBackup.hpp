#include <fstream>
ofstream outfile;

///Move to Zones Nodes////////////////////////////////////////////
class ZoneNodes:public coordinatesToNode{
    private:
    int convPosToNode(int from, int to){
        switch(to)
        {
            case 1: return from-width-1;
            case 2: return from-width;
            case 3: return from-width+1;
            case 4: return from-1;
            case 5: return from+1;
            case 6: return from+width-1;
            case 7: return from+width;
            case 8: return from+width+1;
        }
        assert(0);
        return 0;
    }
    bool closedList[v];int zoneNos[v];
	int colour[100000];bool visited[100000];//Zone
	int valCount[v];int runValCount[v];

public:
	int zoneNumber=0;
	zoneNodes(){fill(zoneNos,zoneNos+v,0);
        fill(valCount,valCount+v,0);fill(runValCount,runValCount+v,0);
        clearVisited();}
    void zones(){
        //Starting Out
        for(int i=0; i<v; i++){closedList[i] = false;}

        zoneNumber=0;
        for(int n=0;n<v;n++){ // Loop through all nodes
            if(closedList[n]) continue;
            int val=getmap(n);
            zoneNumber++;colour[zoneNumber]=val;
            valCount[val]++;

            ///DFS////////////////////////////////////////////////////
            deque<int> openList;
            openList.push_back(n);
            int curr;
            while (!openList.empty())
            {
                curr = openList.front();
                openList.pop_front();

                //Checking Conditions
                if (getmap(curr) != val ) break;
                if(closedList[curr]) continue;
                closedList[curr] = true;

                //Setting Values
                zoneNos[curr] = zoneNumber;
                //Neighbours
                for(int i=1; i<=8; i++)
                {
                    if(conX(curr)==0&&(i==1||i==4||i==6)) continue;
                    if(conX(curr)==width-1&&(i==3||i==5||i==8)) continue;
                    if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
                    if(conY(curr)==height-1&&(i==6||i==7||i==8)) continue;

                    int next=convPosToNode(curr,i);
                    //discard if out of w2map
                    if(conX(next)<0||conX(next)>=width||conY(next)<0||conY(next)>=height) continue;

                    //discard if already closedList
                    if(!closedList[next] && getmap(next) == val){
                        openList.push_back(next);
                    }

                }
            }
            /// //////////////////////////////////////////////////////
        }
    }

    void clearVisited(){fill(visited,visited+sizeof(visited),0);}
    int getZoneNo(coordinates a){return zoneNos[conv(a.pos[0],a.pos[1])];}
    int seenZone(int no){
        if (valCount[colour[no]] <= runValCount[colour[no]]){
                //Reset
                runValCount[colour[no]]=0;
                for (int i=1;i<zoneNumber+1;i++){
                    if(colour[i] == colour[no]){visited[no]=0;}
                }
        }
        return visited[no];
    }
    int seenZone(coordinates a){return seenZone(getZoneNo(a));}
    void setVisitedZone(int no){if (no>0 && !visited[no]){
        visited[no]=1;
        runValCount[colour[no]]++;
    }}
    void print(){
        //cout<<"Red, Blue & Black nodes"<<endl;
        /*
        cout<<"Visited:";
        for(int i=1;i<zoneNumber+1;i++){
            cout<<visited[i]<<",";
        }cout<<endl;*/
    }
};
ZoneNodes z;

///Move to zones////////////////////////////////////////////////
class Zoning{
private:
	OneTime onetime;
	Timer nodeTime;
	int posToX=PositionX1, posToY=PositionY1;

	public:
	class FindZone:public FindNode{
		private:
            int val = 4;

		public:
			FindZone(int v){
				val = v;
			};
			 virtual bool operator() (int x, int y){
			     coordinates n = createCoordinates(x,y);
				 return location.getPixel(x,y) == val && !z.seenZone(n);
			};
	};

    void moveZone(int val){
        if (location.getPixel(PositionX1,PositionY1) != val ){
            FindNode* go = new FindZone(val);
            mapping.path=mapping.getPath(PositionX1,PositionY1,go);
            moveTo(10);
            if (!onetime.toRun()){onetime.reset();nodeTime.reset();}
        }//Random Points
        else{
            //WheelLeft=0;WheelRight=0;
            WheelLeft=4;WheelRight=3;
        }
    }
    void moveRed(){moveZone(location.red);}
    void moveBlue(){moveZone(location.blue);}
    void moveBlack(){moveZone(location.black);}
    void moveDeposit(){moveZone(location.deposit);}

};
Zoning zoning;
////////////////////////
class Cycle:public Zoning{
private:
    Timer Timing;
    bool cycle[3] = {false, false, false};

    bool cycleFull(){
        for (int i=0; i<3; i++){
            if (!cycle[i])return false;
        }
        return true;
    }
    void cycleReset(){
        for (int i=0; i<3; i++){
            cycle[i] = false;
        }
    }
    int AppropriateZone(){
        //Reset
        if (cycleFull()){
            cycleReset();
        }

        moveRed();
        int redPath = (int)mapping.path.size();
        moveBlue();
        int bluePath = (int)mapping.path.size();
        moveBlack();
        int blackPath = (int)mapping.path.size();

        int zone = 2;//Black
        int minPath = blackPath;
        if ( (bluePath <= minPath && !cycle[1]) || cycle[2]){minPath = bluePath;zone = 1;}//Blue
        if ( (redPath <= minPath && !cycle[0]) ){minPath = redPath;zone = 0;}//Red
        return zone;
    }

    int timeToCollect = 20;//20;
    int consecutive = 0;
    int additionalTime = 10;

public:
    int zoneToCollect = -1;
    Cycle(){}
    void changeZone(){
        zoneToCollect = AppropriateZone();
        consecutive = 0;
        Timing.reset();
        cout<<zoneToCollect<<endl;
    }

    int prevZone = -1;
    void collectObjects(bool red, bool blue, bool black){
        cout<<red<<","<<blue<<","<<black<<endl;
        if (red&&blue&&black){zoneToCollect = 4;}
        else if (blue&&black){zoneToCollect=0;}
        else if (red&&black){zoneToCollect=1;}
        else if (red&&blue){zoneToCollect=2;}
        switch(zoneToCollect){
            case 0: //Red
                moveRed();outfile<<"Red";
                cycle[0] = true;
                if (red) zoneToCollect = -1;
                break;
            case 1: //Blue
                moveBlue();outfile<<"Blue";
                cycle[1] = true;
                if (blue) zoneToCollect = -1;
                break;
            case 2: //Black
                moveBlack();outfile<<"Black";
                cycle[2] = true;
                if (black) zoneToCollect = -1;
                break;
            case 4:
                moveDeposit();outfile<<"Deposit";
                if (!red || !blue || !black){zoneToCollect=-1;}
                break;

        }
        if (prevZone != zoneToCollect){
            z.setVisitedZone(z.getZoneNo(mapping.path[mapping.path.size()-1]));
            cout<<endl<<"Set Zone: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<" ";
        }
        outfile<<":"<<zoneToCollect<<endl;
        //if (w2Obj.isCollectedRed() || w2Obj.isCollectedBlue() || w2Obj.isCollectedBlack()){consecutive++;}
        if (Timing.timeout(timeToCollect+consecutive*additionalTime) || zoneToCollect == -1){
            changeZone();
        }
        prevZone=zoneToCollect;
        //cout<<zoneToCollect;
    }

};

Cycle cycle;

///Super Object Collection//////////////////////////////////////////////////////////////////////////////////////////////////////////
class FindFurthestPoint:public FindNode{
		private: int dist = 4;int xpos=0,ypos = 0;
		int pythagoreanDistance(int x1, int y1, int x2, int y2){
			return (x1-x2)*(x1-x2) +(y1-y2)*(y1-y2);
		}
		public:
			FindFurthestPoint(int x, int y, int d){dist = d;};
			 virtual bool operator() (int x, int y){return pythagoreanDistance(xpos,ypos,x,y)>dist && location.isWalkablePixel(x,y);};
	};

Timer SuperObjTimer;
Timer SuperCloseTimer;
int SuperObjX;//[20];
int SuperObjY;//[20];
int SuperTimeOut = 40;
int SuperCloseTimeOut = 3;
OneTime nearingSuper;
coordinates superAwayPoint;
void getAwayPoint(){
	FindNode* go = new FindFurthestPoint(SuperObjX,SuperObjY, 20);
		mapping.getPath(colorSensorX,colorSensorY,go);
		superAwayPoint = nodeSelect(10);
		cout<<"["<<superAwayPoint.pos[0]<<","<<superAwayPoint.pos[1]<<"]";
}
bool superObjAStar(){
	if (w2Obj.isCollectedSuper()){
		cycle.changeZone();
	}
    if (SuperObj_Num>0 && w2Obj.noSuperObj != SuperObj_Num){
            w2Obj.noSuperObj = SuperObj_Num;
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;
		cout<<"("<<SuperObjX<<","<<SuperObjY<<")";
		SuperObjTimer.reset();
		SuperCloseTimer.reset();
        return true;
	}
	 else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,25,25) &&
             SuperCloseTimer.timeout(SuperCloseTimeOut) && !SuperCloseTimer.timeout(SuperCloseTimeOut+5)
        ){
		cout<<"AWAYGAME";
			if (nearingSuper.toRun()){
				getAwayPoint();
			}
		rotateToSuper(superAwayPoint.pos[0], superAwayPoint.pos[1]);

	}
	///TODO: Add timeout, moveback, and moveback in functionality
	else if (w2Obj.noSuperObj>0 && reached(SuperObjX,SuperObjY,25,25) &&
			(!SuperObjTimer.timeout(SuperTimeOut))){
		cout<<"SUPER+++!!!"<<endl;
		FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect(10);
		rotateToSuper(node.pos[0], node.pos[1]);
        return true;
    }
	else if (w2Obj.noSuperObj>0 &&
			(!SuperObjTimer.timeout(SuperTimeOut))){
		cout<<"SUPER!!!"<<endl;
        FindNode* go = new CheckReached(SuperObjX,SuperObjY);
		mapping.getPath(colorSensorX,colorSensorY,go);
		coordinates node = nodeSelect(10);
		rotateToSuper(node.pos[0], node.pos[1]);
		SuperCloseTimer.reset();
		nearingSuper.reset();
		return true;
	}
	else if (SuperObjTimer.timeout(SuperTimeOut)){
        w2Obj.noSuperObj = 0;
		SuperObjTimer.reset();
		nearingSuper.reset();
	}
	return false;
}
