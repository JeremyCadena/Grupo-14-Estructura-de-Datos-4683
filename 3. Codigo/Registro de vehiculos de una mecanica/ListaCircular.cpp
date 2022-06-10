#include "ListaCircular.hpp"
using namespace std;

int validarCadenas(char cadena[50]);
int validarNum(char numero[10]);
int sw=0,validandoL;

ListaCircular::ListaCircular(){
    raiz = NULL;
}

void ListaCircular::agregar(){
    ofstream apArchivo;  
    apArchivo.open("Registro.txt", ios::app);
    if ( ! apArchivo ) {
        cout << "\nProblema al abrir archivo --> Registro.txt" <<endl;
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
	cout<<"\n\t\tRegistro de Vehiculo exitoso!"<<endl;

	Vehiculo *copia=raiz;	
	// Imprimir la lista
	apArchivo << "\n\t\t\t----------------------------" << endl;
	apArchivo << "\t\t\t|     Lista de Registros    |" << endl;
	apArchivo << "\t\t\t----------------------------" << endl;
	do {
		apArchivo<<endl;	
		apArchivo<<"\t\t--------------------------------------------"<<endl;
		apArchivo<<"\t\tMarca: "<<copia->marca<<endl;
		apArchivo<<"\t\tPlaca Vehicular: "<<copia->placaVehicular<<endl;
		apArchivo<<"\t\tPropietario: "<<copia->nombrePropietario<<endl;
		apArchivo<<endl;
		copia=copia->siguiente;

	}while( copia != raiz);
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
		cout << "\t\tNo hay registros disponibles" << endl;
		return;
	}

    cout << "\n\t\t\t--------------------------" << endl;
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

    cout << "\n\t\t\t--------------------------" << endl;
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
		cout<<"\t\tSeguro que desea eliminar? (S/s): "; cin >> resp;
		if ( resp=='S' || resp=='s') {
         while ( raiz->siguiente != eliminar ) {		 
              raiz=raiz->siguiente;
         }
         raiz->siguiente = raiz->siguiente->siguiente;
         raiz->siguiente->siguiente->anterior = raiz;
         free(eliminar);
         cout <<"\t\tREGISTRO ELIMINADO" << endl;
         return;
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
				return;
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
				return;
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
					cout<<"\t\tDesea buscar otra nombre? s/S: "; cin>>resp;
					system("cls");
				}while(resp=='s'||resp=='S');
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