#include <bits/stdc++.h>
using namespace std;

//int PositionX1=98,PositionY1=130;
int Time = 0, Compass=0,PI=3.15926938,
WheelLeft=0,WheelRight=0,PositionX=98,PositionY=130;
void rotateTo(int x,int y);
void rotateToFAST(int x,int y);

// File: Game1/Trigo.c
double dabs (double x){
    if (x<0){return -x;}
    return x;
}
bool xreached(int x,int range){
	return (x-range<=PositionX && PositionX <= x+range);
}
bool yreached(int y,int range){
	return (y-range<=PositionY && PositionY <= y+range);
}
bool reached(int x,int y,int rangex, int rangey){
	return ((x-rangex<=PositionX && PositionX <= x+rangex) &&
	    (y-rangey<=PositionY && PositionY <= y+rangey));
}
void rotateTo(int x,int y){}
void rotateToFAST(int x,int y){}
#include "../../World2/location/map.hpp"
#include "../../World2/location/location.hpp"
#include "../../World2/AStar/astar.hpp"
#include "../../World2/AStar/moveAStar.hpp"
#include "../../World2/AStar/cycle.hpp"


int main(){
    z.zones();
    z.print();
    cout<<z.zoneNumber<<" ";
    cycle.collectObjects(0,0,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
    cout<<"ZoneNo: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<endl;;
    cycle.collectObjects(0,0,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
    cout<<"ZoneNo: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<endl;;
    cycle.collectObjects(0,1,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
    cout<<"ZoneNo: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<endl;;
    cycle.collectObjects(1,1,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;

    z.print();
    cout<<":";
    cycle.collectObjects(0,0,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
    cout<<"ZoneNo: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<endl;;
    cycle.collectObjects(0,0,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
    cout<<"ZoneNo: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<endl;;
    cycle.collectObjects(0,1,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
    cout<<"ZoneNo: "<<z.getZoneNo(mapping.path[mapping.path.size()-1])<<endl;;
    cycle.collectObjects(1,1,1);cout<<"Zone: "<<cycle.zoneToCollect<<endl;
}

///
