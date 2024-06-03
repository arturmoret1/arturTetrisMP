#ifndef TETRIS
#define TETRIS
#include "Partida.h"
#include <list>
using namespace std;

#define SDL_MAIN_HANDLED
#include <windows.h>

#include "../Graphic Lib/libreria.h"

typedef struct
{
	string nom;
	int punts;
} Puntuacio;

class Tetris
{
public:
	Tetris(const string& fitxerPuntuacions);
	int juga(Screen& pantalla, ModeJoc mode, const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments);
	void actualitzaPuntuacio(const string& nom, int punts);
	void visualitzaPuntuacions();
	void guardaPuntuacions(const string& nomFitxer);
private:
	Partida m_partida;
	list<Puntuacio> m_puntuacions;
};

#endif
