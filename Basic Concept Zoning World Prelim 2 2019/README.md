# Sample CoSpace A* Pathfinding Code

Does all the things a typical CoSpace Rescue Simulation Robot should do, such as collecting SuperObjects, Depositing and Stuff.

## Usage
1. Colour the zones (where there are objects/ deposit areas) on an image with a paint software (like Microsoft Paint). The configured colours are (RGB)
  - (255,0,0) for a red object zone
  - (0,0,255) for a cyan object zone
  - (0,168,243) for a black object zone
  - (0,0,0) for walls, traps etc.
  - (0,255,0) for deposit regions
2. Run `Test Scripts/ConvertToBitmap.py` and put in the new image name.
3. Compile `Test Scripts/Zoning/zone.cpp` and run it
4. Run `Test Scripts/Zoning/ZoningShow.py`, and find out the zones
5. Open `World1/world1.hpp` and edit the Teleport variable to the appropriate teleport point on the map
6. Open `World2/world2.hpp`, and edit this code. Here's a sample
```
const int numberOfZones = 5;
int zoneCycle[numberOfZones][2] =  {
    //{Zone number, type}
    {10, 3}, // 3 for multiple objects zone
    {13, 2}, // 2 for black objects zone
    {11, 0}, // 0 for cyan objects zone
    {4, 1},  // 1 for red objects zone
    {1, 1}
};
```