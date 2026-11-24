#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<limits>
#include<queue>
#include <algorithm>
#include "Graph.hpp"

// Binôme: AKRETCHE Ales Samy - LARRUE Joris

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

    cout << "\nEnsemble des arcs (graphe + residuel) :" << endl;
    int n = g.arcs.size();
    for (int i = 0; i < n; i++){
        const Arc& a = g.arcs[i];
        cout << "[" << i << "] (" << a.start << "->" << a.end << ")"
             << " cost: " << a.cost
             << " cap: " << a.cap
             << " flow: " << a.flow
             << " capRes: " << a.capRes
             << " indx: " << a.indx
             << " isInv: " << (a.isInv ? "true" : "false");

            if (a.indx >= 0 && a.indx < n){
                    const Arc& inv = g.arcs[a.indx];
                    bool ok = (inv.start == a.end) && (inv.end == a.start) && (inv.indx == i);
                    if (!ok) cout << "  <-- ERREUR: incoherence avec l'arc inverse";
                } else if (a.indx != -1) {
                    cout << "  <-- ERREUR: indx hors limites";
                }
                cout << endl;
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


void DijkstraVec(Graph& g, int s, vector<float>& dist, vector<int>& pred){
    const float inf = numeric_limits<float>::max();
    int n = g.nbNodes;
    dist.assign(n, inf);
    pred.assign(n, -1);
    vector<bool> definitif(n, false);

    dist[s] = 0;
    for(int k=0; k<n ; k++){
        int u =-1;
        for(int v=0; v<n; v++){
            if(!definitif[v] && (u == -1 ||dist[v] < dist[u])){
                u = v;
            }
        }
        if(dist[u] == inf || u ==-1){
            break;
        }
        definitif[u] = true;

        for(int i : g.nodes[u]){
            const Arc& a = g.arcs[i];
            if(dist[u] + a.cost < dist[a.end]){
                dist[a.end] = dist[u] + a.cost;
                pred[a.end] = u;
            }
        }
    }
}

bool checkCondDijkstra(Graph& g){
    int m = g.arcs.size();
    for(int i=0; i<m; i++){
        const Arc& a = g.arcs[i];
        if (a.cost <0){
            return false;
            break;
        }
    }return true;
}

void DijkstraTas(Graph& g, int s, vector<float>& dist, vector<int>& pred){
    const float inf = std::numeric_limits<float>::max();
    int n = g.nbNodes;
    dist.assign(n, inf);
    pred.assign(n, -1);

    dist[s] = 0;
    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> pq;
    pq.push({0, s});
    while(!pq.empty()){
        float d = pq.top().first;
        int u = pq.top().second;

        pq.pop();
        if(d> dist[u]) continue;
        for(int i : g.nodes[u]){
            const Arc& a = g.arcs[i];
            if(dist[u] + a.cost < dist[a.end]){
                dist[a.end] = dist[u] + a.cost;
                pred[a.end] = u;
                pq.push({dist[a.end], a.end});
            }
        }
    }
}

int BellmanFord(Graph& g, int s, vector<float>& dist, vector<int>& pred){
    const float inf = std::numeric_limits<float>::max();
    int n = g.nbNodes;
    dist.assign(n, inf);
    pred.assign(n, -1);
    dist[s] = 0;

    for(int i = 0; i<n; i++){
        int dernier = -1;
        for(const Arc& a : g.arcs ){
            if(dist[a.start] == inf ) continue;
            if (dist[a.start] + a.cost < dist[a.end]){
                dist[a.end] = dist[a.start] + a.cost;
                pred[a.end] = a.start; 
                dernier = a.end;
            }
        }
        if(dernier == -1) return -1;

        if(i == n-1){
            int x = dernier;
            for(int k =0; k<n; k++ ){
                x = pred[x];
  
            }return x;
        }
    }
    return -1;
}

void addNetworkArc(Graph& g, int start, int end, int cap){
    
    if( (start<0 || start> (g.nbNodes -1) ) || ((end<0 || end> (g.nbNodes -1) ) )){
        cout<<"les sommets n'existent pas dans le graphe"<<endl;
        return;
    }
    Arc arc;
    arc.start = start;
    arc.end = end;
    arc.cap = cap;
    arc.cost = 0;
    arc.flow = 0;

    g.arcs.push_back(arc);
    g.nbArcs ++;

    g.nodes[start].push_back(g.arcs.size()-1);
}

Graph readNetwork(string filename){
    
    fstream infile(filename);
    if(infile){
        int nbNodes, nbArcs;
        infile>>nbNodes>>nbArcs>>ws;
        
        Graph network = initGraph(nbNodes, nbArcs);
        
        for(int i =0; i<nbArcs; i++){
            int n1, n2, cap;
            infile>> n1 >> n2>> cap>> ws;
            addNetworkArc(network, n1, n2, cap);
        }

        return network;   
    }else{
        cout<<endl;
        cout<<-1<<endl;
        cout<<"fichier inexistant"<<endl;
        abort();
    }
}

void makeResidual(Graph& g){
    int m = g.arcs.size();

    for(int i = 0; i < m; i++){
        g.arcs[i].isInv = false;
        g.arcs[i].indx = -1;
        g.arcs[i].capRes = g.arcs[i].cap - g.arcs[i].flow;
    }

    for(int i = 0; i < m; i++){
        if(g.arcs[i].indx != -1) continue;

        int s = g.arcs[i].start;
        int e = g.arcs[i].end;
        int found = -1;

        // on cherche un arc initial (e -> s) non encore apparié
        for(int j = 0; j < (int)g.nodes[e].size(); j++){
            int k = g.nodes[e][j];
            if(k < m && k != i && g.arcs[k].end == s && g.arcs[k].indx == -1){
                found = k;
                break;
            }
        }
        if(found != -1){
            // (s,e) et (e,s) existent tous les deux dans le graphe initial
            g.arcs[i].indx = found;
            g.arcs[found].indx = i;
            g.arcs[i].isInv = true;
            g.arcs[found].isInv = true;
        } else {
            // on crée l'arc inverse (e -> s)
            Arc inv;
            inv.start = e;
            inv.end = s;
            inv.cost = -g.arcs[i].cost;
            inv.cap = 0;
            inv.flow = 0;
            inv.capRes = g.arcs[i].flow; // 0 si le flot initial est nul
            inv.isInv = true;
            inv.indx = i;

            int newIdx = g.arcs.size();
            g.arcs.push_back(inv);
            g.nodes[e].push_back(newIdx);

            g.arcs[i].indx = newIdx; // isInv de l'arc initial reste false
        }
    }
    g.nbArcs = g.arcs.size();
    

}

vector<int> reverseBfs(Graph& g, int t){
    if (t > g.nbNodes - 1 || t < 0){
        cout << "Sommet inexistant dans le graphe! " << endl;
        return {};
    }
    vector<bool> visited(g.nbNodes, false);
    vector<int> dist(g.nbNodes, -1);
    queue<int> q;
    dist[t] = 0;
    q.push(t);

     while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int i : g.nodes[u]){
            const Arc& a = g.arcs[i];
            if (a.isInv && dist[a.end] == -1){
                dist[a.end] = dist[u] + 1;
                q.push(a.end);
            }
        }
    }
    return dist;
}

