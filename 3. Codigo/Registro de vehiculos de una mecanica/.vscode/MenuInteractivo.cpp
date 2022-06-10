#include <iostream> 
#include <conio.h>
#include <stdio.h>  
#include <windows.h>  
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
 
int menuInteractivo(const char *titulo[],const char *opciones[], int n, int m){
	int opcionSeleccionada=1;
	int tecla;
	bool repite = true;
	
	do{
		system("cls");
		
		gotoxy(6,3+opcionSeleccionada); std::cout << "==>";
		//imprime titulo
		for(int j=0;j<m;j++){
				gotoxy(10, 1+j); std::cout << titulo[j];
		}
		//imprimir opciones
		for(int i = 0;i < n+1;i++){
			gotoxy(10,4+i);std::cout<<opciones[i];
		}
		
		do{
			tecla=getch();
		}while(tecla !=ARRIBA && tecla != ABAJO && tecla != ENTER);
		
		switch(tecla){
			case ARRIBA:
				opcionSeleccionada--;
				if (opcionSeleccionada < 1){
					opcionSeleccionada = n;
				}
				break;
			case ABAJO:
				opcionSeleccionada++;
				if(opcionSeleccionada > n){
					opcionSeleccionada = 1;
				}
				break;
			case ENTER:
				repite = false;
				break;
		}
	}while(repite);
	system("cls");
	return opcionSeleccionada;
}