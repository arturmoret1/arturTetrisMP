#include "LlistaMoviment.h"

LlistaMoviment::~LlistaMoviment()
{
    while (m_primer)
    {
        NodeMoviment* aux = m_primer;
        m_primer = m_primer->getSeguent();
        delete aux;
    }
    m_ultim = nullptr;
}


LlistaMoviment::LlistaMoviment(const LlistaMoviment& l)
    : m_primer(nullptr), m_ultim(nullptr)
{
    for (NodeMoviment* aux = l.m_primer; aux != nullptr; aux = aux->getSeguent())
    {
        insereix(aux->getValor());
    }
}


LlistaMoviment& LlistaMoviment::operator=(const LlistaMoviment& l)
{
    if (this != &l)
    {
        while (m_primer)
        {
            elimina();
        }

        for (NodeMoviment* aux = l.m_primer; aux != nullptr; aux = aux->getSeguent())
        {
            insereix(aux->getValor());
        }
    }
    return *this;
}


NodeMoviment* LlistaMoviment::insereix(const TipusMoviment& valor)
{
    NodeMoviment* nou_node = new NodeMoviment;
    if (nou_node)
    {
        nou_node->setValor(valor);
        nou_node->setSeguent(nullptr);
        if (!m_primer)
        {
            m_primer = nou_node;
        }
        else
        {
            m_ultim->setSeguent(nou_node);
        }
        m_ultim = nou_node;
    }
    return nou_node;
}


void LlistaMoviment::elimina()
{
    if (m_primer)
    {
        NodeMoviment* aux = m_primer;
        if (m_primer == m_ultim)
        {
            m_primer = m_ultim = nullptr;
        }
        else
        {
            m_primer = m_primer->getSeguent();
        }
        delete aux;
    }
}


int LlistaMoviment::getNumElements() const
{
    int contador = 0;
    for (NodeMoviment* aux = m_primer; aux != nullptr; aux = aux->getSeguent())
    {
        ++contador;
    }
    return contador;
}
