
void Game0(){
	if (Duration){ //>0
		Duration--;
		return;
	}

	bool collectBlue = true;
	bool collectRed = true;
	bool collectBlack = true;
	bool deposit = true;
	bool avoid = true;

	if (avoidTrap(avoid)){return;}
	else if (objCollectDeposit(collectBlue, collectRed, collectBlack, deposit)){return;} // If ran, let it do its thing
	else if (wallAvoiding()){}
	else {
		WheelLeft=3;WheelRight=3;
	}

	if (Time > 180){
			Teleport = 1;
	}
}

