#include "Tetris.h"
#include <allegro.h>
int mapa[13][22];

Pieza::Pieza(Bloque _b_prin, Bloque _bls[3], int _color_p){
	b_prin = _b_prin;
	for(int i=0; i<3; i++)bls[i]=_bls[i];
	color_p = _color_p;
}

void Pieza::mostrar_pieza(BITMAP *buffer, BITMAP *img_b){
	int xbls, ybls;
	b_prin.tipo = SMEDIO;
	mostrar_bloque(buffer, img_b, b_prin.x, b_prin.y, color_p, b_prin.tipo);
	for(int i=0; i<3; i++){
		xbls = b_prin.x + bls[i].x;
		ybls = b_prin.y + bls[i].y;
		if ((xbls >= b_prin.x) && (ybls >=b_prin.y))bls[i].tipo = SOMBRA;
		else bls[i].tipo = NORMAL;
		mostrar_bloque(buffer, img_b, xbls, ybls, color_p, bls[i].tipo);
	}
}

bool Pieza::colision_abajo(){
	if(mapa[b_prin.y + 1][b_prin.x] != 9) return true;
	int xbls, ybls;
	for(int i=0; i<3; i++){
		xbls = b_prin.x + bls[i].x;
		ybls = b_prin.y + bls[i].y;
		if(mapa[ybls + 1][xbls] != 9)return true;
	}
	return false;
}

bool Pieza::colision_derecha(){
	if(mapa[b_prin.y][b_prin.x + 1] != 9) return true;
	int xbls, ybls;
	for(int i=0; i<3; i++){
		xbls = b_prin.x + bls[i].x;
		ybls = b_prin.y + bls[i].y;
		if(mapa[ybls][xbls + 1] != 9)return true;
	}
	return false;
}

bool Pieza::colision_izquierda(){
	if(mapa[b_prin.y][b_prin.x - 1] != 9) return true;
	int xbls, ybls;
	for(int i=0; i<3; i++){
		xbls = b_prin.x + bls[i].x;
		ybls = b_prin.y + bls[i].y;
		if(mapa[ybls][xbls - 1] != 9)return true;
	}
	return false;
}

void mostrar_muros(BITMAP *buffer, BITMAP *muroH, BITMAP *muroV){
	blit(muroV, buffer, 0, 0, 0, 0, 25, 500);
	blit(muroV, buffer, 0, 0, 275, 0, 25, 500);
	blit(muroH, buffer, 0, 0, 0, 500, 300, 25);
}

void limpiar_mapa(){
	for(int i=0; i<21; i++){
		for(int j=0; j<12; j++){
			if (j == 0 || j == 11 || i == 20) mapa[i][j] = 8;
			else mapa[i][j] = 9;
		}
	}
}
void mostrar_bloque(BITMAP *buffer, BITMAP *img_b, int xb, int yb, int color, int tipo){
	blit(img_b, buffer, tipo*TAMBLOQUE, color*TAMBLOQUE, xb*TAMBLOQUE, yb*TAMBLOQUE, TAMBLOQUE, TAMBLOQUE);
}
