//Name: Sarah Beaver
//Date: February 26, 2018
//Assignment : Program 3
//	Description :
//	 avltree (balanced and complete binary search tree) whose node holds a string and what type it is
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;


/**
* Class avlTree:
*
* Public Methods:
*   void dumpTree();

void insert(string word,string type);

void showInorder();
void showPreorder();
void showPostorder();

int search(string word, string& t);

int height(int key = -1);

int treeHeight();

void remove(string word);

void graphVizMakeConnections(avlnode *avlnodePtr, ofstream &VizOut);

void GraphVizOut(string filename);
*/

struct avlnode{
		string value;
		string type;
		avlnode *left;
		avlnode *right;
		avlnode *parent;
		int avlValue;
		avlnode(string word, string t) {
			value = word;
			type = t;
			left = right = parent = NULL;
			avlValue = 0;
		}
};

class avlTree {

private:
	avlnode * root;
	//************************************************************************
	// Method Name: insert
	//
	// Private 
	//
	// Purpose: Inserts a avlnode into a binary tree
	//
	// Arguments: reference to the root, and a reference to the new avlnode
	//
	// Returns: Nothing.
	//*************************************************************************
	void insert(avlnode *&avlnodePtr, avlnode *&newavlnode) {

		if (avlnodePtr == NULL) {
			avlnodePtr = newavlnode;
		}
		else if (newavlnode->value == avlnodePtr->value) {
			return;
		}
		else if (newavlnode->value < avlnodePtr->value) {
			newavlnode->parent = avlnodePtr;
			insert(avlnodePtr->left, newavlnode);

		}
		else {
			newavlnode->parent = avlnodePtr;
			insert(avlnodePtr->right, newavlnode);
		}

	}
	//************************************************************************
	// Method Name: inorder,postorder,preorder (all the same)
	//
	// Public 
	//
	// Purpose: Traverses a binary tree 
	//
	// Arguments: integer to be placed in binary tree.
	//
	// Returns: Nothing.
	//*************************************************************************
	void inorder(avlnode *avlnodePtr) {
		if (avlnodePtr) {
			inorder(avlnodePtr->left);
			cout << avlnodePtr->value << " " << "(" << avlnodePtr->avlValue << ") ";
			inorder(avlnodePtr->right);
		}
	}
	void preorder(avlnode *avlnodePtr) {
		if (avlnodePtr) {
			cout << avlnodePtr->value << " " << "(" << avlnodePtr->avlValue << ") ";
			inorder(avlnodePtr->left);
			inorder(avlnodePtr->right);
		}
	}
	void postorder(avlnode *avlnodePtr) {
		if (avlnodePtr) {
			inorder(avlnodePtr->left);
			inorder(avlnodePtr->right);
			cout << avlnodePtr->value << " " << "(" << avlnodePtr->avlValue << ") ";
		}
	}

	//************************************************************************
	// Method Name: remove
	//
	// Private 
	//
	// Purpose: Actually removes a avlnode from a tree by pointer manipulation and
	//          frees the memory
	//
	// Arguments: address of avlnode to be deleted
	//
	// Returns: void 
	//*************************************************************************

	avlnode* remove(avlnode*& root, string key)
	{
		if (!root)
		{
			return NULL;
		}
		if (key < root->value)
		{
			cout << "going left" << endl;
			root->left = remove(root->left, key);
		}
		else if (key > root->value)
		{
			cout << "going right" << endl;
			root->right = remove(root->right, key);
		}
		else
		{
			if (root->left == NULL)
			{
				avlnode *temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == NULL)
			{
				avlnode *temp = root->left;
				delete root;
				return temp;
			}

			// avlnode with two children: Get the inorder successor (smallest
			// in the right subtree)
			avlnode *temp = predSuccessor(root);

			printavlnode(temp, "predSuccessor");

			// Copy the inorder successor's content to this avlnode
			root->value = temp->value;

			// Delete the inorder successor
			root->right = remove(root->right, temp->value);
		}
		return root;
	}

	avlnode* predSuccessor(avlnode *root)
	{
		avlnode *current = root;

		if (root->right)
		{
			current = root->right;
			while (current->left != NULL)
			{
				current = current->left;
			}
		}
		else if (root->left)
		{
			current = root->left;
			while (current->right != NULL)
			{
				current = current->right;
			}
		}

		return current;
	}
	void printavlnode(avlnode *n, string label = "")
	{
		if (label != "")
		{
			cout << "[" << label << "]";
		}
		cout << "[[" << n << "][" << n->value << "]]\n";
		if (n->left)
		{
			cout << "\t|-->[L][[" << n->left << "][" << n->left->value << "]]\n";
		}
		else
		{
			cout << "\t\\-->[L][null]\n";
		}
		if (n->right)
		{
			cout << "\t\\-->[R][[" << n->right << "][" << n->right->value << "]]\n";
		}
		else
		{
			cout << "\t\\-->[R][null]\n";
		}
	}
	//************************************************************************
	// Method Name: height
	//
	// Private 
	//
	// Purpose: Actually removes a avlnode from a tree by pointer manipulation and
	//          frees the memory
	//
	// Arguments: address of the root of the tree (or subtree)
	//
	// Returns: void 
	//*************************************************************************
	int height(avlnode *avlnodePtr) {
		int left_height = 0;
		int right_height = 0;
		if (avlnodePtr == NULL)
			return 0;
		else {
			left_height = height(avlnodePtr->left);
			right_height = height(avlnodePtr->right);
		}
		if (left_height>right_height)
			return 1 + left_height;
		else
			return 1 + right_height;
	}

