/*
 * Mapa.cpp
 *
 *  Created on: 04/03/2011
 *      Author: Miguel
 */

#include "Mapa.h"

Mapa::Mapa(unsigned int ancho, unsigned int alto) {
	// TODO Auto-generated constructor stub
	this->alto = alto;
	this->ancho = ancho;
	mapa = new unsigned char[alto*ancho];
	bajando = finalizado = false;
	for(unsigned int i=0;i<ancho*alto;i++)
		mapa[i] = 0;
}

Mapa::~Mapa() {
	// TODO Auto-generated destructor stub
	delete[] mapa;
}

void Mapa::moverAbajo()
{
	dibujar = false;
	if(!bajando)
	{
		bajando = true;
		caja.tipo = (rand() % 3) + 1;
		caja.x = ancho/2;
		caja.y = -1;
	}
	caja.y++;
	mapa[caja.x + caja.y*ancho] = caja.tipo;
	if(caja.y > 0)
		mapa[caja.x + (caja.y-1)*ancho] = 0;
	if(mapa[caja.x + (caja.y+1)*ancho] || caja.y == (alto-1))
		bajando = false;
	dibujar = true;
}



void Mapa::moverIzquierda()
{
	dibujar = false;
	if(bajando)
		if(caja.x && !mapa[caja.x - 1 + caja.y*ancho])
		{
			mapa[caja.x-- + caja.y*ancho] = 0;
			mapa[caja.x + caja.y*ancho] = caja.tipo;
		}
	dibujar = true;
}

void Mapa::moverDerecha()
{
	dibujar = false;
	if(bajando)
		if(caja.x < (ancho-1) && !mapa[caja.x + 1 + caja.y*ancho])
		{
			mapa[caja.x++ + caja.y*ancho] = 0;
			mapa[caja.x + caja.y*ancho] = caja.tipo;
		}
	dibujar = true;
}

unsigned int Mapa::getAlto() const
{
    return alto;
}

void Mapa::setAlto(unsigned int alto)
{
    this->alto = alto;
}

unsigned int Mapa::getAncho() const
{
    return ancho;
}

void Mapa::iniciar(unsigned char dificultad)
{
	this->dificultad = (!dificultad) ? FACIL : (dificultad == 1) ? MEDIO : DIFICIL;
	hThread = (HANDLE)_beginthreadex(NULL, 0, &threadProc, this, 0, &threadId);
}

void Mapa::finalizar()
{
	finalizado = true;
}

void Mapa::iniciarJuego()
{
	while(!finalizado)
	{
		moverAbajo();
		Sleep(dificultad);
	}
}

bool Mapa::poderDibujar()
{
	return dibujar;
}

void Mapa::setAncho(unsigned int alto)
{
    this->ancho = ancho;
}

const unsigned char * const Mapa::obtenerMapa()
{
	return mapa;
}
