#pragma once
#include "Graph.h"

void fill_graph(Graph& g, List<string> tops,  string** input, int stringCount) {
	for (int i = 0; i < stringCount; i++) {
		g.setValue(tops.find(input[i][0]), tops.find(input[i][1]), atoi(input[i][2].c_str()));
	}
}

int max_flow(int V, Graph& graph)
{
	Graph* flow = new Graph(V);
	List<int>* shortestPath = new List<int>;
	shortestPath = graph.BFS(*flow);
	int* residualThroughput = new int[shortestPath->getSize() - 1];
	int to, from, min;
	while (!(shortestPath->isEmpty()) || shortestPath->getSize() == 1) {
		shortestPath = graph.BFS(*flow);
		residualThroughput = new int[shortestPath->getSize() - 1];
		if (shortestPath->isEmpty() || shortestPath->getSize() == 1)
			break;
		for (int i = 0; i < shortestPath->getSize() - 1; i++) {
			to = graph.getValue(shortestPath->at(i), shortestPath->at(i + 1));
			from = graph.getValue(shortestPath->at(i + 1), shortestPath->at(i));
			if (to != 0) {
				residualThroughput[i] = to - flow->getValue(shortestPath->at(i), shortestPath->at(i + 1));
			}
			else if (from != 0) {
				residualThroughput[i] = from - flow->getValue(shortestPath->at(i + 1), shortestPath->at(i));
			}
			else
				residualThroughput[i] = 0;
		}
		min = residualThroughput[0];
		for (int i = 0; i < shortestPath->getSize() - 1; i++) {
			if (residualThroughput[i] < min) {
				min = residualThroughput[i];
			}
		}
		for (int i = 0; i < shortestPath->getSize() - 1; i++) {
			to = flow->getValue(shortestPath->at(i), shortestPath->at(i + 1));
			from = flow->getValue(shortestPath->at(i + 1), shortestPath->at(i));
			if (from == 0)
				flow->setValue(shortestPath->at(i), shortestPath->at(i + 1), to + min);
			else
				flow->setValue(shortestPath->at(i + 1), shortestPath->at(i), from - min);
		}
	}
	int maxflow = 0;
	for (int i = 0; i < V; i++) {
		maxflow += flow->getValue(0, i);
	}
	delete flow;
	delete shortestPath;
	delete[] residualThroughput;
	return maxflow;
}