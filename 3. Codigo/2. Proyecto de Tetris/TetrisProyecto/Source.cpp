#include <iostream>
#include <windows.h>
#include <thread>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <string>



using namespace std;

wstring tetromino[7];				// Numero de piezas de Tetris
int nCampoAncho = 50;				// 12 (Espacios necesarios) * 4 48
int nCampoAlto = 33;				// 24 (Espacios necesarios) * 3 33
unsigned char* pCampo = nullptr;	// Dinamico para poder rellenar con las piezas en tiempo real
int nScreenWidth = 120;				// Tamaño X de la Consola (columnas) 120
int nScreenHeight = 80;				// Tamaño Y de la Consola (filas) 80


int Rotacion(int, int, int);
bool PiezaCabe(int, int, int, int);

int main() {
	system("title Tetris Proyecto");
#pragma region Inicializa Piezas del Tetris y Campo
	//I
	tetromino[0].append(L"....XX..");//.append() nos permite concatenar matrices o listas.
	tetromino[0].append(L"....XX..");
	tetromino[0].append(L"....XX..");
	tetromino[0].append(L"....XX..");
	tetromino[0].append(L"....XX..");
	tetromino[0].append(L"....XX..");
	tetromino[0].append(L"....XX..");
	tetromino[0].append(L"....XX..");

	//Z
	tetromino[1].append(L"....XX..");
	tetromino[1].append(L"....XX..");
	tetromino[1].append(L"..XXXX..");
	tetromino[1].append(L"..XXXX..");
	tetromino[1].append(L"..XX....");
	tetromino[1].append(L"..XX....");
	tetromino[1].append(L"........");
	tetromino[1].append(L"........");

	//S
	tetromino[2].append(L"..XX....");
	tetromino[2].append(L"..XX....");
	tetromino[2].append(L"..XXXX..");
	tetromino[2].append(L"..XXXX..");
	tetromino[2].append(L"....XX..");
	tetromino[2].append(L"....XX..");
	tetromino[2].append(L"........");
	tetromino[2].append(L"........");

	//O
	tetromino[3].append(L"........");
	tetromino[3].append(L"........");
	tetromino[3].append(L"..XXXX..");
	tetromino[3].append(L"..XXXX..");
	tetromino[3].append(L"..XXXX..");
	tetromino[3].append(L"..XXXX..");
	tetromino[3].append(L"........");
	tetromino[3].append(L"........");

	//T
	tetromino[4].append(L"..XX....");
	tetromino[4].append(L"..XX....");
	tetromino[4].append(L"..XXXX..");
	tetromino[4].append(L"..XXXX..");
	tetromino[4].append(L"..XX....");
	tetromino[4].append(L"..XX....");
	tetromino[4].append(L"........");
	tetromino[4].append(L"........");

	//L
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XX....");
	tetromino[5].append(L"..XXXX..");
	tetromino[5].append(L"..XXXX..");
	tetromino[5].append(L"........");
	tetromino[5].append(L"........");

	//J
	tetromino[6].append(L"....XX..");
	tetromino[6].append(L"....XX..");
	tetromino[6].append(L"....XX..");
	tetromino[6].append(L"....XX..");
	tetromino[6].append(L"..XXXX..");
	tetromino[6].append(L"..XXXX..");
	tetromino[6].append(L"........");
	tetromino[6].append(L"........");

	//Campo
	pCampo = new unsigned char[nCampoAncho * nCampoAlto]; //Genera el Campo
	for (int x = 0; x < nCampoAncho; x++)// Limite del Campo
		for (int y = 0; y < nCampoAlto; y++)
			pCampo[y * nCampoAncho + x] = (x == 0 || x == nCampoAncho - 1 || y == nCampoAlto - 1) ? 9 : 0;
#pragma endregion

	//Herramientas Logicas del Juego
	bool bGameOver = false;

	srand(time(NULL));
	int nPiezaActual = 0;			//rand() % 7;
	int nRotacionActual = 0;
	int nActualX = (nCampoAncho / 2) - 2;
	int nActualY = 0;
	int nPuntaje = 0;

	bool bKey[4];
	bool bRotando = true;
	bool TableroPintado = false;

	int nVelocidad = 20;
	int nContVelocidad = 0;
	int ContPiezas = 0;
	bool bFuerzaBajo = false;

	vector<int> vLineas;

	/* Búfer de Pantalla (Código Copiado) */
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,NULL , CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	/* Loop del Juego */

	while (!bGameOver) {
		
		// MIENTRAS se JUEGA ============================================================

		this_thread::sleep_for(50ms);
		nContVelocidad++; // Velocidad de bajar la pieza
		bFuerzaBajo = (nContVelocidad == nVelocidad);
		// INPUT ========================================================================
		for (int k = 0; k < 4; k++)								//  D   I   A Z
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
		// LOGICA DEL JUEGO =============================================================
		//Izquierda
		if (bKey[1]) {
			if (PiezaCabe(nPiezaActual, nRotacionActual, nActualX - 2, nActualY)) {
				nActualX = nActualX - 2;
			}
		}

		//Derecha
		if (bKey[0]) {
			if (PiezaCabe(nPiezaActual, nRotacionActual, nActualX + 2, nActualY)) {
				nActualX = nActualX + 2;
			}
		}

		//Abajo
		if (bKey[2]) {
			if (PiezaCabe(nPiezaActual, nRotacionActual, nActualX, nActualY + 1)) {
				nActualY = nActualY + 1;
			}
		}

		//Rota la Pieza
		if (bKey[3])
		{
			nRotacionActual += (bRotando && PiezaCabe(nPiezaActual, nRotacionActual + 1, nActualX, nActualY)) ? 1 : 0;
			bRotando = false;
		}
		else
			bRotando = true;

		if (bFuerzaBajo) {
			if (PiezaCabe(nPiezaActual, nRotacionActual, nActualX, nActualY + 1))
				nActualY++; // Si puede solo sigue bajando
			else {
				// Si no puede bloquea la pieza en el campo
				for (int px = 0; px < 8; px++)
					for (int py = 0; py < 8; py++)
						if (tetromino[nPiezaActual][Rotacion(px, py, nRotacionActual)] == L'X')
							pCampo[(nActualY + py) * nCampoAncho + (nActualX + px)] = nPiezaActual + 1;

				ContPiezas++;
				if (ContPiezas % 10 == 0)
					if (nVelocidad >= 10) nVelocidad--;

				// Revisa si hemos completado alguna linea
				for (int py = 0; py < 8; py++)
					if (nActualY + py < nCampoAlto - 1) {
						bool bLinea = true;
						for (int px = 1; px < nCampoAncho - 1; px++)
							bLinea &= (pCampo[(nActualY + py) * nCampoAncho + px]) != 0;

						if (bLinea) {
							//Elimina la linea, modifica la linea por #
							for (int px = 1; px < nCampoAncho - 1; px++)
								pCampo[(nActualY + py) * nCampoAncho + px] = 8;
							vLineas.push_back(nActualY + py);
						}
					}

				nPuntaje += 25;
				if (!vLineas.empty()) nPuntaje += (1 << vLineas.size()) * 100;
				// Elige la siguiente pieza
				nActualX = nCampoAncho / 2;
				nActualY = 0;
				nRotacionActual = 0;
				nPiezaActual = rand() % 7;
				//Si no se puede poner mas piezas
				bGameOver = !PiezaCabe(nPiezaActual, nRotacionActual, nActualX, nActualY);
			}
			nContVelocidad = 0;
		}
		// SALIDA RENDERIZADA ===========================================================

		// Dibuja el Campo
		for (int x = 0; x < nCampoAncho; x++)
			for (int y = 0; y < nCampoAlto; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ░▒▓░▒▓░#█"[pCampo[y * nCampoAncho + x]];	//Caracteres mostrados
		
		
		TableroPintado = true;
		// Dibuja la Pieza Actual
		for (int px = 0; px < 8; px++)
			for (int py = 0;py < 8; py++)
				if (tetromino[nPiezaActual][Rotacion(px, py, nRotacionActual)] == L'X') {
					screen[(nActualY + py + 2) * nScreenWidth + (nActualX + px + 2)] = L'▒';
			}

		// Dibuja el puntaje
		swprintf_s(&screen[2 * nScreenWidth + nCampoAncho + 6], 16, L"SCORE: %8d", nPuntaje);

		if (!vLineas.empty()) {

			
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 10,2 }, &dwBytesWritten);
			this_thread::sleep_for(400ms);

			for (auto& v : vLineas)
				for (int px = 1; px < nCampoAncho - 1; px++)
				{
					for (int py = v; py > 0; py--)
						pCampo[py * nCampoAncho + px] = pCampo[(py - 1) * nCampoAncho + px];
					pCampo[px] = 0;
				}

			vLineas.clear();
		}

		// Visualizacion Frame - Pone la consola en el eje 0 0 de la pantalla

		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 10,2 }, &dwBytesWritten);
	}
	
	CloseHandle(hConsole);
	cout << endl << endl << "\t\tFin del Juego!!" <<endl <<"\t\tPuntaje:" << nPuntaje << endl << endl << endl;
	system("pause");

	return 0;
}
int Rotacion(int px, int py, int r) {
	// px: Posicion X
	// py: Posicion Y
	// r: Grado de rotacion 0, 1, 2, 3

	switch (r % 4) {
	case 0: return py * 8 + px;			// 0 grados
	case 1: return 56 + py - (px * 8);	// 90 grados
	case 2: return 63 - (py * 8) - px;	// 180 grados 
	case 3: return 7 - py + (px * 8);	// 270 grados
	}
	return 0;
}
bool PiezaCabe(int nTetromino, int nRotacion, int nPosX, int nPosY) {
	for (int px = 0; px < 8; px++)
		for (int py = 0; py < 8; py++) {
			//Direccion de pieza
			int pi = Rotacion(px, py, nRotacion);

			//Direccion en el campo
			int fi = (nPosY + py) * nCampoAncho + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nCampoAncho) {
				if (nPosY + py >= 0 && nPosY + py < nCampoAlto) {
					if (tetromino[nTetromino][pi] != L'.' && pCampo[fi] != 0)
						return false; // falla en su primer movimiento
				}
			}
		}
	
	return true;
}