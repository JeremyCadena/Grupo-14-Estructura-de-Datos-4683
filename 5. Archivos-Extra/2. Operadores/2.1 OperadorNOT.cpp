#include <iostream>

using namespace std;

/* 		UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE

Programa para sobrecargar el operador negacion (!)
Autor(es): Cadena Jeremy - Dylan Tipan
Fecha de creaci?n: 14/05/2022
Fecha de modificaci?n: 15/05/2022
Grupo # 14
Github del grupo: https://github.com/JeremyCadena/Grupo-14-Estructura-de-Datos-4683.git
Versi?n:
Estructura de Datos 4683 */


//Clase de Vector en Plano 2D
class V2D {   
  float x, y;
  public:
  	V2D(float i=0, float j=0): x(i), y(j) {} 
  	//Sobrecarga del operador logico NOT
  	bool operator!() {
		return ((x > 0 && y > 0) ? false : true );
  	}
  	operator bool() { 
  		return ((x > 0 && y > 0) ? true : false );
    }
};

//Unicamente en el primer cuadrante sera verdadero
int main(){
	V2D p1(3,-2);
	V2D p2(-1, 2);
	V2D p3 = V2D(1,2);
	V2D p4(1, -3);
	
	if (p1) cout << "p1 Pertenece.\n";
	if (p2) cout << "p2 Pertenece.\n";
	if (p3) cout << "p3 Pertenece.\n";
	if (p4) cout << "p4 Pertenece.\n";       
	
	if (!p1) cout << "p1 No pertenece.\n";  
	if (!p2) cout << "p2 No pertenece.\n";  
	if (!p3) cout << "p3 No pertenece.\n";  
	if (!p4) cout << "p4 No pertenece.\n";
	return 0;
}


