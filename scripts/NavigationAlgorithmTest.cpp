#include<iostream>
#include "./Modules/WaypointCalc.h"

void PrintMenu()
{
	std::cout<<"Navigation Algroithm Test\n";
	std::cout<<"+: Add waypoint (Lat: xx.xxxxxx, Long: yy.yyyyyy)\n";
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
			wayptCalc.PushWaypoint("TestLat0", "TestLong0");	
//			wayptCalc.PushWaypoint("TestLat1", "TestLong1");	
		}
		else if(cmd.compare("r")==0)
		{
//			wayptCalc.ReadCurrentWaypoint();
		}
		else
		{
			std::cout<<"Invalid Command\n";
		}
	}
}

