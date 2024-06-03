#include "Joc.h"
#include <fstream>
using namespace std;

bool Joc::novaFigura()
{
	TipusFigura tipus = TipusFigura((rand() % N_TIPUS_FIGURES) + 1);
	int colMaxima;

	switch (tipus)
	{
	case FIGURA_O:
		colMaxima = N_COL_TAULER - 1;
		break;
	case FIGURA_I:
		colMaxima = N_COL_TAULER - 3;
		break;
	default:
		colMaxima = N_COL_TAULER - 2;
		break;
	}

	int columna = (rand() % colMaxima) + 1;
	int nGir = (rand() % 4);
	m_figura.inicialitza(tipus, 1, columna);

	for (int i = 0; i < nGir; i++)
	{
		m_figura.girar(GIR_HORARI);
	}

	return m_tauler.verificarColisio(m_figura);
}


void Joc::novaFigura(InfoFigura figura)
{
	m_figura.inicialitza(figura.tipus, figura.fila, figura.columna);

	int nGir = figura.gir;
	while (nGir > 0)
	{
		m_figura.girar(GIR_HORARI);
		nGir--;
	}
}


void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxerEntrada(nomFitxer);
	if (fitxerEntrada.is_open())
	{
		int tipusFigura, posFila, posColumna, vegadesGirar;
		fitxerEntrada >> tipusFigura >> posFila >> posColumna >> vegadesGirar;
		m_figura.inicialitza(TipusFigura(tipusFigura), posFila, posColumna);
		for (int girActual = 0; girActual < vegadesGirar; girActual++)
		{
			m_figura.girar(GIR_HORARI);
		}

		ColorFigura estatInicialTauler[MAX_FILA][MAX_COL];
		int valorColor;
		for (int fila = 0; fila < MAX_FILA; fila++)
		{
			for (int col = 0; col < MAX_COL; col++)
			{
				fitxerEntrada >> valorColor;
				estatInicialTauler[fila][col] = ColorFigura(valorColor);
			}
		}
		m_tauler.inicialitza(estatInicialTauler);
		fitxerEntrada.close();
	}
}


bool Joc::girarFigura(DireccioGir direccio)
{
	m_figura.girar(direccio);
	bool colisiona = m_tauler.verificarColisio(m_figura);
	if (colisiona)
	{
		if (direccio == GIR_HORARI)
			direccio = GIR_ANTI_HORARI;
		else
			direccio = GIR_HORARI;
		m_figura.girar(direccio);
	}
	return !colisiona;
}


bool Joc::mouFigura(int dirX)
{
	m_figura.mouHorizontal(dirX);
	bool colisiona = m_tauler.verificarColisio(m_figura);
	if (colisiona)
		m_figura.mouHorizontal(-dirX);
	return !colisiona;
}


int Joc::baixarFigura()
{
	int nFiles = -1;
	m_figura.baixar();
	if (m_tauler.verificarColisio(m_figura))
	{
		nFiles = 0;
		m_figura.pujar();
		nFiles = m_tauler.posarFigura(m_figura);
	}
	return nFiles;
}


int Joc::colocaFigura()
{
	int nFiles;
	do
	{
		nFiles = baixarFigura();
	} while (nFiles == -1);
	return nFiles;
}


void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		if (m_figura.getTipus() != NO_FIGURA)
			m_tauler.mostrarFigura(m_figura);
		ColorFigura tauler[MAX_FILA][MAX_COL];
		m_tauler.getEstatTauler(tauler);
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << int(tauler[i][j]) << " ";
			}
			fitxer << endl;
		}

		fitxer.close();
	}
}


void Joc::dibuixa()
{
	m_tauler.dibuixa();
	m_figura.dibuixa();
}