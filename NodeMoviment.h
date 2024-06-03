#include <stdlib.h>
#include "InfoJoc.h"


class NodeMoviment
{
public:
    NodeMoviment() {m_seguent = nullptr;};
	~NodeMoviment() {};
    NodeMoviment(const TipusMoviment& valor) {m_valor = valor; m_seguent = nullptr;}

    NodeMoviment* getSeguent() { return m_seguent; }
    void setSeguent(NodeMoviment* next) { m_seguent = next; }

    TipusMoviment getValor() { return m_valor; }
    void setValor(const TipusMoviment& valor) { m_valor = valor; }
private:
    TipusMoviment m_valor;
    NodeMoviment* m_seguent;
};

