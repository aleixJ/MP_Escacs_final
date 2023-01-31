//
//  Piece.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "../Chess/Piece.hpp"
#include <string>
#include <iostream>
using namespace std;

//Constructor
Piece::Piece()
{
	m_type = CPT_EMPTY;
	m_color = CPC_NONE;
}

void Piece::setTypeAndColor(ChessPieceType type, ChessPieceColor color)
{
	m_type = type;
	m_color = color;
}

string Piece::pieceToString()
{
	string res;
	switch (m_type)
	{
	case CPT_King:
		if (m_color == CPC_Black)
			res = "bR";
		else
			res = "wR";
		break;
	case CPT_Queen:
		if (m_color == CPC_Black)
			res = "bD";
		else
			res = "wD";
		break;
	case CPT_Rook:
		if (m_color == CPC_Black)
			res = "bT";
		else
			res = "wT";
		break;
	case CPT_Bishop:
		if (m_color == CPC_Black)
			res = "bA";
		else
			res = "wA";
		break;
	case CPT_Knight:
		if (m_color == CPC_Black)
			res = "bC";
		else
			res = "wC";
		break;
	case CPT_Pawn:
		if (m_color == CPC_Black)
			res = "bP";
		else
			res = "wP";
		break;
	case CPT_EMPTY:
		res = "__";
		break;
	default:
		cout << "Error: switch case (pieceToString)" << endl;
	}
	return res;
}


bool Piece::obtenirFitxer(IMAGE_NAME& res)
{
	bool trobat = false;
	switch (m_type)
	{
	case CPT_King:
		if (m_color == CPC_Black)
			res = IMAGE_PIECE_KING_BLACK;
		else
			res = IMAGE_PIECE_KING_WHITE;
		break;
	case CPT_Queen:
		if (m_color == CPC_Black)
			res = IMAGE_PIECE_QUEEN_BLACK;
		else
			res = IMAGE_PIECE_QUEEN_WHITE;
		break;
	case CPT_Rook:
		if (m_color == CPC_Black)
			res = IMAGE_PIECE_ROOK_BLACK;
		else
			res = IMAGE_PIECE_ROOK_WHITE;
		break;
	case CPT_Bishop:
		if (m_color == CPC_Black)
			res = IMAGE_PIECE_BISHOP_BLACK;
		else
			res = IMAGE_PIECE_BISHOP_WHITE;
		break;
	case CPT_Knight:
		if (m_color == CPC_Black)
			res = IMAGE_PIECE_KNIGHT_BLACK;
		else
			res = IMAGE_PIECE_KNIGHT_WHITE;
		break;
	case CPT_Pawn:
		if (m_color == CPC_Black)
			res = IMAGE_PIECE_PAWN_BLACK;
		else
			res = IMAGE_PIECE_PAWN_WHITE;
		break;
	case CPT_EMPTY:
		trobat = true;
		break;
	}
	return trobat;
}


void Piece::render(int x, int y)
{
	bool buit;
	IMAGE_NAME file;
	buit = obtenirFitxer(file);
	if(!buit)
		GraphicManager::getInstance()->drawSprite(file, CELL_INIT_X + (x * CELL_W), CELL_INIT_Y + (y * CELL_H));
}


void Piece::showMoves(int x, int y)
{
	GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (x * CELL_W), CELL_INIT_Y + (y * CELL_H));
}