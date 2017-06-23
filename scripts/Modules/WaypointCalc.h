#ifndef WAYPOINTCALC_H
#define WAYPOINTCALC_H

//Constants
#define MAXPOINTS 10

//Global Variables
struct waypoint {
	float Latitude;
	float Longitude;
	bool Valid;
};

class WaypointCalc
{
	private:
		waypoint waypoints[MAXPOINTS];	
		int waypointsWriteIndex;
		int waypointsReadIndex;

	public: 
		void PushWaypoint(float Latitude, float Longitude);
		void PopWaypoint(); 
		void ReadCurrentWaypoint();
		float GetBearing();
};

#endif
