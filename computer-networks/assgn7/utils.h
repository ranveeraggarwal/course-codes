#include <string>
#include <sstream>

std::string intToBin(int); 						//Converts an integer to 8-bit string

struct route_pair
{
	std::string ip;								//Store the network IP
	std::string subnet;							//Store the subnet
	
	route_pair();								//Default constructor
	route_pair(std::string, std::string);		//Another constructor
	
	void getFormat();							//Get IP and subnet into a format such that neteork address can be got
	std::string networkAdd;						//Network address
};
