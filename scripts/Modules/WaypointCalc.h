#ifndef WAYPOINTCALC_H
#define WAYPOINTCALC_H

//Constants
#define MAXPOINTS 10

//Global Variables
struct waypoint {
	std::string Latitude;
	std::string Longitude;
	bool Valid;
};

waypoint waypoints[MAXPOINTS];	
int waypointsWriteIndex = 0;
int waypointsReadIndex = 0;

class WaypointCalc
{
	public:
		void PushWaypoint(std::string Latitude, std::string Longitude);
		void PopWaypoint(); 
		void ReadCurrentWaypoint();
};

#endif
