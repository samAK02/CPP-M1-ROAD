#ifndef GRAPH_HPP
#define GRAPH_HPP

#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

struct Arc {
    int start, end;
    float cost;
};

struct Graph{
    int nbNodes, nbArcs;
    vector<Arc> arcs;
    vector<vector<int>> nodes;
};

Graph initGraph(int nbNodes, int nbArcs);
void addArc(Graph& g, int n1, int n2, int cost);
void printGraph(Graph& g);
vector<int> DFS(Graph& g, int s);
Graph readGraph(string filename);



#endif
