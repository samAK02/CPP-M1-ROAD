#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <limits>

using namespace std;
const int inf = INT_MAX;
// on a une matrice de poids dans notre graphe, m[i][j] = le poids de l'arête (i,j)

void dijkstra(vector<vector<int>>& mat, int source){ 
    
    int n = mat.size(); //j'ai le "n" de la matrice, parce que j'ai fait un référencement de la matric edans la déclaration en paramètres le fameux "&"
    int m = mat[0].size(); // j'ai le "m" de la matrice qui est égal au "n" parce qu'on a une matrice carrée
    vector<bool> visited(n, false); // le vecteur S dans dijkstra
    vector<int> potentiel(n, inf);
    vector<int> pred(n, -1);
    
    if(source < 0 || source > n ){
        cout<<"le noeud de départ n'existe pas dans le graphe"<<endl;
        cout<<"-1"<<endl;
        abort();
    }else{
        potentiel[source] = 0;
        visited[source] =true;
        // on va chercher le sommet non visité de potentiel minimum
        for(int k=1; k<n; k++){ 
            int u = -1;
            int minVal = inf;
            for(int i=0; i<n; i++){
                if(!visited[i] && potentiel[i] <minVal){ //c'est ça qui va détermienr si un sommet est dans S ou pas , c'est de voir si son potentiel n'est pas à inf
                    minVal = potentiel[i];
                    u=i;
                }
            }
            // si le sommet n'est pas atteignable, on arrête et on passe au sommet suivant
            if(u== -1){
                break;
            }
            //là, on va dire que le sommet u est visité
            visited[u] = true;
            //on va attribuer le potentiel de u 
            for(int v=0; v<n; v++){
                if(mat[v][u] != inf && !visited[u]){
                    if(potentiel[u]+mat[u][v] < potentiel[v]){
                        potentiel[v] = potentiel[u]+mat[u][v];
                        pred[v] = u;
                    }
                }
            }
        }
        //on affiche le résultat
        for(int i=0; i<n; i++){
            cout<<"sommet "<<i<<"  a le potentiel: ";
            if(potentiel[i] == inf){
                cout<<"sommet inateignable";
            }else{
                cout<<potentiel[i];
                cout<<endl;
            }
        }
    }
}

void afficher_arbre(vector<int> &pred, int source, int cible ){
    if(cible != source && pred[cible] == -1){
        cout << "pas de chemin jusqu'au sommet " << cible << endl;
        return;
    }
    vector<int> chemin;
    int courant = cible;
    while(courant != -1){
        chemin.push_back(courant);
        courant = pred[courant];
    }
    // ici chemin contient les sommets dans l'ordre cible -> ... -> source
    // il faut donc l'afficher à l'envers

    for(int i = chemin.size() - 1; i >= 0; i--){
        cout << chemin[i];
        if(i != 0) cout << " -> ";
    }
    cout << endl;
}

int main(int argc, char** argv){

    if(argc==3){ // on va prendre en paramètres le fichier, et le noeud de départ
        cout<<"lecture du fichier en cours";
    }
    string filename;
    fstream infile(filename);
    if (infile){
        int n,m;
        infile >> n >> m >>ws;
        vector<vector<int>> mat(n, vector<int>(m)); 
        for(int i=0; i<n; i++){
            for(int j=0; j<m; i++){
                infile >> mat[i][j] >>ws; 
            }
        }
        int source, cible;
        cout<<"veuillez entrer votre noeud de départ: ";
        cin>>source;
        cout<<"veuillez introduire votre sommet d'arrivée: ";
        cin>>cible;
        vector<int> d, pred;
        dijkstra(mat, source);
        for (int v = 0; v < n; v++) {
            cout << "Sommet " << v + 1 << " : distance = ";
            if (d[v] == inf) cout << "infini";
            else cout << d[v];
            cout << " | chemin : ";
            afficher_arbre(pred, source, v);
        }
    }else{
        cout<<" " <<endl;
        cout<<"fichier inexistant"<<endl;
        cout<<"-1"<<endl;
        abort();
    }
    return 0;
}