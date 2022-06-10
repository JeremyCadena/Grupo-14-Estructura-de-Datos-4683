/**
 * @file marquesina.h
 * @authors Cadena Jeremy - Tipan Dylan 
 * @brief Clase Marquesina
 * @version 0.2
 * @date 2022-06-9
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <thread>
#include <chrono>
#include <functional>
#include <string>
#include <Windows.h>

class Marquesina {
	private:
	std::thread cadena;

	std::string marquee_limit(std::string& text, size_t limit) {
		std::string temp = text;
		text.erase(0, 1);
		text += temp[0];

		return text.substr(0, limit);
	}
	
	public:
	/**
	 * @brief Construye un nuevo objeto de Marquesina
	 * @param texto Cadena string 
	 */
	Marquesina(std::string texto) {
		cadena = std::thread(std::bind(&Marquesina::procesarHilo, this, texto));
	}

	/**
	 * @brief procesarHilo Deteccion de mensaje ingresado
	 * @param mensaje Cadena string
	 */
	void procesarHilo(std::string mensaje) {
		HANDLE conhandler = GetStdHandle(STD_OUTPUT_HANDLE);
		std::string texto(mensaje);
		std::string mTexto = texto;

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int col, fil;

		GetConsoleScreenBufferInfo(conhandler, &csbi);
		col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		fil = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		if (mTexto.length() < col) {
			while (mTexto.length() < col) {
				mTexto.append(" ");
			}
		}

		SetConsoleCursorPosition(conhandler, {0, 3});

		while (true) {
			CHAR_INFO* buff = (CHAR_INFO*)calloc(col, sizeof(CHAR_INFO));
			int i = 0;

			for (int i = 0; i < mTexto.length(); i++) {
				buff[i].Char.AsciiChar = mTexto.at(i);
				buff[i].Attributes = 15;
			}

			SMALL_RECT pos = { 0, 0, col, 1 };
			WriteConsoleOutputA(conhandler, buff, {(SHORT)col, 1}, { 0, 0 }, &pos);
			free(buff);

			std::this_thread::sleep_for(std::chrono::milliseconds(200));

			mTexto = marquee_limit(mTexto, col); // limite de la marquesina
		}
	}

	/**
	 * @brief  Presenta en movimiento el mensaje previo ingresado
	 * 
	 */
	void presentar() {
		cadena.detach();
	}
};