#include "Joc.h"
#include <fstream>
using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxerEntrada(nomFitxer);
    if (fitxerEntrada.is_open())
    {
        int tipusFigura, posFila, posColumna, vegadesGirar;
        fitxerEntrada >> tipusFigura >> posFila >> posColumna >> vegadesGirar;
        m_figura.inicialitza(TipusFigura(tipusFigura), posFila, posColumna);
        for (int girActual = 0; girActual < vegadesGirar; girActual++) 
        {
            m_figura.girar(GIR_HORARI);
        }

        ColorFigura estatInicialTauler[MAX_FILA][MAX_COL];
        int valorColor;
        for (int fila = 0; fila < MAX_FILA; fila++) 
        {
            for (int col = 0; col < MAX_COL; col++) 
            {
                fitxerEntrada >> valorColor;
                estatInicialTauler[fila][col] = ColorFigura(valorColor);
            }
        }
        m_tauler.inicialitza(estatInicialTauler);
        fitxerEntrada.close();
    }
}


bool Joc::mouFigura(int desplacamentX)
{
    m_figura.mouHorizontal(desplacamentX);
    bool colisio = m_tauler.verificarColisio(m_figura);
    if (colisio)
        m_figura.mouHorizontal(-desplacamentX);
    return !colisio;
}

int Joc::baixaFigura()
{
    int comptadorFiles = 0;
    m_figura.baixar();
    if (m_tauler.verificarColisio(m_figura))
    {
        m_figura.pujar();
        comptadorFiles = m_tauler.posarFigura(m_figura);
        m_figura.inicialitza(NO_FIGURA, -1, -1);
    }
    return comptadorFiles;
}

bool Joc::giraFigura(DireccioGir direccio)
{
    m_figura.girar(direccio);
    bool colisio = m_tauler.verificarColisio(m_figura);
    if (colisio)
    {
        DireccioGir direccioInversa;
        if (direccio == GIR_HORARI) {
            direccioInversa = GIR_ANTI_HORARI;
        }
        else {
            direccioInversa = GIR_HORARI;
        }
        m_figura.girar(direccioInversa);
    }
    return !colisio;
}

void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxerSortida(nomFitxer);
    if (fitxerSortida.is_open())
    {
        if (m_figura.getTipus() != NO_FIGURA)
        {
            m_tauler.mostrarFigura(m_figura);
        }

        ColorFigura estatActualTauler[MAX_FILA][MAX_COL];
        m_tauler.getEstatTauler(estatActualTauler);

        for (int fila = 0; fila < MAX_FILA; fila++)
        {
            for (int col = 0; col < MAX_COL; col++)
            {
                fitxerSortida << int(estatActualTauler[fila][col]) << " ";
            }
            fitxerSortida << endl;
        }
        fitxerSortida.close();
    }
}
