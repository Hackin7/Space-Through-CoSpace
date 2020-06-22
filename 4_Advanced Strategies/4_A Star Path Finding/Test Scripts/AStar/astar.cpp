#include <bits/stdc++.h>
using namespace std;

int PositionX1=0,PositionY1=0,Time=0;
#include "../../World1/w1map.hpp"
#include "../../World2/w2map.hpp"
#include "../../CoordinateSystem/location.hpp"
#include "../../Navigation/astar.hpp"
#include "../../Navigation/zone.hpp"

void outputMap(int map[width][height]){
    cout<<"Map\n";
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            cout<<map[i][j];
        }
        cout<<"\n";
    }
}
//AStar mapper;
Map location(layout);
coordinatesToNode c(&location);
AStar mapper(&location);
ZoneNodes z(&location);

class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};

void boxOut(int box, int x, int y){
    for(int j=max(0,x-box);j<x;j++){
        for(int k=max(0,y-box);k<y;k++){
            cout<<j<<" "<<k<<"\n";//count++;
    }}
}
int main() {
    srand(12345);

    int x1, y1, x2, y2;
    x1 = 305; y1 = 83; x2 = 35; y2 = 131;//305,83,35,131
    cin>>x1>>y1>>x2>>y2;
    boxOut(10,x1,y1);boxOut(15,x2,y2);
    cout<<"0 0\n";
    /*
    for(int n=0;n<v;n++){
        cout<<c.conX(n)<<" "<<c.conY(n)<<"\n";
    }*/
    //z.zones();z.coutZones();cout<<"0 0\n";
    int count = 0;
    FindNode* reached = new CheckReached(x2,y2);
    vector<coordinates> stuff = mapper.getPath(x1, y1, reached);
    cout<<"1 1\n";
    for (int i=0; i<(int)stuff.size(); i++){
        boxOut(5,stuff[i].pos[0],stuff[i].pos[1]);
        cout<<stuff[i].pos[0]<<" "<<stuff[i].pos[1]<<"\n";
        count++;
    }
    cout<<count;//stuff.size();

}
