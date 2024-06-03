#include <iostream>
#include <string>
#include <conio.h>      
#include "./Tetris.h"

#define SDL_MAIN_HANDLED
#include <windows.h>

#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
using namespace std;

void mostrarOpcions()
{
    cout << endl;
    cout << "Welcome to the main menu" << endl;
    cout << "------------------------" << endl;
    cout << "1. Play in normal mode" << endl;
    cout << "2. Play in test mode" << endl;
    cout << "3. View scores" << endl;
    cout << "4. Exit game" << endl;
}


void llegirNomFitxers(string& nomInicial, string& nomFigures, string& nomMoviments)
{
    cout << "Name of the file with the initial state of the board: ";
    getline(cin, nomInicial);
    nomInicial = "./data/Games/" + nomInicial;
    cout << "Name of the file with the sequence of figures: ";
    getline(cin, nomFigures);
    nomFigures = "./data/Games/" + nomFigures;
    cout << "Name of the file with the sequence of movements: ";
    getline(cin, nomMoviments);
    nomMoviments = "./data/Games/" + nomMoviments;
}


void processOption(char opcio, Tetris& tetris, Screen& pantalla, bool& sortir)
{
    string nomInicial, nomFigures, nomMoviments, nomJugador;
    int punts;

    switch (opcio)
    {
    case '1':
        punts = tetris.juga(pantalla, MODE_NORMAL, "", "", "");
        cout << "Player name: ";
        cin >> nomJugador;
        tetris.actualitzaPuntuacio(nomJugador, punts);
        break;
    case '2':
        Sleep(500);
        llegirNomFitxers(nomInicial, nomFigures, nomMoviments);
        punts = tetris.juga(pantalla, MODE_TEST, nomInicial, nomFigures, nomMoviments);
        break;
    case '3':
        tetris.visualitzaPuntuacions();
        break;
    case '4':
        sortir = true;
        break;
    default:
        cout << "INCORRECT OPTION" << endl;
    }
}


void initSDL()
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
}


void quitSDL()
{
    SDL_Quit();
}


int main(int argc, const char* argv[])
{
    initSDL();

    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    Tetris tetris("./data/Games/puntuacions.txt");
    bool sortir = false;

    do
    {
        mostrarOpcions();
        char opcio = _getch();
        processOption(opcio, tetris, pantalla, sortir);
    } while (!sortir);

    tetris.guardaPuntuacions("./data/Games/puntuacions.txt");
    quitSDL();

    return 0;
}
