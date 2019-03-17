#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <random>

struct graph_node
{
	int key;
	int data;
	struct graph_node *next;
};

void generate_graph(int nodes, int avg_degree, int weight0, int weight1);
struct graph_node **read_graph();
#endif
