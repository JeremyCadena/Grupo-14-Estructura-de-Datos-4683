/**
 * @file ListaCircular.cpp
 * @authors cadena Jeremy - Tipan Dylan
 * @brief Funciones de la ListaCircular
 * @version 1.0
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ListaCircular.hpp"
using namespace std;

int validarCadenas(char cadena[50]);
int validarNum(char numero[10]);
int sw=0,validandoL;

ListaCircular::ListaCircular(){
    raiz = NULL;
}

void ListaCircular::agregar(){
    ofstream apArchivo; //Registro primero ultimo
    ofstream upArchivo; //Registro ultimo primero
    ifstream inArchivo;
    apArchivo.open("Registro.txt", ios::app);
    upArchivo.open("RegistroInverso.txt", ios::trunc);
    inArchivo.open("Registro.txt", ios::in);
    if ( ! apArchivo ) {
        cout << "\nProblema al abrir archivo --> Registro.txt" <<endl;
        system("pause");
        return;
    }
    if ( ! upArchivo ) {
        cout << "\nProblema al abrir archivo --> RegistroInverso.txt" <<endl;
        system("pause");
        return;
    }
    Vehiculo *nuevo;
    int i=0;
    nuevo = new Vehiculo();
    if(nuevo==NULL){
        cout<<"\n\t\t\tNO HAY MEMORIA SUFICIENTE"<<endl;
		return;
	}

    cout<<"\n\t\t\t|Registro del Vehiculo|"<<endl;
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
	
	Vehiculo *aux = raiz;
	string nuevaPlaca;
	string raizPlaca;
	if(aux!=NULL){
		do{
			nuevaPlaca=nuevo->placaVehicular;
			raizPlaca=aux->placaVehicular;
			if(nuevaPlaca == raizPlaca){
				cout <<"\nERROR: La placa ya esta existente."<<endl;
				system("pause");
				return;
			}
			aux=aux->siguiente;
		}while(aux!=raiz);
	}
	if(raiz==NULL){
		nuevo->siguiente=nuevo;
		nuevo->anterior=nuevo;
		raiz=nuevo; //con esto se agrega el nodo
	}else{
		nuevo->siguiente=raiz;
		nuevo->anterior=raiz->anterior;
		raiz->anterior->siguiente=nuevo;
		raiz->anterior=nuevo;		
	}
	cout<<"\n\t\tRegistro de Vehiculo exitoso!"<<endl;
	system("pause");
	
	Vehiculo *copia = raiz;
	//Guardar la lista en el txt////////////////
	string linea;
	string vacio;//buscar si el txt esta vacio
	// Imprimir la lista
	while(!inArchivo.eof()){
		getline(inArchivo,linea);
		vacio=vacio+linea;
	}
	if(vacio.size()==0){
		apArchivo << "\n\t\t\t----------------------------" << endl;
		apArchivo << "\t\t\t|     Lista de Registros    |" << endl;
		apArchivo << "\t\t\t----------------------------" << endl;
		apArchivo<<endl;	
		apArchivo<<"\t\t--------------------------------------------"<<endl;
		
	}
		apArchivo<<"\t\tMarca: "<<nuevo->marca<<endl;
		apArchivo<<"\t\tPlaca Vehicular: "<<nuevo->placaVehicular<<endl;
		apArchivo<<"\t\tPropietario: "<<nuevo->nombrePropietario<<endl;
		apArchivo<<endl;
		apArchivo<<"\t\t--------------------------------------------"<<endl;
		
		upArchivo << "\n\t\t\t----------------------------" << endl;
		upArchivo << "\t\t\t|     Lista de Registros    |" << endl;
		upArchivo << "\t\t\t----------------------------" << endl;
		upArchivo<<endl;	
		upArchivo<<"\t\t--------------------------------------------"<<endl;
	do{	
        upArchivo<<"\t\tMarca: "<<copia->marca<<endl;
        upArchivo<<"\t\tPlaca Vehicular: "<<copia->placaVehicular<<endl;
        upArchivo<<"\t\tPropietario: "<<copia->nombrePropietario<<endl;
        upArchivo<<endl;
        upArchivo<<"\t\t--------------------------------------------"<<endl;
        copia=copia->anterior;
	}while(copia!=raiz->anterior);
	apArchivo.close();
	upArchivo.close();
	inArchivo.close();
	return;
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
		cout << "\n\t\tNo hay registros disponibles" << endl;
		system("pause");
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
	system("pause");
    return;
}

void ListaCircular::consultarUltimo(){
    Vehiculo *copia = raiz->anterior;
    if ( copia == NULL ) {
		cout << "\n\t\tNo hay registros disponibles" << endl;
		system("pause");
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
	} while( copia != raiz->anterior);
	system("pause");
    return;
}

void ListaCircular::borrar(){
    Vehiculo *eliminar = raiz;
    char resp;
    if ( eliminar == NULL ) {
		cout << "\n\t\tNo hay un registro existente" << endl;
		system("pause");
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
    const char *subtitulo[]={"------------------------------","|  Seguro que desea eliminar?  |","------------------------------"};
	    const char *subopciones[]={"\tSi","\tNo","------------------------------"};
	   	int o=2;
	   	int p=3;
	   	int op;
	   	system("pause");
	   	op=menuInteractivo(subtitulo,subopciones,o,p);
	   	switch(op){
	   		case 1:
	   			raiz=NULL;
      	 		free(eliminar);
      	 		cout <<"\n\t\tRegistro eliminado..." << endl;
      	 		system("pause");
	   			break;
	   		case 2:
	   			return;
    			break;
		}
	  return;
	}

	do
	{
		cout << "\t\t\t------------------------------" << endl;
		cout << "\t\t\t|   Eliminacion de registro   |" << endl;
		cout << "\t\t\t------------------------------" << endl;
		cout<<"\n\n";	
		
		cout<<"\t\t|Marca: "<<eliminar->marca<<endl;
		cout<<"\t\t|Placa Vehicular: "<<eliminar->placaVehicular<<endl;
		cout<<"\t\t|Propietario: "<<eliminar->nombrePropietario<<endl;
		cout<<"\t\t------------------------------" << endl;
		const char *subtitulo[]={"------------------------------","|  Seguro que desea eliminar?  |","------------------------------"};
	    const char *subopciones[]={"\tSi","\tNo","------------------------------"};
	   	int o=2;
	   	int p=3;
	   	int op;
	   	system("pause");
	   	op=menuInteractivo(subtitulo,subopciones,o,p);
	   	switch(op){
	   		case 1:
	   			while ( raiz->siguiente != eliminar ) {		 
             	    raiz=raiz->siguiente;
       			    }
       			    raiz->siguiente = raiz->siguiente->siguiente;
        			raiz->siguiente->siguiente->anterior = raiz;
        		    free(eliminar);
         			cout <<"\t\tREGISTRO ELIMINADO" << endl;
        			return;	
	   			break;
	   		case 2:
    			break;
		}
	  eliminar=eliminar->siguiente;			
	} while (raiz != eliminar);
	cout << "\t\tSe mostraron todos los registros..." << endl;
	return;	
}

void ListaCircular::buscar(){
    Vehiculo *copia = raiz;
    int opcionBuscar;
    if(copia==NULL){
        cout<<"\n\t\t No hay registros disponibles"<<endl;
        system("pause");
		return;
	}
	bool regresar = true;
	const char *titulo[]={"----------------------------","|   Busqueda de Vehiculos   |","----------------------------"};
	const char *opciones[]={"\tPor su marca","\tPor placa vehicular","\tPor propietario","Regresar al menu principal","-----------------------------"};
	int n=4;
	int m=3;
	do{
		bool menuBuscar=true;
		opcionBuscar=menuInteractivo(titulo,opciones,n,m);
    	switch(opcionBuscar){
			case 1:	
				char marca[12];
				char resp;
				do{
                	cout << "\n\t\t\t--------------------------" << endl;
					cout << "\t\t\t|        Registro         |" << endl;
					cout << "\t\t\t--------------------------" << endl;
					cout<<"\t\tMarca: ";
					fflush(stdin);
					cin.getline(marca,12);
					fflush(stdin);
						do{	
                	    	if(strcmp(copia->marca, marca) == 0){
                            	cout<<endl;
                            	cout<<"\t\t|Marca: "<< copia->marca<<endl;
						    	cout<<"\t\t|Placa Vehicular: "<< copia->placaVehicular<<endl;
						    	cout<<"\t\t|Propietario: "<< copia->nombrePropietario<<endl;
							}
							cout<<"\t\t--------------------------------" << endl;
    						copia=copia->siguiente;
	    		    	}while(copia!=raiz);
	    		    	const char *subtitulo[]={"----------------------------","|  Desea buscar otra marca?  |","----------------------------"};
	    		    	const char *subopciones[]={"\tSi","\tNo","----------------------------"};
	    		    	int o=2;
	    		    	int p=3;
	    		    	int op;
	    		    	system("pause");
	    		    	op=menuInteractivo(subtitulo,subopciones,o,p);
	    		    	switch(op){
	    		    		case 1:
	    		    			break;
	    		    		case 2:
	    		    			menuBuscar=false;
	    		    			break;
						}
				}while(menuBuscar);
				break;

			case 2:	
				char placaVehicular[10];
				do{
					cout << "\n\t\t\t--------------------------" << endl;
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
					const char *subtitulo[]={"----------------------------","|  Desea buscar otra placa?  |","----------------------------"};
	    		    const char *subopciones[]={"\tSi","\tNo","----------------------------"};
	    		    int o=2;
	    		    int p=3;
	    		    int op;
	    		    system("pause");
	    		    op=menuInteractivo(subtitulo,subopciones,o,p);
	    		    switch(op){
	    		    	case 1:
	    		    		break;
	    		    	case 2:
	    		    		menuBuscar=false;
	    		    		break;
					}
				}while(menuBuscar);
				break;	
			case 3:	
				char nombrePropietario[40];
				do{
					cout << "\n\t\t\t--------------------------" << endl;
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
					const char *subtitulo[]={"-------------------------------","|  Desea buscar otro nombre?  |","-------------------------------"};
	    		    const char *subopciones[]={"\tSi","\tNo","-------------------------------"};
	    		    int o=2;
	    		    int p=3;
	    		    int op;
	    		    system("pause");
	    		    op=menuInteractivo(subtitulo,subopciones,o,p);
	    		    switch(op){
	    		    	case 1:
	    		    		break;
	    		    	case 2:
	    		    		menuBuscar=false;
	    		    		break;
					}
				}while(menuBuscar);
				break;
			case 4:
				regresar = false;
				break;	
			}
	}while(regresar);
	return;
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