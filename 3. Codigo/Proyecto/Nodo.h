#include <string>
using namespace std;

class Nodo{
	private:
		int id;
		string marca;
		string placa;
		string propietario;
		Nodo* siguiente;
		Nodo* atras;
	public:
		void setid(int newid);
		int getid(void);
		void setmarca(string newmarca);
		string getmarca(void);
		void setplaca(string newplaca);
		string getplaca(void);
		void setpropietario(string newpropietario);
		string getpropietario(void);
		Nodo setsiguiente(Nodo* newsiguiente);
		Nodo* getsiguiente(Nodo);
		Nodo setatras(Nodo* newatras);
		Nodo* getatras(Nodo);
		void insertarNodo();
		void mostrarListaPU();
		void mostrarListaUP();
		Nodo();
		~Nodo();
}*primero, *ultimo;

