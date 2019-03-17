#include <iostream>
#include "graph.h"
#include "binary_heap.h"

using namespace std;

#define INIFNITY 100000

void binary_heap_demo(graph_node **adj_list, int nodes, int s)
{
	binary_heap Q;
	int **Nodes = (int **)malloc(nodes * sizeof(int *));

	for (int i = 0; i < nodes; i++)
	{
		Nodes[i] = (int *)malloc(3 * sizeof(int));
		Nodes[i][0] = INFINITY;
		Nodes[i][1] = 1;
		Nodes[i][2] = 0;
	}

	// Initialize source
	Nodes[s][0] = 0;

	// Create Min Binary Heap
	for (int i = 0; i < nodes; i++)
	{
		Q.insert(Nodes[i][0], i);
	}

	while (Q.empty())
	{
		keyval temp = Q.extract_min();
		int i = temp.data;
		int dist = temp.key;

		Nodes[i][0] = dist;
		Nodes[i][1] = 0;
		Nodes[i][2] = 1;

		graph_node *t = adj_list[i];

		while (t != NULL)
		{
			int adj = t->data;
			int adj_dis = t->key;

			if (Nodes[adj][0] > dist + adj_dis)
				Q.decrease_key(adj, dist + adj_dis);
		}
	}

	return;
}

void binomial_heap_demo(graph_node **adj_list, int nodes, int s)
{
	binary_heap Q;
	int **Nodes = (int **)malloc(nodes * sizeof(int *));

	for (int i = 0; i < nodes; i++)
	{
		Nodes[i] = (int *)malloc(3 * sizeof(int));
		Nodes[i][0] = INFINITY;
		Nodes[i][1] = 1;
		Nodes[i][2] = 0;
	}

	// Initialize source
	Nodes[s][0] = 0;

	// Create Min Binary Heap
	for (int i = 0; i < nodes; i++)
	{
		Q.insert(Nodes[i][0], i);
	}

	while (Q.empty())
	{
		keyval temp = Q.extract_min();
		int i = temp.data;
		int dist = temp.key;

		Nodes[i][0] = dist;
		Nodes[i][1] = 0;
		Nodes[i][2] = 1;

		graph_node *t = adj_list[i];

		while (t != NULL)
		{
			int adj = t->data;
			int adj_dis = t->key;

			if (Nodes[adj][0] > dist + adj_dis)
				Q.decrease_key(adj, dist + adj_dis);
		}
	}

	return;
}

void fibonacci_heap_demo(graph_node **adj_list, int nodes, int s)
{
	binary_heap Q;
	int **Nodes = (int **)malloc(nodes * sizeof(int *));

	for (int i = 0; i < nodes; i++)
	{
		Nodes[i] = (int *)malloc(3 * sizeof(int));
		Nodes[i][0] = INFINITY;
		Nodes[i][1] = 1;
		Nodes[i][2] = 0;
	}

	// Initialize source
	Nodes[s][0] = 0;

	// Create Min Binary Heap
	for (int i = 0; i < nodes; i++)
	{
		Q.insert(Nodes[i][0], i);
	}

	while (Q.empty())
	{
		keyval temp = Q.extract_min();
		int i = temp.data;
		int dist = temp.key;

		Nodes[i][0] = dist;
		Nodes[i][1] = 0;
		Nodes[i][2] = 1;

		graph_node *t = adj_list[i];

		while (t != NULL)
		{
			int adj = t->data;
			int adj_dis = t->key;

			if (Nodes[adj][0] > dist + adj_dis)
				Q.decrease_key(adj, dist + adj_dis);
		}
	}

	return;
}

int main(int argc, char *argv)
{
	int nodes = atoi((const char *)argv[1]);
	int avg_degree = atoi((const char *)argv[2]);
	int weight0 = atoi((const char *)argv[3]);
	int weight1 = atoi((const char *)argv[4]);

	generate_graph(nodes, avg_degree, weight0, weight1);
	graph_node **adj_list = read_graph();
}