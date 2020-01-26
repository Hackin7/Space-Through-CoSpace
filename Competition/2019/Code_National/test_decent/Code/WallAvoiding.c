void reverse(){
    if ((270 <= Compass && Compass < 360) ||
            (90 < Compass && Compass <= 180)){ //Slanted towards right
                WheelLeft=5;WheelRight=-5;//Turn Right
            }
        else{
            WheelLeft=-5;WheelRight=5;//Turn Left
        }
}


void wallAvoiding()
{
	if (US_Front < 25 && US_Left < 20 && US_Right < 20){
		reverse();//WheelLeft=5;WheelRight=-5; //Full Turn
		//printf("Corner");
	}
	else if (US_Left < 20){
		WheelLeft=3;WheelRight=0;
		//printf("Left");
	}
	else if (US_Right < 20){
		WheelLeft=0;WheelRight=3;
		//printf("Right");
	}
	else if (US_Front < 20){
        reverse();
            //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}
	else{return false;}// No need to run
	return true; //Ran
}
