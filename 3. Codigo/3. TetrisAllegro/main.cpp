/*
	UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
	CARRERA: TECNOLOGÍAS DE LA INFORMACIÓN

PROGRAMA: PROYECTO U1
AUTOR/ES:

	CADENA JEREMY
	GUERRA LUCIANA
	TIPAN DYLAN

FECHA CREACIÓN: 10/07/2022
FECHA MODIFICACIÓN:19/07/2022
GRUPO:14
GITHUB DEL GRUPO:

			https://github.com/JeremyCadena/Grupo-14-Estructura-de-Datos-4683.git

ASIGNATURA: ESTRUCTURA DE DATOS
NRC:4683
*/

/**
 * @file Main.cpp
 * @author Grupo 14
 * @brief Programa que simula el videojuego tetris 
 * @version 0.2
 * @date 2022-07-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <allegro.h>
#include <iostream>
#include <time.h>
#include "Tetris.h"

 /**
  * @brief Funcion que inicializa la ventana grafica de allegro
  *
  * @param 
  */
void init();

/**
 * @brief Funcion que culmina la ventana grafica de allegro
 *
 * @param 
 */
void deinit();

void tetris();

int main() {
	tetris();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO, ALTO, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
}

void deinit() {
	clear_keybuf();
}

/**
 * @brief Funcion que empieza nuestro juego de tetris
 *
 * @param
 */
 
