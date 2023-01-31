//
//  GameInfo.h
//  LearnChess
//
//  Created by Enric Vergara on 24/2/22.
//

#ifndef GameInfo_h
#define GameInfo_h
#include "../Chess/ChessPosition.hpp"
#include <fstream>
#include <vector>
#include <queue>

struct Direction {
    int dirX;
    int dirY;
};

typedef vector<ChessPosition> VecOfPositions; //s'ha hagut de copiar
typedef queue<ChessPosition> QueueMovements;

const int NUM_COLS = 8;
const int NUM_ROWS = 8;

// Tamany en píxels dels gràfics de les peces
const int CELL_W = 62;
const int CELL_H = 62;

// Posició a pantalla de la casella superior esquerra del tauler
const int CELL_INIT_X = 55;
const int CELL_INIT_Y = 64;

// Posició a pantalla de la casella superior esquerra del tauler per dibuixar les posicions vàlides
const int GREEN_INIT_X = 50;
const int GREEN_INIT_Y = 67;

// Tamany en píxels de la pantalla
const int SCREEN_SIZE_X = 750;
const int SCREEN_SIZE_Y = 850;

typedef enum {
    GM_NORMAL,
    GM_REPLAY,
    GM_NONE
} GameMode;

#endif /* GameInfo_h */
