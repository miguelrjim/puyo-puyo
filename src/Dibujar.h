/*
 * Dibujar.h
 *
 *  Created on: 06/03/2011
 *      Author: Miguel
 */

#ifndef DIBUJAR_H_
#define DIBUJAR_H_

#define REFRESH_MS 100

#include <process.h>
#include <windows.h>
#include "Mapa.h"

class Dibujar {
private:
	Mapa *mapa;
	const unsigned char * mapaDibujar;
	CHAR_INFO *mapaBuffer;
	bool finalizar;
	HANDLE wHnd, hThread;
	unsigned threadId, tamCaja;
	void iniciarDibujar();
	void dibujarCaja(unsigned,unsigned char);
	static unsigned __stdcall threadProc(void *ptr)
	{
		((Dibujar*)ptr)->iniciarDibujar();
		return 0;
	}
public:
	Dibujar(Mapa*,HANDLE,unsigned tamCaja);
	virtual ~Dibujar();
	void iniciar();
	void terminar();
	void clear();
};

#endif /* DIBUJAR_H_ */
