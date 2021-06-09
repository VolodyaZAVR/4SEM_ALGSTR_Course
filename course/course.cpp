#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "List.h"
#include "Graph.h"
#include "Edm-Karp.h"

using namespace std;

bool alreadyInList(List<string>& arr, string str) {
    for (int i = 0; i < arr.getSize(); i++) {
        if (arr[i] == str) {
            return true;
        }
    }
    return false;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    fstream f;

    f.open("input.txt");
    int stringCount = 0;
    string bufString;
    while (!f.eof()) {
        getline(f, bufString);
        stringCount++;
    }
    f.close();

    f.open("input.txt");
    string** input = new string * [stringCount];
    for (int i = 0; i < stringCount; i++) {
        input[i] = new string[3];
        for (int j = 0; j < 2; j++) {
            getline(f, bufString, ' ');
                input[i][j] = bufString;
        }
        getline(f, bufString);
        input[i][2] = bufString;
    }
    f.close();

    for (int i = 0; i < stringCount; i++) {
        for (int j = 0; j < 3; j++) {
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
    
    List<string> tops;
    for (int i = 0; i < stringCount; i++) {
        if (!alreadyInList(tops, input[i][0])) {
            tops.push_back(input[i][0]);
        }
        if (!alreadyInList(tops, input[i][1])) {
            tops.push_back(input[i][1]);
        }
    }
    int V = tops.getSize();
    Graph* g = new Graph(V);
    fill_graph(*g, tops, input, stringCount);
    int maxflow = max_flow(V, *g);
    cout << "Max flow: "<<maxflow << endl;
    return 0;
}