void tetris(){
	init();
	
	//BITMAPS
	BITMAP *buffer = create_bitmap(ANCHO,ALTO); 
	BITMAP *muroH = load_bitmap("Imagenes/muro_horizontal.bmp", NULL);
	BITMAP *muroV = load_bitmap("Imagenes/muro_vertical.bmp", NULL);
	BITMAP *img_b = load_bitmap("Imagenes/piezas.bmp", NULL);
	BITMAP *elimn = load_bitmap("Imagenes/elimina_piezas.bmp", NULL);
	BITMAP *img_texto = load_bitmap("Imagenes/textos.bmp", NULL);
	BITMAP *img_num = load_bitmap("Imagenes/numeros.bmp", NULL);
	BITMAP *goBmp = load_bitmap("Imagenes/GameOver.bmp", NULL);
	
	salto:
		
	//INTEGERS
	int vcaida = 7, aux = 0, pb = 0;
	int random, fila, cfila, fin;
	int puntos = 0, nivel = 0;
	
	//BOOLEANOS
	bool colabajo = false;
	bool colizq = false;
	bool colder = false;
	bool gameOver = false;
	
	//PIEZAS
	Bloque b_prin = { 5, 2, NORMAL};
	Bloque b_prin_sig = { 15, 5, NORMAL};
	Bloque bJ[3] = { { 0, -1, NORMAL}, { 1, -1, NORMAL}, { 0, 1, NORMAL} };
	Bloque bT[3] = { { 0, -1, NORMAL}, { 1, 0, NORMAL}, { -1, 0, NORMAL} };
	Bloque bO[3] = { { 0, -1, NORMAL}, { -1, -1, NORMAL}, { -1, 0, NORMAL} };
	Bloque bI[3] = { { 0, -1, NORMAL}, { 0, 1, NORMAL}, { 0, 2, NORMAL} };
	Bloque bL[3] = { { 0, -1, NORMAL}, { 0, 1, NORMAL}, { 1, 1, NORMAL} };
	Bloque bS[3] = { { 1, -1, NORMAL}, { 0, -1, NORMAL}, { -1, 0, NORMAL} };
	Bloque bZ[3] = { { 1, 1, NORMAL}, { 0, 1, NORMAL}, { -1, 0, NORMAL} };
	
	//GENERA LA PIEZA ALEATORIA
	Pieza pAc(b_prin, bS, VERDE);
	srand(time(NULL));
	random = 1 + rand() % 7;
	if(random == 1) pAc.setBls(bJ), pAc.setColor(AZUL);
	else if(random == 2) pAc.setBls(bT), pAc.setColor(MORADO);
	else if(random == 3) pAc.setBls(bO), pAc.setColor(AMARILLO);
	else if(random == 4) pAc.setBls(bI), pAc.setColor(NARANJA);
	else if(random == 5) pAc.setBls(bL), pAc.setColor(NARANJA);
	else if(random == 6) pAc.setBls(bS), pAc.setColor(VERDE);
	else if(random == 7) pAc.setBls(bZ), pAc.setColor(ROJO);
	
	Pieza pSig(b_prin_sig, bT, 0);
	random = 1 + rand() % 7;
	if(random == 1) pSig.setBls(bJ), pAc.setColor(AZUL);
	else if(random == 2) pSig.setBls(bT), pSig.setColor(MORADO);
	else if(random == 3) pSig.setBls(bO), pSig.setColor(AMARILLO);
	else if(random == 4) pSig.setBls(bI), pSig.setColor(NARANJA);
	else if(random == 5) pSig.setBls(bL), pSig.setColor(NARANJA);
	else if(random == 6) pSig.setBls(bS), pSig.setColor(VERDE);
	else if(random == 7) pSig.setBls(bZ), pSig.setColor(ROJO);
	
	
	limpiar_mapa();
	while (!key[KEY_ESC] && gameOver == false) {
		clear_to_color(buffer, 0x000000);
		mostrar_muros(buffer, muroH, muroV);
		mostrar_mapa(buffer, img_b);
		mostrar_puntos(buffer, img_texto, img_num, puntos, nivel);
		
		if(pAc.colision_abajo())colabajo = true;
		if(pAc.colision_derecha())colder = true;
		if(pAc.colision_izquierda())colizq = true;
		
		//BAJAR LA PIEZA
		if(pb++ >= vcaida && !colabajo){
			pb = 0;
			pAc.incry(1);
		}
		
		//NUEVA PIEZA
		if(colabajo){
			pAc.insertar_mapa();
			fila = pAc.getY() + 2;
			while(fila > 19)
				fila--;
			fin = fila -4;
			cfila = fila;
			while (fila >= fin){
				if(pAc.fila_llena(fila)){
					for (int i=1; i<11; i++) blit(elimn, buffer, 0, 0, i*TAMBLOQUE, fila*TAMBLOQUE, 25, 25);
					blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
					for (int i=1; i<11; i++){
						blit(elimn, buffer, 25, 0, i*TAMBLOQUE, fila*TAMBLOQUE, 25, 25);
						blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
						blit(elimn, buffer, 50, 0, i*TAMBLOQUE, fila*TAMBLOQUE, 25, 25);
						rest(8);
					}
					puntos++;
					if (puntos % 5 == 0) nivel++;
				}
				fila--;
			}
			fila = cfila;
			while (fila >= fin){
				if(pAc.fila_llena(fila)) eliminar_fila(fila);
				else fila--;
			}
			if (pAc.getY() < 3){
				gameOver = true;
				break;
			}
			b_prin.x = 5, b_prin.y = 2;
			pAc = pSig;
			pAc.setBPrin(b_prin);
			random = 1 + rand() % 7;
			if(random == 1) pSig.setBls(bJ), pAc.setColor(AZUL);
		else if(random == 2) pSig.setBls(bT), pSig.setColor(MORADO);
		else if(random == 3) pSig.setBls(bO), pSig.setColor(AMARILLO);
		else if(random == 4) pSig.setBls(bI), pSig.setColor(NARANJA);
		else if(random == 5) pSig.setBls(bL), pSig.setColor(NARANJA);
		else if(random == 6) pSig.setBls(bS), pSig.setColor(VERDE);
		else if(random == 7) pSig.setBls(bZ), pSig.setColor(ROJO);
			colabajo = false;
			rest(100);
		}
		//DETECCION DE TECLAS
		if (key[KEY_RIGHT] && !colder) pAc.incrX(1);
		if (key[KEY_LEFT] && !colizq) pAc.incrX(-1);
		if (key[KEY_UP]){
			Pieza pAux= pAc;
			pAc.rotar();
			pAc.incrX(1);
			if (pAc.colision_izquierda()) pAc = pAux;
			pAc.incrX(-2);
			if (pAc.colision_derecha()) pAc = pAux;
			pAc.incrX(1);
		}
		if (key[KEY_DOWN]) vcaida = 0;
		
		if(++aux >= 7){
			vcaida = 7;
			aux = 0;
		}
		
		pAc.mostrar_pieza(buffer, img_b);
		pSig.mostrar_pieza(buffer, img_b);
		blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
		
		//REINICIAR LOS BOOLEANOS
		colder = false;
		colizq = false;
		
		rest(50);	//Se retrasa 5 milisegundos
	}

	if (gameOver){
		while(!key[KEY_ESC]){
			blit(goBmp, buffer, 0, 0, 29, 175, 243, 108);
			if (key[KEY_ENTER]) goto salto;
			blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
			rest(5);
		}
	}
	deinit();
}
