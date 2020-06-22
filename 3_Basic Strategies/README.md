# 3: Basic Strategies

![](https://lh4.googleusercontent.com/TxPzr9lLRejnjfViQJFumKJgnkWV154T8-bcHGM2csyqK0r1LxEhFOYvt5ESEtSLBW7ROZ95oNTg41jxoFrTt_GHPtLGnMo1Sc1cDWboKNCH21ty_4xDGGclwWNCzjnVXMgfgdsc)

## 3.1 Wall Avoiding

The robot should avoid walls and potentially other robots running the code.

Some cases you can think about:

1.  If all ultrasonic sensor detect walls, the robot should probably reverse / turn around
2.  If only the left/right ultrasonic sensor detects a wall, the robot can turn away from the wall
3.  How much should it turn? (Depends on how close it is to the wall)

## 3.2 Trap Avoiding

If the colour sensors detect the yellow zone, it should turn away / reverse from the trap

You can think of the same cases as that in wall avoiding.

## 3.3 Collection of Objects

Around the map there are Red, Blue and Black objects. Each object collected would have a different amount of points. The robot can store a maximum of 6 objects at 1 time.

To collect objects, the robot needs to stop on/near the coloured object (Only 1 colour sensor needed to detect) and set the LED_1=1 for 2 or so seconds. The code in `3_Object Collection` is advised.

Some things to think about

1.  You can insert a counter variable(s) to keep track of the number (and even type) of objects currently held. If you already have 6 objects, you don’t need to connect more objects, for example
    

## 3.4 Deposition of Objects

Since the robot can only hold 6 objects at a time, to gain more points, the robot should deposit and remove all the objects it currently had. In return, it would gain points of the object it has collected.

eg. The robot has 100 points, 90 points from the objects it currently collected. By depositing, it would get 90 more points, 190 total

To deposit, the robot just needs to stay on the deposit zone for 2 or so seconds (Both colour sensors must be in the deposit zone), and set LED_1=2. The code in `4_Object Deposition` is advised.

Some things you can think about

1.  If only 1 sensor detects orange, just turn the robot in such that both sensors detect orange
    

## 2.7 Teleporting Robot to World 1

Usually after 3 minutes or so, you can teleport the robot to World 2. This is covered in the previous chapter
