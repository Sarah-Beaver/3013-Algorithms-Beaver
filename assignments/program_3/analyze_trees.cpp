//Name: Sarah Beaver
//Date: February 26, 2018
//Assignment : Program 3
//	Description :
//	  using crazy words to compare avl and binary search trees.
#include<iostream>
#include<fstream>
#include "avlTree.h"
#include "BStree.h"
#include <string>


int main(int argc, char **argv)
{
	ifstream animal;
	animal.open("animal.txt");
	ifstream adverb;
	adverb.open("adverb.txt");
	ifstream adjective;
	adjective.open("adjectives.txt");
	ifstream noun, verb;
	noun.open("noun.txt");
	verb.open("verb.txt");
	ofstream out;
	out.open("analysis.out");
	string s;
	string type;
	int numOfAdj=0, numOfAdv=0, numOfAnimal=0, numOfVerb=0, numOfNoun=0,bst=0,avl=0;
	BSTree binarysearch;
	avlTree avlsearch;
	// file pointer
	ifstream fin;

	// count command line args and make sure 
	// a file name is on the line to run this file
	if (argc<2) {
		cout << "You need an input file!\n";
		cout << "Usage: stlmap filename.txt";
		exit(0);
	}

	// open file from command line
	fin.open(argv[1]);

	//inserting the words into the trees
	type = "adjective";
	while (adjective >> s)
	{
		
		binarysearch.insert(s, type);
		avlsearch.insert(s, type);
	}

	type = "adverb";
	while (adverb >> s)
	{
		
		binarysearch.insert(s, type);
		avlsearch.insert(s, type);
	}

	type = "animal";
	while (animal >> s)
	{
		binarysearch.insert(s, type);
		avlsearch.insert(s, type);
	}

	type = "noun";
	while (noun >> s)
	{

		binarysearch.insert(s, type);
		avlsearch.insert(s, type);
	}

	type = "verb";
	while (verb >> s)
	{

		binarysearch.insert(s, type);
		avlsearch.insert(s, type);
	}


	//getting each word and getting number of comparisons to find each word
	while (fin>>s)
	{
		//adding number of comparison to find each word in bstree and avltree
		bst += binarysearch.find(s);
		avl += avlsearch.search(s,type);
		//checking for which type it is
		if (type == "verb")
		{
			numOfVerb++;
		}
		else if (type == "adverb")
		{
			numOfAdv++;
		}
		else if (type == "adjective")
		{
			numOfAdj++;
		}
		else if (type == "noun")
		{
			numOfNoun++;
		}
		else if(type=="animal"){
			numOfAnimal++;
		}


	}

	//creating the output file
	out << "BST Comparisons = " << bst << "\n";
	out << "AVL Comparisons = " << avl << "\n";
	out << "Number of Adjectives = " << numOfAdj << "\n";
	out << "Number of Adverbs = " << numOfAdv << "\n";
	out << "Number of Nouns = " << numOfNoun << "\n";
	out << "Number of Verbs = " << numOfVerb << "\n";
	out << "Number of Animals = " << numOfAnimal << "\n";
}
