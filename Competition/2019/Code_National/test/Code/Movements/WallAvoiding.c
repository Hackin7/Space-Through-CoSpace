void world1wallAvoiding()
{
	if (US_Front < 15 && US_Left < 15 && US_Right < 20){		 //Full Turn
		/*if (Compass < 270 && Compass > 160 )
		{
			WheelLeft=4;WheelRight=-4;
		}
		else if (Compass<30 || Compass> 232)
		{
			WheelLeft=-5;WheelRight=5;
		}
		else
		{
			WheelLeft=-3;WheelLeft=-3;
		}*/
		//printf("Corner");
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

void reverse(){
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


void wallAvoiding(int dist)
{
	if (US_Front < dist+10 && US_Left < dist && US_Right < dist){
		//reverse();
		WheelLeft=5;WheelRight=-5; //Full Turn
		//printf("Corner");
	}
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
	else if (US_Left < dist){
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
        reverse();
        //WheelLeft=-5;WheelRight=5;//Turn Right
		//printf("Front");
	}

	else{return false;}// No need to run
	return true; //Ran
}