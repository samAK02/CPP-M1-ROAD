#include<iostream>
#include<vector>
#include<string>
#include<limits>
#include <algorithm>
#include "Graph.hpp"

using namespace std;


int main(int argc, char** argv){
    if(argc == 1){
        cout<<"veuillez entrer le fichier de votre instance: "<<endl;
    } 

    string filename= argv[1];
    Graph g = readGraph(filename);

    printGraph(g);

    cout << "nous allons faire le parcours en profondeur de ce graphe: " << endl;
    int s;
    cout << "veuillez entrer votre sommet de départ: ";
    cin >> s;

    vector<int> ordre = DFS(g, s);
    cout << "le parcours en profondeur de ce graphe est: " << endl;
    for (size_t i = 0; i < ordre.size(); i++){
        cout << ordre[i] << " ";
    }
    cout << endl;

    vector<int> pred;
    vector<float> dist;
    cout<<"nous allons effectuer le calcul de plus courts chemins via l'algorithme de dijkstra"<<endl;
    if (!checkCondDijkstra(g)){
        cout<<"le graph contient des arcs de poids négatifs, nous ne pouvons calculer l'arborescence des plus courts chemins"<<endl;

    }else{
        
        cout<<"Nous allons d'abord effectuer la version avec des vecteurs: "<<endl;
        DijkstraVec(g, s, dist, pred);
        for(int v = 0; v < g.nbNodes; v++){
            cout << "distance de " << s << " à " << v << " : ";
            if(dist[v] == numeric_limits<float>::max()) cout << "inaccessible";
            else cout << dist[v];
            cout << endl;
        }
        cout<<"Nous allons maintenant effectuer la version avec un tas : "<<endl;
        DijkstraTas(g,s,dist,pred);
        for(int v = 0; v < g.nbNodes; v++){
            cout << "distance de " << s << " à " << v << " : ";
            if(dist[v] == numeric_limits<float>::max()) cout << "inaccessible";
            else cout << dist[v];
            cout << endl;
        }

    }

    cout<<"nous allons maintenant faire la même chose mais avec l'algorithme de Bellman Ford"<<endl;
    if(BellmanFord(g,s,dist,pred) != -1){
        cout<<"il y a un circuit absorbant et le sommet : "<< BellmanFord(g,s,dist,pred)<<" en fait partie"<< endl;
        vector<int> circuit;
        int x = BellmanFord(g,s,dist,pred);
        circuit.push_back(x);
        for(int y = pred[x]; y != x; y = pred[y]) circuit.push_back(y);
        reverse(circuit.begin(), circuit.end());
        circuit.push_back(x);

        cout<<"circuit: ";
        int n = circuit.size();
        for(int i =0; i<n; i++){
            cout<<circuit[i];
            if(i + 1 < n) cout << " -> ";
        }
        cout<<endl;
        cout<<"les plus courts chemins ne sont pas définis"<<endl;
    
    }else{
        BellmanFord(g,s,dist,pred);
        for(int v = 0; v < g.nbNodes; v++){
            cout << "distance de " << s << " à " << v << " : ";
            if(dist[v] == numeric_limits<float>::max()) cout << "inaccessible";
            else cout << dist[v];
            cout << endl;
        }
    }
    
    return 0;
}
