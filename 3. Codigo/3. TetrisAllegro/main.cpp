#include <allegro.h>
#include <iostream>
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
	
	//INTEGERS
	int vcaida = 7, aux = 0, pb = 0;
	
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
	Pieza pAc(b_prin, bS, VERDE);
	
	limpiar_mapa();
	while (!key[KEY_ESC]) {
		clear_to_color(buffer, 0x000000);
		mostrar_muros(buffer, muroH, muroV);
		
		if(pAc.colision_abajo())colabajo = true;
		if(pAc.colision_derecha())colder = true;
		if(pAc.colision_izquierda())colizq = true;
		
		//BAJAR LA PIEZA
		if(pb++ >= vcaida && !colabajo){
			pb = 0;
			pAc.incry(1);
		}
		
		//DETECCION DE TECLAS
		if (key[KEY_RIGHT] && !colder) pAc.incrX(1);
		if (key[KEY_LEFT] && !colizq) pAc.incrX(-1);
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
