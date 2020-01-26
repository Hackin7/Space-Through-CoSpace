import datetime
pathToCode = "../Code/"
filenames=['TEMPLATE/TEMPLATE_START',\
           'Movements/WallAvoiding',\
           'CollectObject',\
           'Movements/TrapAvoiding',\
           'Movements/WallTracer',\
           'Game0',\
           'Game1/Trigo',\
           'Game1/PosInfoLost',\
           'Game1/boundary',\
########## NODES ##############5##########################
           #'Game1NodesANDCoordinates/2018',\
           #'Game1NodesANDCoordinates/2019',\
           #'Game1NodesANDCoordinates/2019Fuller',\
           'Game1NodesANDCoordinates/2019RCJDay1',\
########## Dijkstra ########################################           
           'Game1Dijkstra/dijkstra',\
           'Game1Dijkstra/moveDijkstra',\
           'Game1Dijkstra/superObjDijkstra',\
           'Game1Dijkstra/collectionDijkstra',\
           'Game1Dijkstra/zoneDijkstra',\
########## Strategies #####################################
           'Game1Strategies/BASEStrategies',\
           #'Game1Strategies/Yolo',\
           'Game1Strategies/GoToNode',\
           #'Game1Strategies/GoGetSuperObj',\
           'TEMPLATE/TEMPLATE_END']
counter = 0
with open("../ai.c", 'w') as outfile:
    outfile.write("// Time: "+str(datetime.datetime.now())+"\n")
    counter+=1
    for fname in filenames:
        outfile.write("// File: "+fname+".c\n")
        counter+=1
        print(fname,":",counter)
        with open(pathToCode+fname+".c") as infile:
            for line in infile:
                outfile.write(line)
                counter+=1
print(str(datetime.datetime.now()))
