#include <iostream>
#include<cmath>
using namespace std;


/*exo1 simple SOMME somme.cpp
int main(){

    int s, n,a;
    s = 0;
    n = -1;

    while(n<0){
        cout<<"veuillez entrer un entier strictement positif: ";
        cin>>n;
    }

    for(int i=0; i<n; i++){
        cout<<"nomber numéro "<<i<< ": ";
        cin>>a;
        s += a;
    }

    cout<<"la somme de tous vos entiers est: "<< s <<" "<<endl;

    return 0;
}

*/

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* exo 2 simple minimum.cpp


int main(){

    int n,a, min;
    n=-1;
    while(n<0){
        cout<<"veuillez entrer un entier strictement positif: ";
        cin>>n;
    }

    for(int i=0; i<n; i++){
        cout<<"nomber numéro "<<i<< ": ";
        cin>>a;
        if(a < min){
            min = a;
        }
    }
    cout<<"le minimum de votre liste est : "<< min <<endl;
}


*/

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* exo3 simple somme harmonique 

int main(){

    int n, i;
    float s;
    s=0;
    n= -1;
    i=1;
    while(n <0){
        cout<<"veuillez entrer un entier strictement positif: ";
        cin>>n;
    }
    while(i<=n){
        s+= 1.0 /i;
        i++;
    }
    cout<<"la somme harmonique est : "<< s <<endl;

    return 0;
}

*/

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Exo 4 simple fibonacci.cpp


int fib(int n){
    if(n<=1){
        return n;
    }
    else{
        return fib(n-1) + fib(n-2);
    }
}

int main(){

    int n;
    n=-1;
    while(n<0){
        cout<<"Veuillez entrer un entier Positif de votre suite de fibonacci: ";
        cin>>n;
    }
    cout<<"Le terme numero "<<n<<" de la suite est: "<<fib(n)<<endl;
    return 0;

}

 */

 // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 /*exo5 simple syracuse.cpp */

int main(){

    int n;
    n=-1;
    int prev;
    while(n <0){
        cout<<"veuillez entrer un entier strictement positif: ";
        cin>>n;
    }

    prev = n;
    cout <<prev<<endl;

    while(prev!=1){
    
        if(prev%2 ==0){ 
            prev = prev/2;
        }else{
            prev = 3*prev+1;
        }
        cout<< prev<<endl;
    }

    return 0;
}
