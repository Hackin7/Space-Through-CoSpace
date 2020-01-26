	int mDuration=0;
	int prevLeft=0;
	int prevRight = 0;

	deque<pair<pair<int,int>,int> > steps;
	void moveFixedaddStep(int left, int right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=left;
		step.first.second=right;
		step.second=delay;
		steps.push_back(step);
	}
	bool moveFixedrun(){
		if (mDuration){ //>0
			WheelLeft=prevLeft;WheelRight=prevRight;
			mDuration--;
			return true;
		}
		if (!steps.empty()){
			WheelLeft = steps[0].first.first;
			WheelRight = steps[0].first.second;
			prevLeft = WheelLeft;prevRight=WheelRight;
			mDuration = steps[0].second;
			steps.pop_front();
			cout<<"Move Like An Idiot:"<<WheelLeft<<","<<WheelRight<<","<<Duration<<endl;
			return true;
		}
		return false;
	}

bool isAngle(int angle, int range){
	return angle-range < Compass && Compass < angle+range;
}

bool isUp(int range){
	return 360-range < Compass || Compass < range;
}
///Exit Inner walls
int switchDirection=0;
int switchtiming=10;
int moveOutOfWall=0;
void inInnerWall(){
	cout<<"SwitchDirection: "<<switchDirection<<endl;
	if (isAngle(270,10) && switchDirection==1){
		//moveOutOfWall=1;
		switchDirection=0;
	}
	if (isAngle(90,10)){
		switchDirection=1;
	}
	
	/*if (switchTime.timeout(switchtiming)){
		switchDirection=0;
	}*/
}



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
	else{
		WheelLeft=4;WheelRight=4;
	}
	return true;
}

int ft = 0;
int moveToDeposit=0;int prevCompass = 0;
int moveInside=0;
int prevTime = 0;
int moveInsideMode=0;
static void Game0(){
	
	if (ft==0){
		//90 Degrees clockwise
		moveFixedaddStep(2,-2,8);
		moveFixedaddStep(0,0,2);
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
			moveFixedaddStep(-5,-5,20);
			moveToDeposit=0;
	}
	switch (moveOutOfWall){
		case 1:
		moveFixedaddStep(5,5,20);
		moveOutOfWall=0;
		break;
	}
	switch (moveInside){
		case 1:
		WheelLeft=0;WheelRight=0;
		if (isAngle(45,180))moveInsideMode = 1;
		else if (isAngle(225,180))moveInsideMode = 2;
		else moveInsideMode = 1;
		moveInside = 2;
		case 2:
		WheelLeft=-2;WheelRight=2;
		if (moveInsideMode = 1&&isAngle(225,10))moveInside=3;
		//if (moveInsideMode == 2 && isAngle(45,10))moveInside=3;
		
		case 3:
		moveFixedaddStep(5,5,10);
		prevTime = Time;
		moveInside=0;
		break;
	}
	
	inInnerWall();
	
	int Pink [3] = {188,58,230};
	int zoneblue[3] = {0, 160,245};
	int trapBlue[3] = {56,100,225};
	int trapYellow[3] = {225,225,50};
	int depositOrange[3] = {220,140,20};
	int depRange = 30;
	int zonebluerange=30;
	
	bool collectBlue = w1Obj.LoadedObjects<=7;//&& (w2Obj.LoadedBlue + w2Obj.LoadedSuperObj + w2Obj.noSuperObj)<2;//true;
	bool collectRed = w1Obj.LoadedObjects<=7;// && w2Obj.LoadedRed<2;//true;
	bool collectBlack = w1Obj.LoadedObjects<=7;// && w2Obj.LoadedBlack<2;//true;
	bool deposit = true;// || w2Obj.LoadedObjects>=6 ||  w2Obj.LoadedSuperObj > 0;//true;
	bool avoid = w1Obj.LoadedObjects>=2;//|| w2Obj.LoadedSuperObj > 0;//true;
	
	if (w1Obj.Trap(avoid)){return;}
	else if (world1wallAvoiding()){}
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
	else if (moveFixedrun()){return;}	
	else WT_R();//WheelLeft=5;WheelRight=5;}
	
	if (colorCheck(w2Obj.ignorePurple,30)){
		//if (w1Obj.LoadedObjects>0){
		//	moveToDeposit = 1;
		//	prevCompass = Compass;
		//}
		cout<<"Purple";
		//moveInside = 1;
		
	}
	
		/*if (Time - prevTime >= 10){
			moveFixedaddStep(4,4,10);
			prevTime=Time;
			//moveFixedaddStep(2,-2,8);
		}*/
	if (Time > 180){
			Teleport = 2;
			LoadedObjects=0;
	}
}
