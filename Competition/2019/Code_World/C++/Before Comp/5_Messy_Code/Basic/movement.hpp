class PresetMovement{
	public:
	deque<pair<pair<int,int>,int> > steps;
	void addStep(int left, int right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=left;
		step.first.second=right;
		step.second=delay;
		steps.push_back(step);
	}
	bool run(){
		if (!steps.empty()){
			WheelLeft = steps[0].first.first;
			WheelRight = steps[0].first.second;
			Duration = steps[0].second;
			steps.pop_front();
			cout<<"Move Like An Idiot:"<<WheelLeft<<","<<WheelRight<<","<<Duration<<endl;
			return true;
		}
		return false;
	}
};
PresetMovement moveLikeAnIdiot;

static bool world1wallAvoiding(){
	if (US_Front < 15 && US_Left < 15 && US_Right < 20){
		WheelLeft=-4; WheelRight=4;
	}

	else if (US_Left<30&&US_Right<30 &&US_Front>50) // go through corridor
	{
		if (US_Left-US_Right>8)//left>right, turn right
		{
			WheelLeft=4;
			WheelRight=3;
		}
		else if (US_Right-US_Left<-8)//right>left, turn left
		{
			WheelLeft=3;
			WheelRight=4;
		}
		else
		{
			WheelLeft=4;
			WheelRight=4;
		}
		return false;
	}
	else if (US_Left < 15){
		WheelLeft=4;WheelRight=-1;
		//printf("Left");
	}
	else if (US_Right < 15){
		WheelLeft=-1;WheelRight=4;
		//printf("Right");
	}
	else if (US_Front < 15){

        if ((270 <= Compass && Compass < 360) &&
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=3;WheelRight=-1;//Turn Left
            }
        else{
            WheelLeft=-1;WheelRight=3;//Turn Right
        }
            //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}
	else{return false;}// No need to run
	return true; //Ran
}

static void reverse(){
    /*
    if ((270 <= Compass && Compass < 360) ||
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=4;WheelRight=0;//Turn Right
            }
        else{
            WheelLeft=0;WheelRight=4;//Turn Left
        }*/
        WheelLeft=-3;WheelRight=-2;
        Duration=2;
}


bool wallAvoiding(int dist)
{
	if (US_Front < dist+10 && US_Left < dist && US_Right < dist){
		//reverse();
		WheelLeft=3;WheelRight=-3; //Full Turn
		//printf("Corner");
	}
	/*
	else if (US_Left<40&&US_Right<40 &&US_Front>50) // go through wall
	{
		if (US_Left<15)
		{
			WheelLeft=5;
			WheelRight=4;
		}
		else if (US_Right<15)
		{
			WheelLeft=5;
			WheelRight=4;
		}
		else
		{
			WheelLeft=5;
			WheelRight=5;
		}

	}
	*/else if (US_Left < dist){
		//reverse();
		WheelLeft=3;WheelRight=0;
		//printf("Left");
	}
	else if (US_Right < dist){
		//reverse();
		WheelLeft=0;WheelRight=3;
		//printf("Right");
	}
	else if (US_Front < dist){
        //reverse();
        WheelLeft=-5;WheelRight=-5;//Turn Right
		//printf("Front");
	}

	else{return false;}// No need to run
	return true; //Ran
}