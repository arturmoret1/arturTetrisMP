#include "Tauler.h"
#include "GraphicManager.h"
#include "InfoJoc.h"
#include <iostream>
using namespace std;

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA + 2; i++)
    {
        for (int j = 0; j < MAX_COL + 4; j++)
        {
            if (i < MAX_FILA)
            {
                if (j < 2 || j >= MAX_COL + 2)
                {
                    m_tauler[i][j] = NO_COLOR;
                }
                else
                {
                    m_tauler[i][j] = COLOR_NEGRE;
                }
            }
            else
            {
                m_tauler[i][j] = NO_COLOR;
            }
        }
        if (i < MAX_FILA)
        {
            m_lliures[i] = MAX_COL;
        }
    }
}


void Tauler::inicialitza(ColorFigura taulerInicial[MAX_FILA][MAX_COL])
{
    for (int fila = 0; fila < MAX_FILA; fila++)
    {
        m_lliures[fila] = MAX_COL;
        for (int columna = 0; columna < MAX_COL; columna++)
        {
            m_tauler[fila][columna + 2] = taulerInicial[fila][columna];
            if (taulerInicial[fila][columna] != COLOR_NEGRE)
            {
                m_lliures[fila]--;
            }
        }
    }
} 


bool Tauler::verificarColisio(const Figura& figura)
{
    int filaInici = figura.getFila() - 1, columnaInici = figura.getColumna() + 1;
    int estructura[MAX_ALTURA][MAX_AMPLADA];
    figura.getEstructura(estructura);

    for (int i = 0; i < figura.getAltura(); i++)
    {
        for (int j = 0; j < figura.getAmplada(); j++)
        {
            if (estructura[i][j] && m_tauler[filaInici + i][columnaInici + j] != COLOR_NEGRE)
            {
                return true;
            }
        }
    }
    return false;
}


int Tauler::posarFigura(const Figura& figura)
{
    int filaInici = figura.getFila() - 1, columnaInici = figura.getColumna() + 1;
    int estructura[MAX_ALTURA][MAX_AMPLADA];
    figura.getEstructura(estructura);
    int filesEliminades = 0;

    for (int i = 0; i < figura.getAltura(); i++)
    {
        for (int j = 0; j < figura.getAmplada(); j++)
        {
            if (estructura[i][j])
            {
                m_tauler[filaInici + i][columnaInici + j] = figura.getColor();
                m_lliures[filaInici + i]--;
                if (m_lliures[filaInici + i] == 0)
                {
                    baixarFila(filaInici + i);
                    filesEliminades++;
                }
            }
        }
    }
    return filesEliminades;
}


void Tauler::mostrarFigura(const Figura& figura)
{
    int mascara[MAX_ALTURA][MAX_AMPLADA];

    ColorFigura color = figura.getColor();
    figura.getEstructura(mascara);
    int filaTauler = figura.getFila() - 1;
    for (int filaMascara = 0; filaMascara < figura.getAltura(); filaMascara++)
    {
        int colTauler = figura.getColumna() + 1;
        for (int colMascara = 0; colMascara < figura.getAmplada(); colMascara++)
        {
            if (mascara[filaMascara][colMascara] > 0)
            {
                m_tauler[filaTauler][colTauler] = color;
            }
            colTauler++;
        }
        filaTauler++;
    }
}


void Tauler::baixarFila(int fila)
{
    for (int i = fila; i > 0; i--)
    {
        for (int j = 2; j < MAX_COL + 2; j++)
        {
            m_tauler[i][j] = m_tauler[i - 1][j];
        }
        m_lliures[i] = m_lliures[i - 1];
    }
    for (int j = 2; j < MAX_COL + 2; j++)
    {
        m_tauler[0][j] = COLOR_NEGRE;
    }
    m_lliures[0] = MAX_COL;
}


void Tauler::getEstatTauler(ColorFigura tauler[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            tauler[i][j] = m_tauler[i][j + 2];
        }
    }
}


void Tauler::dibuixa()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            if (m_tauler[i][j + 2] != COLOR_NEGRE)
                dibuixaQuadrat(m_tauler[i][j + 2], POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + (i * MIDA_QUADRAT));
        }
}