int findAdmissibleArc(Graph& g, vector<int>& dist, int i){

    for(int indx: g.nodes[i]){
        const Arc a = g.arcs[indx];
        if(a.capRes > 0 && dist[i] == dist[a.end] +1){
            return indx;
        }
    }
    return -1; // si on trouve rien 
}

int relabel(Graph& g, vector<int>& dist, int i){
    int relab = g.nbNodes;   // infini si aucun arc résiduel

    for(int indx : g.nodes[i]){
        const Arc& a = g.arcs[indx];
        if(a.capRes > 0){
            relab = min(relab, dist[a.end] + 1);
        }
    }

    dist[i] = relab;
    return relab;
}



int computeDelta(Graph& g, int s, int t, vector<int>& pred){
    if (s < 0 || s >= g.nbNodes || t < 0 || t >= g.nbNodes){
        cout << "les sommets n'existent pas dans le graphe" << endl;
        return 0;
    }

    int delta = INT_MAX;
    int v = t;
    while (v != s){
        int idx = pred[v];          // indice de l'arc qui arrive en v
        if (idx == -1) return 0;    // pas de chemin jusqu'à s

        const Arc& a = g.arcs[idx];
        delta = min(delta, a.capRes);
        v = a.start;                // on remonte vers le prédécesseur
    }
    return delta;
}

void augmenteFlow(Graph& g, int s, int t,  vector<int>& pred, int delta){

    int v = t;
    while(v!=s){
        int i = pred[v];
        Arc& a = g.arcs[i];
        Arc& inverse = g.arcs[a.indx];

        a.capRes += delta;
        inverse.capRes -= delta;

        if(!a.isInv){
            a.flow += delta;
            
        }else{
            inverse.flow -= delta;
        }
        
        v = a.start;

        
    }
}

int EdmondsKarp(Graph& g,int s, int t){
    int n = g.nbNodes;
    vector<int> dist = reverseBfs(g, t);
    vector<int> pred(n, -1);
    vector<int> admissiblePath;

    // sommets qui n'atteignent pas t, on lui donne une distance de n
    for (int v = 0; v < n; v++) {
        if (dist[v] == -1){
            dist[v] = n;
        } 
    }


    int x = 0;
    int i = s;
    while(dist[s] <n  ){
        int j = findAdmissibleArc(g, dist, i);
        if(j != -1){
            int v = g.arcs[i].end;
            pred[v] = i;
            i = v;
            if( i == t){
                int delta = computeDelta(g, s, t, pred);
                augmenteFlow(g,s,t,pred, delta);
                x+=delta;
                i =s;
            }
        }else{
           
            if(i != s){
                i = pred[i];
            }
        }
    } 
    return x;
}

bool checkflow(Graph& g, int s, int t, int x){

    int n = g.nbNodes;
    for(int i = 0; i<n; i++){
        Arc& a = g.arcs[i];
        if(a.flow < 0){
            
        }
    }

}
