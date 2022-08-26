#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>  // Para ofstream
using namespace std;

int main(){
	float x[40], j=0.0;
	int x1[4], k=0; 
	ofstream fich("datos.dat");
  	if (!fich){
  		cout << "Error al abrir datos.dat\n";
    	exit(EXIT_FAILURE);
  	}

	for (int i = 0; i <= 40; i++){
  		x[i] = j;
  		fich << x[i]<< endl;
		j = j + 0.1;
  	}
    
        
	for(int i = 0; i<=4; i++){
		x1[i] = k;
		k= k + 1;	
		fich << x1[i]<< endl;
	}
    printf(" Creacion de datos completado");
    return 0;
}