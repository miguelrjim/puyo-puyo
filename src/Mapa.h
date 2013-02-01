/*
 * Mapa.h
 *
 *  Created on: 04/03/2011
 *      Author: Miguel
 */

#ifndef MAPA_H_
#define MAPA_H_

#define DIFICIL 500
#define MEDIO 1000
#define FACIL 1500

#include <stdlib.h>
#include <windows.h>
#include <process.h>

struct Caja {
	unsigned char tipo;
	unsigned int x;
	unsigned int y;
};

class Mapa {
private:
	unsigned char *mapa;
	unsigned alto, ancho, threadId, dificultad;
	bool bajando, finalizado, dibujar;
	Caja caja;
	HANDLE hThread;
	void iniciarJuego();
	static unsigned __stdcall threadProc(void *ptr)
	{
		((Mapa*)ptr)->iniciarJuego();
		return 0;
	}
public:
	void iniciar(unsigned char);
	Mapa(unsigned int, unsigned int);
	virtual ~Mapa();
	void moverDerecha();
	void moverIzquierda();
	void moverAbajo();
	void finalizar();
	bool poderDibujar();
	const unsigned char * const obtenerMapa();
    unsigned int getAlto() const;
    void setAlto(unsigned int alto);
    unsigned int getAncho() const;
    void setAncho(unsigned int alto);
};

#endif /* MAPA_H_ */
