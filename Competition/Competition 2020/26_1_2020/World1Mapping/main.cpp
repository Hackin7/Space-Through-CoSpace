#include "Core/system.hpp"
using namespace std;
static constexpr bool ENABLEDEBUG=false;
//#undef printf
#undef assert
//#define printf(...) (void)0 //disable printf
#define assert(...) (void)0 //disable asserts


#include "Basic/movement.hpp"
#include "Basic/collectObject.hpp"

#include "CoordinateSystem/trigo.hpp"
#include "CoordinateSystem/posInfoLost.hpp"
#include "World1/w1map.hpp"
#include "World2/w2map.hpp"
#include "CoordinateSystem/location.hpp"

#include "Navigation/astar.hpp"
#include "Navigation/moveAStar.hpp"
#include "Navigation/cycle.hpp"

#include "World1/world1.hpp"

#include "World2/boundary.hpp"
#include "World2/superObj.hpp"
#include "World2/mapping.hpp"

#include "World2/world2.hpp"


extern "C" {
DLL_EXPORT char* GetDebugInfo()
{
	if(!ENABLEDEBUG) return (char*)(0);
	static char info[1024];
	//Debugging
	//sprintf(info,"going_to_place=%d;going_to_rand_pt=%d;going_to_super=%d;rDist[3]=%d;currLocIt->color=%d;SuperObjTimeout=%d;WallTimeout=%d;TrapTimeout=%d;loaded_objects[S]=%d;loaded_objects[R]=%d;loaded_objects[G]=%d;loaded_objects[B]=%d;loaded_objects[RG]=%d;loaded_objects[RB]=%d;loaded_objects[GB]=%d;loaded_objects[RGB]=%d;WheelLeft=%d;WheelRight=%d;PositionX1=%d;PositionY1=%d;",going_to_place,going_to_rand_pt,going_to_super,rDist[3],currLocIt->color,SuperObjTimeout,WallTimeout,TrapTimeout,loaded_objects[S],loaded_objects[R],loaded_objects[G],loaded_objects[B],loaded_objects[RG],loaded_objects[RB],loaded_objects[GB],loaded_objects[RGB],WheelLeft,WheelRight,PositionX1,PositionY1);
	return info;
}

} //extern "C"
