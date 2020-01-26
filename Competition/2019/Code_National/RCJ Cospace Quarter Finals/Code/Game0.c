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
				WheelLeft=5; WheelRight=5;/*
				color=2;
				if (LoadedObjects>-1 && prevcolor==1&&color==2&&Compass>245&&Compass<285)
				{//antic
					printf("'AAAAAAA'");
					Duration=2;
						WheelLeft=-5;WheelRight=5;
				}*/
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
			Teleport = 1;
	}
}
