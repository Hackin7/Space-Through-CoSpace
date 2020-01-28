#include <bits/stdc++.h>
using namespace std;
#include "../../World2/location/map.hpp"
#include "../../World2/location/location.hpp"
#include "../../World2/AStar/astar.hpp"

void outputMap(int map[width][height]){
    cout<<"Map\n";
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            cout<<map[i][j];
        }
        cout<<endl;
    }
}
    AStar mapper;
class CheckReached:public FindNode{
    private: int x1, y1;
public:
     CheckReached(int x, int y) {x1 = x; y1 = y;};
     virtual bool operator() (int x, int y){return (x == x1 && y == y1);};
};
class FindZones:public FindNode{
private:
	vector<int> zoneVal;
public:
    FindZones(vector<int> val){zoneVal = val;};
    virtual bool operator() (int x, int y){
		for (int i=0; i<(int)zoneVal.size(); i++){
			if (::map[x][y] == zoneVal[i]){return true;}//If True
		}
		return false;
	};
};
vector<int> colours;// Red, Blue, Black
int main() {
    colours.push_back(2);
    colours.push_back(3);
    colours.push_back(4);
    srand(12345);
    //generateMap();
    //outputMap(::map);
    //vector<coordinates> stuff = mapper.calculatePath({2,3}, {9,8});
    //vector<coordinates> stuff = mapper.calculatePath({150,130}, {310,190});

    int x1, y1, x2, y2;
    x1 = 98; y1 = 130; x2 = 300; y2 = 190;
    cin>>x1>>y1>>x2>>y2;
    //mapper.aStar({x1,y1}, {x2,y2});

    //vector<coordinates> stuff = mapper.calculatePath({x1,y1}, {x2,y2});
    FindNode* reached = new CheckReached(x2,y2);
    //FindNode* reached = new FindZones(colours);
    vector<coordinates> stuff = mapper.getPath(x1, y1, reached);

    for (int i=0; i<(int)stuff.size(); i++){
        cout<<stuff[i].pos[0]<<" "<<stuff[i].pos[1]<<endl;
        ::map[stuff[i].pos[0]][stuff[i].pos[1]] = 4;
    }/*
    for (int i=0;i<mapper.path.size();i++){
        cout<<mapper.path[i]<<"_";
    }*/
    //outputMap(::map);
    cout<<stuff.size();
}
