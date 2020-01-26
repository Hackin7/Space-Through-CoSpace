/* Deposit Conditions
Compass == 180
int Pink [3] = {216,66,254}
US_Front < 30
walltrace left: US_Left<40
walltrace right: US_right<40
*/
// File: Movements/WallTracer.c
//int timeout=0;
//only walltrace if walltrace = 1;
// wallfollowing
bool WT_R(){
	timeout = 0;
	if (US_Right<25){
		WheelLeft = 0;   //turn left
		WheelRight = 2;
		cout << "WT_R running" << endl;
		timeout = timeout + 1;
		if (US_Left<11){
			WheelLeft = 2;
			WheelRight = 0;
		}
	}
	else if (US_Right>30){
		WheelLeft = 2;
		WheelRight = 0;
		if (US_Left<15){
			WheelLeft = 2;
			WheelRight = 0;
			cout << "crap" << endl;
		}
	}
	else if (timeout >= 100){
		cout << "loop exit";
		return false;
	}
	return true;
}
bool WT_L(){
	timeout = 0;
	if (US_Left<25){
		WheelLeft = 2;   //turn left
		WheelRight = 0;
		cout << "WT_L running" << endl;
		timeout = timeout + 1;
		if (US_Right<11){
			WheelLeft = 0;
			WheelRight = 2;
		}
	}
	else if (US_Left>30){
		WheelLeft = 0;
		WheelRight = 2;
		if (US_Right<15){
			WheelLeft = 0;
			WheelRight = 2;
			cout << "crap" << endl;
		}
	}
	else if (timeout >= 100){
		cout << "loop exit";
		return false;
	}
	return true;
}
//deflection = how big zigzag will be
//l_value = initial US_Left value, r_value = initial US_Right value
//init_d = initial Compass value
bool Sweeper(int deflection, int L_value, int R_value, int init_d){
	int opp_d = abs(deflection - init_d);
	int side = L_value - R_value; // >0 right side (towards left).<0 left side (towards right)
	if (US_Left<20){
		//turn right
		WheelLeft = 3;
		WheelRight = 2;
		if (Compass != init_d){ //turn left to correct error
			cout << "Error: " << abs(Compass-init_d) << endl;
			WheelLeft = -2;
			WheelRight = 2;
			if (Compass == init_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout <<"Corrected" << endl;
			}
		}
		else if (Compass != opp_d){
			cout << "Error: " << abs(Compass-opp_d) << endl;
			WheelLeft = -2;
			WheelRight = 2;
			if (Compass == opp_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout << "Corrected" << endl;
			}
		}
		
	}
	else if (US_Right<20){
		//turn left
		WheelRight = 3;
		WheelLeft = 2;
		if (Compass != init_d){ //turn right to correct error
			cout << "Error: " << abs(Compass-init_d) << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass == init_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout <<"Corrected" << endl;
			}
		}
		else if (Compass != opp_d){
			cout << "Error: " << abs(Compass-opp_d) << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass == opp_d){
				WheelLeft = 4;
				WheelRight = 4;
				cout << "Corrected" << endl;
			}
		}
		
		
	}
	else if(US_Front<15 && US_Left<15 && US_Right<20){
		WheelLeft=-3; WheelRight=3;
		if (Compass == init_d){
			cout << "Set point (Front)" << endl;
			WheelLeft = 4;
			WheelRight = 4;
			
		}
	}
	else if (US_Front<20 && (US_Left>40 && US_Right>40) && (Compass==init_d || Compass==opp_d)){ //(reached a wall about to turn)
		if (side>0){
			//turn left wrt robot
			WheelRight = 3;
			WheelLeft = -3;
		}
		else if (side<0){
			//turn right wrt robot
			WheelRight = -3;
			WheelLeft = 3;
		}
		else { //robot wedged between 2 walls, so cannot determine side
		// by default turn right
			WheelRight = -3;
			WheelLeft = 3;
		}
		
	}
	return false;
	
}

bool DepositW1D1(){
	int depositOrange[3] = {235,147,20};
	int depRange = 35;
	if (colorCheck(depositOrange,depRange))
	{
		//2 color sensors must be in orange
		if (! colorRightCheck(depositOrange,depRange)){ // Turn Right
			WheelLeft=0;WheelRight=3;
			return true;
		}
		if (! colorLeftCheck(depositOrange,depRange)){ // Turn Left
			WheelLeft=3;WheelRight=0;
			return true;
		}
		WheelLeft=0;WheelRight=0;
		LED_1 =2;
		Duration=60;
		
	}
	else{return false;}
	return true;

}
bool color_LeftCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSLeft_R && CSLeft_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSLeft_G && CSLeft_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSLeft_B && CSLeft_B <= objBlue[2] + objRange
		);
}
bool color_RightCheck(int *objBlue, int objRange)
{
	return (objBlue[0] - objRange <= CSRight_R && CSRight_R <= objBlue[0] + objRange &&
	      objBlue[1] - objRange <= CSRight_G && CSRight_G <= objBlue[1] + objRange &&
	      objBlue[2] - objRange <= CSRight_B && CSRight_B <= objBlue[2] + objRange
		);
}
bool color_Check(int *objBlue, int objRange)
{return ( color_LeftCheck(objBlue, objRange) || color_RightCheck(objBlue, objRange));}

