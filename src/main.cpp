//============================================================================
// Name        : prueba.cpp
// Author      : Miguel Ricardo Jimenez Gomez
// Version     :
// Copyright   : Arriba el america
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <ctime>

#include "Mapa.h"
#include "Dibujar.h"

#define TIEMPO_ESPERA 100

using namespace std;

HANDLE wHnd, rHnd;
Mapa *mapa;
Dibujar *dibujar;

int main() {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitleA(TEXT("Prueba"));
	SMALL_RECT windowSize = {0, 0, 29, 29};
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = {30, 30};
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	cout << "Dificultad (0=Facil, 1=Medio, 2=Dificil): " << endl;
	unsigned char dificultad;
	cin >> dificultad;
	mapa = new Mapa(10, 10);
	mapa->iniciar(dificultad);
	dibujar = new Dibujar(mapa, wHnd, 3);
	dibujar->iniciar();
	bool appIsRunning = true;
	DWORD numEventos=0;
	while(appIsRunning)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEventos);
		if(numEventos > 0)
		{
			DWORD numEventosLeidos=0;
			INPUT_RECORD *eventosBuffer = new INPUT_RECORD[numEventos];
			ReadConsoleInputA(rHnd, eventosBuffer, numEventos, &numEventosLeidos);
			for(DWORD i=0;i<numEventosLeidos;i++)
				if(eventosBuffer[i].EventType == KEY_EVENT && !eventosBuffer[i].Event.KeyEvent.bKeyDown)
					switch(eventosBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{
					case VK_ESCAPE:
						appIsRunning = false;
						break;
					case VK_LEFT:
						mapa->moverIzquierda();
						break;
					case VK_RIGHT:
						mapa->moverDerecha();
						break;
					}
			delete[] eventosBuffer;
		}
	}
	delete mapa;
	delete dibujar;
	return 0;
}
