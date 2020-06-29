#include <bits/stdc++.h>
using namespace std;

#include "../../World1/w1map.hpp"
#include "../../World2/w2map.hpp"
#include "../../CoordinateSystem/location.hpp"
#include "../../Navigation/astar.hpp"
//const int v=width*height;

int Time = 0, PositionX1=0,PositionY1=0;

int random(int size){
	srand(Time);
	return (int) rand() % size;
}
///Finding Zone Nodes////////////////////////////////////////////
class ZoneNodes:public coordinatesToNode{
private:
    bool closedList[v];
    int zoneNos[v];vector<int> zoneCoor[10000];
	int colour[100000];bool visited[100000];//Zones the robot has visited
	int valCount[v];int runValCount[v];
public:
    ZoneNodes(Map *ll):coordinatesToNode(ll){}

	int zoneNumber=0;
    int currZoneNo=0; //Outside Reference
	zoneNodes(){fill(zoneNos,zoneNos+v,0);
        fill(valCount,valCount+v,0);fill(runValCount,runValCount+v,0);
        clearVisited();}

    int ans = 0;
    void dfs(int curr, int val){
        if (getmap(curr) != val) return;
        if (closedList[curr]){return;}
        closedList[curr] = true;
        //cout<<conX(curr)<<" "<<conY(curr)<<"\n";
        //Setting Values
        zoneNos[curr] = zoneNumber;
        zoneCoor[zoneNumber].push_back(curr);

        //Neighbours
        for(int i=1; i<=8; i++){
            if(conX(curr)==0&&(i==1||i==4||i==6)) return;
            if(conX(curr)==currlocation->Width-1&&(i==3||i==5||i==8)) return;
            if(conY(curr)==0&&(i==1||i==2||i==3)) return;
            if(conY(curr)==currlocation->Height-1&&(i==6||i==7||i==8)) return;

            int next=convPosToNode(curr,i);
            if(!closedList[next] && getmap(next) == val){
                dfs(next,val);
            }
        }
    }

    void zonesdfs(){
        //Starting Out
        for(int i=0; i<v; i++){closedList[i] = false;}
        zoneNumber=0;

        for(int n=0;n<v;n++){ // Loop through all nodes
            if(closedList[n]) continue;
            int val=getmap(n);

            if (!(val==currlocation->red || val==currlocation->blue || val== currlocation->black)){continue;}
            zoneNumber++;colour[zoneNumber]=val;
            valCount[val]++;
            dfs(n,val);
        }
    }

    void zones(){
        //Starting Out
        for(int i=0; i<v; i++){closedList[i] = false;}
        zoneNumber=0;

        for(int n=0;n<v;n++){ // Loop through all nodes
            if(closedList[n]) continue;
            int val=getmap(n);

            if (!(val==currlocation->red || val==currlocation->blue || val== currlocation->black)){continue;}
            zoneNumber++;colour[zoneNumber]=val;
            valCount[val]++;

            ///BFS////////////////////////////////////////////////////
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
                zoneCoor[zoneNumber].push_back(curr);
                //Neighbours
                for(int i=1; i<=8; i++)
                {
                    if(conX(curr)==0&&(i==1||i==4||i==6)) continue;
                    if(conX(curr)==currlocation->Width-1&&(i==3||i==5||i==8)) continue;
                    if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
                    if(conY(curr)==currlocation->Height-1&&(i==6||i==7||i==8)) continue;

                    int next=convPosToNode(curr,i);
                    //discard if out of w2map
                    //if(conX(next)<0||conX(next)>=currlocation->Width||conY(next)<0||conY(next)>=currlocation->Height) continue;

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
    int getZoneNo(int x,int y){return zoneNos[conv(x,y)];}
    int getZoneNo(coordinates a){return zoneNos[conv(a.pos[0],a.pos[1])];}
    int seenZone(int no){
        if (runValCount[colour[no]] >= valCount[colour[no]]){
                //Reset
                cout<<"RESET Colour Zone";
                /*
                runValCount[colour[no]]=0;
                for (int i=1;i<zoneNumber+1;i++){
                    if(colour[i] == colour[no]){visited[no]=0;}
                }*/
                memset(visited,0,sizeof(visited));
        }
        return visited[no];
    }
    int seenZone(coordinates a){return seenZone(getZoneNo(a));}
    void setVisitedZone(int no){if (no>0 && !visited[no]){
        visited[no]=1;
        runValCount[colour[no]]++;
    }}

    void setVisitedZone(coordinates a){setVisitedZone(getZoneNo(a));}

    void coutZones(){
         for (int i=currlocation->Width-1;i>=0;i--){
            for (int j=0;j<currlocation->Height;j++){
                if (zoneNos[conv(i,j)]){
                    cout<<i<<" "<<j<<"\n";
                }
            }
         }
    }
    coordinates randomNode(int no){
        //cout<<endl<<"No:"<<no<<" Size:"<<zoneCoor[no].size()<<" "<<endl;
        if (zoneCoor[no].size()<=0){cout<<"ERROR,NO NODES!!!!!!!!!!!!!!";return createCoordinates(PositionX1,PositionY1);}
        int node = zoneCoor[no][random(zoneCoor[no].size())];
        return createCoordinates(convX(node),convY(node));
    }
    ofstream zoneFile;
    void fileOut(){
        if (!zoneFile.is_open()){
            zoneFile.open("zone.txt"); //Check the Robotics Dev Studio Folder
        //}else{
            ///Map
            for (int i=currlocation->Width-1;i>=0;i--){
                for (int j=0;j<currlocation->Height;j++){
                    //Coordinates
                    //if (zoneNos[conv(i,j)]){
                        zoneFile<<i<<" "<<j<<" "<<zoneNos[conv(i,j)]<<"\n";
                    //}
                    //if(j!=0)zoneFile<<" ";
                    //zoneFile<<visited[conv(i,j)];
                    //zoneFile<<visited[zoneNos[conv(i,j)]];
                }zoneFile<<endl;
            }
            //outfile<<data;
            zoneFile.close();
            //zoneFile.flush();
            //zoneFile.seekp(0, ios::beg);
        }
    }
};

Map location(layout);
ZoneNodes zn(&location);
int main(){
    zn.zones();
    zn.fileOut();
    cout<<zn.zoneNumber<<endl;
    //zn.fileOut();
}
