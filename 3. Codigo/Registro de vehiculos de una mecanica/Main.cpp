#include<stdlib.h>
#include "ListaCircular.cpp"
#include "marquesina.h"
#include "menuInteractivo.cpp"
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
	int sw=0,validandoL;
	int convertir;
<<<<<<< HEAD
	char opcion[2]; // validacion de solo numeros
=======
	int opcion;
>>>>>>> 1ac6e1fa14e4165d27b76fe11b3a3eb9a59650a6
    ListaCircular lst;
	bool repite = true;							
	do{
		opcion=menuInteractivo(titulo, opciones,n);
		/*system("cls");
		cout<<"\n\n";
		cout<<"\t\t--------------------------------------\n";
		cout<<"\t\t|         MECANICA SAN EDUARDO        |\n";
		cout<<"\t\t--------------------------------------\n";
		cout<<"\t\tRegistro de vehiculos................[1]\n\n";
		cout<<"\t\tConsultar vehiculo al inicio.........[2]\n\n";
		cout<<"\t\tConsultar vehiculo al final..........[3]\n\n";
		cout<<"\t\tBorrar un vehiculo...................[4]\n\n";
		cout<<"\t\tBuscar un vehiculo...................[5]\n\n";
		cout<<"\t\tSalida del sistema...................[6]\n\n";
		cout<<"\t\t----------------------------------------\n\n";
		cout<<"\t\tINGRESE LA OPCION: ";cin>>opcion;
		system("cls");
		*/
		//valido que ingrese numero y no pueda ingresar otro tipo de dato
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
	    system("pause");
	}while(repite);
	return;
}
