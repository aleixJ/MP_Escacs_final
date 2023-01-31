//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"


CurrentGame::CurrentGame()
{
    m_mode = GM_NONE;
    m_torn = CPC_White;
    m_posXAnterior = -1;
    m_posYAnterior = -1;
    m_posicions.clear();
    m_delay = 0;
}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{

    switch (mode)
    {
    case GM_NORMAL:
        m_tauler.LoadBoardFromFile(intitialBoardFile);
		//falta guardar els moviments
        break;
    case GM_REPLAY:
        m_tauler.LoadBoardFromFile(intitialBoardFile);
        loadReplayFromFile(movementsFile);
        break;

    default:
        //és a dir, GM_NONE
        break;
    }
}


void CurrentGame::end(const string& movementsFile)
{
    if (m_mode == GM_NORMAL)
    {
        //guardem la cua de moviments al fitxer
        ofstream fitxer;
        fitxer.open(movementsFile);
        if (fitxer.is_open())
        {
            while (!m_moviments.empty())
            {
                fitxer << m_moviments.front() << " ";
                m_moviments.pop();
                fitxer << m_moviments.front() << "\n";
                m_moviments.pop();
            }
        }
        fitxer.close();
    }
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    int i = m_posXAnterior;
    int j = m_posYAnterior;
   // GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    switch (m_mode)
    {
    case GM_NONE:
        pantallaInicial(mousePosX, mousePosY, mouseStatus);
        break;
    case GM_NORMAL:
        GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 620, 0.8, "Game Mode: Normal");
        m_tauler.render();
        if (!m_tauler.jaqueMate(m_torn))
        {
            mostrarTorn();
            if (obtenirCasella(i, j, mousePosX, mousePosY, mouseStatus))
            {
                if (!m_posicions.empty())
                    m_tauler.checkMoves(m_posXAnterior, m_posYAnterior, m_posicions, mousePosX, mousePosY, mouseStatus, m_moviments, m_torn);
                m_tauler.showMoves(i, j, m_posicions, m_torn);
            }
        }
        else
        {
            m_delay++;
            mostrarGuanyador();
            if (m_delay == 2500)
                return true;
        }
        break;
    case GM_REPLAY:
        GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 620, 0.8, "Game Mode: RePlay");
        m_tauler.render();
        mostrarTorn();
        m_tauler.movesReplay(mousePosX, mousePosY, mouseStatus, m_moviments, m_torn);
        break;
    }
    m_posXAnterior = i;
    m_posYAnterior = j;
    return false;
}


void CurrentGame::pantallaInicial(int mousePosX, int mousePosY, bool mouseStatus)
{
    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * 2) + 60;
    std::string msg_normal = "GAME MODE: NORMAL";
    std::string msg_replay = "GAME MODE: REPLAY";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 1, msg_normal);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY + 60, 1, msg_replay);

    /*prova: saber les coordenades del ratoli
    int posTextXaux = CELL_INIT_X;
    int posTextYaux = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextXaux, posTextYaux, 0.8, msg);
    */

    //per poder saber a quin mode de joc han triat.
    if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= 260) &&
        (mousePosX <= (380)) &&
        (mousePosY <= (285)))
        m_mode = GM_NORMAL;

    if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= 320) &&
        (mousePosX <= (380)) &&
        (mousePosY <= (345)))
        m_mode = GM_REPLAY;
}

bool    CurrentGame::obtenirCasella(int& i, int& j, int mousePosX, int mousePosY, bool mouseStatus)
{
    //primer hem de veure si el cursor esta al tauler
    //aquesta funcio pot retornar 3 valors. 0 si si no ha click, 1 si ha fet click pero no al tauler i 2 si ha fet click al tauler. Aixo per poder mostrar els movimements sense haver de mantenir el click
    bool ret = 1;
    if (mouseStatus)
    {
        if ((mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
            (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
            (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
        {
            i = (mousePosX - CELL_INIT_X) / CELL_W;
            j = (mousePosY - CELL_INIT_Y) / CELL_H;
        }
        else
        {
            ret = 0;
            i = -1;
            j = -1;
        }
    }
    return ret;
}


void    CurrentGame::loadReplayFromFile(const string& path)
{
    ifstream fitxer;
    string posFrom;
    string posTo;

    fitxer.open(path);
    if (fitxer.is_open())
    {
        fitxer >> posFrom >> posTo;
        while (!fitxer.eof())
        {
            m_moviments.push(posFrom);
            m_moviments.push(posTo);
            fitxer >> posFrom >> posTo;
        }
        fitxer.close();
    }
}

void    CurrentGame::mostrarTorn() const
{
    if (m_torn == CPC_Black)
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 680, 0.8, "Turn: Black");
    else
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 680, 0.8, "Turn: White");
}

void    CurrentGame::mostrarGuanyador() const
{
    if (m_torn == CPC_White)
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 250, 2.5, "Winner: Black");
    else
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 250, 2.5, "Winner: White");
}
