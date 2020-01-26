'''
reached = input("reached")
counter = 0
while reached:
    rang=2
    randomstuff = [0,0],[0.1,1],[0.2,2],[0.3,3]
    coordinates = [0,0],[1,1],[2,2],[3,3]
    print((int(randomstuff[counter][0]*rang+coordinates[counter][0]),int(randomstuff[counter][1]*rang+coordinates[counter][1])))
    reach = input("reached")
    if reach:
        counter+=1
        if counter >= len(randomstuff):
            counter = 0

'''
'''
def angleRangeCheck(theta1 ,range):
    if ((theta1 + range)>360):
        return (Compass < (theta1 + range)%360 or Compass > (theta1 - range)%360)
    return (theta1 - range)%360<=Compass<=(theta1 + range)%360
'''
#import random
#l = [[random.random(), random.random()] for i in range(10)]
#str(l).replace("[","{").replace("]","}")
# {{0.6169011912620882, 0.41359524497141387}, {0.08755616375412689, 0.7009712280389377}, {0.7872038990460901, 0.4833193040772631}, {0.7350020616781006, 0.6070434995859642}, {0.14521003377638675, 0.07102237538339928}, {0.6808936060819739, 0.43353382884636915}, {0.5393546784424003, 0.4166507272523542}, {0.6348521888982387, 0.2724089257609801}, {0.740697955711559, 0.5928818961567596}, {0.9443143236809757, 0.1805145219031291}}
