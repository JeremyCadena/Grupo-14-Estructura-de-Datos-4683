#include <allegro.h>
#include <iostream>
#include <time.h>
#include "Tetris.h"

void init();
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

void tetris(){
	init();
	
	//BITMAPS
	BITMAP *buffer = create_bitmap(ANCHO,ALTO); 
	BITMAP *muroH = load_bitmap("Imagenes/muro_horizontal.bmp", NULL);
	BITMAP *muroV = load_bitmap("Imagenes/muro_vertical.bmp", NULL);
	BITMAP *img_b = load_bitmap("Imagenes/piezas.bmp", NULL);
	BITMAP *elimn = load_bitmap("Imagenes/elimina_piezas.bmp", NULL);
	
	//INTEGERS
	int vcaida = 7, aux = 0, pb = 0;
	int random, fila, cfila, fin;
	
	//BOOLEANOS
	bool colabajo = false;
	bool colizq = false;
	bool colder = false;
	
	//PIEZAS
	Bloque b_prin = { 5, 2, NORMAL};
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
	
	limpiar_mapa();
	while (!key[KEY_ESC]) {
		clear_to_color(buffer, 0x000000);
		mostrar_muros(buffer, muroH, muroV);
		mostrar_mapa(buffer, img_b);
		
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
				}
				fila--;
			}
			fila = cfila;
			while (fila >= fin){
				if(pAc.fila_llena(fila)) eliminar_fila(fila);
				else fila--;
			}
			b_prin.x = 5, b_prin.y = 2;
			pAc.setBPrin(b_prin);
			random = 1 + rand() % 7;
			if(random == 1) pAc.setBls(bJ), pAc.setColor(AZUL);
			else if(random == 2) pAc.setBls(bT), pAc.setColor(MORADO);
			else if(random == 3) pAc.setBls(bO), pAc.setColor(AMARILLO);
			else if(random == 4) pAc.setBls(bI), pAc.setColor(NARANJA);
			else if(random == 5) pAc.setBls(bL), pAc.setColor(NARANJA);
			else if(random == 6) pAc.setBls(bS), pAc.setColor(VERDE);
			else if(random == 7) pAc.setBls(bZ), pAc.setColor(ROJO);
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
		blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
		
		//REINICIAR LOS BOOLEANOS
		colder = false;
		colizq = false;
		
		rest(50);	//Se retrasa 5 milisegundos
	}

	deinit();
}
