#include "NodeFigura.h"

class LlistaFigura
{
public:
    LlistaFigura() : m_primer(nullptr), m_ultim(nullptr) {}
    ~LlistaFigura();
    LlistaFigura(const LlistaFigura& llista);

    LlistaFigura& operator=(const LlistaFigura& llista);
    NodeFigura* afegeix(const InfoFigura& info);
    void elimina();
    int getNumElements() const;

    InfoFigura getPrimer() const { return m_primer->getValor(); }
    bool estaBuida() const { return m_primer == nullptr; }

private:
    NodeFigura* m_primer;
    NodeFigura* m_ultim;
};
