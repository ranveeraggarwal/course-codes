#include "trie.h"
#include <iostream>
using namespace std;

node::node(int v)			//Constructor definition
{
	val = v;
	isIp = false;			//Defaulted to false
	index = -1;				//-1 by default
	this->child0 = NULL;	//Defaulted to NULL
	this->child1 = NULL;	//Defaulted to NULL
}

trie::trie()
{
	this->root = new node(0);	//Root by default
}

void trie::insert(string str, int ind)
{
	node* temp = root;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '1')
		{
			if (temp->child1 == NULL)
			{
				temp->child1 = new node(1);	//If no child1, create new
			}
			temp = temp->child1;			//Go to child1
		}
		else
		{
			if (temp->child0 == NULL)
			{
				temp->child0 = new node(0); //If no child0, create new
			}
			temp = temp->child0;			//Go to child0
		}
	}
	temp->index = ind;						//Insert current vector index
}

int trie::retrieve(string str)
{
	int res = -1;
	node* temp = root;
	for (int i = 0; i < str.length(); i++)
	{
		if (temp == NULL)
		{
			break;
		}
		if (str[i] == '1')
		{
			temp = temp->child1;			//If a 1 is seen, go to child1
		}
		else temp = temp->child0;			//Else go to child0
		if((temp != NULL) && (temp->index != -1))
		{
			res = temp->index;				//If we find required index, return it.
		}
	}
	return res;
}
