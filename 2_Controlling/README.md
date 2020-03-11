
# CoSpace Rescue Tutorial

2: Controlling Robot

We will be using the C++ template code from the previous lessons.

To manipulate the robot you have a whole bunch of variables to work with.
![](https://lh5.googleusercontent.com/U4B5KdPfSl2EGeETwz5DoW-jF1Xalb7DQ7mc3Yeg8WALJCnWKb72UL8zn5Uen37Jw-VuIVsFNn-GKIXOiXp_BxFd2h3inwpAqI0mu_4lbRNs_ymz8QoJWp4U0CShuipVC0ZB1bC6)

  

Man that’s a lot. However, we first must know what the robot has.

## Wheels

The robot has 2 wheels for left and right. You access these variables through WheelLeft and WheelRight. They are to be assigned integer values from -5 to 5, 5 is fastest speed forward, -5 is fastest speed backward, 0 is not moving.

So let’s write some code in ai.cpp!
```
void Game0(){
	WheelLeft = 5;
	WheelRight = 5;
}
```

Run the code in world 1

![](https://docs.google.com/drawings/u/0/d/sCw_NJWdnL2FGVkJy1MDR6w/image?w=267&h=208&rev=2&ac=1&parent=1Kfhepqx416POwdTQElWz_dDPmrLhhJeCxpRywlHVRJQ)

![](https://lh5.googleusercontent.com/OkPSyXCLq-MjdKk8laTGlLyL9ryhBRXHvx88WpytlM4omqC0IMCAvJfV227abxNeRQCj4zDGlhXQoz7dZXItocr_BtPrCCXGt0rsvQo67PuoiW_A8JV1fsmOJMHtdgoeqgwzv7AS)

  

## Turning

Set one wheel value to be the negative of the other to turn in place
```
void Game0(){
	WheelLeft = -5;
	WheelRight = 5;
}
```
  

Experiment with whatever values, to find out what kind of movement you want. Turn while moving straight? How to get a smaller degree turn? etc.
```
void Game0(){
	WheelLeft = 5;
	WheelRight = 3;
}
```
  
  

# Ultrasonic Sensors

US_Front, US_Left, US_Right for the front, right & left ultrasonic sensors respectively.

Speaking of which you know this window? You can use it to check your values

![](https://docs.google.com/drawings/u/0/d/sLu3eKaDdjMFRDrx7ISgo2A/image?w=275&h=422&rev=138&ac=1&parent=1Kfhepqx416POwdTQElWz_dDPmrLhhJeCxpRywlHVRJQ)

Position your robot and you can check your sensor readings

## Wall Avoiding

```
void Game0(){
	WheelLeft = 5;WheelRight=5;
	if (US_Front < 20){
		WheelLeft = -3;
		WheelRight = -3;
	}
}
```
![](https://lh3.googleusercontent.com/rG6SdwUdYj11mini0JvluAEcPBNqX4n7QDTv1_49gxgiwzv0Re9j8XjHum4A5zMye7j5qE76txS9WuE8O_kyOD_KaSNOAA-Y2xJEKWl8timhndeaulJHSycNDPNXsxcc53-wInJl)

## Other Applications

1.  How do you avoid a wall at the side?   
	a.  Hint: If Side Ultrasonic sensors measure a distance less than the acceptable one, turn ?
2.  When would you turn around completely?
    

# Colour Sensors

The robot has 2 colour sensors on the left and right, accessed by the variables CSLeft_R, CSLeft_G, CSLeft_B and CSRight_R, CSRight_G, CSRight_B.

## Stop when orange
What colour is orange? Let’s measure it for ourselves!
![](https://lh4.googleusercontent.com/_rt2yxvbX25_raXEcxuK4JFfmvxd63iShlI2BL4WTqHVhhteDn8PihI5C2NVM32CvvJDTW7GNHeocB9WHnY7ufOhDu2iv8LjiHsSdmJA1IWWtflWk_EZ-cd5fGAhZMmImXdq218R)

However, when the robot is moving, it isn’t likely to measure these exact values, as it may cast a shadow on itself, colour sensor may not detect properly due to movement, etc. Hence, What you want to do is let the robot stop moving when the colour detected is in a range

You can use either sensor to detect.
```
bool colorLeftCheck(int *color, int objRange){
	return (color[0] - objRange <= CSLeft_R && CSLeft_R <= color[0] + objRange &&
			color[1] - objRange <= CSLeft_G && CSLeft_G <= color[1] + objRange &&
			color[2] - objRange <= CSLeft_B && CSLeft_B <= color[2] + objRange
	);
}
bool colorRightCheck(int *color, int objRange){
	return (color[0] - objRange <= CSRight_R && CSRight_R <= color[0] + objRange &&
			color[1] - objRange <= CSRight_G && CSRight_G <= color[1] + objRange &&
			color[2] - objRange <= CSRight_B && CSRight_B <= color[2] + objRange
	);
}

bool colorCheck(int *color, int objRange){
	return ( colorLeftCheck(color, objRange) || colorRightCheck(color, objRange));
}

int depositOrange[3] = {235,148,0};
void Game0(){
	WheelLeft=5;WheelRight=5;
		if (colorCheck(depositOrange, 10)){
		WheelLeft=0;WheelRight=0;
	}
}
```
![](https://lh5.googleusercontent.com/lFozRIxAUuyOxWnPkKr8c_VT5p0SuO7N84O1Qhp0UJA3wia5mViToFwCX2DrBmMCd0t2WlJwpSMlRZDMVh0fMWJlj-AzELGzZu2uj_FxO_AAgB7hbaio607c8Xe_ITuuiroXlU_F)

## Other Applications
1.  How would you avoid yellow regions?
2.  Stay in light blue regions?

# LED
LED_1 = 0; for the LED on the robot to be off

LED_1 = 1; for the LED on the robot to blink

LED_1 = 2; for the LED on the robot to be constant (to deposit objects)

The usage of this is for the robot to collect & deposit objects around the map. More about this in later tutorials.

# Compass

Compass gives the angle that the front of the robot is pointing to in degrees. The top is 0 degrees, and it measures it anticlockwise to 359 degrees.

## Turn to Angle
The Basic Idea is that you can use it to turn to a certain angle to move to. You could read and test the sample code just to test.

# Position (Only for World 2)

Position_X, Position Y. The (0,0) coordinate starts from the bottom left corner

The X-Value goes from 0 to 360, while the Y-Value goes from 0 to 270

You can test the code in the corresponding folder on github to know more about how to get the position coordinates.

# Time Left
Time variable has the time passed since the game started in seconds. The main reason you want the time left is to teleport to world 2 early, or to plan strategies for collecting other objects

eg.
`if (Time > 180){Teleport = 1;}`

By the way, you can set Teleport from 1-4 to teleport to 4 different locations respectively, and you can only teleport after 3 min. After 5 min, CoSpace Simulator will automatically teleport you
