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
            return con(x,y);
            //x = max(0, min(currlocation->Width-1, x));
            //y = max(0, min(currlocation->Height-1, y));
            //x = min((int)round(x*(currlocation->Width/currlocation->Width)), currlocation->Width-1);
            //y = min((int)round(y*(currlocation->Height/currlocation->Height)), currlocation->Height-1);
            //return round(y * (currlocation->Height/currlocation->Height) * currlocation->Width + x * (currlocation->Width/currlocation->Width));
        }
        int convX(int d){return conX(d);}//return round((d % currlocation->Width) * (currlocation->Width/currlocation->Width));}
        int convY(int d){return conY(d);}//return round((d / currlocation->Height) * (currlocation->Height/currlocation->Height));}
        int convFinalX(int d){return convX(d);}
        int convFinalY(int d){return convY(d);}
        int getmap(int node){
            //return ::map[convX(node)][convY(node)];
            return currlocation->getPixel(convX(node),convY(node));
        }

        //Connected nodes
        int convPosToNode(int from, int dir){
            switch(dir)
            {
                case 1: return from-currlocation->Width-1;//-1,-1
                case 2: return from-currlocation->Width;//0,-1
                case 3: return from-currlocation->Width+1;//1,-1
                case 4: return from-1; //-1,0
                case 5: return from+1;//1,0
                case 6: return from+currlocation->Width-1;//-1,1
                case 7: return conv(conX(from),conY(from)+1);//0,1
                case 8: return conv(conX(from)+1,conY(from)+1);//1,1
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
    double startShow(int start, FindNode* end){
        pathnum.clear();
        pathnum.push_front(start);
    }
	double bfs(int start, FindNode* end){
		for(int i=0; i<v; i++)
        {
            parent[i] = -1;
            closedList[i] = false;
            gscores[i] = INF;
        }
        gscores[start] = 0;
        parent[start] = start;

        int curr=start;
		queue<pair<int, int> > q;
		q.push(make_pair(curr,0));
		for(int n=0;n<v;n++) {
			curr = q.front().first;
			int d = q.front().second;
			q.pop();

			//if ( (*end)(convX(curr), convY(curr)) ) break;
            if(closedList[curr]) continue;
			closedList[curr] = true;

			for(int i=1; i<=8; i++)
            {
                //Skip if invalid
                if(conX(curr)==0&&(i==1||i==4||i==6)) continue;
                if(conX(curr)==currlocation->Width-1&&(i==3||i==5||i==8)) continue;
                if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
                if(conY(curr)==currlocation->Height-1&&(i==6||i==7||i==8)) continue;

                int next=convPosToNode(curr,i);
                //double oldgscore = gscores[next];//update vertex
                //double newgscore = gscores[curr] + getCcost(curr, next, i);//computecost
				//discard if already closedList
                if(!closedList[next]){
					//if (gscores[next]==-1 || d+1 < gscores[next]){
					if (currlocation->isWalkablePixel(conX(next),conY(next))){
                        parent[next] = curr;//gscores[next]=d+1;
						q.push(make_pair(next, d+1));
					}
                }
            }
		}/*
		for (int i=0;i<v;i++){
            if (closedList[i])cout<<conX(i)<<" "<<conY(i)<<"\n";
            int x = conX(i),y=conY(i),box=3;
            for(int j=max(0,x-box);j<x;j++){
                for(int k=max(0,y-box);k<y;k++){
                    cout<<(max(0,j)%currlocation->Width)<<" "<<(max(0,k)%currlocation->Height)<<"\n";//count++;
            }}
		}*/

		pathnum.clear();
        pathnum.push_front(curr);
        int i = curr;
        while(i != start)
        {
            pathnum.push_front(parent[i]);
            i = parent[i];
        }
        pathnum.push_front(start);
        return gscores[curr];
	}
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
            //cout<<convX(curr)<<" "<<convY(curr)<<"\n";
            for(int i=1; i<=8; i++){
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
                    //cout<<convX(next)<<" "<<convY(next)<<"\n";
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
        pathnum.push_front(start);
        return gscores[curr];
    }

public:
    AStar(Map *ll):coordinatesToNode(ll){}

    vector<coordinates> path;
    vector<coordinates> getPath(int x1, int y1, FindNode* end){
        path.clear();

        //bfs(conv(x1,y1),end);
        aStar(conv(x1,y1),end);
        //startShow(conv(x1,y1),end);
        for (int i=0; i<(int)pathnum.size();i++){
            coordinates curr;
            curr.pos[0] = convX(pathnum[i]);
            curr.pos[1] = convY(pathnum[i]);
            path.push_back(curr);
        }
        return path;
    }

};
