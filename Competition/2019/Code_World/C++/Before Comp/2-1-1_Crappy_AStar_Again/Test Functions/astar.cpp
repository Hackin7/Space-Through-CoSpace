#include <bits/stdc++.h>
using namespace std;
#include "../World2/AStar/astar.hpp"

void outputMap(int map[width][height]){
    cout<<"Map\n";
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            cout<<map[i][j];
        }
        cout<<endl;
    }
}

int main() {
    srand(12345);
    AStar mapper;
    //generateMap();
    //outputMap(::map);
    //vector<coordinates> stuff = mapper.calculatePath({2,3}, {9,8});
    //vector<coordinates> stuff = mapper.calculatePath({150,130}, {310,190});

    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    vector<coordinates> stuff = mapper.calculatePath({x1,y1}, {x2,y2});;

    for (int i=0; i<(int)stuff.size(); i++){
        cout<<stuff[i].pos[0]<<" "<<stuff[i].pos[1]<<endl;
        ::map[stuff[i].pos[0]][stuff[i].pos[1]] = 4;
    }
    //outputMap(::map);
    cout<<stuff.size();
}
