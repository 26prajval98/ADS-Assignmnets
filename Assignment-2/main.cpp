#include <iostream>
#include <ctime>
#include "graph.h"
#include "binary_heap.h"
#include "binomial_heap.h"
#include "fibonacci_heap.h"

using namespace std;

#define INF 10000
#define ARR_SIZE 1

void print_into_file(string file_name, int **Nodes, int nodes)
{
	ofstream file(file_name);
	for (int i = 0; i < nodes; i++)
	{
		file << i << " , " << Nodes[i][0] << endl;
	}
	
	if(file.is_open())
		file.close();
		
	return;
}

void binary_heap_demo(graph_node **adj_list, int nodes, int s)
{
	clock_t start = clock();

	binary_heap Q;
	int **Nodes = (int **)malloc(nodes * sizeof(int *));

	for (int i = 0; i < nodes; i++)
	{
		Nodes[i] = (int *)malloc(ARR_SIZE * sizeof(int));
		Nodes[i][0] = (int)INF;
		// Nodes[i][1] = 1;
		// Nodes[i][2] = 0;
	}

	// Initialize source
	Nodes[s][0] = 0;

	// Create Min Binary Heap
	for (int i = 0; i < nodes; i++)
	{
		Q.insert(Nodes[i][0], i);
	}

	while (!Q.empty())
	{
		keyval temp = Q.extract_min();
		int i = temp.data;
		int dist = temp.key;

		Nodes[i][0] = dist;
		// Nodes[i][1] = 0;
		// Nodes[i][2] = 1;

		graph_node *t = adj_list[i];

		while (t != NULL)
		{
			int adj = t->data;
			int adj_dis = t->key;
			if (Nodes[adj][0] > dist + adj_dis)
			{
				Nodes[adj][0] = dist + adj_dis;
				Q.decrease_key(adj, dist + adj_dis);
			}
			t = t->next;
		}
	}

	clock_t end = clock();
	double time_e = (double)end - (double)start;
	cout << "Binary Heap Operations = " << Q.operations << " and time taken is :" << time_e << "ms" << endl;
	print_into_file("binary.txt", Nodes, nodes);
	return;
}

void binomial_heap_demo(graph_node **adj_list, int nodes, int s)
{
	binomial_heap Q;
	int **Nodes = (int **)malloc(nodes * sizeof(int *));

	for (int i = 0; i < nodes; i++)
	{
		Nodes[i] = (int *)malloc(ARR_SIZE * sizeof(int));
		Nodes[i][0] = (int)INF;
		// Nodes[i][1] = 1;
		// Nodes[i][2] = 0;
	}
	clock_t start = clock();

	// Initialize source
	Nodes[s][0] = 0;

	// Create Min Binomial Heap
	for (int i = 0; i < nodes; i++)
	{
		Q.insert(Nodes[i][0], i);
	}

	while (!Q.empty())
	{
		keyval temp = Q.extract_min();
		int i = temp.data;
		int dist = temp.key;

		Nodes[i][0] = dist;
		// Nodes[i][1] = 0;
		// Nodes[i][2] = 1;

		graph_node *t = adj_list[i];

		while (t != NULL)
		{
			int adj = t->data;
			int adj_dis = t->key;

			if (Nodes[adj][0] > dist + adj_dis)
			{
				Nodes[adj][0] = dist + adj_dis;
				Q.decrease_key(adj, dist + adj_dis);
			}
			t = t->next;
		}
	}

	clock_t end = clock();
	double time_e = (double)end - (double)start;
	cout << "Binomial Heap Operations = " << Q.operations << " and time taken " << time_e << "ms" << endl;;
	print_into_file("binomial.txt", Nodes, nodes);
	return;
}

void fibonacci_heap_demo(graph_node **adj_list, int nodes, int s)
{
	fibonacci_heap Q;
	int **Nodes = (int **)malloc(nodes * sizeof(int *));

	for (int i = 0; i < nodes; i++)
	{
		Nodes[i] = (int *)malloc(ARR_SIZE * sizeof(int));
		Nodes[i][0] = INF;
		// Nodes[i][1] = 1;
		// Nodes[i][2] = 0;
	}
	clock_t start = clock();

	// Initialize source
	Nodes[s][0] = 0;

	// Create Min Fibonacci Heap
	for (int i = 0; i < nodes; i++)
	{
		Q.insert(Nodes[i][0], i);
	}

	while (!Q.empty())
	{
		keyval temp = Q.extract_min();
		int i = temp.data;
		int dist = temp.key;
		Nodes[i][0] = dist;
		// Nodes[i][1] = 0;
		// Nodes[i][2] = 1;
		graph_node *t = adj_list[i];

		while (t != NULL)
		{
			int adj = t->data;
			int adj_dis = t->key;
			if (Nodes[adj][0] > dist + adj_dis)
			{
				Nodes[adj][0] = dist + adj_dis;
				Q.decrease_key(adj, dist + adj_dis);
			}
			t = t->next;
		}
	}


	clock_t end = clock();

	double time_e = (double)end - (double)start;
	cout << "Fibonacci Heap Operations =  = " << Q.operations << " and time taken " << time_e << "ms" << endl;
	print_into_file("fibonacci.txt", Nodes, nodes);
	return;
}

int main(int argc, char *argv[])
{
	int nodes = atoi((const char *)argv[1]);
	int avg_degree = atoi((const char *)argv[2]);
	int weight0 = atoi((const char *)argv[3]);
	int weight1 = atoi((const char *)argv[4]);

	generate_graph(nodes, avg_degree, weight0, weight1);
	graph_node **adj_list = read_graph();
	
	cout << endl <<"Started Binary Heap"<< endl;
	binary_heap_demo(adj_list, nodes, 0);
	cout << endl  <<"Started Binomial Heap"<< endl;
	binomial_heap_demo(adj_list, nodes, 0);
	cout << endl  <<"Started Fibonacci Heap"<< endl;
	fibonacci_heap_demo(adj_list, nodes, 0);
}