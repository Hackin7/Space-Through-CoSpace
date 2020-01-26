template<typename T> static inline bool inRange(T a, T b, T c){return b<=a&&a<=c;}

class Vector2 {
public:

	double x,y;
	bool reverse;

	void setWheels(int WL, int WR)
	{
		double coeff=215.0;
		reverse = WL<0 && WR<0;
		x = 0;
		y = abs(WL + WR)/coeff;
	}

	pair<double,double> rotate(double prevX, double prevY, double prevAngle, double currAngle, int numIT)
	{
		//convert degrees to radians
		currAngle*=0.0174532925199432958;
		prevAngle*=0.0174532925199432958;

		double rate_of_rotation = (currAngle - prevAngle)/numIT;
		pair<double,double> result = make_pair(prevX, prevY);

		for (int i=0; i<numIT; i++)
		{
			currAngle = prevAngle + rate_of_rotation*i;
			double sin_ = sin(currAngle);
			double cos_ = cos(currAngle);

			double tx = -sin_ * y;
			double ty = cos_ * y;

			if (!reverse)
			{
				result.first += tx;
				result.second += ty;
			}
			else
			{
				result.first -= tx;
				result.second -= ty;
			}

		}
		return result;
	}
} ;
enum {
	W1_COLOUR_RED,
	W1_COLOUR_GREEN,
	W1_COLOUR_BLACK,
	W1_COLOUR_YELLOW,
	W1_COLOUR_BONUS,
	W1_COLOUR_DEPOSIT,
	W1_COLOUR_TRAP1_INSIDE,
	W1_COLOUR_TRAP2_INSIDE,
	W1_COLOUR_WHITE,
	W1_COLOUR_FLOOR_TILE_DARK,
	W1_COLOUR_FLOOR_TILE_DARK_UPPER,
	W1_COLOUR_FLOOR_TILE_LIGHT,
	W1_COLOUR_FLOOR_TILE_LIGHT_LOWER,
	W2_COLOUR_RED,
	W2_COLOUR_GREEN,
	W2_COLOUR_BLACK,
	W2_COLOUR_SUPEROBJ,
	W2_COLOUR_YELLOW,
	W2_COLOUR_BONUS,
	W2_COLOUR_SWAMP,
	W2_COLOUR_DEPOSIT,
	W2_COLOUR_TRAP1_INSIDE,
	W2_COLOUR_TRAP2_INSIDE,
	TOTAL_COLOURS
};

static uintf8 colours[TOTAL_COLOURS][3][2];

static void ColourInformationStorer(uintf8 num,uintf8 r1,uintf8 r2,uintf8 g1,uintf8 g2,uintf8 b1,uintf8 b2)
{
	colours[num][0][0] = r1;
	colours[num][0][1] = r2;
	colours[num][1][0] = g1;
	colours[num][1][1] = g2;
	colours[num][2][0] = b1;
	colours[num][2][1] = b2;
}

static void InputColourInfo()
{
	//Add colour RGB here
	ColourInformationStorer(W2_COLOUR_YELLOW,204,235,217,248,0,0);
	ColourInformationStorer(W2_COLOUR_RED,190,255,0,90,0,90);
	ColourInformationStorer(W2_COLOUR_GREEN,25,45,215,255,240,255);
	ColourInformationStorer(W2_COLOUR_BLACK,25,75,25,75,25,75);
	ColourInformationStorer(W2_COLOUR_BONUS,0,0,150,171,0,0);
	ColourInformationStorer(W2_COLOUR_SWAMP,101,116,108,123,143,158);
	ColourInformationStorer(W2_COLOUR_DEPOSIT,204,235,140,160,0,0);
	ColourInformationStorer(W2_COLOUR_SUPEROBJ,200,255,20,50,200,255);
	ColourInformationStorer(W2_COLOUR_TRAP1_INSIDE,152,177,0,0,0,0);
	ColourInformationStorer(W2_COLOUR_TRAP2_INSIDE,122,140,87,99,255,255);
}
static inline uintf8 ColorSensorDetection(int color)
{
	/*
		0 - Not detected
		1 - Left Side Detected
		2 - Right Side Detected
		3 - Both Detected
	*/
	static constexpr uintf8 o = 0;
	uintf8 r1 = colours[color][0][0];
	uintf8 r2 = colours[color][0][1];
	uintf8 g1 = colours[color][1][0];
	uintf8 g2 = colours[color][1][1];
	uintf8 b1 = colours[color][2][0];
	uintf8 b2 = colours[color][2][1];

	// if (color == W2_COLOUR_TRAP_INSIDE) //if the map has colours similar to trap
	// {
	// 	if ((CSLeft_R==r1 && CSLeft_G==g1 && CSLeft_B==b1) || (CSLeft_R==r2 && CSLeft_G==g2 && CSLeft_B==b2))
	// 		return 1;
	// 	if ((CSRight_R==r1 && CSRight_G==g1 && CSRight_B==b1) || (CSRight_R==r2 && CSRight_G==g2 && CSRight_B==b2))
	// 		return 2;
	// 	return 0;
	// }

	uintf8 result = 0;
	// if( inRange(CSLeft_R,r1-o,r2+o)&&inRange(CSLeft_G,g1-o,g2+o)&&inRange(CSLeft_B,b1-o,b2+o) &&
	//   inRange(CSRight_R,r1-o,r2+o)&&inRange(CSRight_G,g1-o,g2+o)&&inRange(CSRight_B,b1-o,b2+o) )
	//   	result+=2;
	if ( inRange(CSLeft_R,r1-o,r2+o) && inRange(CSLeft_G,g1-o,g2+o) && inRange(CSLeft_B,b1-o,b2+o) )
		result++;//left
	if ( inRange(CSRight_R,r1-o,r2+o) && inRange(CSRight_G,g1-o,g2+o) && inRange(CSRight_B,b1-o,b2+o) )
		result+=2;//right
	return result;
}
int colorSensorX, colorSensorY;
static inline bool isOnSwamp() {return ColorSensorDetection(W2_COLOUR_SWAMP);}
int prevCompass=0;
static void Game1()
{
	if (Duration){ //>0
		Duration--;
		return;
	}
	
	if (PositionX!=0&&PositionY!=0){
		PositionX1 = PositionX;
		PositionY1 = PositionY;
	}else{
		posInfoLost();
	}
	PositionX1 = PositionX;
	PositionY1 = PositionY;
	
	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);
	cout<<"_";//<<PositionX1<<","<<PositionY1<<"_"<<endl;

	//moveAStar(330, 190);
	moveBlue();
}