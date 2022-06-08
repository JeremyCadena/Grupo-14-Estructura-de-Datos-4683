#include <iostream>
#include "Nodo.h"

using namespace std;

void Nodo::setid(int newid){
	id=newid;
}

int Nodo::getid(void){
	return id;
}

void Nodo::setmarca(string newmarca){
	marca=newmarca;
}
string Nodo::getmarca(void){
	return marca;
}

void Nodo::setplaca(string newplaca){
	placa=newplaca;
}

string Nodo::getplaca(void){
	return placa;
}

void Nodo::setpropietario(string newpropietario){
	propietario=newpropietario;
}

string Nodo::getpropietario(void){
	return propietario;
}
Nodo Nodo::setsiguiente(Nodo* newsiguiente){
	siguiente= newsiguiente;
}

Nodo* Nodo::getsiguiente(Nodo){
	return siguiente;
}
		
void Nodo::insertarNodo(){
	Nodo* nuevo_nodo = new Nodo();
	cout << "Ingrese el id del nuevo vehiculo: ";
	cin >> nuevo_nodo->id;
	cout << "Ingrese la marca del nuevo vehiculo: ";
	cin >> nuevo_nodo->marca;
	cout << "Ingrese la placa del nuevo vehiculo: ";
	cin >> nuevo_nodo->placa;
	cout << "Ingrese el nombre del propietario del nuevo vehiculo: ";
	cin >> nuevo_nodo->propietario;
	if(primero==NULL){
		primero = nuevo_nodo;
		ultimo = nuevo_nodo;
		primero->siguiente = primero; 
		primero->atras = ultimo;
	}
	else{
		ultimo->siguiente = nuevo_nodo;
		nuevo_nodo->atras = ultimo;
		nuevo_nodo->siguiente = primero;
		ultimo = nuevo_nodo;
		primero->atras = ultimo;
	}
	cout << "\n Nodo Ingresado\n\n";
}

void Nodo::mostrarListaPU(){
	cout << "\t--LISTA DE VEHICULOS EN LA MECANICA--\n"<<endl;
	Nodo* actual_nodo=new Nodo();
	actual_nodo=primero;
	if(primero!=NULL){
		do{
			
			cout << "ID: "<<actual_nodo->id<<endl<<"Marca: "<<actual_nodo->marca<<endl;
			cout << "Placa: " << actual_nodo->placa<<endl<<"Propietario: "<<actual_nodo->propietario<<endl<<endl;
			actual_nodo=actual_nodo->siguiente;
		}while(actual_nodo!=primero);
	}else{
		cout << "\n La lista esta vacia." <<endl <<endl;
	}
}

void Nodo::mostrarListaUP(){
	cout << "\t--LISTA DE VEHICULOS EN LA MECANICA--\n"<<endl;
	Nodo* actual_nodo=new Nodo();
	actual_nodo=ultimo;
	cout <<endl;
	if(primero!=NULL){
		do{
			cout << "ID: "<<actual_nodo->id<<endl<<"Marca: "<<actual_nodo->marca<<endl;
			cout << "Placa: " << actual_nodo->placa<<endl<<"Propietario: "<<actual_nodo->propietario<<endl<<endl;
			actual_nodo=actual_nodo->atras;
		}while(actual_nodo!=ultimo);
	}else{
		cout << "\n La lista esta vacia." <<endl <<endl;
	}
}

Nodo::Nodo(){}
Nodo::~Nodo(){}

