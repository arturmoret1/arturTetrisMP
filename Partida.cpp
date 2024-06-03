#include "Partida.h"
#include "GraphicManager.h"
#include <fstream>

void Partida::inicialitza(const string& nomFitxer, const string& nomFitxerFigures, const string& nomFitxerMoviments)
{
    if (m_mode != MODE_NORMAL)
    { 
        m_joc.inicialitza(nomFitxer); 
        inicialitzarPeces(nomFitxerFigures); 
        inicialitzarMoviments(nomFitxerMoviments); 
    }
    else
    {
        m_finalJoc = m_joc.novaFigura();
    }
}


void Partida::inicialitzarPeces(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        InfoFigura figura;
        int tipus;
        while (fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir)
        {
            figura.tipus = TipusFigura(tipus);
            m_peces.afegeix(figura);
        }
        fitxer.close();
    }
}


void Partida::inicialitzarMoviments(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        int tipus;
        while (fitxer >> tipus)
        {
            m_moviments.insereix(TipusMoviment(tipus));
        }
        fitxer.close();
    }
}


void Partida::actualitzarNormalMode(float deltaTime)
{
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
    {
        m_joc.mouFigura(1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
    {
        m_joc.mouFigura(-1);
    }

    if (Keyboard_GetKeyTrg(KEYBOARD_UP))
    {
        m_joc.girarFigura(GIR_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
    {
        m_joc.girarFigura(GIR_ANTI_HORARI);
    }

    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        int nFilesEliminades = m_joc.colocaFigura();
        actualitzarPuntuacio(nFilesEliminades);
        m_finalJoc = m_joc.novaFigura();
        m_temps = 0.0;
    }
    else
    {
        m_temps += deltaTime;
        if (m_temps > m_velocitat)
        {
            int nFilesEliminades = m_joc.baixarFigura();
            if (nFilesEliminades != -1)
            {
                m_finalJoc = m_joc.novaFigura();
                actualitzarPuntuacio(nFilesEliminades);
            }
            m_temps = 0.0;
        }
    }
}


void Partida::actualitzarTestMode(float deltaTime)
{
    m_temps += deltaTime;
    if (m_temps <= m_velocitat)
    {
        return;
    }

    m_temps = 0.0;

    if (m_moviments.estaBuida())
    {
        m_finalJoc = true;
        return;
    }

    TipusMoviment moviment = m_moviments.getPrimer();
    m_moviments.elimina();

    switch (moviment)
    {
    case MOVIMENT_DRETA:
        m_joc.mouFigura(1);
        break;
    case MOVIMENT_ESQUERRA:
        m_joc.mouFigura(-1);
        break;
    case MOVIMENT_GIR_HORARI:
        m_joc.girarFigura(GIR_HORARI);
        break;
    case MOVIMENT_GIR_ANTI_HORARI:
        m_joc.girarFigura(GIR_ANTI_HORARI);
        break;
    case MOVIMENT_BAIXA_FINAL:
    {
        int nFilesEliminades = m_joc.colocaFigura();
        actualitzarPuntuacio(nFilesEliminades);
        if (!m_peces.estaBuida())
        {
            InfoFigura figura = m_peces.getPrimer();
            m_peces.elimina();
            m_joc.novaFigura(figura);
        }
        else
        {
            m_finalJoc = true;
        }
        break;
    }
    case MOVIMENT_BAIXA:
    {
        int nFilesEliminades = m_joc.baixarFigura();
        if (nFilesEliminades != -1)
        {
            actualitzarPuntuacio(nFilesEliminades);
            if (!m_peces.estaBuida())
            {
                InfoFigura figura = m_peces.getPrimer();
                m_peces.elimina();
                m_joc.novaFigura(figura);
            }
            else
            {
                m_finalJoc = true;
            }
        }
        break;
    }
    }
}


void Partida::actualitza(float deltaTime)
{
    if (!m_finalJoc)
    {
        switch (m_mode)
        {
            case MODE_NORMAL:
                actualitzarNormalMode(deltaTime);
                break;
            default:
                actualitzarTestMode(deltaTime);
                break;
        }
    }

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa();

    string msgPunts = "Score: " + to_string(m_punts);
    string msgNivell = "Level: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_PUNTUACIO, POS_Y_PUNTUACIO, 0.8, msgPunts);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_NIVELL, POS_Y_NIVELL, 0.8, msgNivell);

    if (m_finalJoc)
    {
        string msgFinal = "YOU LOST.";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_FINAL_JOC, POS_Y_FINAL_JOC, 2, msgFinal);
    }
}


void Partida::actualitzarPuntuacio(int nFilesEliminades)
{
    if (nFilesEliminades == 0)
        m_punts += PUNTS_FIGURA;
    else
    {
        m_punts += PUNTS_LINIA;
        switch (nFilesEliminades)
        {
        case 2:
            m_punts += DOBLE_LINIA;
            break;
        case 3:
            m_punts += TRIPLE_LINIA;
            break;
        case 4:
            m_punts += QUADRUPLE_LINIA;
            break;
        }
    }
    if (m_punts > (m_nivell * NIVELL_SEGUENT))
    {
        m_nivell += 1;
        m_velocitat *= VELOCITAT_INCREMENT;
    }
}
