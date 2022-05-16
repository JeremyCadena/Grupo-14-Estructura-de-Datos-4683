#include <iostream>
#include "Cproceso.cpp"

/* 		UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE

Programa para la correcion de un TDA
Autor(es): Cadena Jeremy - Dylan Tipan
Fecha de creación: 11/05/2022
Fecha de modificación: 12/05/2022
Grupo # 14
Github del grupo: https://github.com/JeremyCadena/Grupo-14-Estructura-de-Datos-4683.git
Versión:
Estructura de Datos 4683 */


int main(int argc, char** argv) {
	int a=18,b=3;
	Cproceso *obj1=new Cproceso(a,b);
	Cproceso *obj2=new Cproceso(15,5);
	Cproceso *obj3=new Cproceso(0,0);
	obj3->racional(*obj1,*obj2);
	obj1->imprimirObj(*obj1);
	obj2->imprimirObj(*obj2);
	obj3->imprimirObj(*obj3);
	return 0;
}
