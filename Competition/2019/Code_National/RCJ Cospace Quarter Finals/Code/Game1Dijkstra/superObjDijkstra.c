int SuperObjTime = 0;
int SuperObjStartTime = 0;
bool superObjDijkstra(){
    if (SuperObj_Num>0 && noSuperObj != SuperObj_Num){
        //if (noSuperObj<SuperObj_Num){
            //Collect 1 superobject at a time
            noSuperObj = SuperObj_Num;
        //}
		SuperObjX = SuperObj_X;
		SuperObjY = SuperObj_Y;

        int endNode = 0;
        if (SuperObj_Num>0){
            endNode = closestNode(SuperObjX,SuperObjY);
            startDijkstra(endNode);
        }
        SuperObjStartTime = Time;
        return true;
	}
	else if (noSuperObj>0 && reached(SuperObjX,SuperObjY,22,22)){
        WheelLeft=3;WheelRight=3;
        quarrantine(SuperObjX-11,
                    SuperObjX+11,
                    SuperObjY-11,
                    SuperObjY+11,11, 11);
        return true;
    }
	else if (noSuperObj>0 && !reached(SuperObjX-5,SuperObjY-5,5,5)
          && Time - SuperObjStartTime  < 60){
            printf("SuperObj \t");

        //Recalculate if sidetracked
        if (SuperObjTime != Time){
            int endNode = 0;
            if (SuperObj_Num>0){
                endNode = closestNode(SuperObjX,SuperObjY);
                startDijkstra(endNode);
            }
        }
        SuperObjTime=Time;

		moveDijkstra(SuperObjX,SuperObjY);
        return true;
	}
	else if (Time - SuperObjStartTime  >= 40){
        noSuperObj = 0;
	}
	return false;
}
