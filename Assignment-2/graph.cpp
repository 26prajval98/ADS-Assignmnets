#include "graph.h"

using namespace std;

void generate_graph(int nodes, int avg_degree, int weight0, int weight1)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::ofstream graph_file("graph.txt");

	graph_file << nodes << std::endl;

	for (int i = 0; i < nodes; i++)
	{
		std::normal_distribution<> d(avg_degree, 2);

		int deg = (int)d(gen);

		graph_file << deg << std::endl;

		for (int j = 0; j < deg; j++)
		{
			int wt = weight0 + rand() % (weight1 - weight0 + 1);
			int node = rand() % nodes;
			graph_file << node << " " << wt << std::endl;
		}
	}

	graph_file.close();
}

graph_node *add_to_graph(graph_node *list, int data, int key)
{
	graph_node *item = (struct graph_node *)malloc(sizeof(struct graph_node)), *t;
	item->next = NULL;
	item->data = data;
	item->key = key;

	if (list == NULL)
	{
		return item;
	}

	t = list;

	while (t->next != NULL)
	{
		t = t->next;
	}
	t->next = item;

	return list;
}

graph_node **read_graph()
{
	std::ifstream graph_file("graph.txt");

	int nodes, x, y;

	graph_file >> nodes;

	struct graph_node **graph = (struct graph_node **)malloc(nodes * sizeof(struct graph_node *));

	for (int i = 0; i < nodes; i++)
	{
		int deg;

		graph_file >> deg;

		graph[i] = NULL;

		for (int j = 0; j < deg; j++)
		{
			graph_file >> x >> y;
			graph[i] = add_to_graph(graph[i], x, y);
		}
	}

	graph_file.close();
	
	return graph;
}