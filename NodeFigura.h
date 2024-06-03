#include <stdlib.h>
#include "InfoJoc.h"


class NodeFigura
{
public:
    NodeFigura() {m_seguent = nullptr;};
	~NodeFigura() {};
    NodeFigura(const InfoFigura& valor) {m_valor = valor; m_seguent = nullptr;}

    NodeFigura* getSeguent() { return m_seguent; }
    void setSeguent(NodeFigura* next) { m_seguent = next; }

    InfoFigura getValor() { return m_valor; }
    void setValor(const InfoFigura& valor) { m_valor = valor; }
private:
    InfoFigura m_valor;
    NodeFigura* m_seguent;
};

