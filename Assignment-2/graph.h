#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <assert.h>
#include <fstream>
#include <random>

void generate_graph(int nodes, int avg_degree, int weight0, int  weight1)
{
	assert(weight0 <= weight1);
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::ofstream graph_file("graph.file");

	graph_file << nodes << std::endl;

	for(int i = 0; i < nodes; i++)
	{
		std::normal_distribution<int> d(avg_degree, 0);

		int deg = d(gen);
		
		graph_file << deg << std::endl;
		
		for(int j = 0; j < deg; j++)
		{
			int wt = weight0 + rand() % (weight1 - weight0 + 1);
			int node = rand() % nodes;
			graph_file << node << wt << std::endl;
		}
		
	}
}

#endif