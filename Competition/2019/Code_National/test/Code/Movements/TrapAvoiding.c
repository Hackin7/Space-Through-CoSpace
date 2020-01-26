bool avoidTrap(bool avoid){
	int trapYellow[3] = {220,235,20};
	int trapBlue[3] = {95,43,190};
	int trapRange=20;
	if (colorCheck(trapBlue,trapRange)){
		LoadedObjects=0;
		LoadedPoints = 0;
		LoadedBlue=0;LoadedRed=0;LoadedBlack=0;LoadedSuperObj=0;
	}
	else if (LoadedObjects > 0 && colorCheck(trapYellow,trapRange) && avoid){//objRange ) &&)){

	            WheelLeft=-3;WheelRight=-5; // Turn
            //Duration=5;

		if (! colorRightCheck(trapYellow,trapRange*2)){ // Turn Right
			WheelLeft=3;WheelRight=0;
			//Duration = 5;
		}
		else if (! colorLeftCheck(trapYellow,trapRange*2)){ // Turn Left
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
