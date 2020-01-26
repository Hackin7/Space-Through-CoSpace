bool quarrantine(int x1, int x2, int y1, int y2, int rangex, int rangey){
    if (xreached(x1,rangex) && 0<=Compass && Compass <180){
            if (Compass < 90){
                WheelLeft=5;WheelRight=0;//reverse();
            }
            else{
                WheelLeft=0;WheelRight=5;//reverse();
            }
			return true;
	}
	else if (xreached(x2,rangex) && 180<=Compass && Compass <=360){
            if (Compass < 270){
                WheelLeft=5;WheelRight=0;//reverse();
            }
            else{
                WheelLeft=0;WheelRight=5;//reverse();
            }
        //WheelLeft=-5;WheelRight=5;//reverse();
		return true;
	}
	if (yreached(y1,rangey) && 90<=Compass && Compass <=270){
        reverse();
		return true;
		}
	else if (yreached(y2,rangey) && (Compass>270 || Compass <90)){
        reverse();
		return true;
	}
    return false;
}

bool boundary(){
    if ((xreached(10,5) && 0<=Compass && Compass <180)||
        (xreached(340,5) && 180<=Compass && Compass <=360)||
        (yreached(10,5) && 90<=Compass && Compass <=270)||
        (yreached(250,5) && (Compass>270 || Compass <90))){
			WheelLeft=-3;WheelRight=3;
			return true;
			}
    return false;//quarrantine(10,335,10,250,5,5);
}

