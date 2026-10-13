#include<iostream>
#include<vector>
#include<string>
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

    return 0;

}