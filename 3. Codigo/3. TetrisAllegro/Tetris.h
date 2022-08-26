/**
 * @file Tetris.h
 * @author CADENA JEREMY - GUERRA LUCIANA -	TIPAN DYLAN
 * @brief Clase que simula el videojuego tetris
 * @version 0.2
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <allegro.h>
//TAMAÑO DE CONSOLA
#define ANCHO		1280
#define ALTO 		720
#define TAMBLOQUE 	25
//COLORES
#define NARANJA		0
#define AZUL		1
#define MORADO		2
#define ROJO		3
#define AMARILLO	4
#define VERDE		5
//TIPO DE BLOQUE
#define NORMAL	0
#define SMEDIO	1
#define SOMBRA	2

void mostrar_fondo(BITMAP*, BITMAP*);
void mostrar_muros(BITMAP*, BITMAP*, BITMAP*);
void mostrar_numero(BITMAP*, BITMAP*, int, int, int);
void mostrar_puntos(BITMAP*, BITMAP*, BITMAP*, int, int);
void mostrar_bloque(BITMAP*, BITMAP*, int, int, int, int);
void limpiar_mapa();
void mostrar_mapa(BITMAP*, BITMAP*);
void eliminar_fila(int fila);

struct Bloque{
	int x, y, tipo;
};

class Pieza{
	private:
		Bloque b_prin;	//Bloque ancla
		Bloque bls[3];	//Bloques secundarios
		int color_p;
	public:
		Pieza(Bloque _b_prin, Bloque _bls[3], int _color_p);
		
		int getY(){ return b_prin.y;}
		int getX(){ return b_prin.x;}
		void setBPrin(Bloque newB_prin){ b_prin = newB_prin;}
		void setBls(Bloque newBls[3]){ for(int i=0; i<3; i++) bls[i] = newBls[i];}
		void setColor(int newColor){ color_p = newColor;}
		/**
		* @brief Funcion que maneja las piezas del tetris
		*
		* @param *buffer
		* @param *img_b
		*/
		void mostrar_pieza(BITMAP *buffer, BITMAP *img_b);
		
		/**
		* @brief Mueve la pieza de tetris de manera horizontal (eje x)
		*
		* @param incr
		*/
		void incrX(int incr){ b_prin.x += incr; }
		
		/**
		* @brief Mueve la pieza de tetris de manera vertical (eje y)
		*
		* @param incr
		*/
		void incry(int incr){ b_prin.y += incr; }
		
		/**
		* @brief Regresa un True choca contra la parede inferior o false si no.
		*
		* @return true
		* @return false
		*/
		bool colision_abajo();
		
		/**
		* @brief Regresa un True choca contra la parede lateral derecha o false si no.
		*
		* @return true
		* @return false
		*/
		bool colision_derecha();
		
		/**
		* @brief Regresa un True choca contra la parede lateral izquierda o false si no.
		*
		* @return true
		* @return false
		*/
		bool colision_izquierda();
		bool fila_llena(int fila);
		
		void insertar_mapa();
		void rotar();
		
	
};
