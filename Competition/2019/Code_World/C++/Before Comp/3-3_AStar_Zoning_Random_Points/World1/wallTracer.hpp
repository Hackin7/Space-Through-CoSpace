// File: Movements/WallTracer.c
int timeout;
//only walltrace if walltrace = 1;
// wallfollowing
bool WallTracer_right(){
	timeout = 0;
	if (US_Right<30){
		WheelLeft = 0;
		WheelRight = 2;
		printf ("wall right");
		timeout++;
	}
	else if (US_Right>50){
		WheelLeft = 2;
		WheelRight = 0;
	}
	else if (timeout >= 100){
		return false;
	}
	return true;
}
