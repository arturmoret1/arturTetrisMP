#include "Figura.h"


void Figura::reiniciarForma()
{
    for (int i = 0; i < m_altura; i++)
        for (int j = 0; j < m_amplada; j++)
            m_estructura[i][j] = 0;
}


void Figura::inicialitzaForma(TipusFigura tipus)
{
    switch (tipus)
    {
    case FIGURA_J:
        m_amplada = 3;
        m_altura = 3;
        reiniciarForma();
        m_estructura[0][0] = 1;
        m_estructura[1][0] = 1;
        m_estructura[1][1] = 1;
        m_estructura[1][2] = 1;
        m_color = COLOR_BLAUFOSC;
        break;
    case FIGURA_L:
        m_amplada = 3;
        m_altura = 3;
        reiniciarForma();
        m_estructura[0][2] = 1;
        m_estructura[1][0] = 1;
        m_estructura[1][1] = 1;
        m_estructura[1][2] = 1;
        m_color = COLOR_TARONJA;
        break;
    case FIGURA_S:
        m_amplada = 3;
        m_altura = 3;
        reiniciarForma();
        m_estructura[0][1] = 1;
        m_estructura[0][2] = 1;
        m_estructura[1][0] = 1;
        m_estructura[1][1] = 1;
        m_color = COLOR_VERD;
        break;
    case FIGURA_Z:
        m_amplada = 3;
        m_altura = 3;
        reiniciarForma();
        m_estructura[0][0] = 1;
        m_estructura[0][1] = 1;
        m_estructura[1][1] = 1;
        m_estructura[1][2] = 1;
        m_color = COLOR_VERMELL;
        break;
    case FIGURA_T:
        m_amplada = 3;
        m_altura = 3;
        reiniciarForma();
        m_estructura[0][1] = 1;
        m_estructura[1][0] = 1;
        m_estructura[1][1] = 1;
        m_estructura[1][2] = 1;
        m_color = COLOR_MAGENTA;
        break;
    case FIGURA_I:
        m_amplada = 4;
        m_altura = 4;
        reiniciarForma();
        m_estructura[1][0] = 1;
        m_estructura[1][1] = 1;
        m_estructura[1][2] = 1;
        m_estructura[1][3] = 1;
        m_color = COLOR_BLAUCEL;
        break;
    case FIGURA_O:
        m_amplada = 2;
        m_altura = 2;
        m_estructura[0][0] = 1;
        m_estructura[0][1] = 1;
        m_estructura[1][0] = 1;
        m_estructura[1][1] = 1;
        m_color = COLOR_GROC;
        break;
    }
}


void Figura::inicialitza(TipusFigura tipus, int fila, int columna)
{
    m_tipus = tipus;
    m_fila = fila;
    m_columna = columna;
    m_gir = 0;
    inicialitzaForma(tipus);
}


void Figura::mouHorizontal(int dirX)
{
    m_columna += dirX;
}


void Figura::baixar()
{
    m_fila += 1;
}


void Figura::pujar()
{
    m_fila -= 1;
}


void Figura::getEstructura(int estructura[MAX_ALTURA][MAX_AMPLADA]) const
{
    for (int i = 0; i < m_altura; i++)
        for (int j = 0; j < m_amplada; j++)
            estructura[i][j] = m_estructura[i][j];
}


void Figura::girar(DireccioGir direccio)
{
    transposarEstructura();
    if (direccio == GIR_HORARI)
    {
        invertirColumnes();
        m_gir = (m_gir + 1) % 4;
    }
    else
    {
        invertirFiles();
        m_gir = (m_gir - 1) % 4;
    }
}


void Figura::transposarEstructura()
{
    int aux;
    for (int i = 1; i < m_altura; i++)
        for (int j = 0; j < i; j++)
        {
            aux = m_estructura[i][j];
            m_estructura[i][j] = m_estructura[j][i];
            m_estructura[j][i] = aux;
        }
}


void Figura::invertirColumnes()
{
    int columna1, columna2;

    if (m_amplada == 3)
    {
        columna1 = 0;
        columna2 = 2;
    }
    else if (m_amplada > 2)
    {
        columna1 = 1;
        columna2 = 2;
    }
    else
    {
        return; // Si m_amplada es 2 o menos, no hacemos nada.
    }

    for (int i = 0; i < m_altura; i++)
    {
        int aux = m_estructura[i][columna1];
        m_estructura[i][columna1] = m_estructura[i][columna2];
        m_estructura[i][columna2] = aux;
    }
}


void Figura::invertirFiles()
{
    int fila1, fila2;

    if (m_altura == 3)
    {
        fila1 = 0;
        fila2 = 2;
    }
    else if (m_altura > 2)
    {
        fila1 = 1;
        fila2 = 2;
    }
    else
    {
        return; // Si m_altura es 2 o menos, no hacemos nada.
    }

    for (int i = 0; i < m_amplada; i++)
    {
        int aux = m_estructura[fila1][i];
        m_estructura[fila1][i] = m_estructura[fila2][i];
        m_estructura[fila2][i] = aux;
    }
}


void Figura::dibuixa()
{
    int posX, posY;
    for (int i = 0; i < m_altura; i++)
    {
        for (int j = 0; j < m_amplada; j++)
        {
            if (m_estructura[i][j] != 0)
            {
                posX = POS_X_TAULER + ((m_columna + j) * MIDA_QUADRAT);
                posY = POS_Y_TAULER + ((m_fila - 1 + i) * MIDA_QUADRAT);
                dibuixaQuadrat(m_color, posX, posY);
            }
        }
    }
}

