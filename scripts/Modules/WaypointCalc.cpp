#include<iostream>
#include<math.h>
#include "WaypointCalc.h"

void WaypointCalc::PushWaypoint(float Latitude, float Longitude)
{
	if(waypointsWriteIndex < MAXPOINTS)
	{
		waypoint waypt;
		waypt.Latitude = Latitude;
		waypt.Longitude = Longitude;
		waypt.Valid = true;

		//Push into the array
		waypoints[waypointsWriteIndex] = waypt;
		waypointsWriteIndex++;
		std::cout << "Waypoint Added\n";
	}
	else
	{
		std::cout << "ERROR: Waypoint list is full\n";
	}
}

void WaypointCalc::PopWaypoint()
{
	if(waypointsReadIndex <= waypointsWriteIndex)
	{
		waypoints[waypointsReadIndex].Valid = false;
	  waypointsReadIndex++;
		std::cout << "Waypoint Removed\n";
	}
	else
	{
		std::cout << "ERROR: No waypoints in queue\n";
	}
}

void WaypointCalc::ReadCurrentWaypoint()
{
	if(waypoints[waypointsReadIndex].Valid == true)
	{
		std::cout<<"Latitude: " << waypoints[waypointsReadIndex].Latitude << "\n";
		std::cout<<"Longitude: " << waypoints[waypointsReadIndex].Longitude << "\n";
	}
	else
	{
		std::cout<<"ERROR: No valid waypoints in queue\n";
	}
}	

float WaypointCalc::GetBearing()
{
	float angle = 0.0;
	if(waypointsWriteIndex >= 2 && waypointsReadIndex <= waypointsWriteIndex - 1)
	{
		float lat1 = waypoints[waypointsReadIndex].Latitude;
		float long1 = waypoints[waypointsReadIndex].Longitude;
		float lat2 = waypoints[waypointsReadIndex+1].Latitude;
		float long2 = waypoints[waypointsReadIndex+1].Longitude;
		float dy = lat2 - lat1;
		//std::cout<<"dy: " << dy;
		float dx = cosf(M_PI/180 * lat1)*(long2 - long1);
		//std::cout<<"dx: " << dx;
		angle = atan2f(dy, dx);		
		//std::cout<<"angle: " << angle;
	}
  else
	{
		std::cout<<"ERROR: Not enough points have been loaded into the queue\n";
	}
	return angle;
}
