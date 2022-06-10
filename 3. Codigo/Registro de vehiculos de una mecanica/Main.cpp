#include<stdlib.h>
#include "ListaCircular.cpp"
#include "marquesina.h"
#define USER "admin"
#define PASS "admin123"

using namespace std;
void menu();

int main(int argc, char** argv) {
	string usuario;   
	string password;
	int k=0;
	bool ingresa = false;

	do
	{
		system("cls");
		cout<<"\t\t|        Login de Usuario        |"<<endl;
		cout<<"\t\t----------------------------------"<<endl;
		cout << "\n\tUsuario: ";
		getline(cin, usuario);
		cout << "\n\tPassword: ";
		getline(cin, password);
		if(usuario==USER && password==PASS){
			ingresa = true;
		}else{
			cout << "\n\tEl usuario y/o contraseña son incorrectos"<<endl;
			cin.get();
			k++;
		}	
	} while (ingresa == false && k <3);

	if(ingresa==false){
		cout << "Usted ha fallado todos los intentos de ingreso al programa" <<endl;
		cin.get();
	}else{
		cout << "\n\tBienvenido al sistema" <<endl;
		cin.get();
		Marquesina marquesina("Registro de vehiculos de una mecanica");
		menu();
		marquesina.presentar();
	}
	
	return 0;
}

void menu(){
	const char *titulo[] = {"--------------------------------------","|         MECANICA SAN EDUARDO        |","--------------------------------------"};
	const char *opciones[]={"\tRegistro de vehiculos","\tConsultar vehiculo al inicio","\tConsultar vehiculo al final","\tBorrar un vehiculo","\tBuscar un vehiculo","\tSalida del sistema", "----------------------------------------"};
	int n = 6; // Numero de opciones
	int m = 3; //Numero de lineas de titulo
	int sw=0,validandoL;
	int convertir;
	int opcion;
    ListaCircular lst;
	bool repite = true;							
	do{
		opcion=menuInteractivo(titulo, opciones,n,m);
		switch(opcion){
			case 1:
				lst.agregar();
				break;
			case 2:
				lst.consultarPrimero();
				break;	
			case 3:
				lst.consultarUltimo();
				break;
			case 4:
				lst.borrar();
				break;
			case 5:
				lst.buscar();
				break;	
			case 6:
				repite = false;
				cout<<"\n\t\tGracias por usar el programa :D"<<endl;
				break;
	    }
	}while(repite);
}