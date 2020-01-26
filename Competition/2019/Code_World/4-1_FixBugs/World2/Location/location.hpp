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
	bool isVisited(int i, int j){return visited[i][j];}

	int getPixel(int i, int j){return map[i][j];}
	bool isVal(int i, int j, int val){return map[i][j] == val;}
	bool isWalkablePixel(int i, int j){
		return  getPixel(i,j) == empty ||
				getPixel(i,j) == deposit ||
				getPixel(i,j) == red ||
				getPixel(i,j) == blue ||
				getPixel(i,j) == black;// ||
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
			visited[x][y] = true;
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
//Map location;