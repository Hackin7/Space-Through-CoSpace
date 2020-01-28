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
    int range=7;

    if(PositionX1<=x1 && 0<=Compass && Compass <90){WheelLeft=3;WheelRight=-3;return true;}
    else if(PositionX1<=x1 && 90-range<=Compass && Compass <180+range){WheelLeft=-3;WheelRight=3;return true;}
    else if(PositionX1>=x2 && 180-range<=Compass && Compass <270+range){WheelLeft=3;WheelRight=-3;return true;}
    else if(PositionX1>=x2 && 270-range<=Compass && Compass <=360+range){WheelLeft=-3;WheelRight=3;return true;}
    else if (PositionY1<=y1 && 90-range <=Compass && Compass <=180+range){
        WheelLeft=3;WheelRight=-3;return true;
    }
    else if (PositionY1<=y1 && 180-range<=Compass && Compass <=270+range){
        WheelLeft=-3;WheelRight=3;return true;
    }
    else if (PositionY1>=y2 && (270-range <= Compass  && Compass <= 360+range)){
        //cout<<"Up";
        //WheelLeft=3;WheelRight=0;
        WheelLeft=3;WheelRight=-3;return true;
    }
    else if (PositionY1>=y2 && (-range< Compass && Compass < 90+range)){
        //cout<<"Left";
        //WheelLeft=0;WheelRight=3;
        WheelLeft=-3;WheelRight=3;return true;
    }
    else{
        return false;//quarrantine(10,335,10,250,5,5);
    }
}
