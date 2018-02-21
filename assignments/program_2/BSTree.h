//A binary search tree where everything on left is 
//smaller than parent, everything on right is greater than parent

#include <iostream>
#include <fstream>
#include <string>
#pragma once
using namespace std;

/**
* Class BSTree:
*
* Public Methods:
*    int count();

	void insert(int x);

	void deleteNode(int key);

	void minValue();

	int height(int key = -1);

	int top();

	void printLevelOrder();

	void GraphVizOut(string filename);
*/

struct node
{
	int data;
	node *left;
	node *right;
	node()
	{
		data = -1;
		left = NULL;
		right = NULL;
	}
	node(int x)
	{
		data = x;
		left = NULL;
		right = NULL;
	}
};

class BSTree
{
private:
	node * root;

	/**
	* Function count:
	*     counts the number of elements in the tree
	*
	* Params:
	*     node* root
	* Returns
	*      int -number of items in tree
	*/
	int count(node *root);

	/**
	* Function Insert:
	*      Inserts an item into the tree
	*
	* Params:
	*     node*& root, node*&temp
	* Returns
	*      void
	*/
	void insert(node *&root, node *&temp);

	/**
	* Function print_node:
	*     prints out the tree and states if its left child or right child
	*
	* Params:
	*     node* node, string label
	* Returns
	*      void
	*/
	void print_node(node *n, string label = "");

	/**
	* Function minVlueNode:
	*      finds the predecessor or successor for when deleting a nod
	*
	* Params:
	*     node* root
	* Returns
	*      node*
	*/
	node *minValueNode(node *root);

	/**
	* Function deleteNode:
	*     finds and deletes a key from the tree
	*
	* Params:
	*     node*& root,int key
	* Returns
	*      node*
	*/
	node *deleteNode(node *&root, int key);

	/**
	* Function height:
	*      calculates the height of the tree
	*
	* Params:
	*     node* root
	* Returns
	*      int
	*/
	int height(node *root);

	/**
	* Function printGivenLevel:
	*      print nodes at a given level
	*
	* Params:
	*     node* root, int level
	* Returns
	*      void
	*/
	void printGivenLevel(node *root, int level);

	//************************************************************************
	// Method to help create GraphViz code so the expression tree can
	// be visualized. This method prints out all the unique node id's
	// by traversing the tree.
	// Recivies a node pointer to root and performs a simple recursive
	// tree traversal.
	//************************************************************************
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);

	//************************************************************************
	// This method is partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	// Don't worry about what this method and the above method do, just
	// use the output as your told:)
	//************************************************************************
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);

public:
	BSTree();

	~BSTree();

	/**
	* Function count:
	*      calls private count to get number of items in tree
	*
	* Params:
	*     none
	* Returns
	*      int
	*/
	int count();

	/**
	* Function insert:
	*     calls real insert to insert x into tree
	*
	* Params:
	*    int x
	* Returns
	*      void
	*/
	void insert(int x);

	/**
	* Function deletNode:
	*      looks for key and calls real delete to delete key from tree
	*
	* Params:
	*     int key
	* Returns
	*      void
	*/
	void deleteNode(int key);

	/**
	* Function minValue:
	*      call real minValue and gets predecessor or sucessor
	*
	* Params:
	*     none
	* Returns
	*      void
	*/
	void minValue();

	/**
	* Function height:
	*     calls real height to get height of the tree
	*
	* Params:
	*     int key
	* Returns
	*      int
	*/
	int height(int key = -1);

	/**
	* Function top:
	*     returns value of root node
	*
	* Params:
	*     none
	* Returns
	*      int
	*/
	int top();

	/**
	* Function printLevelOrder:
	*      Function to line by line print level order traversal a tree
	*
	* Params:
	*     none
	* Returns
	*      none
	*/
	void printLevelOrder();

	//************************************************************************
	// Recieves a filename to place the GraphViz data into.
	// It then calls the above two graphviz methods to create a data file
	// that can be used to visualize your expression tree.
	//************************************************************************
	void GraphVizOut(string filename);
};

