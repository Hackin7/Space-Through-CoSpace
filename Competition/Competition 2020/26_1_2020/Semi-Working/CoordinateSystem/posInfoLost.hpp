double tx=220,ty=80;
int icompass=0;
int speed;

void posInfoLost(){
    if (PositionX==0 && PositionY==0)
    {
        if ((WheelLeft<2 && WheelLeft>-2) || (WheelRight>-2 && WheelRight<2)) // can ignore i guess? since its probably turning
        {
            PositionX=tx;
            PositionY=tx;
            return;
        }
        speed=(WheelLeft+WheelRight)/3.48;
        tx = speed * cos((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + tx;
        ty =speed * sin((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + ty;
        PositionX1=tx;
        PositionY1=ty;
    }else{
        tx = PositionX1;
        ty = PositionY1;
    }

//icompass=Compass;
}

void w1posInfoLost(){
        if ((WheelLeft<2 && WheelLeft>-2) || (WheelRight>-2 && WheelRight<2)) // can ignore i guess? since its probably turning
        {
            PositionX=tx;
            PositionY=tx;
            return;
        }
        speed=(WheelLeft+WheelRight)/3.48*1.25;
        if (US_Front < 5){speed=0;}
        tx = speed * cos((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + tx;
        ty =speed * sin((Compass+90)%360 * 3.1415926535897932384626433832795 / 180) + ty;
        PositionX1=tx;
        PositionY1=ty;
        if (tx<0){tx=0;}if (tx>240){tx=240;}
        if (ty<0){ty=0;}if (ty>180){ty=180;}
//icompass=Compass;
}
