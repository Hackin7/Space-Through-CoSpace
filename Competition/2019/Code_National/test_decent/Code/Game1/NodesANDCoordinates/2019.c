#define MAX 11
int coordinates[MAX][2] = {{50, 220}, {70, 144}, {139, 137}, {155, 225}, {197, 113}, {317, 155}, {296, 177},{278,101},{276,50},{337,47},{344,21}};

#define DEPOSITNODES 1
int depositNodes[DEPOSITNODES] = {10};

#define OBJPOINTS 2
int objectPoints[OBJPOINTS] = {0,4};
int objectPointsSize[OBJPOINTS][2] = {{50,25},{25,25}};

#define REDPOINTS 2
int redNodes[REDPOINTS] = {9,18};
#define BLUEPOINTS 3
int blueNodes[BLUEPOINTS] = {32, 43, 29};
#define BLACKPOINTS 1
int blackNodes[BLACKPOINTS] = {33};

int cost[MAX][MAX];
void setCostValues(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            cost[i][j] = 9999;
        }
    }

cost[0][1] = 1;
cost[1][0] = 1;
cost[1][2] = 1;
cost[2][1] = 1;
cost[2][3] = 1;
cost[3][2] = 1;
cost[2][4] = 1;
cost[4][2] = 1;
cost[4][5] = 1;
cost[5][4] = 1;
cost[5][6] = 1;
cost[6][5] = 1;
cost[7][4] = 1;
cost[4][7] = 1;
cost[7][8] = 1;
cost[8][7] = 1;
cost[9][8] = 1;
cost[8][9] = 1;
cost[9][10] = 1;
cost[10][9] = 1;

    }

