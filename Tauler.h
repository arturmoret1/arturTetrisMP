#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 21; 
const int MAX_COL = 11;  

class Tauler
{
public:
    Tauler();
    void inicialitza(ColorFigura taulerInicial[MAX_FILA][MAX_COL]);
    bool verificarColisio(const Figura& figura);
    int posarFigura(const Figura& figura);
    void mostrarFigura(const Figura& figura);
    void getEstatTauler(ColorFigura tauler[MAX_FILA][MAX_COL]);
    void dibuixa();
    void baixarFila(int fila); 

private:
    ColorFigura m_tauler[MAX_FILA + 2][MAX_COL + 4];
    int m_lliures[MAX_FILA];
};
#endif
