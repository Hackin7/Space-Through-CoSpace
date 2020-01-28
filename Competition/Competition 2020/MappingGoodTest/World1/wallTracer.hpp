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
