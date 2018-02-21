
///////////////////////////////////////////////////////////////////////////////
// Title:           assignment 4
// Files:            BSTree.h, BSTree.cpp
// Semester:         Advanced Algortithms Spring 2018
//
// Author:           Sarah Beaver
// Email:            sbeaver57@yahoo.com
// Description:
//       fixed the deletion method and tested a Binary Search Tree
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BSTree.h"

//http://www.webgraphviz.com/

using namespace std;


int main()
{
	srand(2342);

	BSTree B;

	B.insert(38);
	B.insert(10);
	B.insert(29);
	B.insert(27);
	B.insert(5);
	B.insert(43);
	B.insert(36);
	B.insert(3);
	B.printLevelOrder();
	B.GraphVizOut("before.txt");

	 while(B.top()){
	     cout<<"removing: "<<B.top()<<endl;
	     B.deleteNode(B.top());
	 }


	B.GraphVizOut("after.txt");
	system("pause");
	return 0;
}
