#include<stdlib.h>
#include "ListaCircular.cpp"

using namespace std;

int main(int argc, char** argv) {
	   
    int sw=0,validandoL;
	int convertir;
	char opcion[2]; // lo declaro como char para hacer la validacion de que solo ingrese numeros usando strlen
    ListaCircular lst;
								
	do{
		system("cls");
		cout<<"\n\n";
		cout<<"\t\t--------------------------------------"<<endl;
		cout<<"\t\t|         MECANICA SAN EDUARDO        |"<<endl;
		cout<<"\t\t--------------------------------------"<<endl;
		cout<<"\t\tRegistro de vehiculos................[1]"<<endl;
		cout<<endl;
		cout<<"\t\tConsultar vehiculo al inicio.........[2]"<<endl;
		cout<<endl;
		cout<<"\t\tConsultar vehiculo al final..........[3]"<<endl;
		cout<<endl;
		cout<<"\t\tBorrar un vehiculo...................[4]"<<endl;
		cout<<endl;
		cout<<"\t\tBuscar un vehiculo...................[5]"<<endl;
		cout<<endl;
		cout<<"\t\tSalida del sistema...................[0]"<<endl;
		cout<<endl;
		cout<<"\t\t----------------------------------------"<<endl;
		cout<<"\t\tINGRESE LA OPCION: ";cin>>opcion;
		system("cls");
		
		//valido que ingrese numero y no pueda ingresar otro tipo de dato
		sw=validarNum(opcion);
		if(sw!=0){
            cout<<"\t\tINGRESE NUMERO 1-6"<<endl;
		}	
			
		convertir = atoi(opcion); 
		switch(convertir){
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
			case 0:
				cout<<"\t\tGracias por usar el programa :D"<<endl;
				break;				
			default:
				cout<<"\t\tEsta opcion no es valida"<<endl;
				break;
	    }
	    system("pause");
	}while(convertir!=0);
	return 0;	
}
