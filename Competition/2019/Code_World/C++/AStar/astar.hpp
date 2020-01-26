#include "./map.hpp"
void generateMap(){
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            ::map[i][j] = 0;
            if ((float)rand()/(float)RAND_MAX > 0.75){
                ::map[i][j] = 1;
            }
        }
    }
}

struct coordinates { int pos[2];};

class AStar{
    public:
    coordinates parent[width][height];
    double gscores[width][height];
    bool closedList[width][height];

struct node {
    vector<coordinates> path; //Path Taken
    int pos[2];
    double f=0,g=0; // Cost from Start, Cost to End
};
class nodeCostCompare{
public:
  bool operator() (const node& lhs, const node& rhs) const
  {
    return (lhs.g>rhs.g); //greater than comparison, smaller at top
  }
};

double manhattenDistance(int x1,int y1,int x2,int y2){
    //linear movement - no diagonals - just cardinal directions (NSEW)
    return abs(x1 - x2) + abs(y1 - y2);
}
double elucidianDistance(int x1,int y1,int x2,int y2){
    return sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
}
double costFunction(coordinates Point, coordinates Goal){
    return elucidianDistance(Point.pos[0], Point.pos[1], Goal.pos[0], Goal.pos[1]);
}

bool canWalkHere(int x,int y){
    return (::map[x][y] ==0); //Walkable Tile Value
}
vector<coordinates> Neighbours(int x,int y){
    int North = y-1,
    South = y+1,
    East = x+1,
    West = x-1;
    bool NorthConnected = false,
    SouthConnected = false,
    EastConnected = false,
    WestConnected = false;
    if (North>-1){if (canWalkHere(x,North)){NorthConnected = true;}}
    if (South<height){if (canWalkHere(x,South)){SouthConnected = true;}}
    if (East<width){if (canWalkHere(East,y)){EastConnected = true;}}
    if (West>-1){if (canWalkHere(West, y)){WestConnected =  true;}}

    vector<coordinates> neighbours;
    if (NorthConnected){
        neighbours.push_back({x,North});}
    if (SouthConnected){
        neighbours.push_back({x,South});}
    if (EastConnected){
        neighbours.push_back({East,y});}
    if (WestConnected){
        neighbours.push_back({West,y});}
    //For Diagonal movement
    if(NorthConnected){
		if(EastConnected && canWalkHere(East,North))
		neighbours.push_back({East,North});
		if(WestConnected && canWalkHere(West, North))
		neighbours.push_back({West, North});
	}
	if(SouthConnected){
		if(EastConnected && canWalkHere(East, South))
		neighbours.push_back({East, South});
		if(WestConnected && canWalkHere(West, South))
		neighbours.push_back({West, South});
	}
    return neighbours;
}

vector<coordinates> calculatePath(coordinates start, coordinates end){
    bool visited[width][height]; //Visited Nodes
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            visited[i][j] = false;

            parent[i][j] = {-1,-1};
            closedList[i][j] = false;
            gscores[i][j] = width*height;
        }
    }

    // create Nodes from Start and End x, y coordintes
    node pathStart;
    pathStart.pos[0] = start.pos[0];
    pathStart.pos[1] = start.pos[1];
    pathStart.g = costFunction(start, end);
    gscores[start.pos[0]][start.pos[1]] = 0;
    priority_queue<node, vector<node>, nodeCostCompare> openList;
    openList.push(pathStart);
    //vector<node> Closed; // Dead Ends

    vector <coordinates> result;

    //Iterate through openList until no nodes left
    while (!openList.empty()){
        node myNode = openList.top();openList.pop();

        //Is it destination node?
        if (myNode.pos[0] == end.pos[0] && myNode.pos[1] == end.pos[1]){
            myNode.path.push_back(end);
            result = myNode.path;
        }
        else{ //not destination
            vector <coordinates> myNeighbours = Neighbours(myNode.pos[0], myNode.pos[1]);
            for (int i=0;i<(int)myNeighbours.size();i++){
                node myPath;
                myPath.path = myNode.path;
                myPath.path.push_back({myNode.pos[0], myNode.pos[1]});

                myPath.pos[0] = myNeighbours[i].pos[0];
                myPath.pos[1] = myNeighbours[i].pos[1];

                if (!visited[myPath.pos[0]][myPath.pos[1]]){ 
                    myPath.g = myNode.g + costFunction(myNeighbours[i], {myNode.pos[0],myNode.pos[1]});
                    myPath.f = myPath.g + costFunction(myNeighbours[i], {end.pos[0],end.pos[1]});
                    
                    node curr = myNode;
                    node next = myPath;
                    double oldgscore = gscores[next.pos[0]][next.pos[1]];
                    //computecost
                    double newgscore = gscores[curr.pos[0]][curr.pos[1]] + costFunction({curr.pos[0],curr.pos[1]}, {next.pos[0],next.pos[1]} );                
                    if(newgscore < oldgscore)
                    {
                        gscores[next.pos[0]][next.pos[1]] = newgscore;
                        openList.push(myPath); 
                    }
                
                    //openList.push(myPath);//Next Nodes to visit
                    visited[myPath.pos[0]][myPath.pos[1]] = true;
                }
            }
        }
    }
    return result;

}

};

