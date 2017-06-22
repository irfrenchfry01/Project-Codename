#include<iostream>
#include "./Modules/WaypointCalc.h"
//test
void PrintMenu()
{
	std::cout<<"\nNavigation Algroithm Test\n";
	std::cout<<"+: Add waypoint (Lat: xx.xxxxxx, Long: yy.yyyyyy)\n";
	std::cout<<"-: Remove current waypoint\n";	
	std::cout<<"r: Read Current Waypoint\n";	
	std::cout<<"q: Quit\n";
}

std::string GetCommand()
{
	std::string cmd;
	std::getline(std::cin, cmd);
	//Remove the new line character at the end of the string
	//cmd.erase(cmd.size() - 1);
	return cmd;
}

int main()
{
	WaypointCalc wayptCalc;
	bool exit = false;
	std::string cmd = "";
	while(!exit)
	{
		PrintMenu();
		//Receive the command
		cmd = GetCommand();
		if(cmd.compare("q")==0)
		{
			std::cout<<"Exiting Script";
			exit = true;	
		}
		else if(cmd.compare("+")==0)
		{
			std::string lat;
			std::string lon;
			std::cout<<"Enter Latitude in the following format (xx.xxxxxx)\n";
			std::getline(std::cin, lat);
			std::cout<<"Enter Longitude in the following format (yy.yyyyyy)\n";
			std::getline(std::cin, lon);
			wayptCalc.PushWaypoint(lat, lon);
		}
		else if(cmd.compare("-")==0)
		{
			wayptCalc.PopWaypoint();
		}
		else if(cmd.compare("r")==0)
		{
			wayptCalc.ReadCurrentWaypoint();
		}
		else
		{
			std::cout<<"Invalid Command\n";
		}
	}
}

