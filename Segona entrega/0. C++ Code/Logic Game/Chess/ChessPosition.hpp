//
//  ChessPosition.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//



#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class ChessPosition {

public:
    ChessPosition() { m_posX = 0; m_posY = 0; };
    ChessPosition(int x, int y) { m_posX = x; m_posY = y; };
    ChessPosition(string pos)
    {
        m_posX = pos[0] - 97;
        m_posY = 56 - pos[1];
    };
    int getPosX() const { return m_posX; };
    int getPosY() const { return m_posY; };

    bool validaPosicio(); // no s'utilitza

    //Sobrecarrega
    bool operator==(const ChessPosition& pos) const;

private:
    int m_posX; //Column
    int m_posY; //Row
    
};

ostream& operator<<(ostream& output, const ChessPosition& pos);

#endif /* ChessPosition_hpp */

