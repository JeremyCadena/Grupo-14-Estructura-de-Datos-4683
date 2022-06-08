
#include "Nodo.cpp"

using namespace std;
void menu();

int main(int argc, char** argv) {
	/*typedef int (WINAPI *Validar_int_P)(const char*);//Tipo de dato que ingresa, tipo de dato que sale
	typedef int (WINAPI *Validar_int_NP)(const char*);
	Validar_int_P validar_int_P;
	Validar_int_NP validar_int_NP;
	
	HINSTANCE libDLL=NULL;// inicializamos la libreria con Null
	libDLL = LoadLibrary ("Proyecto 1.dll"); //Cargamos la libreria
	
	validar_int_P=(Validar_int_P)GetProcAddress(libDLL,"ingresarDatos_Int_P");
	validar_int_NP=(Validar_int_NP)GetProcAddress(libDLL,"ingresarDatos_Int_N_P");*/
	menu();
	return 0;
}
void menu(){
	Nodo *lista=NULL;
	int op;
	cout << "\t--REGISTRO DE VEHICULOS EN UNA MECANICA--\n" << endl;
	cout << "Menu de opciones:"<<endl;
	cout << " 1. Ingresar un nuevo vehiculo."<<endl;
	cout << " 2. Mostrar vehiculos."<<endl;
	cout << " 3. Salida."<<endl;
	cout << "\nIngrese la accion que desea realizar: ";
	cin >> op;
	switch(op){
		case 1:
			int n;
			cout<<"Ingrese el numero de vehiculos a ingresar: ";
			cin >> n;
			for(int i=1;i<=n;i++){
				lista->insertarNodo();
			}
			system("pause");
			system("cls");
			menu();
			break;
		case 2:
			cout << "";
			lista->mostrarListaPU();
			lista->mostrarListaUP();
			system("pause");
			system("cls");
			menu();
			break;
		case 3:
			cout << "\nSaliendo del programa con exito.\n";
			break;
		default:
			cout << "\nERROR: Por favor ingrese un numero valido.\n";
			system("pause");
			system("cls");
			menu();
	}
}


