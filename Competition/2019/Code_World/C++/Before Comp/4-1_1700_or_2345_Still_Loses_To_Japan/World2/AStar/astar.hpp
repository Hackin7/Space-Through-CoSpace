#include "./map.hpp"

struct coordinates{int pos[2] = {-1,-1};};

class Map{
	public:
	//Colour Values
	const int empty = 0;
	const int deposit = 1;
	const int red = 2;
	const int blue = 3;
	const int black = 4;
	const int wall = 5;
	const int border = 6;
	const int trap = 7;
	const int slow = 8;
	
	bool toAvoidTrap = true;
	int map[width][height];
	bool visited[width][height];
	const int v = width*height;
	
	Map(){
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++)
				map[i][j] = empty;
		}
	}
	Map(int mapData[width][height]){
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++)
				map[i][j] = mapData[i][j];
		}
	}
	////Getter////////////////////////////////////////////////////
	int getPixel(int i, int j){return map[i][j];}
	bool isVal(int i, int j, int val){return map[i][j] == val;}
	bool isWalkablePixel(int i, int j){
		return  map[i][j] == empty || 
				map[i][j] == deposit ||
				map[i][j] == red ||
				map[i][j] == blue ||
				map[i][j] == black;// ||
	}
	int valCost(int val){
		if (val == empty ||
			val == deposit ||
			val == red ||
			val == blue ||
			val == black){
				return 1;
			}
		if (val == wall ||
			val == slow){
				return v;
			}
		if (val == trap){
			if (toAvoidTrap){return v;}
			else{return 1;}
		}
		if (val == border){
			return v;
		}
		return v;
	}
	////Setter////////////////////////////////////////////////////
	void setPixel(int i, int j, int val){
		map[i][j] = val;
	}
	void rectfill(int x1,int x2,int y1,int y2, int color)
	{
		for (int x=x1; x <= x2; x++){
			for (int y=y1; y<= y2; y++){
			map[x][y]=color;
			}
		}
	}
	
	void squareFill(int x, int y, int val,int len)
	{
	  int x1=x - len;
	  int x2=x + len;
	  int y1=y - len;
	  int y2=y + len;
	  if (x1 < 0){x1=0;}
	  if (x2 > 480){x2=480;}
	  if (y1 < 0){y1=0;}
	  if (y2 > 270){y2=270;}
	  rectfill(x1,x2,y1,y2,val);
	}
	
};
Map location(::map);

class FindNode{
public:
     FindNode() {};
     virtual bool operator() (int x, int y)=0;
};
const int v = width*height;

class coordinatesToNode{
	public:
	int con(int x,int y){return y * width + x;}
  int conX(int d){return d % width;}
  int conY(int d){return d / width;}
  int conv(int x, int y){
		x = max(0, min(359, x));
		y = max(0, min(269, y));
		x = min((int)round(x*(width/360.0)), width-1);
		y = min((int)round(y*(height/270.0)), height-1);
		return round(y * (height/270.0) * width + x * (width/360.0));
	}
  int convX(int d){return round((d % width) * (360.0/width));}
  int convY(int d){return round((d / width) * (270.0/height));}
  int convFinalX(int d){return convX(d);}
  int convFinalY(int d){return convY(d);}
  int getmap(int node){
	//return ::map[convX(node)][convY(node)];
	return location.getPixel(convX(node),convY(node));
	}

	coordinates convCoordinates(int node){
		return {convX(node),convY(node)};
	}
	int valCost(int val){return location.valCost(val);}
};

class AStar:private coordinatesToNode{
private:

 deque<int> pathnum;
 int parent[v] ;
 double gscores[v] ;
 bool closedList[v];
const int INF = v;



#define sqrt2 1.414213562373095

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
  int convToRelPos(int from, int to){
	int x = conX(from) - conX(to);
	int y = conY(from) - conY(to);
	if(x==-1&&y==1)  return 1;
	if(x==0&&y==1)   return 2;
	if(x==1&&y==1)   return 3;
	if(x==-1&&y==0)  return 4;
	if(x==1&&y==0)   return 5;
	if(x==-1&&y==-1) return 6;
	if(x==0&&y==-1)  return 7;
	if(x==1&&y==-1)  return 8;
	assert(0);
	return 0;
}

	
  double getCcost(int from, int to, int relPos){
	double lineDist = (relPos==1||relPos==3||relPos==6||relPos==8) ? sqrt2 : 1;
	return lineDist * 0.5 * (valCost(getmap(from)) + valCost(getmap(to)));
}
  double getHcost(int from, int goal){
	// return 0.0;
	double D = valCost(location.empty), D2 = sqrt2 * valCost(location.empty);
	int dx = abs(conX(from) - conX(goal));
	int dy = abs(conY(from) - conY(goal));
    return D * (dx + dy) + (D2 - 2 * D) * min(dx, dy);
}
class nodeCostCompare{
public:
  bool operator() (const pair<double,int>& lhs, const pair<double,int>& rhs) const
  {
    return (lhs.first>rhs.first); //greater than comparison, smaller at top
  }
};



 double aStar(int start, FindNode* end){
	for(int i=0; i<v; i++)
	{
		parent[i] = -1;
		closedList[i] = false;
		gscores[i] = INF;
	}
	gscores[start] = 0;
	parent[start] = start;

	priority_queue< pair<double,int>, vector<pair<double,int> >, nodeCostCompare > openList;
	openList.push(make_pair(INF, start));//getHcost(start, goal), start));

	int curr=start;
	while (!openList.empty())
	{
		curr = openList.top().second;
		openList.pop();
		//if(curr == goal) break;
		if ( (*end)(convX(curr), convY(curr)) ) break;
		if(closedList[curr]) continue;

		closedList[curr] = true;

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
			if(!closedList[next])
			{
				//update vertex
				double oldgscore = gscores[next];
				//computecost
				double newgscore = gscores[curr] + getCcost(curr, next, i);
				if(newgscore < oldgscore)
				{
					parent[next] = curr;
					gscores[next] = newgscore;
				}

				//continue updatingvertex
				if(gscores[next] < oldgscore)
				{
					openList.push(make_pair(gscores[next] + getHcost(curr, next), next));
				}
			}
		}
	}

	pathnum.clear();
	pathnum.push_front(curr);
	int i = curr;
	while(i != start)
	{
		pathnum.push_front(parent[i]);
		i = parent[i];
	}
	return gscores[curr];
}

public:
vector<coordinates> path;


vector<coordinates> getPath(int x1, int y1, FindNode* end){
	path.clear();

	aStar(conv(x1,y1),end);
	for (int i=0; i<(int)pathnum.size();i++){
        coordinates curr;
		curr.pos[0] = convX(pathnum[i]);
		curr.pos[1] = convY(pathnum[i]);
		path.push_back(curr);
	}
	return path;
}

};