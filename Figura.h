#ifndef FIGURA_H
#define FIGURA_H
#include "InfoJoc.h"

const int MAX_ALTURA = 4;
const int MAX_AMPLADA = 4;

class Figura
{
public:
    Figura() : m_tipus(NO_FIGURA), m_color(NO_COLOR), m_amplada(MAX_AMPLADA),
        m_altura(MAX_ALTURA), m_fila(0), m_columna(0), m_gir(0)
    {
        reiniciarForma();
    }

    void inicialitza(TipusFigura tipus, int fila, int columna);
    void girar(DireccioGir direccio);
    void mouHorizontal(int dirX);
    void baixar();
    void pujar();
    void dibuixa();

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }
    ColorFigura getColor() const { return m_color; }
    int getAltura() const { return m_altura; }
    int getAmplada() const { return m_amplada; }
    void getEstructura(int estructura[MAX_ALTURA][MAX_AMPLADA]) const;
    TipusFigura getTipus() const { return m_tipus; }

private:
    TipusFigura m_tipus;
    ColorFigura m_color;
    int m_amplada;
    int m_altura;
    int m_estructura[MAX_ALTURA][MAX_AMPLADA];
    int m_fila;
    int m_columna;
    int m_gir;

    void reiniciarForma();
    void inicialitzaForma(TipusFigura tipus);
    void transposarEstructura();
    void invertirFiles();
    void invertirColumnes();
};

#endif
