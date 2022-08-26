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

void Pieza::insertar_mapa(){
	int xbls, ybls;
	mapa[b_prin.y][b_prin.x] = (b_prin.tipo*10) + color_p;
	for (int i=0; i<3; i++){
		xbls = b_prin.x + bls[i].x;
		ybls = b_prin.y + bls[i].y;
		mapa[ybls][xbls] = (bls[i].tipo*10) + color_p;
	}
}

void Pieza::rotar(){
	int aux;
	for(int i=0; i<3; i++){
		aux = bls[i].x;
		bls[i].x = bls[i].y;
		bls[i].y = aux;
		bls[i].x *= -1;
	}
}

bool Pieza::fila_llena(int fila){
	for (int i=1; i<11; i++)
		if(mapa[fila][i] == 9) return false;
	return true;
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

void mostrar_numero(BITMAP *buffer, BITMAP *img_num, int numero, int xnum, int ynum){
	int uDigito, pos = 0;
	if (numero !=0){
		while (numero != 0){
			uDigito = numero % 10;
			blit(img_num, buffer, uDigito*30, 0, xnum - pos, ynum, 30, 60);
			numero /= 10;
			pos += 38;
		}
	}
	else blit (img_num, buffer, 0, 0, xnum, ynum, 30, 60);
}

void mostrar_puntos(BITMAP* buffer, BITMAP* img_texto, BITMAP* img_num, int puntos, int nivel){
	blit (img_texto, buffer, 0, 0, 320, 50, 146, 34);
	blit (img_texto, buffer, 0, 34, 320, 210, 119, 34);
	mostrar_numero (buffer, img_num, puntos, 430, 260);
	blit(img_texto, buffer, 0, 68, 320, 340, 82, 34);
	mostrar_numero (buffer, img_num, nivel, 430, 390);
}

void mostrar_mapa(BITMAP *buffer, BITMAP *img_b){
	int t, c;
	for(int i=0; i<20; i++){
		for(int j=1; j<11; j++){
			if (mapa[i][j] != 9){
				t = mapa[i][j] / 10;
				c = mapa[i][j] % 10;
				mostrar_bloque(buffer, img_b, j, i, c, t);
			}
		}
	}
}

void eliminar_fila(int fila){
	for (int i=fila; i>0; i--)
		for(int j=1; j<11; j++)
			mapa[i][j] = mapa[i-1][j];
}