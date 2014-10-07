#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "trie.h"

using namespace std;

int main()
{
	vector <route_pair> table;
	string ip, subnet;
	cin >> ip >> subnet;
	while(1)							//Taking table inputs
	{
		cin >> ip;
		if (ip == "default")
		{
			break;
		}
		else
		{
			cin >> subnet;
			route_pair temp_pair(ip, subnet);
			table.push_back(temp_pair);
		}
	}
	
	trie* mainTrie = new trie();
	for (int i = 0; i < table.size(); i++)
	{
		mainTrie->insert(table[i].networkAdd, i);
	}									//Insert into trie
	
	int t;
    cin >> t;
    while (t--) 
    {
        string ip;
        cin >> ip;						//Get IP to check
        string oip = ip;
        string ipToken[4];
        int point = 0;
		for (unsigned int i = 0; i < ip.size(); i++)
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
		ip = "";
        for (int i = 0; i < 4; i++)
		{
			int tempIpToken;
			istringstream (ipToken[i]) >> tempIpToken;
			ip = ip + intToBin(tempIpToken);			//Tokenise, convert to integers, convert to binary string, get IP in binary form
		}
        int index = mainTrie->retrieve(ip);				//Retrieve IP from trie if present
        if (index == -1)
        {
			cout << oip << " default" << endl;
		}
        else
        {
            cout << oip << " " << table[index].ip << " " << table[index].subnet << endl;
		}
    }
}
