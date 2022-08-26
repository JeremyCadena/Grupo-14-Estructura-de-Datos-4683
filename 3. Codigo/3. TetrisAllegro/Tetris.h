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

void mostrar_muros(BITMAP*, BITMAP*, BITMAP*);
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
		void mostrar_pieza(BITMAP *buffer, BITMAP *img_b);
		void incrX(int incr){ b_prin.x += incr; }
		void incry(int incr){ b_prin.y += incr; }
		bool colision_abajo();
		bool colision_derecha();
		bool colision_izquierda();
		bool fila_llena(int fila);
		void insertar_mapa();
		void setBPrin(Bloque newB_prin){ b_prin = newB_prin;}
		void setBls(Bloque newBls[3]){ for(int i=0; i<3; i++) bls[i] = newBls[i];}
		void setColor(int newColor){ color_p = newColor;}
		void rotar();
		int getY(){ return b_prin.y;}
		int getX(){ return b_prin.x;}
};
