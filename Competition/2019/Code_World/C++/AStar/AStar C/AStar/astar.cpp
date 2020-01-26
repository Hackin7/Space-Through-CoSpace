#include <bits/stdc++.h>
using namespace std;
#include "./astar.hpp"

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
    x1 = 98; y1 = 130; x2 = 310; y2=190;
    //cin>>x1>>y1>>x2>>y2;
    /*
    mapper.Neighbours(98, 130);
    for (int i=0; i<8; i++){
        cout<<mapper.neighbours[i].pos[0]<<" "<<mapper.neighbours[i].pos[1]<<endl;
    }*/

    vector<coordinates> stuff = mapper.calculatePath({x1,y1}, {x2,y2});

    for (int i=0; i<(int)stuff.size(); i++){
        //cout<<mapper.path[i].pos[0]<<" "<<mapper.path[i].pos[1]<<endl;
        cout<<stuff[i].pos[0]<<" "<<stuff[i].pos[1]<<endl;
        //::map[stuff[i].pos[0]][stuff[i].pos[1]] = 4;
    }
    //outputMap(::map);
    cout<<stuff.size();
    //cout<<mapper.pathLength;

}
