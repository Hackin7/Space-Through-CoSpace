// File: Game1NodesANDCoordinates/2019RCJDay2.c
#define MAX 49
int coordinates[MAX][2] = {{19, 245},
 {106, 251},
  {178, 251},
   {258, 252},
    {64, 228},
    {101, 229},
    {142, 227},
    {180, 227},
    {218, 228},
    {259, 228},
    {303, 228},
    {339, 245},
    {19, 202},
    {64, 201},
    {96, 193},
    {140, 202},
    {180, 202},
    {218, 203},
    {265, 194},
    {298, 203},
    {341, 198},
    {19, 160},
    {65, 156},
    {80, 152},
     {143, 157},
      {182, 159},
       {218, 158},
        {272, 161},
         {297, 161},
         {338, 157},
         {18, 119},
         {54, 120},
         {88, 120},
         {272, 120},
         {297, 118},
         {339, 117},
         {26, 76},
         {63, 76},
         {103, 95},
         {134, 83},
          {226, 83},
          {263, 91},
          {300, 93},
          {61, 60},
          {100, 60},
          {258, 60},
          {337, 79},
          {301, 57}};

#define DEPOSITNODES 2
int depositNodes[DEPOSITNODES] = {14,18};//,6};

#define OBJPOINTS 6
int objectPoints[OBJPOINTS] = {25,43,25,45,2,3};
int objectPointsSize[OBJPOINTS][2] = {{20,20},{20,20},{20,20},{20,20},{30,30},{30,30}};

#define BLACKNODES 3
int blackNodes[BLACKNODES] = {1,2,3};
int blackNodesSize[BLACKNODES][2] = {{30,30},{30,30},{30,30}};

#define REDNODES 2
int redNodes[REDNODES] = {28,18};
int redNodesSize[REDNODES][2] = {{30,30},{30,30}};
#define BLUENODES 2
int blueNodes[BLUENODES] = {30,20};
int blueNodesSize[BLUENODES][2] = {{30,30},{30,30}};



int cost[MAX][MAX];
void setCostValues(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            cost[i][j] = 9999;
        }
    }cost[0][4] = 1;
cost[4][0] = 1;
cost[4][5] = 1;
cost[5][4] = 1;
cost[5][6] = 1;
cost[6][5] = 1;
cost[6][7] = 1;
cost[7][6] = 1;
cost[7][8] = 1;
cost[8][7] = 1;
cost[8][9] = 1;
cost[9][8] = 1;
cost[9][10] = 1;
cost[10][9] = 1;
cost[10][11] = 1;
cost[11][10] = 1;
cost[0][12] = 1;
cost[12][0] = 1;
cost[12][21] = 1;
cost[21][12] = 1;
cost[11][20] = 1;
cost[20][11] = 1;
cost[20][29] = 1;
cost[29][20] = 1;
cost[19][20] = 1;
cost[20][19] = 1;
cost[19][28] = 1;
cost[28][19] = 1;
cost[28][34] = 1;
cost[34][28] = 1;
cost[34][35] = 1;
cost[35][34] = 1;
cost[35][46] = 1;
cost[46][35] = 1;
cost[42][46] = 1;
cost[46][42] = 1;
cost[46][47] = 1;
cost[47][46] = 1;
cost[45][47] = 1;
cost[47][45] = 1;
cost[41][45] = 1;
cost[45][41] = 1;
cost[41][47] = 1;
cost[47][41] = 1;
cost[41][42] = 1;
cost[42][41] = 1;
cost[33][41] = 1;
cost[41][33] = 1;
cost[27][33] = 1;
cost[33][27] = 1;
cost[40][41] = 1;
cost[41][40] = 1;
cost[40][45] = 1;
cost[45][40] = 1;
cost[26][27] = 1;
cost[27][26] = 1;
cost[25][26] = 1;
cost[26][25] = 1;
cost[24][25] = 1;
cost[25][24] = 1;
cost[23][24] = 1;
cost[24][23] = 1;
cost[23][32] = 1;
cost[32][23] = 1;
cost[32][38] = 1;
cost[38][32] = 1;
cost[38][39] = 1;
cost[39][38] = 1;
cost[39][44] = 1;
cost[44][39] = 1;
cost[43][44] = 1;
cost[44][43] = 1;
cost[37][38] = 1;
cost[38][37] = 1;
cost[36][37] = 1;
cost[37][36] = 1;
cost[36][43] = 1;
cost[43][36] = 1;
cost[30][36] = 1;
cost[36][30] = 1;
cost[30][31] = 1;
cost[31][30] = 1;
cost[22][31] = 1;
cost[31][22] = 1;
cost[13][22] = 1;
cost[22][13] = 1;
cost[12][13] = 1;
cost[13][12] = 1;
cost[37][44] = 1;
cost[44][37] = 1;
cost[38][43] = 1;
cost[43][38] = 1;
cost[38][44] = 1;
cost[44][38] = 1;
cost[37][43] = 1;
cost[43][37] = 1;
cost[42][45] = 1;
cost[45][42] = 1;
cost[42][47] = 1;
cost[47][42] = 1;
cost[14][15] = 1;
cost[15][14] = 1;
cost[15][16] = 1;
cost[16][15] = 1;
cost[16][17] = 1;
cost[17][16] = 1;
cost[17][18] = 1;
cost[18][17] = 1;
cost[15][24] = 1;
cost[24][15] = 1;
cost[16][25] = 1;
cost[25][16] = 1;
cost[17][26] = 1;
cost[26][17] = 1;
cost[15][25] = 1;
cost[25][15] = 1;
cost[16][24] = 1;
cost[24][16] = 1;
cost[17][25] = 1;
cost[25][17] = 1;
cost[16][26] = 1;
cost[26][16] = 1;
cost[1][4] = 1;
cost[4][1] = 1;
cost[1][5] = 1;
cost[5][1] = 1;
cost[1][6] = 1;
cost[6][1] = 1;
cost[2][6] = 1;
cost[6][2] = 1;
cost[2][7] = 1;
cost[7][2] = 1;
cost[2][8] = 1;
cost[8][2] = 1;
cost[3][8] = 1;
cost[8][3] = 1;
cost[3][9] = 1;
cost[9][3] = 1;
cost[3][10] = 1;
cost[10][3] = 1;
cost[0][1] = 2;
cost[1][0] = 2;
cost[3][11] = 2;
cost[11][3] = 2;
cost[1][2] = 1;
cost[2][1] = 1;
cost[2][3] = 1;
cost[3][2] = 1;

    }