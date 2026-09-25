#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(int argc, char** argv){
    int  indice_min;

    if(argc ==1){
        cout<<"Veuillez introduire le nom du fichier: ";
    }
    string filename = argv[1];
    cout<<"Lecture du fichier "<<filename<<endl;

    ifstream infile(filename);
    if(infile){
        int size;
        infile>> size>> ws;
        vector<int> tab(size);

        for(int i=0; i<size; i++){
            infile>> tab[i] >> ws;
        }
        for(int i=0; i<size; i++){
            indice_min = i;
            for(int j=i; j<size; j++){
                if (tab[j]<tab[indice_min]){
                    indice_min =j;
                }
            }
            swap(tab[i], tab[indice_min]);
        }

        cout<<"Le tableau trié est: ";
        for(int i=0; i<size; i++){
            cout<< tab[i] <<" ";
        }

        infile.close();

    }else{
        cout<< endl;
        cout<<-1<<endl;
        cout<<"fichier inexistant"<<endl;
        abort();
    }

    return 0;    
}