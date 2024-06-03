#include "Tetris.h"
#include <fstream>
#include <iostream>
using namespace std;

#include <windows.h>
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"

Tetris::Tetris(const string& fitxerPuntuacions)
{
    ifstream fitxer(fitxerPuntuacions);

    if (fitxer)
    {
        Puntuacio p;

        while (fitxer >> p.nom >> p.punts)
        {
            m_puntuacions.push_back(p);
        }

        fitxer.close();
    }
}


void Tetris::visualitzaPuntuacions()
{
    cout << endl;
    cout << "HALL OF FAME" << endl;
    cout << "-------------" << endl;

    int ordre = 1;
    for (const auto& puntuacio : m_puntuacions)
    {
        cout << ordre << ". " << puntuacio.nom << " " << puntuacio.punts << endl;
        ordre++;
    }

    cout << endl;
}


void Tetris::guardaPuntuacions(const string& nomFitxer)
{
    ofstream fitxer(nomFitxer);
    for (const auto& puntuacio : m_puntuacions)
    {
        fitxer << puntuacio.nom << " " << puntuacio.punts << endl;
    }
}


void Tetris::actualitzaPuntuacio(const string& nom, int punts)
{
    auto it = m_puntuacions.begin();
    while (it != m_puntuacions.end() && it->punts <= punts)
    {
        ++it;
    }

    Puntuacio p{ nom, punts };
    m_puntuacions.insert(it, p);
}


int Tetris::juga(Screen& pantalla, ModeJoc mode, const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments)
{
    pantalla.show();

    Partida game(mode);
    game.inicialitza(nomFitxerInicial, nomFitxerFigures, nomFitxerMoviments);

    Uint64 NOW = SDL_GetPerformanceCounter();
    double deltaTime = 0;

    while (true)
    {
        Uint64 LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = static_cast<double>(NOW - LAST) / SDL_GetPerformanceFrequency();

        pantalla.processEvents();

        game.actualitza(deltaTime);

        pantalla.update();

        if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
            break;
    }
    return game.getPuntuacio();
}
