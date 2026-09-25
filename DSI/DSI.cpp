#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

// Teste si v est orthogonal a chacun des vecteurs de ev
// ev[j] = j-ieme vecteur du sous-espace
bool estOrthogonal(const vector<double>& v, const vector<vector<double>>& ev) {
    bool orthogonal = true;
    for (size_t j = 0; j < ev.size(); j++) {
        double somme = 0;
        for (size_t k = 0; k < v.size(); k++) {
            somme += v[k] * ev[j][k];
        }
        cout << "produit scalaire avec le vecteur " << j << " : " << somme << endl;
        if (fabs(somme) > 1e-6) orthogonal = false;
    }
    return orthogonal;
}

int main(int argc, char** argv) {
    vector<double> v;
    vector<vector<double>> ev;

    if (argc == 1) {
        // Cas sans argument : exemple code en dur
        cout << "aucun fichier fourni, utilisation de l'exemple par defaut" << endl;
        double r2 = sqrt(2.0);
        ev = {
            {1,  1,  r2, 1},
            {0,  1,  2,  r2},
            {r2, -1, 1,  0}
        };
        v = {
            (-2 + r2) / (1 + 2 * r2),
            2 / (1 + 2 * r2),
            2 * r2 / (1 + 2 * r2),
            -r2
        };
    }
    else if (argc == 3) {
        // Lecture du vecteur
        ifstream infile(argv[1]);
        if (!infile) {
            cerr << "impossible d'ouvrir " << argv[1] << endl;
            return 1;
        }
        int size;
        infile >> size;
        v.resize(size);
        for (int i = 0; i < size; i++) infile >> v[i];

        // Lecture du sous-espace : "dimension nb_vecteurs" puis nb_vecteurs lignes
        ifstream infile2(argv[2]);
        if (!infile2) {
            cerr << "impossible d'ouvrir " << argv[2] << endl;
            return 1;
        }
        int dim, nbVec;
        infile2 >> dim >> nbVec;
        vector<vector<double>> ev(nbVec, vector<double>(dim));
        for (int j = 0; j < nbVec; j++)
            for (int k = 0; k < dim; k++)
                infile2 >> ev[j][k];

        if (dim != size) {
            cout << "dimensions differentes" << endl;
            cout << -1 << endl;
            return 1;
        }
    }
    else {
        cout << "usage : " << argv[0] << " [<fichier_vecteur> <fichier_sous_espace>]" << endl;
        cout << "sans argument, un exemple par defaut est utilise" << endl;
        return 1;
    }

    if (estOrthogonal(v, ev)) {
        cout << "le vecteur est orthogonal a chacun des vecteurs du s-ev" << endl;
        cout << 1 << endl;
    } else {
        cout << "le vecteur n'est pas orthogonal au s-ev" << endl;
        cout << 0 << endl;
    }
    return 0;
}



