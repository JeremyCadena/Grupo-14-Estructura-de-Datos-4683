#include "ListaCircular.hpp"
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

int validarCadenas(char cadena[50]);
int validarNum(char numero[10]);
int sw=0,validandoL;

ListaCircular::ListaCircular(){
    raiz = NULL;
}

void ListaCircular::agregar(){
    ofstream apArchivo;  
    apArchivo.open("C:/Users/jejoc/OneDrive/Escritorio/Jeremy  ESPE/Software/Semestre SI MAY-SEP22/1. Estructura de Datos/Trabajos en C++/Registro de vehiculos de una mecanica/Registro.txt", ios::app);
    if ( ! apArchivo ) {
        cout << "Problema al abrir archivo --> Registro.txt" <<endl;
        return;
    }

    Vehiculo *nuevo;
    int i=0;
    nuevo = new Vehiculo();
    if(nuevo==NULL){
        cout<<"\t\t\tNO HAY MEMORIA SUFICIENTE"<<endl;
		return;
	}

    cout<<"\t\t\t|Registro del Vehiculo|"<<endl;
	cout<<"\t\t\t-----------------------"<<endl;
	cout<<endl;

    do{
        cin.clear();		
        fflush(stdin);
        cout<<"\t\t|Ingrese la Marca del Vehiculo: ";
        cin.getline(nuevo->marca,12);
        validandoL=validarCadenas(nuevo->marca);
	}while(validandoL!=0); 

    cin.clear();
    fflush(stdin);
    cout<<"\t\t|Ingrese la Placa del Vehiculo: ";
    cin.getline(nuevo->placaVehicular,10);
    fflush(stdin);
    
    do{
        cin.clear();
        fflush(stdin);
        cout<<"\t\t|Ingrese el Nombre de su Propietario: ";
        cin.getline(nuevo->nombrePropietario,40);
        validandoL=validarCadenas(nuevo->nombrePropietario);
	}while(validandoL!=0);

    if(raiz==NULL){
		nuevo->siguiente=nuevo;
		nuevo->anterior=nuevo;
		raiz=nuevo; //con esto se agrega el nodo
	}else{
		nuevo->siguiente=raiz->siguiente;
		nuevo->anterior=raiz;
		raiz->siguiente->anterior=nuevo;
		raiz->siguiente=nuevo;		
	}
	cout<<"\t\tRegistro de Vehiculo exitoso!"<<endl;
}

bool ListaCircular::vacia(){
    if (raiz == NULL)
        return true;
    else
        return false;
}

void ListaCircular::consultarPrimero(){
    Vehiculo *copia = raiz;
    if ( copia == NULL ) {
		cout << "\t\tNo hay registros disponibles" << endl;
		return;
	}

    cout << "\t\t\t--------------------------" << endl;
	cout << "\t\t\t|      Registros         |" << endl;
	cout << "\t\t\t--------------------------" << endl;

	do {
        cout<<endl;	
        cout<<"\t\t--------------------------------------------"<<endl;
        cout<<"\t\tMarca: "<<copia->marca<<endl;
        cout<<"\t\tPlaca Vehicular: "<<copia->placaVehicular<<endl;
        cout<<"\t\tPropietario: "<<copia->nombrePropietario<<endl;
        cout<<endl;
        copia=copia->siguiente;
	} while( copia != raiz);
    return;
}

void ListaCircular::consultarUltimo(){
    Vehiculo *copia = raiz;
    if ( copia == NULL ) {
		cout << "\t\tNo hay registros disponibles" << endl;
		return;
	}

    cout << "\t\t\t--------------------------" << endl;
	cout << "\t\t\t|      Registros         |" << endl;
	cout << "\t\t\t--------------------------" << endl;

	do {
        cout<<endl;	
        cout<<"\t\t--------------------------------------------"<<endl;
        cout<<"\t\tMarca: "<<copia->marca<<endl;
        cout<<"\t\tPlaca Vehicular: "<<copia->placaVehicular<<endl;
        cout<<"\t\tPropietario: "<<copia->nombrePropietario<<endl;
        cout<<endl;
        copia=copia->anterior;
	} while( copia != raiz);
    return;
}

void ListaCircular::borrar(){
    Vehiculo *eliminar = raiz;
    char resp;
    if ( eliminar == NULL ) {
		cout << "\t\tNo hay un registro existente" << endl;
		return;
	}

    if ( raiz == raiz->siguiente) {
	cout << "\t\t\t------------------------------" << endl;
	cout << "\t\t\t|   Eliminacion de registro   |" << endl;
	cout << "\t\t\t------------------------------" << endl;
	cout<<"\n\n";	
	
	cout<<"\t\t|Marca: "<<eliminar->marca<<endl;
	cout<<"\t\t|Placa Vehicular: "<<eliminar->placaVehicular<<endl;
	cout<<"\t\t|Propietario: "<<eliminar->nombrePropietario<<endl;
    cout<<"\t\t------------------------------" << endl;
    cout<<"\t\tSeguro que desea eliminar? (S/s): "; cin >> resp;

    if ( resp=='S' || resp=='s') {
      	 raiz=NULL;
      	 free(eliminar);
      	 cout <<"\t\tRegistro eliminado..." << endl;
      	 system("pause");
	  }
	  return;
	}
}

