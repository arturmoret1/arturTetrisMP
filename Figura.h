#ifndef FIGURA_H
#define FIGURA_H

const int N_TIPUS_FIGURES = 7;

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;


typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

const int MAX_ALTURA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    Figura();

    void inicialitza(TipusFigura tipus, int fila, int columna);
    void mouHorizontal(int dirX);
    void baixar();
    void pujar();
    void girar(DireccioGir direccio);

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }
    int getAltura() const { return m_altura; }
    int getAmplada() const { return m_amplada; }
    void getEstructura(int estructura[MAX_ALTURA][MAX_AMPLADA]) const;
    ColorFigura getColor() const { return m_color; }
    TipusFigura getTipus() const { return m_tipus; }
    void inicialitzaForma(TipusFigura tipus);
    void reiniciarForma();
    void transposarEstructura();
    void invertirFiles();
    void invertirColumnes();

private:
    TipusFigura m_tipus;
    ColorFigura m_color;
    int m_fila;
    int m_columna;
    int m_amplada;
    int m_altura;
    int m_gir;
    int m_estructura[MAX_ALTURA][MAX_AMPLADA];
};


#endif
