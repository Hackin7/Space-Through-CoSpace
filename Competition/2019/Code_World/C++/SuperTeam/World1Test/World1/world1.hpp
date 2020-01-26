
class PresetMovement{
	public:
	int Duration=0;
	int prevLeft=0;
	int prevRight = 0;

	deque<pair<pair<int,int>,int> > steps;
	void addStep(int left, int right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=left;
		step.first.second=right;
		step.second=delay;
		steps.push_back(step);
	}
	bool run(){
		if (Duration){ //>0
			WheelLeft=prevLeft;WheelRight=prevRight;
			Duration--;
			return true;
		}
		if (!steps.empty()){
			WheelLeft = steps[0].first.first;
			WheelRight = steps[0].first.second;
			prevLeft = WheelLeft;prevRight=WheelRight;
			Duration = steps[0].second;
			steps.pop_front();
			cout<<"Move Like An Idiot:"<<WheelLeft<<","<<WheelRight<<","<<Duration<<endl;
			return true;
		}
		return false;
	}
};
PresetMovement moveFixed;

bool WT_R(){
	if (US_Right>= 15 && US_Right<20){
		WheelLeft = 3;   //turn left
		WheelRight = 1;
		cout << "WT_R running" << endl;
		if (US_Left<11){   //senses wall on the left
			WheelLeft = 2;
			WheelRight = 0;
		}
	}
	else if (US_Right>30){
		WheelLeft = 3;
		WheelRight = 1;
		if (US_Left<15){
			WheelLeft = 2;
			WheelRight = 0;
			cout << "crap" << endl;
		}
	}
	return true;
}

int ft = 0;
int moveToDeposit=0;
int prevCompass = 0;
static void Game0(){
	
	if (ft==0){
		//90 Degrees clockwise
		moveFixed.addStep(2,-2,8);
		moveFixed.addStep(0,0,2);
		//moveFixed.addStep(3,3,50);
		//90 Degrees Anticlockwise
		//moveFixed.addStep(-2,2,8);
		//moveFixed.addStep(0,0,2);
		//moveFixed.addStep(3,3,50);
		ft = 1;
	}
	
	if (Duration){ //>0
		Duration--;
		return;
	}
		switch (moveToDeposit){
		case 1:
			WheelLeft=-1;WheelRight=1;
			if ((0<prevCompass&&prevCompass < 180) && (180-10<Compass&&Compass <180+10)){moveToDeposit++;}
			if ((270<prevCompass || prevCompass < 90) && (50-10<Compass&&Compass <50+10)){moveToDeposit++;}
			if (180 <= prevCompass && prevCompass<=270){moveToDeposit=0;}
			return;break;
		case 2:
			WheelLeft=3;WheelRight=3;
			if (w1Obj.LoadedObjects ==0){moveToDeposit++;}break;
		case 3:
			moveFixed.addStep(-5,-5,20);
			moveToDeposit=0;
	}

	
	int Pink [3] = {188,58,230};
	int zoneblue[3] = {0, 160,245};
	int trapBlue[3] = {56,100,225};
	int trapYellow[3] = {225,225,50};
	int depositOrange[3] = {235,140,20};
	int depRange = 30;
	int zonebluerange=30;
	
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	if (moveFixed.run()){return;}
	else if (w1Obj.Trap(avoid)){return;}
	else if (w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (w1Obj.LoadedObjects > 0 && colorCheck(depositOrange,depRange))
	{
		//2 color sensors must be in orange
		if (! colorRightCheck(depositOrange,depRange)){ // Turn Right
			WheelLeft=0;WheelRight=3;
			return ;
		}
		if (! colorLeftCheck(depositOrange,depRange)){ // Turn Left
			WheelLeft=3;WheelRight=0;
			return;
		}
		WheelLeft=0;WheelRight=0;
		LED_1 =2;
		Duration=60;
		w1Obj.LoadedObjects=0;
		w1Obj.LoadedPoints = 0;
		w1Obj.LoadedBlue=0;w1Obj.LoadedRed=0;w1Obj.LoadedBlack=0;w1Obj.LoadedSuperObj=0;
	}
	else if (world1wallAvoiding()){}
	else if (moveToDeposit==0)WT_R();//WheelLeft=5;WheelRight=5;}
	if (colorCheck(Pink,30)){
		if (w1Obj.LoadedObjects>0){
			moveToDeposit = 1;
			prevCompass = Compass;
		}
		cout<<"Pink";
	}
			
	if (Time > 180){
			Teleport = 2;
			LoadedObjects=0;
	}
}
