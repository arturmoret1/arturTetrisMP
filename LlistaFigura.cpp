#include "LlistaFigura.h"

LlistaFigura::~LlistaFigura()
{
    while (m_primer != nullptr)
        elimina();
}


LlistaFigura::LlistaFigura(const LlistaFigura& llista)
{
    m_primer = nullptr;
    m_ultim = nullptr;
    NodeFigura* actual = llista.m_primer;
    while (actual != nullptr)
    {
        afegeix(actual->getValor());
        actual = actual->getSeguent();
    }
}


LlistaFigura& LlistaFigura::operator=(const LlistaFigura& llista)
{
    if (this != &llista)
    {
        while (m_primer != nullptr)
            elimina();
        NodeFigura* actual = llista.m_primer;
        while (actual != nullptr)
        {
            afegeix(actual->getValor());
            actual = actual->getSeguent();
        }
    }
    return *this;
}


NodeFigura* LlistaFigura::afegeix(const InfoFigura& info)
{
    NodeFigura* nouNode = new NodeFigura;
    if (nouNode != nullptr)
    {
        nouNode->setValor(info);
        nouNode->setSeguent(nullptr);
        if (m_primer == nullptr)
        {
            m_primer = nouNode;
        }
        else
        {
            m_ultim->setSeguent(nouNode);
        }
        m_ultim = nouNode;
    }

    return nouNode;
}


void LlistaFigura::elimina()
{
    NodeFigura* aux;
    if (m_primer == m_ultim)
    {
        delete m_primer;
        m_primer = nullptr;
        m_ultim = nullptr;
    }
    else
    {
        aux = m_primer->getSeguent();
        delete m_primer;
        m_primer = aux;
    }
}


int LlistaFigura::getNumElements() const
{
    int nElements = 0;
    NodeFigura* aux = m_primer;
    while (aux != NULL)
    {
        nElements++;
        aux = aux->getSeguent();
    }

    return nElements;
}
