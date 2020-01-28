class Map{
	public:
	//Colour Values
	const int unexplored = -1;
	const int predictedEmpty = -2;
	const int empty = 0;
	const int deposit = 1;
	const int red = 2;
	const int blue = 3;
	const int black = 4;
	const int redBlue=10;
	const int redBlack = 11;
	const int blueBlack = 12;
	const int redBlueBlack = 13;
	const int wall = 5;
	const int border = 6;
	const int trapBorder = 7;
	const int trap = 8;
	const int slow = 9;

	int Width=0,Height=0;
	bool toAvoidTrap = true;
	int map[width][height];
	bool visited[width][height];
	const int v = width*height;

	Map(){
	    Width=width;Height=height;
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++)
				map[i][j] = unexplored;
		}
	}
	Map(int mapData[width][height]){
	    Width=width;Height=height;
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++){
				map[i][j] = mapData[i][j];
				if (mapData[i][j] != unexplored){
					visited[i][j] = true;
				}
				else{visited[i][j] = false;}
			}
		}
	}

	Map(int mapData[width0][height0]){
	    Width=width;Height=height;
	    for (int i=0; i<width; i++){
			for (int j=0;j<height; j++){
				map[i][j] = mapData[i][j];
				if (mapData[i][j] != unexplored){
					visited[i][j] = true;
				}
				else{visited[i][j] = false;}
			}
		}
	}
	////Getter////////////////////////////////////////////////////
	bool isVisited(int i, int j){return visited[i][j];}
	bool isRed(int val){
		return  val == red ||
				val == redBlue ||
				val == redBlack ||
				val == redBlueBlack;
	}
	bool isBlue(int val){
		return  val == blue ||
				val == redBlue ||
				val == blueBlack ||
				val == redBlueBlack;
	}
	bool isBlack(int val){
		return  val == black ||
				val == blueBlack ||
				val == redBlack ||
				val == redBlueBlack;
	}
	int getPixel(int i, int j){return map[i][j];}
	bool isVal(int i, int j, int val){return map[i][j] == val;}
	bool isWalkableVal(int val){
		return  val == unexplored ||
				val == empty ||
				val == deposit ||
				val == red ||
				val == blue ||
				val == black;
	}
	bool isWalkablePixel(int i, int j){
		return  isWalkableVal(getPixel(i,j));
	}
	int valCost(int val){
		if (isWalkableVal(val)){
				return 1;
			}
		if (val == wall){
			return v;
		}
		if (val == slow){
				return 50;
		}
		if (val == trap){
			if (toAvoidTrap){return v;}
			else{return 10;}
		}
		if (val == border){
			return 40;
		}
		return v;
	}
	////Setter////////////////////////////////////////////////////
	void reset(int mapData[width][height]){
		for (int i=0; i<width; i++){
			for (int j=0;j<height; j++)
				map[i][j] = mapData[i][j];
		}
	}


int findValPriority(int val){
	if (val == unexplored)
		return 1;
	if (val == wall)
		return 2;
	if (val == unexplored)
		return 3;
	if (val == empty)
		return 4;
	if (val == red ||
		val == black ||
		val == blue||
		val == deposit)
		return 5;
	if (val == slow ||
		val == border ||
		val == trap)
		return 6;
	return 6;
}
	void setPixel(int i, int j, int val){
	    if (findValPriority(map[i][j]) < findValPriority(val)){
            map[i][j] = val;
            visited[i][j] = true;
        }

	}
	void rectfill(int x1,int x2,int y1,int y2, int color)
	{
		for (int x=x1; x <= x2; x++){
			for (int y=y1; y<= y2; y++){
                setPixel(x,y,color);
			//visited[x][y] = true;
			}
		}
		//cout<<map[x1][y1]<<"]";
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

//Map location;
