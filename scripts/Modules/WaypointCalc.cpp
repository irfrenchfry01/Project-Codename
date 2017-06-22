#include<iostream>
#include "WaypointCalc.h"

void PushWaypoint(std::string Latitude, std::string Longitude)
{
	if(waypointsWriteIndex < MAXPOINTS)
	{
		waypoint waypt = new waypoint;
		waypt.Latitude = Latitude;
		waypt.Longitude = Longitude;
		waypt.Valid = true;

		//Push into the array
		waypoints[waypointsWriteIndex] = waypt;
		waypointsIndex++;
		std::cout << "Waypoint Added\n";
	}
	else
	{
		std::cout << "ERROR: Waypoint list is full\n";
	}
}

void PopWaypoint()
{
	if(waypointsReadIndex <= waypointsWriteIndex)
	{
		waypoints[waypointsReadindex].Valid = false;
	  waypointsReadIndex++;
		std::cout << "Waypoint Removed\n";
	}
	else
	{
		std::cout << "ERROR: No waypoints in queue\n";
	}
}

void ReadCurrentWaypoint()
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

