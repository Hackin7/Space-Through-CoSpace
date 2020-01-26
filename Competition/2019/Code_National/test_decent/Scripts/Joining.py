import datetime
pathToCode = "../Code/"
filenames=['TEMPLATE_START',\
           'WallAvoiding',\
           'CollectObject',\
           'Game0',\
           'Game1/Trigo',\
           'Game1/PosInfoLost',\
           #'Game1/NodesANDCoordinates/2018',\
           #'Game1/NodesANDCoordinates/2019',\
           'Game1/NodesANDCoordinates/2019Fuller',\
           'Game1/dijkstra',\
           'Game1/moveDijkstra',\
           'Game1Strategies/BASEStrategies',\
#########################################################
           #'Game1Strategies/Yolo',\
           'Game1Strategies/GoToNode',\
           #'Game1Strategies/GoGetSuperObj',\
           'TEMPLATE_END']
counter = 0
with open("../ai.c", 'w') as outfile:
    outfile.write("// Time: "+str(datetime.datetime.now())+"\n")
    for fname in filenames:
        print(fname,":",counter)
        with open(pathToCode+fname+".c") as infile:
            for line in infile:
                outfile.write(line)
                counter+=1
print(str(datetime.datetime.now()))
