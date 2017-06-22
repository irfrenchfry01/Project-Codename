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

class WaypointCalc
{
	private:
		waypoint waypoints[MAXPOINTS];	
		int waypointsWriteIndex;
		int waypointsReadIndex;

	public: 
		void PushWaypoint(std::string Latitude, std::string Longitude);
		void PopWaypoint(); 
		void ReadCurrentWaypoint();
};

#endif
