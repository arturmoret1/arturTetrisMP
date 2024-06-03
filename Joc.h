#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
    Joc() {}
    void inicialitza(const string& nomFitxer);
    bool mouFigura(int dirX);
    int baixarFigura();
    bool girarFigura(DireccioGir direccio);
    void escriuTauler(const string& nomFitxer);

    bool novaFigura();
    void novaFigura(InfoFigura figura);
    int colocaFigura();
    void dibuixa();

private:
    Tauler m_tauler;
    Figura m_figura; 
};

#endif
