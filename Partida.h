#ifndef PARTIDA
#define PARTIDA

#include "./Joc.h"
#include "./InfoJoc.h"
#include "LlistaFigura.h"
#include "LlistaMoviment.h"
#include <ctime>

const int PUNTS_FIGURA = 10;
const int PUNTS_LINIA = 100;
const int DOBLE_LINIA = 50;
const int TRIPLE_LINIA = 75;
const int QUADRUPLE_LINIA = 100;

const int NIVELL_SEGUENT = 200;
const double VELOCITAT_INICIAL = 0.6;
const double VELOCITAT_INCREMENT = 0.75;

typedef enum
{
    MODE_NORMAL,
    MODE_TEST
} ModeJoc;

class Partida
{
public:
    Partida()
    {
        inicialitzarAtributs(MODE_NORMAL);
    }

    Partida(ModeJoc mode)
    {
        inicialitzarAtributs(mode);
    }

    void inicialitza(const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments);
    void actualitza(float deltaTime);
    int getPuntuacio() const { return m_punts; }

private:
    LlistaFigura m_peces; 
    LlistaMoviment m_moviments;
    Joc m_joc;
    ModeJoc m_mode;
    bool m_finalJoc;
    double m_temps;
    double m_velocitat;
    int m_punts;
    int m_nivell;


    void inicialitzarAtributs(ModeJoc mode)
    {
        m_mode = mode;
        m_temps = 0.0;
        m_punts = 0;
        m_nivell = 1;
        m_velocitat = VELOCITAT_INICIAL;
        m_finalJoc = false;
        srand(time(0));
    }

    void inicialitzarPeces(const string& nomFitxer);
    void inicialitzarMoviments(const string& nomFitxer);
    void actualitzarPuntuacio(int nFilesEliminades);
    void actualitzarNormalMode(float deltaTime);
    void actualitzarTestMode(float deltaTime);

};
#endif
