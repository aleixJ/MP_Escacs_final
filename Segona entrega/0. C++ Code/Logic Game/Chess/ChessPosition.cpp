//
//  ChessPosition.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "../Chess/ChessPosition.hpp"
#include "GameInfo.h"

//Sobrecarregues
bool ChessPosition::operator==(const ChessPosition& pos) const
{
    bool res = 0;
    if (m_posX == pos.m_posX)
    {
        if (m_posY == pos.m_posY)
            res = 1;
    }
    return res;
}

ostream& operator<<(ostream& output, const ChessPosition& pos)
{
    string posicio = "xx";
    posicio[0] = pos.getPosX() + 97;
    posicio[1] = 56 - pos.getPosY();
    output << posicio[0] << posicio[1];
    return output;
}

/* Coordinate system:
    Y (rows)
  . ^
  . |  ***Black***
  4 |
  3 |
  2 |
  1 |  ***White***
 (0,0)----------> X (cols)
      a b c ...
*/
bool ChessPosition::validaPosicio()
{
    bool valid = false;
    if ((m_posX > -1) && (m_posX < 97) && (m_posY > -1) && (m_posY < 56))
        valid = true;
    return valid;
}
