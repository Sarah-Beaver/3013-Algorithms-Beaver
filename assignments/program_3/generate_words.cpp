//Name: Sarah Beaver
//Date: February 26, 2018
//Assignment : Program 3
//	Description :
//	  creating crazy words from adverbs, adjectives, animals, nouns, and verbs
#include<iostream>
#include <fstream>
#include <time.h>
#include <string>
#include<vector>
#include <stdlib.h>     
#include <time.h>
using namespace std;

int main()
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
	ofstream output;
	output.open("tenthousandwords.txt");

	//lists to hold each type of word and the final word
	vector<string>animallist;
	vector<string>adverblist;
	vector<string>adjectivelist;
	vector<string>nounlist;
	vector<string>verblist;
	vector<string> words;
	//holds a word and used to create crazy words
	string s;
	srand(57);

	//inserting the words into apprpiate lists
	while (animal.good())
	{
		animal >> s;
		animallist.push_back(s);
	}
	while (adverb.good())
	{
		adverb >> s;
		adverblist.push_back(s);
	}
	while (adjective.good())
	{
		adjective >> s;
		adjectivelist.push_back(s);
	}
	while (noun.good())
	{
		noun >> s;
		nounlist.push_back(s);
	}
	while (verb.good())
	{
		verb >> s;
		verblist.push_back(s);
	}

	//creating 10000 crazy words
	for (int i = 0; i < 10000; i++)
	{
		//7 is number of different random possibilities
		int j = rand() % 7;
		int spot;
		//adv adj animal
		if (j==1)
		{
			
			spot = rand() % adverblist.size();
			s += adverblist[spot] + " ";
			spot = rand() % adjectivelist.size();
			s += adjectivelist[spot] + " ";
			spot = rand() % animallist.size();
			s += animallist[spot] + " ";
		}
		// adj verb adv noun
		else if (j == 2)
		{
			spot = rand() % adjectivelist.size();
			s += adjectivelist[spot] + " ";
			spot = rand() % verblist.size();
			s += verblist[spot] + " ";
			spot = rand() % adverblist.size();
			s += adverblist[spot] + " ";
			spot = rand() % nounlist.size();
			s += nounlist[spot] + " ";
		}
		//adjective adjective noun
		else if (j == 3)
		{
			spot = rand() % adjectivelist.size();
			s += adjectivelist[spot] + " ";
			spot = rand() % adjectivelist.size();
			s += adjectivelist[spot] + " ";
			spot = rand() % nounlist.size();
			s += nounlist[spot] + " ";
		}
		//noun adjective noun
		else if (j == 4)
		{
			spot = rand() % nounlist.size();
			s += nounlist[spot] + " ";
			spot = rand() % adjectivelist.size();
			s += adjectivelist[spot] + " ";
			spot = rand() % nounlist.size();
			s += nounlist[spot] + " ";
		}
		//adv verb animal
		else if (j == 5)
		{
			spot = rand() % adverblist.size();
			s += adverblist[spot] + " ";
			spot = rand() % verblist.size();
			s += verblist[spot] + " ";
			spot = rand() % animallist.size();
			s += animallist[spot] + " ";
		}
		//adv adv verb animal
		else if(j==6)
		{
			spot = rand() % adverblist.size();
			s += adverblist[spot] + " ";
			spot = rand() % adverblist.size();
			s += adverblist[spot] + " ";
			spot = rand() % verblist.size();
			s += verblist[spot] + " ";
			spot = rand() % animallist.size();
			s += animallist[spot] + " ";
		}
		//adv adj verb animal
		else 
		{
			spot = rand() % adverblist.size();
			s += adverblist[spot] + " ";
			spot = rand() % adjectivelist.size();
			s += adjectivelist[spot] + " ";
			spot = rand() % verblist.size();
			s += verblist[spot] + " ";
			spot = rand() % animallist.size();
			s += animallist[spot] + " ";
		}
		bool check = false;
		//looking for duplicates in the list;
		for (int j = 0; j < words.size(); j++)
		{
			if (s == words[j])
				check = true;
		}
		//if check is true means was a duplicate and decrease i for another loop
		if (check == true)
			i--;
		//else outputs the word
		else
		{
			output << s << "\n";
		}
		s = "";
	
	}
}
