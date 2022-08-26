/*
               UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE

Programa para ingresar un string y despues tranformarlo a numerico

Autores: Cadena Jeremy
		 Guerra  Luciana		 
		 Tipan Dilan
		 

Fecha de Creacion:  4 de agosto del 2022

Version del programa: Version 1

Materia: Estructuras de datos

Nrc: 4683
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>


void leerArchivo();
int infoC(int);
int metaCerca();
void MuestraLaberinto();
void borraRastro(int,int,int);
void mueveJugador(int);
void dimensionaMatriz();
void menu();
bool backtracking(char, int, int);

int **m; // Matriz dinamica que guarda los datos del archivo.            
int f,c; // filas y columnas del laberinto            
int fp,cp; // coordenadas del jugador
int fs,cs; // coordenadas de la salida o meta
int ifp,icp; // coordenadas iniciales del jugador
const int ARRIBA=0, DERECHA=1, IZQUIERDA=2, ABAJO=3;
int direccion=ARRIBA; // El jugador inicia viendo hacia arriba
int movs; // Cuenta los movimientos que hace un jugador para llegar a la meta
int espacios; // Cuenta los espacios que hay en un laberinto
bool pasoApaso=false; // true si queremos ver el recorrido paso a paso 
int metodo=1;
int pasosReales; // Solo para metodo backtracking
char ruta[20]="laberinto.txt"; // Nombre del archivo que tiene los datos del laberinto
bool ya;

bool backtracking(int i, int j){
   if(m[i][j]==3){ //comprueba si es solucion 
       MuestraLaberinto();
       fp=i; cp=j;
      return true;
   }
   m[i][j]=4; // Pone un punto por donde ya paso
   
   if (pasoApaso) {
      fp=i; cp=j;
      MuestraLaberinto();
      printf("Movimientos %d, pasos reales %d. ",movs, pasosReales);
      system("pause");
   }
   movs++;
   pasosReales++; 
    if(i-1>=0 && i-1<f && (m[i-1][j]==0 || m[i-1][j]==3))  if(backtracking(i-1, j)) return true; //arriba   
    if(j+1>=0 && j+1<c && (m[i][j+1]==0 || m[i][j+1]==3))  if(backtracking(i, j+1)) return true; //derecha     
    if(i+1>=0 && i+1<f && (m[i+1][j]==0 ||  m[i+1][j]==3)) if(backtracking(i+1, j)) return true; //abajo     
    if(j-1>=0 && j-1<c && (m[i][j-1]==0 ||  m[i][j-1]==3)) if(backtracking(i, j-1)) return true;//izquierda     
      
    m[i][j]=0;//desmarcar el camino porque devolverá un paso
    movs--;
    if (pasoApaso) {
      fp=i; cp=j;
      MuestraLaberinto();
      printf("Movimientos %d, pasos reales %d. ",movs, pasosReales);
      pasosReales++;
      system("pause");
   }
    return false;
}


void menu() {
     int opcion;
     
     while (opcion!=1) {
         system("cls");
         printf("------------------------ * M E N U *------------------------\n\n");
         printf ("\n Backtracking \n");
         printf(" \n Archivo:%s ",ruta);
         printf("\n\n\n");  
         
         printf("1) Resolver.\n\n");
         printf("2) Paso a Paso.\n\n");
         printf("3) mostrar.\n\n");
         printf("4) Salir.\n\n");
         
         while (opcion<0 && opcion>5)
         opcion = getch(); 
         printf("Opcion:");
         scanf ("%d",&opcion);        
         switch (opcion) {
         	   case 1: metodo=2; 
				break;
                case 2:
                    if (pasoApaso) pasoApaso=false;
                    else pasoApaso=true; 
					break;
					
					case 3:
						MuestraLaberinto();
						system("pause");
							break;
                case 4: exit(EXIT_SUCCESS);
				 break;
				 
				 
         }
     }                      
}

void dimensionaMatriz() {
     bool flag=true; // Sirve para que aumente el numero de columnas solo hasta que encuentre el primer salto de linea
    FILE *archivo;
    char caracter;
    int codigo; // codigo ascii del caracter leido de archivo
    
    archivo=fopen(ruta,"rt");   // comprobamos el archivo
    if (archivo==NULL) { 
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE); // Terminacion del programa por falla
    }
    f=1;c=1;
    while(!feof(archivo)) { 
            caracter=fgetc(archivo);
            codigo = caracter; // obtenemos el codigo Ascii de el caracter
            
            if (codigo==10) { // codigo del salto de linea
               f++; // Si encontramos un enter añadimos una fila mas a nuestra matriz
               if (flag) flag=false; // solo lo hacemos una vez
            } 
            else if (flag) c++;// añadimos una columna mas a nuestra matriz               
    }
    fclose(archivo); 

    m = (int **)malloc (f*sizeof(int *));        
    for (int j=0;j<f;j++) m[j] = (int *) malloc (c*sizeof(int));      
}

void leerArchivo() {
    int ff,cc,codigo;
    FILE *archivo;
    char caracter;      
    
    archivo=fopen(ruta,"rt"); // abrimos el archivo 
    if (archivo==NULL) { // En caso de que el archivo no exista o que este mal el nombre
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE); // Terminacion del programa por falla
    }
    
    for (int i=0;i<f-1;i++){
       for (int ii=0;ii<c;ii++) {
           caracter=fgetc(archivo);
           codigo = caracter; // obtenemos el codigo Ascii de el caracter               
           if (codigo!=10) {
               m[i][ii]=codigo-48; // usamos el codigo ascii del caracter del archivo para hacerlo entero
               if (m[i][ii]==2){ifp=i;icp=ii;}
               if (m[i][ii]==3){fs=i;cs=ii;}
               if (m[i][ii]==0) espacios++; // contamos los espacios 
           }
               
       }
    }        
    fclose(archivo);      
}

int infoC(int dir) { // Devuelve informacion de la casilla inmediata al jugador
    switch (dir) {
       case ARRIBA: return m[fp-1][cp];break;
       case ABAJO: return m[fp+1][cp]; break;
       case IZQUIERDA: return m[fp][cp-1]; break;
       case DERECHA: return m[fp][cp+1];break;
    }
}

int infoC(int dir,int dist) { // Devuelve informacion de la casilla a cierta distancia del jugador
    switch (dir) {
       case ARRIBA: return m[fp-dist][cp];break;
       case ABAJO: return m[fp+dist][cp]; break;
       case IZQUIERDA: return m[fp][cp-dist]; break;
       case DERECHA: return m[fp][cp+dist];break;
    }
}

int metaCerca() { // verifica si la meta esta a una posicion
       int lejos=1,aux=0,dir=-1;
       
       while (aux!=1 && aux!=3) {
           aux=infoC(ABAJO,lejos);
           if (aux==3) dir=ABAJO;
           lejos++;
       } lejos=1;aux=0;
       if (dir==-1) {
           while (aux!=1 && aux!=3) {
               aux=infoC(DERECHA,lejos);
               if (aux==3) dir=DERECHA;
               lejos++;
           } lejos=1;aux=0;
       }
       if (dir==-1) {
       while (aux!=1 && aux!=3) {
           aux=infoC(ARRIBA,lejos);
           if (aux==3) dir=ARRIBA;
           lejos++;
       } lejos=1;aux=0;
       }
       if (dir==-1) {
          while (aux!=1 && aux!=3) {
               aux=infoC(IZQUIERDA,lejos);
               if (aux==3) {dir=IZQUIERDA;}
               lejos++;
           } lejos=1;
       }
      return dir;  
}

void MuestraLaberinto() {
    system("cls");
    for (int i=0;i<f;i++) {
        for (int ii=0;ii<c;ii++) {
           if (m[i][ii]==1) printf ("%c",char(219)); // Bloque
           else if (i==fs && ii==cs) printf ("M");
           else if (i==fp && ii==cp) printf ("J");
           else if (m[i][ii]==4) printf ("."); // Es por donde ya paso el jugador
           else printf (" ");
        }
    printf ("\n");
    }
}

void Rastro(int dir,int f,int c) {
     switch(dir){ // Si ya pasamos por ahi lo recordamos para el sigueinte ciclo
        case ARRIBA: if (infoC(ARRIBA)==4) ya=true;
        case DERECHA: if (infoC(DERECHA)==4) ya=true;           
        case IZQUIERDA: if (infoC(IZQUIERDA)==4) ya=true;
        case ABAJO: if (infoC(ABAJO)==4) ya=true;            
     }
     m[f][c]=4; // Marcamos para poner un punto      
}
void mueveJugador(int dir) {
     switch(dir){ 
        case ARRIBA: m[fp-1][cp]=2;           
            fp--;      
        break;            
        case DERECHA: m[fp][cp+1]=2;             
             cp++;        
        break;            
        case IZQUIERDA: m[fp][cp-1]=2;        
            cp--;          
        break; 
        case ABAJO: m[fp+1][cp]=2;
            fp++;      
        break;            
     }     
}    

int main() { 
    int old_fp,old_cp;  // espacio en donde estaba el jugador 
    int meta=-1; 
    int codAscii;
    char tcl;
               
    dimensionaMatriz();       
    
    while (tcl!=27) {
        pasosReales=0;
        leerArchivo(); // Leemos archivo de texto con la informacion del laberinto 
        menu();
        movs=0; fp=ifp;cp=icp;
        while (fp!=fs || cp!=cs) {// Cuando encontramos la meta, salimos del ciclo
            old_fp=fp; old_cp=cp; 
            if (pasoApaso && metodo!=2) {
             MuestraLaberinto();
             printf("Movimientos %d. ",movs);
             system("pause");                 
            }
            if (meta!=-1) direccion=meta;  
                else  {
                      printf("Calculando...");
                      backtracking(fp, cp);
                }
            
            if (metodo!=2) {
                mueveJugador(direccion);
                Rastro(direccion,old_fp, old_cp);
                movs++;
                if (espacios*2-movs<0) break;
            }
        }
        MuestraLaberinto();
        if (fp==fs && cp==cs) {
           printf ("%d movimientos con el metodo de Backtracking.\n", movs);
        }
        else if (metodo!=2) printf ("El laberinto no tiene solucion.");
        printf("Quieres probar otro metodo? <esc> para no, cualquier tecla para si.");
        tcl = getch();
    }
    return 0;
}
