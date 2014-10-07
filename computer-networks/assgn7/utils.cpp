#include "utils.h"
#include <iostream>
using namespace std;

route_pair::route_pair(){}							//default constructor definition

route_pair::route_pair(string ip, string subnet)	//constructor definiton
{
	this->ip = ip;
	this->subnet = subnet;
	networkAdd = "";
	getFormat();
}

string intToBin(int num)
{
	string res = string();
	while (1)
	{
		if (num <= 1)
		{ 
			res = "1" + res;
			break;
		}
		int temp = num%2;
		if (temp) res = "1" + res;
		else res = "0" + res;
		num = num/2;
	}
	int diff = 8 - res.size();
	for (int i = 0; i < diff; i++)
	{
		res = "0" + res;
	}
	return res;
}

void route_pair::getFormat()
{
	string ip = this->ip;
	string subnet = this->subnet;
	string ipToken[4];								//break IP, Subnet into tokens such that it's easier to access them
	string subnetToken[4];
	int point = 0;
	for (unsigned int i = 0; i < ip.size(); i++)	//Get IP tokens
	{
		if (i==0) 
		{
			ipToken[0] = ip[i];
		}
		else if (ip[i] == '.')
		{
			i++;
			point++;
			ipToken[point] = ip[i];
		}
		else ipToken[point] = ipToken[point] + ip[i];
	}
	point = 0;
	for (unsigned int i = 0; i < subnet.size(); i++) //Get Subnet tokens
	{
		if (i==0) 
		{
			subnetToken[0] = subnet[i];
		}
		else if (subnet[i] == '.')
		{
			i++;
			point++;
			subnetToken[point] = subnet[i];
		}
		else subnetToken[point] = subnetToken[point] + subnet[i];
	}
	ip = "";
	subnet = "";
	for (int i = 0; i < 4; i++)
	{
		int tempIpToken;
		int tempSubnetToken;
		istringstream (ipToken[i]) >> tempIpToken;
		istringstream (subnetToken[i]) >> tempSubnetToken;
		ip = ip + intToBin(tempIpToken);			 //Get tokens, convert to binary strings and completely change the address to binary
		subnet = subnet + intToBin(tempSubnetToken);
	}
	int i = 0;
	while(true)
	{
		if (i == 32) break;
		if (subnet[i] == '1')
		{
			networkAdd = networkAdd + ip[i];		//Get network address correspondin to subnet.
			i++;
		}
		else break;
	}
}
