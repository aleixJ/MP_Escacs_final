//
//  Chessboard.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "../Chess/Piece.hpp"
#include "../Chess/GameInfo.h"



class Chessboard {

public:
    Chessboard();

    VecOfPositions  GetValidMoves(const ChessPosition& pos);
    bool            MovePiece (const ChessPosition& posFrom, const ChessPosition& posTo);

    string ToString();
    void InicialitzaTauler();
    void LoadBoardFromFile(const string& path);

    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;

    //FUNCIONS DE PROVA
    void mostrarGetPiece(int x, int y);
    ChessPosition obtenirPosicio(string pos) { return ChessPosition(pos); }
    void mostrarVector(VecOfPositions temp) const;


    Piece m_board[NUM_COLS][NUM_ROWS];

    void canviTorn(ChessPieceColor& torn);
    //llibreria grafica
    void render();
    void showMoves(int i, int j, VecOfPositions& posValid, ChessPieceColor& torn);
    void checkMoves(int i, int j, VecOfPositions posValid, int mousePosX, int mousePosY, bool mouseStatus, QueueMovements& moviments, ChessPieceColor& torn);
    void movesReplay(int mousePosX, int mousePosY, bool mouseStatus, QueueMovements& moviments, ChessPieceColor& torn);

    bool jaque(ChessPieceColor reiComprovar);
    bool AuxMovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, VecOfPositions temporal);
    VecOfPositions  AuxGetValidMoves(const ChessPosition& pos);
    bool jaqueMate(ChessPieceColor torn);

private:
    ChessPieceColor ToColor(int color);
    ChessPieceType ToType(char type);
    bool dinsMatriu(const int x, const int y) const;
    void movPawn(const ChessPosition& pos, VecOfPositions& temporal) const;
    void movKnight(const ChessPosition& pos, VecOfPositions& temporal) const;
    void movKing(const ChessPosition& pos, VecOfPositions& temporal) const;
    void movRecte(const ChessPosition& pos, VecOfPositions& temporal) const;
    void movDiagonal(const ChessPosition& pos, VecOfPositions& temporal) const;
    bool checkMov(int x, int y, ChessPieceColor color, VecOfPositions& temporal) const;
};


#endif /* Chessboard_hpp */
