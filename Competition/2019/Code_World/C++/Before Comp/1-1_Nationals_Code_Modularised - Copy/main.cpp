#include "Core/system.hpp"
using namespace std;
static constexpr bool ENABLEDEBUG=false;
//#undef printf
#undef assert
//#define printf(...) (void)0 //disable printf
#define assert(...) (void)0 //disable asserts


#include "Basic/movement.hpp"
#include "Basic/collectObject.hpp"
#include "Basic/avoidTrap.hpp"
#include "World1/wallTracer.hpp"
#include "World1/world1.hpp"

#include "World2/trigo.hpp"
#include "World2/posInfoLost.hpp"
#include "World2/boundary.hpp"
#include "World2/Dijkstra/map.hpp"
#include "World2/Dijkstra/dijkstra.hpp"
#include "World2/Dijkstra/moveDijkstra.hpp"
#include "World2/Dijkstra/superObjDijkstra.hpp"
#include "World2/Dijkstra/collectionDijkstra.hpp"
#include "World2/Dijkstra/zoneDijkstra.hpp"
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