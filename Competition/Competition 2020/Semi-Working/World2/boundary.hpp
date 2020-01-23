// File: Game1/boundary.c
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
        WheelLeft=5;WheelRight=-4;
		return true;
		}
	else if (yreached(y2,rangey) && (Compass>270 || Compass <90)){
        WheelLeft=5;WheelRight=-4;
		return true;
	}
    return false;
}

bool boundary(int border){
    //int x1 = 22, x2 = 343, y1 = 22, y2 = 250;
    //int x1 = 20, x2 = 345, y1 = 10, y2 = 250;
	int x1 = 0+border, x2 = 360-border, y1 = border, y2 = 270-border;
    int range=45;
    /*
    (xreached(x1,5) && 0<=Compass && Compass <90)
    (xreached(x1,5) && 90<=Compass && Compass <180)
    (xreached(x2,5) && 180<=Compass && Compass <270)
    (xreached(x2,5) && 270<=Compass && Compass <=360)*/
    if (yreached(y1,5) && 90<=Compass && Compass <180-range){
        WheelLeft=3;WheelRight=0;
    }
    else if (yreached(y1,5) && 180+range<=Compass && Compass <=270){
        WheelLeft=0;WheelRight=3;
    }
    else if (yreached(y2,5) && (Compass > 270 && Compass < 360-range)){
        WheelLeft=3;WheelRight=0;
    }
    else if (yreached(y2,5) && (Compass > range && Compass < 90)){
        WheelLeft=0;WheelRight=3;
    }
    else
        if ((xreached(x1,5) && 0<=Compass && Compass <180)&&
        (yreached(y1,5) && 90<=Compass && Compass <=270)){
			WheelLeft=3;WheelRight=0;
			//Duration=2;
			return true;
			}
    if ((xreached(x1,5) && 0<=Compass && Compass <180)&&
        (yreached(y2,5) && (Compass>270 || Compass <90))){
			WheelLeft=0;WheelRight=3;
			//Duration=2;
			return true;
			}
	if ((xreached(x2,5) && 180<=Compass && Compass <=360)&&
        (yreached(y1,5) && 90<=Compass && Compass <=270)){
			WheelLeft=0;WheelRight=3;
			//Duration=2;
			return true;
			}
	if ((xreached(x2,5) && 180<=Compass && Compass <=360)&&
        (yreached(y2,5) && (Compass>270 || Compass <90))){
			WheelLeft=3;WheelRight=0;
			//Duration=2;
			return true;
			}
if ((xreached(x1,5) && 0<=Compass && Compass <180)||
        (xreached(x2,5) && 180<=Compass && Compass <=360)||
        (yreached(y1,5) && 90<=Compass && Compass <=270)||
        (yreached(y2,5) && (Compass>270 || Compass <90))){
			WheelLeft=-3;WheelRight=3;
			//Duration=2;
			return true;
			}
    return false;//quarrantine(10,335,10,250,5,5);
}
