/*void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	int timeout = 0;

	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;


	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding(20)){}
	else if (WallTracer_right()){}
	else {
		WheelLeft=4;WheelRight=4;
	}

	if (Time > 180){
			Teleport = 1;
	}
}
*/
/*
void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	int zonewhite[3]={220,230,250};
	int zoneblue[3] = {0, 160,245};
	int zonebluerange=30;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;
	int color=0;
	int prevcolor=0;
	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (world1wallAvoiding()){}
	else {
		if (LoadedObjects == 0)
		{
			WheelLeft=5; WheelRight = 5;
		}
		else{
			if (colorCheck(zoneblue, zonebluerange))
			{
				WheelLeft=5; WheelRight=5;
			}
			else {
				WheelLeft=3;WheelRight=3;color=0;
				if (colorCheck(zonewhite, 30))
				{
					color=1;
				}
			}

			prevcolor=color;
				}
				}

	if (Time > 180){
			LoadedObjects=0;LoadedPoints=0;
			Teleport = 2;
	}
}
*/
void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}
	/*
	if (Time<5)
	{
		printf("%d\n",Time );;
		if (Time<1){WheelLeft=5;WheelRight=-5;}
		else{WheelLeft=5;WheelRight=5;}
		return;
	}*/
	int zoneblue[3] = {0, 160,245};
	int trapYellow[3] = {225,225,50};
	int depositOrange[3] = {215,140,20};
	int zonebluerange=30;
	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;

	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (world1wallAvoiding()){}
	else if (LoadedObjects>3 && colorRightCheck(trapYellow,30) && ((US_Front>30 && US_Front<65) && (US_Left<37 || US_Right<37) )){
		WallTracer_right();
		if (colorLeftCheck(depositOrange,30)){
			objCollectDeposit(collectBlue, collectRed, collectBlack, deposit);
		}
	}

	else {
		if (LoadedObjects == 0)
		{
			WheelLeft=5; WheelRight = 5;
		}
		else{
			if (colorCheck(zoneblue, zonebluerange))
			{
				printf("Slow down\n" );
				WheelLeft=2; WheelRight=2;
			}
			else {WheelLeft=4;WheelRight=4;}
				}

				}

	if (Time > 180){
			Teleport = 2;
			LoadedObjects=0;
	}
}
