#define GRAPH_HPP

// Binôme: AKRETCHE Ales Samy - LARRUE Joris
#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

struct Arc {
    int start, end;
    float cost;
    int cap, flow;
    int capRes, indx;
    bool isInv;

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
void DijkstraVec(Graph& g, int s, vector<float>& dist, vector<int>& pred);
bool checkCondDijkstra(Graph& g);
void DijkstraTas(Graph& g, int s, vector<float>& dist, vector<int>& pred);
int BellmanFord(Graph& g, int s, vector<float>& dist, vector<int>& pred);
void addNetworkArc(Graph& g, int start, int end, int cap);
Graph readNetwork(string filename);
void makeResidual(Graph& g);
vector<int> reverseBfs(Graph& g, int t);
int findAdmissibleArc(Graph& g, vector<int>& dist, int i);
int relabel(Graph& g, vector<int>& dist, int i);
int computeDelta(Graph& g, int s, int t, vector<int>& pred);
void augmentFlow(Graph& g, int s, int t, vector<int>& pred, int delta);
int EdmondsKarp(Graph& g,int s, int t);
bool checkflow(Graph& g, int s, int t, int x);


