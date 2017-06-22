#include<iostream>
#include "WaypointCalc.h"

void WaypointCalc::PushWaypoint(std::string Latitude, std::string Longitude)
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
	if(waypointsWriteIndex >= 2 && waypointsReadIndex <= waypointsWriteIndex - 1)
	{
		
	}
	else
	{
		std::cout<<"ERROR: Not enough points have been loaded into the queue\n";
	}
	return 0.0;
}