bool avoid_Trap(){
	
	int trapYellow[3] = {220,235,20};
	int trapRange = 40;

	
	if (LoadedObjects > 0){//objRange ) &&)){

	    WheelLeft=-3;WheelRight=-5; // Turn
            //Duration=5;

		if (! color_RightCheck(trapYellow,trapRange*2)){ // Turn Right
			WheelLeft=3;WheelRight=0;
			//Duration = 5;
		}
		else if (! color_LeftCheck(trapYellow,trapRange*2)){ // Turn Left
			WheelLeft=0;WheelRight=3;
			//Duration = 5;
		}
		else{
            WheelLeft=-2;WheelRight=-4; // Turn
            Duration=5;
		}
		printf("Danger\n");
		return true;
	}
		//Duration=41;
	else{ return false;}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////

static void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	
	class PresetMovement{
	public:
	deque<pair<pair<int,int>,int> > steps;
	void addStep(int wheel_left, int wheel_right, int delay){
		pair<pair<int,int>,int> step;
		step.first.first=wheel_left;
		step.first.second=wheel_right;
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
PresetMovement moveFixed;

	int Pink [3] = {216,66,254};
	int zoneblue[3] = {0, 160,245};
	int trapYellow[3] = {225,225,50};
	int depositOrange[3] = {215,140,20};
	int zonebluerange=30;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	
	
	if (w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;}
	else if (w1Obj.Trap(avoid)){return;} // If ran, let it do its thing
	else if (((Compass>170 && Compass<190) && color_Check(Pink,30) && LoadedObjects>0 && US_Front<35) && US_Left<40){
		WT_L();
		if (color_Check(depositOrange,30)){
			DepositW1D1();
		}
	}
	else if (((Compass>170 && Compass<190) && color_Check(Pink,30) && LoadedObjects>0 && US_Front<35) && US_Right<40){
		WT_R();
		if (color_Check(depositOrange,30)){
			DepositW1D1();
		}
	}

	else if ((color_Check(zoneblue,30) && LoadedObjects<6)&& (US_Right<35 && (Compass>=70 && Compass<=110))){
		WT_R();
	}
	else if ((color_Check(zoneblue,30) && LoadedObjects<6)&& (US_Left<35 && (Compass>=250 && Compass<=290))){
		WT_L();
	}
	//fully loaded
	else if (LoadedObjects==6){
		if ((Compass>=135 && Compass<=190)&& (US_Right<20 &&(US_Left>30 && US_Left<120)||(US_Front>30 && US_Front<120))){
			WT_R();
			if (colorCheck(Pink,30)){
				WheelLeft = 1;
				WheelRight = 1;
				if (US_Front<15){
					WT_R();
						if (colorCheck(depositOrange,30)){
							DepositW1D1();
						}
					}
				}
			}
		
	else if ((Compass>=170 && Compass<=230)&& (US_Left<20 &&(US_Right>30 && US_Right<120)||(US_Front>30 && US_Front<120))){
		WT_L();
		if (colorCheck(Pink,30)){
			WheelLeft = 1;
			WheelRight = 1;
			if (US_Front<15){
				WT_L();
					if (colorCheck(depositOrange,30)){
						DepositW1D1();
					}
				}
			}
		}
		}
	else if (LoadedObjects>0 && color_Check(trapYellow,35) && US_Right<10){
		//turn left + move foward until detect pink
		cout <<"Stuck mear Deposit"<<endl;
		WheelRight = 3;
		WheelLeft = -1;
		if (colorCheck(Pink,30)){
			WT_R();
			if (colorCheck(depositOrange,30)){
				DepositW1D1();
			}
		}
	}
	else if (LoadedObjects>0 && color_Check(trapYellow,35) && US_Left<10){
		//turn left + move foward until detect pink
		cout <<"Stuck near Deposit" << endl;
		WheelRight = 3;
		WheelLeft = -1;
		if (colorCheck(Pink,30)){
			WT_L();
			if (colorCheck(depositOrange,30)){
				DepositW1D1();
			}
		}
	}
	else if (world1wallAvoiding()){}
	else {
		//optimise, dont waste time wandering around
		WheelLeft = 3;
		WheelRight = 3;

	}

	if (Time > 180){
			Teleport = 4;
			LoadedObjects=0;
	} 
}
