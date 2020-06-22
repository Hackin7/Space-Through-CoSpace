# 4: World 2 Strategies

![](https://lh6.googleusercontent.com/XKvGEojuEI_hubF8GK0t-RT1MQ7eVoaGfLeuEyiaBMhWhJgWHrNbo-7EOkRSm0AioVk11zaUoOXKyZ3GHO-97hFSs2xsXFq10r2yiiubLWOkhW6lSCkbuP8krQqaDMiYB8BQFXA6)

With world 2, you are now able to use PositionX and Position Y variables to tell you the coordinates

## 4.1 Border Avoiding

As you can see, unlike in World 1, World 2 does not have a border around the map. This means that if the robot goes out of the map, the robot would be relocated and get a time penalty of 10 seconds.

To avoid this you can get the robot to move inside when
-   It is located very close to the border of the map (Use PositionX and Position Y to check)
-   It is facing towards outside the map (Use Compass to check)
-   Additionally you can check if it is moving outside (You can check if both Wheels are positive or negative), but usually the robot moves in the direction it faces, and doesn’t really reverse

## 4.2 Trigonometry

In world 2, since you have the coordinates of the robot, and you are also given the map, technically, you can get the robot to move from 1 position to another. But how?

Well with the power of Trigonometry (more specifically tangent inverse), you can.

![](https://docs.google.com/drawings/u/0/d/s-xRX30RggKsuiu65etG1aA/image?w=383&h=257&rev=69&ac=1&parent=1mC5qfia8kMSgHi26EDHr_7Z0IXQVDEcwk-2YxLMxEao)

In this case to find θ, you can get the tangent inverse of (y2-y1)/(x2-x1). In C++, you can use the [arctan function](http://www.cplusplus.com/reference/cmath/atan/) to do just that. Take note to set your variable type to double.

After that, using the robot’s compass, you can turn the robot to that angle and move to that location

-   If the robot’s angle is within a certain range, move straight
-   If the robot’s angle is not in the range, turn till the robot is at that angle

Take note:

-   The compass of the robot is in the manner below, so you have to calculate the respective compass angle from θ
    
![](https://docs.google.com/drawings/u/0/d/seA0rIF_MhX2At1sLCZwUmQ/image?w=260&h=243&rev=53&ac=1&parent=1mC5qfia8kMSgHi26EDHr_7Z0IXQVDEcwk-2YxLMxEao)

-   You have to think about whether is it more optimal to turn clockwise/ anticlockwise
-   The degree of turning? The greater the angle difference the faster the turning    
-   Can the robot move while turning?

## 4.3 Dijkstra

First you should understand more about graph theory from here: [https://drive.google.com/drive/folders/1mzbcjnSuOJTX0PlfYSuxFG_Nk5Rl4qdd](https://drive.google.com/drive/folders/1mzbcjnSuOJTX0PlfYSuxFG_Nk5Rl4qdd)

However, using Trigo to move to one place to another (and manually coding moving 1 place to another) can be very tedious. Hence, we use Dijkstra, a Path finding algorithm. (You can copy online)

Since we are given the World 2 Map beforehand, we set nodes at each point (To manuvere around the obstacles). After that, to get from one position to another, find the shortest path (With dijkstra), and use Trigo to move the robot from 1 node to another

![](https://lh3.googleusercontent.com/qYmeh5gxRJsOQQYy8C7UBDwdE4SaZBgVh7XBGjnk8gNvSmMcnJHaD7mK10hr4TnD0_rI5n0m5ukdrSEmwmgR7leqnNTsoLn8G2T0M113x6fE2CwCEqstm7snuTiY5BAK7wAK3VmN)

Map of all the nodes

Our seniors (NYCasuals 2018) had python code to generate the nodes and costs. It is given in `CreateNodes.py`

Things to think about
-   What if your robot gets displaced significantly?
-   Just keep recalculating Dijkstra on the Fly
-   What about going to a specific coordinate, not just node
-   Trigo to the node, thn trigo to the coordinate

Sample Dijkstra Code (Or you can copy the algorithm online)
```
#define UINT_MAX 4294967295;
int pathLength;
int pathNodes[1000];
int pathCost = 0;
void dijkstra(int G[MAX][MAX], int n, int startnode, int endnode)
{
    int infinity = 9999;
	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i,j;
	for(i=0;i < n;i++)
		for(j=0;j < n;j++)
			if(G[i][j]==0)
				cost[i][j]=infinity;
			else
				cost[i][j]=G[i][j];

	for(i=0;i< n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count < n-1){
		mindistance=infinity;
		for(i=0;i < n;i++)
			if(distance[i] < mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
		visited[nextnode]=1;
		for(i=0;i < n;i++)
			if(!visited[i])
				if(mindistance+cost[nextnode][i] < distance[i])
				{
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}
			count++;
	}

	for(i=0;i < n;i++)
		if(i!=startnode && i==endnode)
		{
			printf("\nDistance of %d = %d", i, distance[i]);
			pathCost = distance[i];

			for(int k=0;k< 1000;k++)
            {
                pathNodes[k] = 0;
            }

			printf("\nPath = %d", i);
            pathLength = 0;
			pathNodes[pathLength] = i;
			j=i;
			do
			{
				j=pred[j];
				pathLength++;
				pathNodes[pathLength] = j;
				printf(" <-%d", j);
			}
			while(j!=startnode);
		}
}
```

## 4.4 Bitmapping and A* Pathfinding

Gradually, setting all the positions and edges of the nodes by hand becomes very tedious. Hence, a way to overcome that is to use bitmapping. This refers to basically taking in a raw image and generating a map array for use in the C++ program. This can be done with the help of the Python Imaging Library or `Pillow`.

After that, another suitable pathfinding algorithm, A*, would be used to calculate the shortest distance to move the robot.