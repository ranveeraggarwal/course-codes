#include <string>

struct node
{
	int val; 		//Contains 0 or 1
	bool isIp;		//a 1 would man that an IP address has completed
	int index;		//index in the vector of ip/subnet pairs
	node* child0;	//pointer to child node 0
	node* child1;	//pointer to child node 1
	
	node(int v); 	//Constructor
};

struct trie
{
	node* root;							//Root node of the trie
	void insert(std::string, int);		//Insert a string
	int retrieve (std::string);			//Get a string
	
	trie();								//Default constructor
};
