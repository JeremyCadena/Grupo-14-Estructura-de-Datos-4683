/**
 * @file Main.cpp
 * @authors Cadena Jeremy - Tipan Dylan 
 * @brief Archivo principal de nuestro programa
 * @version 0.3
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define USER "admin"
#define PASS "******"
#include<stdlib.h>
#include "ListaCircular.cpp"
#include "Marquesina.h"

using namespace std;
void menu();
void menuOpcionPixelar();
void drawImage(std::string imagePath, HDC* console);
int main(int argc, char** argv) {
	string usuario;   
	string password;
	int k=0;
	bool ingresa = false;

	do
	{
		system("cls");
		cout<<"\t\t|        Login de Usuario        |"<<endl;
		cout<<"\t\t----------------------------------"<<endl;
		cout << "\n\tUsuario: ";
		getline(cin, usuario);
		cout << "\n\tPassword: ";
		getline(cin, password);
		if(usuario==USER && password==PASS){
			ingresa = true;
		}else{
			cout << "\n\tEl usuario y/o contraseña son incorrectos"<<endl;
			cin.get();
			k++;
		}	
	} while (ingresa == false && k <3);

	if(ingresa==false){
		cout << "Usted ha fallado todos los intentos de ingreso al programa" <<endl;
		cin.get();
	}else{
		cout << "\n\tBienvenido al sistema" <<endl;
		cin.get();
		Marquesina marquesina("Registro de vehiculos de una mecanica");
		menu();
		marquesina.presentar();
	}
	
	return 0;
}

void menu(){
	const char *titulo[] = {"--------------------------------------","|         MECANICA SAN EDUARDO        |","--------------------------------------"};
	const char *opciones[]={"\tRegistro de vehiculos","\tConsultar vehiculo","\tBuscar un vehiculo","\tFoto Pixelada", "\tManual de ayuda","\tSalida del sistema", "----------------------------------------"};
	int n = 6; // Numero de opciones
	int m = 3; //Numero de lineas de titulo
	int sw=0,validandoL;
	int convertir;
	int opcion;
    ListaCircular lst;
	bool repite = true;							
	do{
		opcion=menuInteractivo(titulo, opciones,n,m);
		switch(opcion){
			case 1:
				lst.agregar();
				break;
			case 2:
				lst.consultarPrimero();
				break;	
			case 3:
				lst.buscar();
				break;	
			case 4:
				menuOpcionPixelar();
				break;
			case 5:
				ShellExecute(GetDesktopWindow(), "open","Manual de registro de vehiculos.pdf", NULL, NULL, SW_SHOWNORMAL);
				break;
			case 6:
				repite = false;
				cout<<"\n\t\tGracias por usar el programa :D"<<endl;
				break;
	    }
	}while(repite);
}
void menuOpcionPixelar() {
		HWND console = GetConsoleWindow();
		HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
		HDC dc = GetDC(console);
				
		CONSOLE_FONT_INFOEX Font = { sizeof(Font) };
		GetCurrentConsoleFontEx(output, FALSE, &Font);
				
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 1;
		cfi.dwFontSize.Y = 1;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
				
		ShowWindow(console, SW_SHOWMAXIMIZED);
				
					//COORD pos = { 0, 15 };
					//SetConsoleCursorPosition(output, pos);
				
					std::cout << std::endl;
					drawImage("thumb_content_2255260-_1_.bmp", &dc);
					_getch();
				
					SetCurrentConsoleFontEx(output, FALSE, &Font);
					system("cls");
				}

void drawImage(std::string imagePath, HDC* console) {
	BMP image;
	image.ReadFromFile(imagePath.c_str());

	double original_width = image.TellWidth();
	double original_height = image.TellHeight();
	double ratio = ratio = original_width / original_height;

	double max_width = 500;
	double width = original_width;
	double height = original_height;

	if (original_width > max_width) {
		height = max_width / ratio;
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int RED = image.GetPixel(x, y).Red;
			int GREEN = image.GetPixel(x, y).Green;
			int BLUE = image.GetPixel(x, y).Blue;

			int ALPHA = image.GetPixel(x, y).Alpha;

			COLORREF COLOUR = RGB(RED, GREEN, BLUE);
			if (ALPHA == 0) {
				//SetPixel(*console, x, y, COLOUR);

				std::cout << "\033["
					<< 48
					<< ";2;"
					<< RED << ";"
					<< GREEN << ";"
					<< BLUE << "m"
					<< '##'
					<< "\033[0;00m";

				if (x == width - 1) {
					std::cout << std::endl;
				}
			}
		}
	}
}