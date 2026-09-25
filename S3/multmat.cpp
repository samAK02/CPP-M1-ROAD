#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(int argc, char** argv){

    if(argc == 3){
        cout<<"Veuillez entrer le nom de vos fichiers contenant vos matrices: ";
    }

    string filename1=argv[1];
    string filename2 = argv[2];
    cout<<"lecture des fichiers"<<filename1<< " ainsi que "<<filename2<<endl;

    ifstream infile(filename1);
    ifstream infile2(filename2);
    if(infile){

        int n1, m1;
        infile>> n1>>m1>>ws;
        vector<vector<int>> mat1(n1, vector<int>(m1,0));

        //je vais essaeyr de lire la matrice du premier fichier et la mettre dans mat1
        for(int i=0; i<n1; i++){
            for(int j=0; j<m1; j++){
                infile>>mat1[i][j] >> ws; // ?? pas sûr de ça en vrai
            }
        }

        //lecture de la deuxième matrice ????
        if(infile2){
            int n2, m2;
            infile2>> n2>>m2>>ws;
            vector<vector<int>> mat2(n2, vector<int> (m2,0));

            for(int k=0; k<n2; k++){
                for(int l=0; l<m2; l++){
                    infile2>>mat2[k][l]>>ws;
                }
            }

            if(m1 == n2){
                string filename3;
                cout<<"veuillez nommer le fichier de sortie: ";
                cin>>filename3;
                ofstream outfile(filename3);

                //c'est là que je vais faire la multiplication de matrices: 
                int n3 = n1;
                int m3 = m2;
                vector<vector<int>> mat3(n1,vector<int>(m2,0));
                for(int a=0; a<n1; a++){
                    for(int b=0; b<m2; b++){
                        for(int c=0; c<m1; c++){
                            mat3[a][b] += mat1[a][c]*mat2[c][b];
                        }
                    }
                }

                //je vais afficher la matrice résultante dans le 3ème fichier 
                outfile <<n3<< " "<< m3 <<"\n";
                for(int d=0; d< n3; d++){
                    for(int e=0; e<m3; e++){
                        outfile << mat3[d][e];
                        if(e <m3-1) outfile << " ";
                    }
                    outfile <<"\n";
                }

                outfile.close();
            }else{
                cout<<"la taille des deux matrices sont incompatibles, multipliacation impossible"<<endl;
                return -1;
            }
            infile2.close();
        }else{
            cout <<endl;
            cout<<-1<<endl;
            cout<<"Fichier "<< filename2<<"  inexistant"<<endl;
            abort();
        }
        infile.close();
        
    }else{
        cout<<endl;
        cout<<-1<<endl;
        cout<<"fichier" << filename1<< " inexistant"<<endl;
        abort();
    }

    return 0;
}