void ListaCircular::buscar(){
    Vehiculo *copia = raiz;
    char opcionBuscar[2];
	int convertir;
    if(copia==NULL){
        cout<<"\t\t No hay registros disponibles"<<endl;
		return;
	}

    cout << "\t\t\t----------------------------" << endl;
	cout << "\t\t\t|   Busqueda de Vehiculos   |" << endl;
	cout << "\t\t\t----------------------------" << endl;
	cout<<"\n\n";
		
	cout<<"\t\t-----------------------------" << endl;
	cout<<"\t\tPor su marca..............[1]"<<endl;
	cout<<"\t\tPor placa vehicular.......[2]"<<endl;
	cout<<"\t\tPor propietario...........[3]"<<endl;
	cout<<"\t\t-----------------------------" << endl;
	cout<<"\t\tIngrese su opcion:";cin>>opcionBuscar;
	
    int sw=0;
	sw=validarNum(opcionBuscar);
	if(sw!=0){
		cout<<"\t\tIngrese una opcion validad (1-3)";
	}	
	
    convertir = atoi(opcionBuscar);
	system("cls");
    switch(convertir){
		case 1:	
			char marca[12];
			char resp; //
			do{
                cout << "\t\t\t--------------------------" << endl;
				cout << "\t\t\t|        Registro         |" << endl;
				cout << "\t\t\t--------------------------" << endl;
				cout<<"\t\tMarca: ";
					fflush(stdin);
					cin.getline(marca,12);
					fflush(stdin);
					do{	
                        if(strcmp(copia->marca,marca)==0){
                            cout<<endl;
                            cout<<"\t\t|Marca: "<<copia->marca<<endl;
						    cout<<"\t\t|Placa Vehicular: "<<copia->placaVehicular<<endl;
						    cout<<"\t\t|Propietario: "<<copia->nombrePropietario<<endl;
						}
						cout<<"\t\t*********************************" << endl;
    					copia=copia->siguiente;
	    		    }while(copia!=raiz);
					cout<<"\t\tDesea buscar otro nombre? s/S: "; cin>>resp;
					system("cls");
			}while(resp=='s'||resp=='S');
			return;
			break;
		case 2:	
			char placaVehicular[10];
			do{
				cout << "\t\t\t--------------------------" << endl;
				cout << "\t\t\t|        Registro         |" << endl;
				cout << "\t\t\t--------------------------" << endl;
				cout<<"\t\tPlaca vehicular: ";
				fflush(stdin);
				cin.getline(placaVehicular,10);
				fflush(stdin);
				do{	
                    if(strcmp(copia->placaVehicular,placaVehicular)==0){
                        cout<<endl;
                        cout<<"\t\t|Marca: "<<copia->marca<<endl;
					    cout<<"\t\t|Placa Vehicular: "<<copia->placaVehicular<<endl;
						cout<<"\t\t|Propietario: "<<copia->nombrePropietario<<endl;
					}
					cout<<"\t\t*********************************" << endl;
    				copia=copia->siguiente;
	    		}while(copia!=raiz);
				cout<<"\t\tDesea buscar otra placa vehicular? s/S: "; cin>>resp;
					system("cls");
			}while(resp=='s'||resp=='S');
			return;
			break;	
		case 3:	
			char nombrePropietario[40];
			do{
				cout << "\t\t\t--------------------------" << endl;
				cout << "\t\t\t|        Registro         |" << endl;
				cout << "\t\t\t--------------------------" << endl;
				cout<<"\t\tPropietario: ";
				fflush(stdin);
				cin.getline(nombrePropietario,40);
				fflush(stdin);
				do{	
                    if(strcmp(copia->nombrePropietario,nombrePropietario)==0){
                        cout<<endl;
                        cout<<"\t\t|Marca: "<<copia->marca<<endl;
					    cout<<"\t\t|Placa Vehicular: "<<copia->placaVehicular<<endl;
						cout<<"\t\t|Propietario: "<<copia->nombrePropietario<<endl;
					}
					cout<<"\t\t*********************************" << endl;
    				copia=copia->siguiente;
	    		}while(copia!=raiz);
				cout<<"\t\tDesea buscar otra nombre? s/S: "; cin>>resp;
					system("cls");
			}while(resp=='s'||resp=='S');
			return;
			break;	
            default:
			cout<<"\t\tOpcion no valida"<<endl;
						
		}
}

int validarNum(char numero[10]){

	int i=0,sw=0,j;
	j=strlen(numero);
	
	while(i<j &&sw==0){
		if(isdigit(numero[i])!=0){
			i++;
		}else{
			sw=1;
		}
	}
	return sw;
}

int validarCadenas(char cadena[50]){
	int i=0, validandoL=0, j;
	j=strlen(cadena); //se asigna el numero de caracteres que tiene la cadena a J
	
	while(i<j&&validandoL==0){
	
		if(isalpha(cadena[i])!=0||cadena[i]==32) // 32 para que acepte espacios tambien 
		{
			i++; //si es una letra avanza de lo contrario entra al else para salirse del ciclo
		}else{
			validandoL=1;
		}	
	}	
 return validandoL;
}