	//************************************************************************
	// Method Name: computeAvlValues
	//
	// Private 
	//
	// Purpose: Private method to calculate the avl values of the entire tree.
	//
	// Arguments: address of a avlnode
	//
	// Returns: void 
	//*************************************************************************
	void computeAvlValues(avlnode *&avlnodePtr)
	{
		if (avlnodePtr) {
			computeAvlValues(avlnodePtr->left);
			computeAvlValues(avlnodePtr->right);
			avlnodePtr->avlValue = avlValue(avlnodePtr);
			if (avlnodePtr->avlValue > 1) {
				rotateLeft(avlnodePtr);
			}
			else if (avlnodePtr->avlValue < -1) {
				rotateRight(avlnodePtr);
			}
		}
	}
	//************************************************************************
	// Method Name: rotateLeft 
	//
	// Private 
	//
	// Purpose: Private method to perform a left rotation from a given position in a tree
	//
	// Arguments: address of a avlnode
	//
	// Returns: void 
	//*************************************************************************
	void rotateLeft(avlnode *&SubRoot)
	{


		if (leftHeavy(SubRoot->right)) {
			rotateRight(SubRoot->right);
		}

		avlnode *Temp;

		Temp = SubRoot->right;
		SubRoot->right = Temp->left;
		Temp->left = SubRoot;
		SubRoot = Temp;

		computeAvlValues(SubRoot);
	}
	//************************************************************************
	// Method Name: rotateRight 
	//
	// Private 
	//
	// Purpose: Private method to perform a right rotation from a given position in a tree
	//
	// Arguments: address of a avlnode
	//
	// Returns: void 
	//*************************************************************************
	void rotateRight(avlnode *&SubRoot)
	{
		if (rightHeavy(SubRoot->left)) {
			rotateLeft(SubRoot->left);
		}

		avlnode *Temp;

		Temp = SubRoot->left;
		SubRoot->left = Temp->right;
		Temp->right = SubRoot;
		SubRoot = Temp;

		computeAvlValues(SubRoot);
	}
	//************************************************************************
	// Method Name: avlValue
	//
	// Private 
	//
	// Purpose: Private method to calculate the avl value of a avlnode.
	//
	// Arguments: address of a avlnode
	//
	// Returns: void 
	//*************************************************************************
	int avlValue(avlnode *avlnodePtr)
	{
		return height(avlnodePtr->right) - height(avlnodePtr->left);
	}
	//************************************************************************
	// Method Name: doDumpTree 
	//
	// Private 
	//
	// Purpose: Private method to show the basic pointer structure of the tree. 
	//          Initially written to help with debugging.
	//
	// Arguments: address of a avlnode
	//
	// Returns: void 
	// Outputs: tree information
	//*************************************************************************
	void doDumpTree(avlnode *avlnodePtr)
	{
		if (avlnodePtr) {
			cout << "Add:    " << avlnodePtr << "\n"
				<< "Parent->" << avlnodePtr->parent << "\n"
				<< "Val:    " << avlnodePtr->value << "\n"
				<< "Avl:    " << avlnodePtr->avlValue << "\n"
				<< "Left->  " << avlnodePtr->left << "\n"
				<< "Right-> " << avlnodePtr->right << "\n\n";

			doDumpTree(avlnodePtr->left);
			doDumpTree(avlnodePtr->right);
		}
	}
	//************************************************************************
	// Method Name: leftHeavy,rightHeavy 
	//
	// Private 
	//
	// Purpose: Compares the subtrees of a avlnode to see which is taller
	//
	// Arguments: address of a avlnode
	//
	// Returns: true if (left/right) heavy 
	//
	//*************************************************************************
	bool leftHeavy(avlnode *avlnodePtr)
	{
		return height(avlnodePtr->left)>height(avlnodePtr->right);
	}

	bool rightHeavy(avlnode *avlnodePtr)
	{
		return height(avlnodePtr->right)>height(avlnodePtr->left);

	}

public:

	avlTree() {
		root = NULL;
	}
	~avlTree() {

	}
	
	void dumpTree() {
		cout << "---------------------------------" << endl;
		cout << "Root:   " << root << "\n";
		doDumpTree(root);
	};

