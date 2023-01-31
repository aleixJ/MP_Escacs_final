//
//  Piece.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include "../Chess/GameInfo.h"
#include "../GraphicManager.h"
using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,
    CPT_Bishop,
    CPT_Knight,
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;





class Piece {

public:
    Piece();    //Constructor
    Piece(ChessPieceType tipo, ChessPieceColor color) { m_type = tipo; m_color = color; };

    ChessPieceType getType() const { return m_type; }
    ChessPieceColor getColor() const { return m_color; }

    void setType(ChessPieceType type) { m_type = type; }
    void setColor(ChessPieceColor color) { m_color = color; }
    void setTypeAndColor(ChessPieceType type, ChessPieceColor color);

    string pieceToString();

    //llibreria grafica
    void render(int x, int y);
    void showMoves(int x, int y);

private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;

    //llibreria grafica
    bool obtenirFitxer(IMAGE_NAME& res);
 };


#endif /* Piece_hpp */
