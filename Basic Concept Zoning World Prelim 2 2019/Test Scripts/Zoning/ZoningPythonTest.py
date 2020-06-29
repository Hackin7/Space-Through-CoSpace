import sys
sys.path.append('./Python_Libraries/')
from hppToMap import readMapData
data = readMapData("../World2/w2map.hpp") 

X, Y = 10,10#len(data), len(data[0])
visited = [[0 for i in range(Y)] for i in range(X)]



def bfs(startX, startY, floodval):
    dirNo = 4
    dx = [0, 0, 1, -1, 1, 1, -1, -1]
    dy = [1, -1,  0, 0, 1, -1, 1, -1]
    queue = []
    queue.insert(0, (startX, startY))
    while len(queue) > 0:
        print(len(queue))
        x,y = queue.pop()
        visited[x][y] = floodval
        for d in range(dirNo):
            newX = x+dx[d]
            newY = y+dy[d]
            if 0 < newX < X and 0 < newY < Y \
               and data[x][y] == data[newX][newY] \
               and visited[newX][newY] == 0:
                queue.insert(0, (newX,newY))
        

    
counter = 1
for x in range(X):
    for y in range(Y):
        if visited[x][y] != 0: continue
        else:
            bfs(x, y, counter)
            counter += 1
        

print(f"Number of zones: {counter}")