	//************************************************************************
	// Method Name: insertavlnode
	//
	// Public 
	//
	// Purpose: Creates a new avlnode and assigns the passed in value to it. Subsequently
	//          calls insert to actually travers the binary tree and link the avlnode in
	//          proper location. 
	//
	// Arguments: integer to be placed in binary tree.
	//
	// Returns: Nothing.
	//*************************************************************************
	void insert(string word,string type) {
		avlnode *newavlnode;

		newavlnode = new avlnode(word,type);
		insert(root, newavlnode);
		computeAvlValues(root);
	}
	//************************************************************************
	// Method Name: inorder,postorder,preorder (all the same)
	//
	// Public 
	//
	// Purpose: Traverses a binary tree 
	//
	// Arguments: nothing
	//
	// Returns: Nothing.
	//*************************************************************************
	void showInorder() { inorder(root); }
	void showPreorder() { preorder(root); }
	void showPostorder() { postorder(root); }
	//************************************************************************
	// Method Name: searchavlnode
	//
	// Public 
	//
	// Purpose: Traverses a binary tree looking for a key value
	//
	// Arguments: integer to look for
	//
	// Returns: true if found, false otherwise 
	//*************************************************************************
	int search(string word, string& t) {
		avlnode *avlnodePtr = root;
		int compare = 0;
		while (avlnodePtr) {
			if (avlnodePtr->value == word)
			{
				t = avlnodePtr->type;
				return compare;
			}
				
			else if (word < avlnodePtr->value)
			{
				avlnodePtr = avlnodePtr->left;
				compare++;
			}
				
			else
			{
				avlnodePtr = avlnodePtr->right;
				compare++;
			}
				
		}
		return 0;
	}
	//************************************************************************
	// Method Name: remove
	//
	// Public 
	//
	// Purpose: Public method to call the private remove method
	//
	// Arguments: word
	//
	// Returns: void 
	//*************************************************************************
	void remove(string word) { root = remove(root, word); };
	//************************************************************************
	// Method Name: treeHeight
	//
	// Public 
	//
	// Purpose: Public method to call the private height method
	//
	// Arguments: none
	//
	// Returns: void 
	//*************************************************************************
	int treeHeight() {
		return height(root);
	}
	//************************************************************************
	// Method to help create GraphViz code so the expression tree can 
	// be visualized. This method prints out all the unique avlnode id's
	// by traversing the tree.
	// Recivies a avlnode pointer to root and performs a simple recursive 
	// tree traversal.
	//************************************************************************
	void graphVizGetIds(avlnode *avlnodePtr, ofstream &VizOut) {
		static int NullCount = 0;
		if (avlnodePtr) {
			graphVizGetIds(avlnodePtr->left, VizOut);
			VizOut << "avlnode" << avlnodePtr->value
				<< "[label=\"" << avlnodePtr->value << "\\n"
				<< "Avl:" << avlnodePtr->avlValue << "\\n"
				//<<"Add:"<<avlnodePtr<<"\\n"
				//<<"Par:"<<avlnodePtr->parent<<"\\n"
				//<<"Rt:"<<avlnodePtr->right<<"\\n"
				//<<"Lt:"<<avlnodePtr->left<<"\\n"
				<< "\"]" << endl;
			if (!avlnodePtr->left) {
				NullCount++;
				VizOut << "navlnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
			}
			graphVizGetIds(avlnodePtr->right, VizOut);
			if (!avlnodePtr->right) {
				NullCount++;
				VizOut << "navlnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;

			}
		}
	}
	//************************************************************************
	// This method is partnered with the above method, but on this pass it 
	// writes out the actual data from each avlnode.
	// Don't worry about what this method and the above method do, just
	// use the output as your told:)
	//************************************************************************
	void graphVizMakeConnections(avlnode *avlnodePtr, ofstream &VizOut) {
		static int NullCount = 0;
		if (avlnodePtr) {
			graphVizMakeConnections(avlnodePtr->left, VizOut);
			if (avlnodePtr->left)
				VizOut << "avlnode" << avlnodePtr->value << "->" << "avlnode" << avlnodePtr->left->value << endl;
			else {
				NullCount++;
				VizOut << "avlnode" << avlnodePtr->value << "->" << "navlnode" << NullCount << endl;
			}

			if (avlnodePtr->right)
				VizOut << "avlnode" << avlnodePtr->value << "->" << "avlnode" << avlnodePtr->right->value << endl;
			else {
				NullCount++;
				VizOut << "avlnode" << avlnodePtr->value << "->" << "navlnode" << NullCount << endl;
			}

			graphVizMakeConnections(avlnodePtr->right, VizOut);

		}
	}
	//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void graphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	graphVizGetIds(root, VizOut);
	graphVizMakeConnections(root, VizOut);
	VizOut.close();

}
};

