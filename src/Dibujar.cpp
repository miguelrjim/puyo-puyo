/*
 * Dibujar.cpp
 *
 *  Created on: 06/03/2011
 *      Author: Miguel
 */

#include "Dibujar.h"

Dibujar::Dibujar(Mapa *mapa, HANDLE wHnd, unsigned tamCaja) {
	// TODO Auto-generated constructor stub
	this->mapa = mapa;
	mapaDibujar = mapa->obtenerMapa();
	finalizar = false;
	this->wHnd = wHnd;
	this->tamCaja = tamCaja;
	mapaBuffer = new CHAR_INFO[mapa->getAlto()*tamCaja*mapa->getAncho()*tamCaja];
	clear();
}

Dibujar::~Dibujar() {
	// TODO Auto-generated destructor stub
	terminar();
	WaitForSingleObject(hThread, INFINITE);
	delete[] mapaBuffer;
}

void Dibujar::iniciarDibujar()
{
	while(!finalizar)
	{
		while(!mapa->poderDibujar());
		for(unsigned i=0;i<mapa->getAlto();i++)
			for(unsigned d=0;d<mapa->getAncho();d++)
				if(!mapaDibujar[i*mapa->getAncho()+d])
					for(unsigned e=0;e<tamCaja;e++)
						for(unsigned f=0;f<tamCaja;f++)
							mapaBuffer[i*mapa->getAncho()*tamCaja*tamCaja+d*tamCaja +
							           (f+e*mapa->getAncho()*tamCaja)].Char.AsciiChar = ' ';
				else
					dibujarCaja(i*mapa->getAncho()*tamCaja*tamCaja+d*tamCaja, mapaDibujar[i*mapa->getAncho()+d]);
		COORD mapaBufSize, characterPos = {0, 0}, bufSize;
		SMALL_RECT writeArea = {0, 0, 0, 0};
		bufSize.X = mapa->getAncho()*tamCaja;
		bufSize.Y = mapa->getAlto()*tamCaja;
		mapaBufSize.X = mapa->getAncho()*tamCaja;
		mapaBufSize.Y = mapa->getAlto()*tamCaja;
		writeArea.Right = mapa->getAncho()*tamCaja-1;
		writeArea.Bottom = mapa->getAlto()*tamCaja-1;
		WriteConsoleOutputA(wHnd, mapaBuffer, bufSize, characterPos, &writeArea);
		Sleep(REFRESH_MS);
	}
}

void Dibujar::iniciar()
{
	hThread = (HANDLE)_beginthreadex(NULL, 0, &threadProc, this, 0, &threadId);
}

void Dibujar::terminar()
{
	finalizar = true;
}

void Dibujar::dibujarCaja(unsigned int pos, unsigned char tipo)
{
	mapaBuffer[pos].Char.AsciiChar = 0xDA; //Arriba
	mapaBuffer[pos+1].Char.AsciiChar = 0xC4;
	mapaBuffer[pos+2].Char.AsciiChar = 0xBF;
	mapaBuffer[pos+mapa->getAncho()*tamCaja].Char.AsciiChar = 0xB3; //Centro
	mapaBuffer[pos+1+mapa->getAncho()*tamCaja].Char.AsciiChar = 0xB0 + tipo; //Figura
	mapaBuffer[pos+2+mapa->getAncho()*tamCaja].Char.AsciiChar = 0xB3;
	mapaBuffer[pos+mapa->getAncho()*tamCaja*2].Char.AsciiChar = 0xC0; //Abajo
	mapaBuffer[pos+1+mapa->getAncho()*tamCaja*2].Char.AsciiChar = 0xC4;
	mapaBuffer[pos+2+mapa->getAncho()*tamCaja*2].Char.AsciiChar = 0xD9;
}

void Dibujar::clear()
{
	for(unsigned i=0;i<mapa->getAlto()*tamCaja*mapa->getAncho()*tamCaja;i++)
	{
		mapaBuffer[i].Char.AsciiChar = ' ';
		mapaBuffer[i].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
	}
}
