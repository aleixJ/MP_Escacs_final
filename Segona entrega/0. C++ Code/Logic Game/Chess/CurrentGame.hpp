//
//  CurrentGame.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include "../Chess/GameInfo.h"
#include "../Chess/Chessboard.hpp"
#include "../GraphicManager.h"

using namespace std;



class CurrentGame {

public:
    CurrentGame();
    
    void            init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool			updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void            end(const string& movementsFile);
    void            pantallaInicial(int mousePosX, int mousePosY, bool mouseStatus);
    bool            obtenirCasella(int& i, int& j, int mousePosX, int mousePosY, bool mouseStatus);
    GameMode        getMode() const { return m_mode; };
    void            loadReplayFromFile(const string& movementsFile);
    void            mostrarTorn() const;
    void            mostrarGuanyador() const;
    
private:
    
    Chessboard m_tauler;
    GameMode m_mode;
    ChessPieceColor m_torn;
    int m_delay;
    //per guardar a quina posicio del tauler es la ultima que s'ha fet click
    int m_posXAnterior;
    int m_posYAnterior;
    VecOfPositions m_posicions;
    QueueMovements m_moviments;    //per guardar la cua de moviemnts
};

#endif /* CurrentGame_hpp */

