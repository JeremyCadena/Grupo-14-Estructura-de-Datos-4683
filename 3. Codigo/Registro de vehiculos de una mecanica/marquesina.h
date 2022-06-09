#pragma once
#include <thread>
#include <chrono>
#include <functional>
#include <string>
#include <Windows.h>

class Marquesina {
public:
	Marquesina(std::string texto) {
		hilo = std::thread(std::bind(&Marquesina::procesarHilo, this, texto));
	}

	void procesarHilo(std::string mensaje) {
		HANDLE conhandler = GetStdHandle(STD_OUTPUT_HANDLE);
		std::string texto(mensaje);
		std::string marquesinaTexto = texto;

		// obtener tamaño consola
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int columnas, filas;

		GetConsoleScreenBufferInfo(conhandler, &csbi);
		columnas = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		filas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		if (marquesinaTexto.length() < columnas) {
			while (marquesinaTexto.length() < columnas) {
				marquesinaTexto.append(" ");
			}
		}

		SetConsoleCursorPosition(conhandler, {0, 3});

		while (true) {
			CHAR_INFO* buff = (CHAR_INFO*)calloc(columnas, sizeof(CHAR_INFO));
			int i = 0;

			for (int i = 0; i < marquesinaTexto.length(); i++) {
				buff[i].Char.AsciiChar = marquesinaTexto.at(i);
				buff[i].Attributes = 15;
			}

			SMALL_RECT pos = { 0, 0, columnas, 1 };
			WriteConsoleOutputA(conhandler, buff, {(SHORT)columnas, 1}, { 0, 0 }, &pos);
			free(buff);

			std::this_thread::sleep_for(std::chrono::milliseconds(200));

			marquesinaTexto = marquee_limit(marquesinaTexto, columnas);
		}
	}

	void iniciar() {
		hilo.detach();
	}

private:
	std::thread hilo;

	std::string marquee_limit(std::string& text, size_t limit) {
		std::string temp = text;
		text.erase(0, 1);
		text += temp[0];

		return text.substr(0, limit);
	}
};