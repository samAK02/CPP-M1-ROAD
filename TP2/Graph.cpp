#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<limits>
#include<queue>
#include <algorithm>
#include "Graph.hpp"

using namespace std;

Graph initGraph(int nbNodes, int nbArcs){

    Graph g;
    g.nbNodes = nbNodes;
    g.nbArcs = 0;
    g.nodes.resize(nbNodes);

    return g;
}

void addArc(Graph& g, int n1, int n2, int cost){
    if( (n1<0 || n1> (g.nbNodes -1) ) || ((n2<0 || n2> (g.nbNodes -1) ) )){
        cout<<"les sommets n'existent pas dans le graphe"<<endl;
        return;
    }
    Arc arc;
    arc.start = n1;
    arc.end = n2;
    arc.cost = cost;

    g.arcs.push_back(arc);
    g.nbArcs ++;

    g.nodes[n1].push_back(g.arcs.size()-1); 
    
}

void printGraph(Graph& g){

    cout<<"nombre de sommets du graphe: "<<g.nbNodes<< ", Nombre d'arcs du graphe: "<<g.nbArcs<<endl;
    
    cout<<"l'ensemble des sommets: "<<endl;
    for (int i = 0; i < g.nbNodes; i++){
        cout << "sommet " << i << " : ";
        for (size_t j = 0; j < g.nodes[i].size(); j++){
            const Arc& a = g.arcs[g.nodes[i][j]];   // j-ème arc incident à i
            cout << "(" << a.start << "->" << a.end << ", cost: " << a.cost << ") ";
        }
        cout << endl;
    }

    cout<<"l'ensemble de arcs: "<<endl;
    int n = g.arcs.size();
    for(int i = 0; i <n ; i++){
        cout<<"("<<g.arcs[i].start <<"->"<<g.arcs[i].end<<") cost: "<< g.arcs[i].cost<<endl;
    }
}


vector<int> DFS(Graph& g, int s){
    if (s > g.nbNodes - 1 || s < 0){
        cout << "Sommet inexistant dans le graphe! " << endl;
        return {};
    }
    vector<bool> visited(g.nbNodes, false);
    vector<int> parent(g.nbNodes, -1);
    vector<int> ordre;
    stack<int> F;
    visited[s] = true;
    F.push(s);

    while (!F.empty()){
        int u = F.top();
        ordre.push_back(u);
        F.pop();
        for (int i : g.nodes[u]){
            int v = g.arcs[i].end;
            if (!visited[v]){
                visited[v] = true;
                parent[v] = u;
                F.push(v);
            }
        }
    }
    return ordre;
}

Graph readGraph(string filename){
    fstream infile(filename);

    if(infile){
        int nbNodes, nbArcs;
        infile>> nbNodes >> nbArcs;

        Graph g = initGraph(nbNodes, nbArcs);

        for(int i =0; i<nbArcs; i++){
            int n1, n2, cost;
            infile>> n1 >> n2>> cost>> ws;
            addArc(g, n1, n2, cost);
        }

        return g;
        
    }else{
        cout<<endl;
        cout<<"fichier inexistant"<<endl;
        cout<<-1<<endl;
        abort();
    }
}

vector<float> dijkstra(Graph& g, int source){
    const float inf = std::numeric_limits<float>::max(); 
    vector<float> dist(g.nbNodes, inf);
    vector<float> parent(g.nbNodes, -1);

    dist[source] = 0;
    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> pq;
    pq.push({0, source});
    while(!pq.empty()){
        float d = pq.top().first;   
        int   u = pq.top().second; 
        pq.pop();
        if(d > dist[u]) continue;
        for(int i : g.nodes[u]){
            const Arc& a = g.arcs[i];
            if(dist[u] + a.cost < dist[a.end]){
                dist[a.end] = dist[u] +a.cost;
                parent[a.end] = u;
                pq.push({dist[a.end], a.end});
            }
        }

    }
    return dist;
}

vector<int> chemin(const vector<int>& parent, int t){
    vector<int> p;
    for(int v = t; v != -1; v = parent[v]) p.push_back(v);
    reverse(p.begin(), p.end());    
    return p;
}

