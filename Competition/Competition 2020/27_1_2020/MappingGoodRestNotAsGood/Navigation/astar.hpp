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


const int v = width*height;//Max width & height

///Flattening out Nodes///////////////////////////////////////////////////////////
class coordinatesToNode{
	public:
	    Map *currlocation;
	    coordinatesToNode(Map *ll){currlocation=ll;}

        int con(int x,int y){return y * currlocation->Width + x;}
        int conX(int d){return d % currlocation->Width;}
        int conY(int d){return d / currlocation->Width;}
        int conv(int x, int y){
            x = max(0, min(359, x));
            y = max(0, min(269, y));
            x = min((int)round(x*(currlocation->Width/360.0)), currlocation->Width-1);
            y = min((int)round(y*(currlocation->Height/270.0)), currlocation->Height-1);
            return round(y * (currlocation->Height/270.0) * currlocation->Width + x * (currlocation->Width/360.0));
        }
        int convX(int d){return round((d % currlocation->Width) * (360.0/currlocation->Width));}
        int convY(int d){return round((d / currlocation->Width) * (270.0/currlocation->Height));}
        int convFinalX(int d){return convX(d);}
        int convFinalY(int d){return convY(d);}
        int getmap(int node){
        //return ::map[convX(node)][convY(node)];
            return currlocation->getPixel(convX(node),convY(node));
        }
        //Connected nodes
        int convPosToNode(int from, int to){
            switch(to)
            {
                case 1: return from-currlocation->Width-1;
                case 2: return from-currlocation->Width;
                case 3: return from-currlocation->Width+1;
                case 4: return from-1;
                case 5: return from+1;
                case 6: return from+currlocation->Width-1;
                case 7: return from+currlocation->Width;
                case 8: return from+currlocation->Width+1;
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
        int valCost(int val){return currlocation->valCost(val);}
};

//Reached Condition///////////////////
class FindNode{
public:
     FindNode() {};
     virtual bool operator() (int x, int y)=0;
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
        double D = valCost(currlocation->empty), D2 = sqrt2 * valCost(currlocation->empty);
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
                if(conX(curr)==currlocation->Width-1&&(i==3||i==5||i==8)) continue;
                if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
                if(conY(curr)==currlocation->Height-1&&(i==6||i==7||i==8)) continue;

                int next=convPosToNode(curr,i);


                if(conX(next)<0||conX(next)>=currlocation->Width||conY(next)<0||conY(next)>=currlocation->Height) continue;//discard if out of w2map

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
    AStar(Map *ll):coordinatesToNode(ll){}

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
