struct coordinates{
    int pos[2] = {-1,-1};
};
coordinates createCoordinates(int x,int y){
    coordinates out;
    out.pos[0]=x;out.pos[1]=y;
    return out;
}
void showCoordinates(coordinates a){
    cout<<"("<<a.pos[0]<<","<<a.pos[1]<<")";
}

//Reached Condition///////////////////
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
    //Connected nodes
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

	coordinates convCoordinates(int node){
	    coordinates c;
	    c.pos[0] = convX(node);
	    c.pos[1] = convY(node);
		return c;
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

  double getCcost(int from, int to, int relPos){
	double lineDist = (relPos==1||relPos==3||relPos==6||relPos==8) ? sqrt2 : 1;
	return lineDist * 0.5 * (valCost(getmap(from)) + valCost(getmap(to)));
}
  double getHcost(int from, int goal){
	//return 0.0;
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


                if(conX(next)<0||conX(next)>=width||conY(next)<0||conY(next)>=height) continue;//discard if out of w2map

                //discard if already closedList
                if(!closedList[next]){
                    double oldgscore = gscores[next];//update vertex
                    double newgscore = gscores[curr] + getCcost(curr, next, i);//computecost
                    if(newgscore < oldgscore){
                        parent[next] = curr;
                        gscores[next] = newgscore;
                    }
                    if(gscores[next] < oldgscore){//continue updatingvertex
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
