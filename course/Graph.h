#pragma once
#include "List.h"

class Graph {
private:
    int** matrix;
    int size;
public:
    Graph(int);
    ~Graph();
    void setValue(int, int, int);
    int getValue(int, int);
    List<int>* BFS(Graph&);
    void print();
};

Graph::Graph(int _size) {
    this->size = _size;
    matrix = new int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Graph::setValue(int V1, int V2, int value) {
    matrix[V1][V2] = value;
}

int Graph::getValue(int V1, int V2) {
    return matrix[V1][V2];
}

List<int>* Graph::BFS(Graph& flow) {
    List<int> queue;
    List<int>* path = new List<int>;
    int* level = new int[size];
    bool* isVisited = new bool[size];
    int V, V0, V1, V2, u;
    level[0] = 0;
    std::fill(isVisited, isVisited + size, false);
    queue.push_back(0);
    isVisited[0] = true;
    while (!queue.isEmpty()) {
        u = queue.pop_front();;
        for (int i = 0; i < size; i++) {
            if (u == i)
                continue;
            V = matrix[u][i];
            V0 = flow.getValue(u, i);
            V1 = flow.getValue(i, u);
            V2 = matrix[i][u];
            if (!isVisited[i] && ((V != V0) || ((V2 != V1) && V1 != 0))) {
                queue.push_back(i);
                isVisited[i] = true;
                level[i] = level[u] + 1;
            }
        }
    }
    int max = level[size - 1];
    path->push_front(size - 1);
    while (max > 0) {
        for (int i = 0; i < size; i++) {
            V = matrix[i][path->at(0)];
            V0 = flow.getValue(i, path->at(0));
            V1 = flow.getValue(path->at(0), i);
            V2 = matrix[path->at(0)][i];
            if (level[i] == max - 1 && ((V != V0) || ((V2 != V1) && V1 != 0))) {
                if (level[i] == max - 1)
                {
                    path->push_front(i);
                    max--;
                    break;
                }
            }
        }
    }
    delete[] level;
    delete[] isVisited;
    return path;
}

void Graph::print() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}