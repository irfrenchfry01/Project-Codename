#include<iostream>

void PrintMenu()
{
	std::cout<<"Navigation Algroithm Test\n";
	std::cout<<"+: Add waypoint (Lat: xx.xxxxxx, Long: yy.yyyyyy)\n";
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

void AddPoint()
{

}

int main()
{
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
		else
		{
			std::cout<<"Invalid Command\n";
		}
	}
}

