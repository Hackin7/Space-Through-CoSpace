// File: Movements/WallTracer.c
int timeout=0;
//only walltrace if walltrace = 1;
// wallfollowing
bool WallTracer_right(){
	timeout = 0;
	if (US_Right<20){
		WheelLeft = 1;
		WheelRight = 3;
		printf ("wall right");
		timeout++;
	}
	else if (US_Right>40){
		WheelLeft = 3;
		WheelRight = 1;
	}
	else if (timeout >= 100){
		return false;
	}
	else{WheelLeft=4;WheelRight=4;}
	return true;
}
bool WT_R(){
	timeout = 0;
	if (US_Right>= 15 && US_Right<20){
		WheelLeft = 0;   //turn left
		WheelRight = 2;
		cout << "WT_R running" << endl;
		timeout = timeout + 1;
		if (US_Left<11){   //senses wall on the left
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
	if (US_Left<20){
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

static void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	int Pink [3] = {216,66,254};
	int zoneblue[3] = {0, 160,245};
	int trapBlue[3] = {56,100,225};
	int trapYellow[3] = {225,225,50};
	int depositOrange[3] = {215,140,20};
	int zonebluerange=30;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;

	if (w1Obj.Trap(avoid)){return;}
	else if (w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (world1wallAvoiding()){}
	
	else if (LoadedObjects>0 && colorCheck(trapYellow,35) && US_Left<10 && (Compass>205 && Compass<245)){
		//turn left + move foward until detect pink
		cout <<"Stuck near Deposit" << endl;
		WheelRight = 3;
		WheelLeft = -1;
		if (colorCheck(Pink,30)){
			cout << "#CodePink_ter" << endl;
			WT_L();
			if (colorCheck(depositOrange,30) && LoadedObjects>0){
				w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
				
			
			}
		}
	}
	
	else if (colorCheck(Pink,30) && (Compass>35 && Compass<125) && US_Front>15 && LoadedObjects>0){
		cout << "#CodePink_ter" << endl;
		WheelLeft = 2;
		WheelRight = -2;
		if (Compass>85 && Compass<95){
			WheelLeft = 2;
			WheelRight = 2;
			if (colorCheck(depositOrange,30) && LoadedObjects>0){
				w1Obj.objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
				
				
			}
		}
	}
	
		else if ((colorRightCheck(Pink,30)) && (US_Left<19 && US_Front<19) && (Compass>=270 && Compass<=259)){
			cout << Compass << endl;
			cout << "Deposit1 turn right" << endl;
			WheelLeft = 2;
			WheelRight = -2;
			if (Compass>=178 && Compass<=182){
				WheelLeft = 2;
				WheelRight = 2;
			}
		}
		else if ((colorRightCheck(Pink,30)) && (US_Right<19 && US_Front<19) && (Compass>=0 && Compass<=90)){
			cout << Compass << endl;
			cout << "Deposit1 turn left" << endl;
			WheelRight = 2;
			WheelLeft = -2;
			if (Compass>=178 && Compass<=182){
				WheelLeft = 2;
				WheelRight = 2;
			}
		}
	

	else {
		if (LoadedObjects == 0)
		{
		WheelLeft = 4;
		WheelRight = 4;
		}
	
		
		else{
			if (colorCheck(zoneblue, zonebluerange) && (Compass>240 && Compass<300))
			{
				cout << "Slow down" << endl;
				WT_R();
			}
				if (colorCheck(zoneblue, zonebluerange) && (Compass>50 && Compass<130))
			{
				cout << "Slow down" << endl;
				WT_L();
			}
			
				}

				}

	if (Time > 180){
			Teleport = 2;
			LoadedObjects=0;
	}
}
