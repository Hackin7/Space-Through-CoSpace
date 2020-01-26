#define MAX 43
int coordinates[MAX][2] = {{33, 245}, {80, 246}, {148, 253}, {199, 253}, {284, 258}, {317, 243}, {58, 210}, {147, 216}, {200, 221}, {250, 240}, {98, 211}, {333, 208}, {32, 175}, {61, 150}, {121, 146}, {178, 148}, {239, 157}, {328, 155}, {31, 124}, {74, 108}, {125, 101}, {186, 100}, {233, 116}, {296, 131}, {269, 97}, {299, 96}, {26, 71}, {272, 61}, {329, 59}, {23, 25}, {85, 46}, {124, 48}, {169, 45}, {202, 48}, {301, 63}, {85, 22}, {125, 21}, {171, 18}, {202, 19}, {239, 17}, {262, 19}, {336, 22}};

#define DEPOSITNODES 2
int depositNodes[DEPOSITNODES] = {29,41};

#define OBJPOINTS 4
int objectPoints[OBJPOINTS] = {0,7,22,33};
int objectPointsSize[OBJPOINTS][2] = {{50,25},{25,25},{50,50},{50,50}};
/*
#define REDPOINTS 2
int redNodes[REDPOINTS] = {9,18};
#define BLUEPOINTS 3
int blueNodes[BLUEPOINTS] = {32, 43, 29};
#define BLACKPOINTS 1
int blackNodes[BLACKPOINTS] = {33};
*/
int cost[MAX][MAX];
void setCostValues(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            cost[i][j] = 9999;
        }
    }
cost[32][33] = 1;
cost[33][32] = 1;
cost[37][38] = 1;
cost[38][37] = 1;
cost[32][37] = 1;
cost[37][32] = 1;
cost[33][38] = 1;
cost[38][33] = 1;
cost[0][1] = 1;
cost[1][0] = 1;
cost[0][6] = 1;
cost[6][0] = 1;
cost[1][6] = 1;
cost[6][1] = 1;
cost[13][19] = 2;
cost[19][13] = 2;
cost[6][13] = 3;
cost[13][6] = 3;
cost[19][20] = 2;
cost[20][19] = 2;
cost[13][20] = 3;
cost[20][13] = 3;
cost[14][19] = 3;
cost[19][14] = 3;
cost[13][14] = 2;
cost[14][13] = 2;
cost[14][20] = 2;
cost[20][14] = 2;
cost[20][21] = 2;
cost[21][20] = 2;
cost[21][22] = 1;
cost[22][21] = 1;
cost[22][24] = 1;
cost[24][22] = 1;
cost[22][23] = 2;
cost[23][22] = 2;
cost[23][24] = 2;
cost[24][23] = 2;
cost[14][15] = 2;
cost[15][14] = 2;
cost[15][16] = 2;
cost[16][15] = 2;
cost[15][21] = 2;
cost[21][15] = 2;
cost[14][21] = 3;
cost[21][14] = 3;
cost[15][20] = 3;
cost[20][15] = 3;
cost[16][21] = 3;
cost[21][16] = 3;
cost[15][22] = 3;
cost[22][15] = 3;
cost[16][22] = 2;
cost[22][16] = 2;
cost[2][3] = 2;
cost[3][2] = 2;
cost[7][8] = 2;
cost[8][7] = 2;
cost[2][7] = 1;
cost[7][2] = 1;
cost[3][8] = 1;
cost[8][3] = 1;
cost[2][8] = 3;
cost[8][2] = 3;
cost[3][7] = 3;
cost[7][3] = 3;
cost[6][10] = 2;
cost[10][6] = 2;
cost[7][10] = 2;
cost[10][7] = 2;
cost[6][12] = 2;
cost[12][6] = 2;
cost[12][13] = 1;
cost[13][12] = 1;
cost[13][18] = 2;
cost[18][13] = 2;
cost[18][19] = 2;
cost[19][18] = 2;
cost[12][18] = 2;
cost[18][12] = 2;
cost[19][26] = 3;
cost[26][19] = 3;
cost[26][29] = 2;
cost[29][26] = 2;
cost[31][36] = 1;
cost[36][31] = 1;
cost[30][35] = 1;
cost[35][30] = 1;
cost[30][31] = 1;
cost[31][30] = 1;
cost[35][36] = 1;
cost[36][35] = 1;
cost[20][31] = 1;
cost[31][20] = 1;
cost[39][40] = 3;
cost[40][39] = 3;
cost[27][40] = 3;
cost[40][27] = 3;
cost[38][39] = 3;
cost[39][38] = 3;
cost[31][32] = 1;
cost[32][31] = 1;
cost[36][37] = 1;
cost[37][36] = 1;
cost[31][37] = 1;
cost[37][31] = 1;
cost[32][36] = 1;
cost[36][32] = 1;
cost[28][41] = 2;
cost[41][28] = 2;
cost[24][27] = 1;
cost[27][24] = 1;
cost[24][25] = 1;
cost[25][24] = 1;
cost[27][34] = 1;
cost[34][27] = 1;
cost[25][34] = 1;
cost[34][25] = 1;
cost[24][34] = 1;
cost[34][24] = 1;
cost[25][27] = 1;
cost[27][25] = 1;
cost[28][34] = 1;
cost[34][28] = 1;
cost[17][23] = 1;
cost[23][17] = 1;
cost[11][17] = 2;
cost[17][11] = 2;
cost[5][11] = 1;
cost[11][5] = 1;
cost[4][5] = 1;
cost[5][4] = 1;
cost[4][9] = 1;
cost[9][4] = 1;
cost[8][9] = 2;
cost[9][8] = 2;
cost[3][9] = 2;
cost[9][3] = 2;

    }

