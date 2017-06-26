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
	if(waypointsWriteIndex >= 2 && waypointsReadIndex < waypointsWriteIndex - 1)
	{
		float lat1 = waypoints[waypointsReadIndex].Latitude * M_PI / 180;
		float lon1 = waypoints[waypointsReadIndex].Longitude * M_PI / 180;
		float lat2 = waypoints[waypointsReadIndex+1].Latitude * M_PI / 180;
		float lon2 = waypoints[waypointsReadIndex+1].Longitude * M_PI / 180;
		/*
		float dy = lat2 - lat1;
		//std::cout<<"dy: " << dy;
		float dx = cosf(M_PI/180 * lat1)*(long2 - long1);
		//std::cout<<"dx: " << dx;
		angle = atan2f(dy, dx);		
		//std::cout<<"angle: " << angle;
		*/
		float dy = lon2 - lon1;
		//std::cout<<"dy: "<<dy;
		float x = cos(lat2) * sin(dy);
		//std::cout<<"X: " << x;
		float y = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dy);
		//std::cout<<"Y: " << y;
		//Convert back to degrees
		angle = atan2(x,y) * 180 / M_PI;
	}
  else
	{
		std::cout<<"ERROR: Not enough points have been loaded into the queue\n";
	}
	return angle;
}

float WaypointCalc::GetDistance(float altitude)
{
	float distance = 0.0;
	if(waypointsWriteIndex >= 2 && waypointsReadIndex < waypointsWriteIndex - 1)
	{
		float lat1 = waypoints[waypointsReadIndex].Latitude * M_PI / 180;
		float lon1 = waypoints[waypointsReadIndex].Longitude * M_PI / 180;
		float lat2 = waypoints[waypointsReadIndex+1].Latitude * M_PI / 180;
		float lon2 = waypoints[waypointsReadIndex+1].Longitude * M_PI / 180;

		float dx = lat2 - lat1;
		float dy = lon2 - lon1;

		float a = sin2(dx/2) + cos(lat1) * cos(lat2) * sin2(dy/2);
		float sa = sqrt(a);
		float ssa = sqrt(1-a);
		float c = 2 * atan2(sa, ssa);

		distance = altitude * c;
	}
	else
	{
		std::cout<<"ERROR: Not enough points have been loaded into the queue\n";
	}
	return distance;
}
