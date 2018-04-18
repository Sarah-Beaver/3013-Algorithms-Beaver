//Name: Sarah Beaver
//Class: Advanced Algorithms 
//Date: April 6, 2018
//Program 4: Using graphs to create paths between cities(vertixes) useing their lon and lat(edge). 
//Each city can only have at most three edges.
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include<queue>
#include "edge_heap.h"

using namespace std;
/*



*/

int main(int argc, char **argv)
{
	//starter state if nothing else chosen or bad choice
	string city = "Lebanon";
	string state = "KS";
	string county = "Smith";
	latlon st(39.809734, -98.55562);
	int maxedge = 3;
	ofstream output;
	output.open("output.txt", fstream::app);
	int numloop = 1;

	if (argc > 1 && argc<4) {
		state = argv[1];
		maxedge = (int)argv[2];
	}
	else {
		cout << "Usage: ./graph state(or ALL)" << endl;
		exit(0);
	}



	//if user selects all states then loops 5 times for each state
	if (state == "ALL" || state == "All")
		numloop = 5;
	//loop to loop for each state or just once
	for (int z = 0; z < numloop; z++)
	{
		double miles = 0;
		int edges = 0;
		vector<edge*> distances;
		queue<vertex *> list;
		vector<vertex *> cities;
		graph G;
		vertex* start;
	
		//checks if numloop equals 5 for five loops
		if (numloop == 5)
		{
			if (z == 1)
				state = "FL";
			else if (z == 2)
				state = "TX";
			else if (z == 3)
				state = "MA";
			else if (z == 4)
				state = "PR";
		}
		//checks if state is not Puerto Ricoo
		if (state != "PR")
		{
			G = loadGraphCSV("filtered_cities.csv");
			//checks for good choices else will default to KS, if good choice will find the right city
			if (state == "FL" || state == "TX" || state == "MA" || state == "OR") {
				for (int i = 0; i < G.vertexList.size(); i++)
				{
					if (state == "FL"&&G.vertexList[i]->city == "Miami Beach"&&G.vertexList[i]->state == "FL")
					{
						start = G.vertexList[i];
						city = "Miami Beach";
						break;
					}
					else if (state == "TX"&&G.vertexList[i]->city == "Lake Dallas"&&G.vertexList[i]->state == "TX")
					{
						start = G.vertexList[i];
						city = "Lake Dallas";
						break;
					}
					else if (state == "MA"&&G.vertexList[i]->city == "Boston"&&G.vertexList[i]->state == "MA") {
						start = G.vertexList[i];
						city = "Boston";
						break;
					}
					else if (state == "OR"&&G.vertexList[i]->city == "Oregon City"&&G.vertexList[i]->state == "OR") {
						start = G.vertexList[i];
						city = "Oregon City";
						break;
					}
				}
				cities = G.vertexList;
			}
			//defualts to Lebonan KS and adds it
			else
			{
				state = "KS";
				G.addVertex("Lebonan", "KS", "Smith", st.lat, st.lon);
				cities = G.vertexList;
				start = cities.back();
			}
		}
		//Add Puerto Rico cities only and find correct city to start with
		else
		{
			G = loadPRGraphCSV("filtered_cities.csv");
			for (int i = 0; i < G.vertexList.size(); i++)
			{
				if (G.vertexList[i]->state == "PR"&&G.vertexList[i]->city == "San Juan")
				{
					start = G.vertexList[i];
					city = "San Juan";
					break;
				}
			}
			cities = G.vertexList;
		}

		list.push(start);
		//loops while the queue is not empty
		while (!list.empty())
		{
			start = list.front();
			list.pop();
			//checking if has less than three edges
			if (start->E.size() < maxedge) {
				distances.push_back(nullptr);
				//loops through the cities to find closest ones
				for (int i = 0; i < cities.size(); i++)
				{
					//checks if it is same city as start, no loops to self
					if (cities[i]->ID == start->ID)
					{
						cities.erase(cities.begin() + i);
						i--;
					}
					//checks if city already has three edges
					else if (G.vertexList[cities[i]->ID]->E.size() >= maxedge)
					{
						cities.erase(cities.begin() + i);
						i--;
					}
					else
					{
						double temp;

						temp = distanceEarth(start->loc.lat, start->loc.lon, cities[i]->loc.lat, cities[i]->loc.lon);
						if (temp < 300)
							distances.push_back(new edge(cities[i]->ID, temp));
					}
				}
				//see how many edges has left
				int loop = maxedge - start->E.size();
				edgeHeap min;
				min.Heapify(distances, distances.size());

				//add appropiate amount of edges and makes sure dist has changed
				for (int i = 0; i < loop; i++)
				{
					edge* temp = min.Extract();
					if (temp)
					{
						if (list.size() < 3)
						{
							if ((G.vertexList[temp->toID]->E.size() < (maxedge-1)))
							{
								G.addEdge(start->ID, temp->toID, temp->weight);
								miles += temp->weight;
								edges++;
								if (G.vertexList[temp->toID]->E.size() < maxedge)
									list.push(G.vertexList[temp->toID]);
							}
							else
								break;

						}
						else
						{
							G.addEdge(start->ID, temp->toID, temp->weight);
							miles += temp->weight;
							edges++;
							if (G.vertexList[temp->toID]->E.size() < maxedge)
								list.push(G.vertexList[temp->toID]);
						}
					}
					else
						break;
				}
				min.Clear();
				distances.clear();
			}
		}
		if (state == "PR")
		{
			ofstream out;
			out.open("graph.txt");
			out << G.graphViz();
		}


		output << "- " << city << ", " << state << endl;
		output << "    " << miles << " miles " << edges << " edges" << endl;
		miles = 0;
		edges = 0;
	}
	return 0;

}
