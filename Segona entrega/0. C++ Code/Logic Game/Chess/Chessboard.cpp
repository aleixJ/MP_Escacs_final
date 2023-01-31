//
//  Chessboard.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "../Chess/Chessboard.hpp"
#include <iostream>
#include <string>

using namespace std;

Chessboard::Chessboard()
{

}

void Chessboard::InicialitzaTauler()
{
	//Inicialitzem cada posicio de la matriu amb la pe�a i color corresponent

	//Part "superior", assignem les peces de color blanc
	m_board[0][0].setTypeAndColor(CPT_Rook, CPC_Black);
	m_board[1][0].setTypeAndColor(CPT_Knight, CPC_Black);
	m_board[2][0].setTypeAndColor(CPT_Bishop, CPC_Black);
	m_board[3][0].setTypeAndColor(CPT_Queen, CPC_Black);
	m_board[4][0].setTypeAndColor(CPT_King, CPC_Black);
	m_board[5][0].setTypeAndColor(CPT_Bishop, CPC_Black);
	m_board[6][0].setTypeAndColor(CPT_Knight, CPC_Black);
	m_board[7][0].setTypeAndColor(CPT_Rook, CPC_Black);

	//Part "inferior", assignem les peces de color negre
	m_board[0][7].setTypeAndColor(CPT_Rook, CPC_White);
	m_board[1][7].setTypeAndColor(CPT_Knight, CPC_White);
	m_board[2][7].setTypeAndColor(CPT_Bishop, CPC_White);
	m_board[3][7].setTypeAndColor(CPT_Queen, CPC_White);
	m_board[4][7].setTypeAndColor(CPT_King, CPC_White);
	m_board[5][7].setTypeAndColor(CPT_Bishop, CPC_White);
	m_board[6][7].setTypeAndColor(CPT_Knight, CPC_White);
	m_board[7][7].setTypeAndColor(CPT_Rook, CPC_White);

	//Peons
	for (int i = 0; i < NUM_COLS; i++) {
		m_board[i][1].setTypeAndColor(CPT_Pawn, CPC_Black);
		m_board[i][6].setTypeAndColor(CPT_Pawn, CPC_White);
	}
}

ChessPieceType Chessboard::ToType(char type)
{
	ChessPieceType res = CPT_EMPTY;
	switch (type)
	{
	case 'R':
		res = CPT_King;
		break;
	case 'D':
		res = CPT_Queen;
		break;
	case 'T':
		res = CPT_Rook;
		break;
	case 'A':
		res = CPT_Bishop;
		break;
	case 'C':
		res = CPT_Knight;
		break;
	case 'P':
		res = CPT_Pawn;
		break;
	default:
		cout << "Error: switch case (ToType)" << endl;
	}
	return res;
}

ChessPieceColor Chessboard::ToColor(int color)
{
	ChessPieceColor res = CPC_NONE;
	switch (color)
	{
	case 0:
		res = CPC_White;
		break;
	case 1:
		res = CPC_Black;
		break;
	default:
		cout << "Error: switch case (ToColor)" << endl;
	}
	return res;
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const
{
	int x, y;
	x = pos.getPosX();
	y = pos.getPosY();
	return m_board[x][y].getType();
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const
{
	int x, y;
	x = pos.getPosX();
	y = pos.getPosY();
	return m_board[x][y].getColor();
}

string Chessboard::ToString() //Per imprimir el tauler per pantalla;
{
	string res;
	string space = " ";
	for (int j = 0; j < NUM_COLS; j++)
	{
	res += to_string(8 - j) + space; //to_string �s una funcio de <string>
	for (int i = 0; i < NUM_ROWS; i++)
	{
		res += m_board[i][j].pieceToString() + space;
	}
	res += "\n";
	}
	res += "  a  b  c  d  e  f  g  h";
	res += "\n";
	return res;
}

void Chessboard::LoadBoardFromFile(const string& path)
{
	ifstream fitxer;
	int color;
	char type;
	string pos;
	int x, y;
	fitxer.open(path);
	ChessPosition temp;
	if (fitxer)
	{
		cout << "Fitxer trobat!" << endl;
	}
	else
	{
		cout << "Fitxer no trobat!" << endl;
	}
	if (fitxer.is_open())
	{
		fitxer >> color;
		fitxer >> type;
		fitxer >> type;
		fitxer >> pos;
		while (!fitxer.eof())
		{
			//La idea seria agafar la primera lletra com a variable i guardar la segona lletra i el numero (que es la posicio del tauler), connvertir la lletra a un numero del 0 al 7; restar 1 al numero que et donen. Un cop fet aixo guardar a la posicio de la matriu el tipus de pe�a (la primera lletra) i el color (el primer numero)
			ChessPosition temp(pos);
			x = temp.getPosX();
			y = temp.getPosY();
			m_board[x][y].setTypeAndColor(ToType(type), ToColor(color));

			fitxer >> color;
			fitxer >> type;
			fitxer >> type;
			fitxer >> pos;
		}
		ChessPosition temp(pos);
		x = temp.getPosX();
		y = temp.getPosY();
		m_board[x][y].setTypeAndColor(ToType(type), ToColor(color));

		fitxer.close();
	}
}

void Chessboard::mostrarGetPiece(int x, int y)
{
	cout << m_board[x][y].getColor() << endl << m_board[x][y].getType();
}


VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos)
{
	VecOfPositions temporal;

	switch (GetPieceTypeAtPos(pos))
	{
	case CPT_King:
		movKing(pos, temporal);
		break;
	case CPT_Queen:
		movDiagonal(pos, temporal);
		movRecte(pos, temporal);
		break;
	case CPT_Rook:
		movRecte(pos, temporal);
		break;
	case CPT_Bishop:
		movDiagonal(pos, temporal);
		break;
	case CPT_Knight:
		movKnight(pos, temporal);
		break;
	case CPT_Pawn:
		movPawn(pos, temporal);
		break;
	case CPT_EMPTY:
		break;
	}
	//mostrarVector(temporal);
	//eliminem les posicions que provoquen auto jaque
	
	if (!temporal.empty())
	{
		int i = 0;
		while(i < temporal.size())
		{
			if (AuxMovePiece(pos, temporal[i], temporal))
			{
				temporal.erase(temporal.begin() + i);
			}
			else
				i++;
		}
	}

	return temporal;
}

void Chessboard::mostrarVector(VecOfPositions temp) const
{
	if (temp.size() == 0)
		cout << "vector buit";
	for (int i = 0; i < temp.size(); i++)
	{
		cout << temp[i] << " "; //utilitza la sobrecarrega '<<' per mostrar per pantalla la posicio en format "a1"
	}
	cout << endl;
}

bool Chessboard::dinsMatriu(const int x, const int y) const
{
	bool res = false;
	if ((x < NUM_COLS) && (0 <= x) && (y < NUM_ROWS) && (0 <= y))
		res = true;
	return res;
}

void Chessboard::movPawn(const ChessPosition& pos, VecOfPositions& temporal) const
{
	int x, y;
	x = pos.getPosX();
	y = pos.getPosY();
	if (GetPieceColorAtPos(pos) == CPC_White)
	{
		if (y != 6)//vol dir que s'ha mogut
		{
			if (dinsMatriu(x, y - 1))
			{
				if ((m_board[x][y - 1].getType() == CPT_EMPTY))
					temporal.push_back(ChessPosition(x, y - 1));
			}
		}
		else
		{
			if ((m_board[x][y - 1].getType() == CPT_EMPTY) && (m_board[x][y - 2].getType() == CPT_EMPTY))
			{
				temporal.push_back(ChessPosition(x, y - 1));
				temporal.push_back(ChessPosition(x, y - 2));
			}
			else
			{
				if (m_board[x][y - 1].getType() == CPT_EMPTY)
					temporal.push_back(ChessPosition(x, y - 1));
			}
		}
		//ara comproven si pot matar
		if (dinsMatriu(x - 1, y - 1))
		{
			if (m_board[x - 1][y - 1].getColor() == CPC_Black)
				temporal.push_back(ChessPosition(x - 1, y - 1));
		}
		if (dinsMatriu(x + 1, y - 1))
		{
			if (m_board[x + 1][y - 1].getColor() == CPC_Black)
				temporal.push_back(ChessPosition(x + 1, y - 1));
		}
	}
	else
	{ //el peo es una piece negra
		if (y != 1)//vol dir que s'ha mogut
		{
			if (dinsMatriu(x, y + 1))
			{
				if ((m_board[x][y + 1].getType() == CPT_EMPTY))
					temporal.push_back(ChessPosition(x, y + 1));
			}
		}
		else
		{
			if ((m_board[x][y + 1].getType() == CPT_EMPTY) && (m_board[x][y + 2].getType() == CPT_EMPTY))
			{
				temporal.push_back(ChessPosition(x, y + 1));
				temporal.push_back(ChessPosition(x, y + 2));
			}
			else
			{
				if (m_board[x][y + 1].getType() == CPT_EMPTY)
					temporal.push_back(ChessPosition(x, y + 1));
			}
		}
		//ara comproven si pot matar
		if (dinsMatriu(x + 1, y + 1))
		{
			if (m_board[x + 1][y + 1].getColor() == CPC_White)
				temporal.push_back(ChessPosition(x + 1, y + 1));
		}
		if (dinsMatriu(x - 1, y + 1))
		{
			if (m_board[x - 1][y + 1].getColor() == CPC_White)
				temporal.push_back(ChessPosition(x - 1, y + 1));
		}
	}
}

void Chessboard::movRecte(const ChessPosition& pos, VecOfPositions& temporal) const
{

	int x = pos.getPosX();
	int y = pos.getPosY();

	int j = 1;
	bool end_left = false;
	bool end_right = false;
	bool end_up = false;
	bool end_down = false;

	ChessPieceColor pos_color = GetPieceColorAtPos(pos);
	while (!(end_left && end_right && end_up && end_down)) {

		if (!end_left) {
			end_left = checkMov(x - j, y, pos_color, temporal);
		}

		if (!end_right) {
			end_right = checkMov(x + j, y, pos_color, temporal);
		}

		if (!end_up) {
			end_up = checkMov(x, y - j, pos_color, temporal);
		}

		if (!end_down) {
			end_down = checkMov(x, y + j, pos_color, temporal);
		}
		j++;
	}
}


void Chessboard::movDiagonal(const ChessPosition& pos, VecOfPositions& temporal) const
{

	int x = pos.getPosX();
	int y = pos.getPosY();

	int j = 1;
	bool end_up_left = false;
	bool end_down_right = false;
	bool end_up_right = false;
	bool end_down_left = false;

	ChessPieceColor pos_color = GetPieceColorAtPos(pos);
	while (!(end_up_left && end_down_right && end_up_right && end_down_left)) {

		if (!end_up_left) {
			end_up_left = checkMov(x - j, y + j, pos_color, temporal);
		}

		if (!end_down_right) {
			end_down_right = checkMov(x + j, y - j, pos_color, temporal);
		}

		if (!end_up_right) {
			end_up_right = checkMov(x + j, y + j, pos_color, temporal);
		}

		if (!end_down_left) {
			end_down_left = checkMov(x - j, y - j, pos_color, temporal);
		}
		j++;
	}
}

bool Chessboard::checkMov(int x, int y, ChessPieceColor color, VecOfPositions& temporal) const {
	bool end = false;

	if (dinsMatriu(x, y)) {
		if (m_board[x][y].getType() == CPT_EMPTY) {
			temporal.push_back(ChessPosition(x, y));
		}
		else {
			if (m_board[x][y].getColor() != color) {
				temporal.push_back(ChessPosition(x, y));
			}
			end = true;
		}
	}
	else {
		end = true;
	}

	return end;
}

void Chessboard::movKnight(const ChessPosition& pos, VecOfPositions& temporal) const
{

	int x, y;

	x = pos.getPosX();

	y = pos.getPosY();

	ChessPieceColor colorK = GetPieceColorAtPos(pos);

	if (dinsMatriu(x - 1, y - 2))

	{
		if (m_board[x - 1][y - 2].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x - 1, y - 2));
		}
	}

	if (dinsMatriu(x + 1, y + 2))

	{
		if (m_board[x + 1][y + 2].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x + 1, y + 2));
		}
	}

	if (dinsMatriu(x - 2, y - 1))

	{
		if (m_board[x - 2][y - 1].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x - 2, y - 1));
		}
	}

	if (dinsMatriu(x + 2, y + 1))

	{
		if (m_board[x + 2][y + 1].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x + 2, y + 1));
		}
	}

	if (dinsMatriu(x - 1, y + 2))

	{
		if (m_board[x - 1][y + 2].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x - 1, y + 2));
		}
	}

	if (dinsMatriu(x + 1, y - 2))

	{
		if (m_board[x + 1][y - 2].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x + 1, y - 2));
		}
	}

	if (dinsMatriu(x - 2, y + 1))

	{
		if (m_board[x - 2][y + 1].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x - 2, y + 1));
		}
	}

	if (dinsMatriu(x + 2, y - 1))

	{
		if (m_board[x + 2][y - 1].getColor() != colorK)

		{
			temporal.push_back(ChessPosition(x + 2, y - 1));
		}
	}

}


void Chessboard::movKing(const ChessPosition& pos, VecOfPositions& temporal) const
{

	int x = pos.getPosX();

	int y = pos.getPosY();

	ChessPieceColor colorRey = GetPieceColorAtPos(pos);

	if (dinsMatriu(x - 1, y))

	{
		if (m_board[x - 1][y].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x - 1, y));
		}
	}

	if (dinsMatriu(x + 1, y))

	{
		if (m_board[x + 1][y].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x + 1, y));
		}
	}


	if (dinsMatriu(x, y - 1))

	{
		if (m_board[x][y - 1].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x, y - 1));
		}
	}

	if (dinsMatriu(x, y + 1))

	{
		if (m_board[x][y + 1].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x, y + 1));
		}
	}

	if (dinsMatriu(x - 1, y - 1))

	{
		if (m_board[x - 1][y - 1].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x - 1, y - 1));
		}
	}

	if (dinsMatriu(x + 1, y + 1))

	{
		if (m_board[x + 1][y + 1].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x + 1, y + 1));
		}
	}

	if (dinsMatriu(x - 1, y + 1))

	{
		if (m_board[x - 1][y + 1].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x - 1, y + 1));
		}
	}

	if (dinsMatriu(x + 1, y - 1))

	{
		if (m_board[x + 1][y - 1].getColor() != colorRey)

		{
			temporal.push_back(ChessPosition(x + 1, y - 1));
		}
	}

}

bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	VecOfPositions temporal = GetValidMoves(posFrom);
	bool trobat = false;
	int xF, yF, xT, yT, i = 0;
	xF = posFrom.getPosX();
	yF = posFrom.getPosY();
	xT = posTo.getPosX();
	yT = posTo.getPosY();
	ChessPieceColor colorF = m_board[xF][yF].getColor();
	ChessPieceType typeF = m_board[xF][yF].getType();

	while (!trobat && i < temporal.size())
	{
		if (temporal[i] == posTo)
		{
			//per fer que un peó es converteixi en dama automaticament si arriba al final.
			if ((posTo.getPosY() == 0 && m_board[xF][yF].getType() == CPT_Pawn) || (posTo.getPosY() == 7 && m_board[xF][yF].getType() == CPT_Pawn))
			{
				m_board[xT][yT].setTypeAndColor(CPT_Queen, colorF);
				m_board[xF][yF].setTypeAndColor(CPT_EMPTY, CPC_NONE);
			}
			else
			{
				m_board[xT][yT].setTypeAndColor(typeF, colorF);
				m_board[xF][yF].setTypeAndColor(CPT_EMPTY, CPC_NONE);
			}
			trobat = true;
		}
		else
			i++;
	}
	return trobat;
}

void Chessboard::render()
{
	for (int j = 0; j < NUM_COLS; j++)
	{
		for (int i = 0; i < NUM_ROWS; i++)
			m_board[i][j].render(i, j);
	}
}


void Chessboard::showMoves(int i, int j, VecOfPositions& posValid, ChessPieceColor& torn)
{
	bool trobat = false;
	if (m_board[i][j].getColor() == torn)
	{
		ChessPosition pos(i, j);
		posValid = GetValidMoves(pos);
		if (!posValid.empty())
		{
			trobat = true;
			for (int k = 0; k < posValid.size(); k++)
			{
				int x = posValid[k].getPosX();
				int y = posValid[k].getPosY();
				m_board[i][j].showMoves(x, y);
			}
		}
	}
}


void Chessboard::checkMoves(int i, int j, VecOfPositions posValid, int mousePosX, int mousePosY, bool mouseStatus, QueueMovements& moviments, ChessPieceColor& torn)
{
	ChessPosition posFrom(i, j);
	bool trobat = false;
	int k = 0;
	if (m_board[i][j].getColor() == torn)
	{
		if (!posValid.empty())
		{
			int posX = (mousePosX - CELL_INIT_X) / CELL_W;
			int posY = (mousePosY - CELL_INIT_Y) / CELL_H;
			ChessPosition posTo(posX, posY);

			while (k < posValid.size() && !trobat)
			{
				int x = posValid[k].getPosX();
				int y = posValid[k].getPosY();
				ChessPosition posAux(x, y);
				if ((posAux == posTo) && mouseStatus)
				{
					MovePiece(posFrom, posTo);
					trobat = true;
					canviTorn(torn);
					//guardem el moviment a la cua.
					moviments.push(posFrom);
					moviments.push(posTo);
				}
				else
					k++;
			}
		}
	}
}

void Chessboard::canviTorn(ChessPieceColor& torn)
{
	if (torn == CPC_Black)
		torn = CPC_White;
	else
		torn = CPC_Black;
}


void Chessboard::movesReplay(int mousePosX, int mousePosY, bool mouseStatus, QueueMovements& moviments, ChessPieceColor& torn)
{
	if (moviments.empty())
	{
		GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, 740, 0.8, "No more moves to replay");
	}
	else
	{
		//s'ha fet que es repredueixi el moviment si s'apreta "return" perque amb el click es reproduient tots de cop (no hi ha delay)
		if (Keyboard_GetKeyTrg(KEYBOARD_RETURN))
		{
			ChessPosition posFrom = moviments.front();
			cout << moviments.front() << " ";
			moviments.pop();
			ChessPosition posTo = moviments.front();
			cout << moviments.front() << "\n";
			moviments.pop();
			MovePiece(posFrom, posTo);
			canviTorn(torn);
		}
	}
}


bool Chessboard::jaque(ChessPieceColor reiComprovar)
{
	ChessPosition posRei;
	for (int i = 0; i < NUM_COLS; i++)
	{
		for (int j = 0; j < NUM_ROWS; j++)
		{
			if ((m_board[i][j].getType() == CPT_King) && (m_board[i][j].getColor() == reiComprovar))
				posRei = ChessPosition(i,j);
		}
	}

	for (int i = 0; i < NUM_COLS; i++)
	{
		for (int j = 0; j < NUM_ROWS; j++)
		{
			if ((m_board[i][j].getType() != CPT_EMPTY) && (m_board[i][j].getColor() != reiComprovar))
			{
				ChessPosition posTemp(i, j);
				VecOfPositions temporal = AuxGetValidMoves(posTemp);
				for (int k = 0; k < temporal.size(); k++)
				{
					if (temporal[k] == posRei)
						return true;
				}
			}
		}
	}
	return false;
}


bool Chessboard::AuxMovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, VecOfPositions temporal)
{
	Chessboard aux;
	for (int i = 0; i < NUM_COLS; i++)
	{
		for (int j = 0; j < NUM_ROWS; j++)
		{
			aux.m_board[i][j] = m_board[i][j];
		}
	}
	int xF, yF, xT, yT, i = 0;
	xF = posFrom.getPosX();
	yF = posFrom.getPosY();
	xT = posTo.getPosX();
	yT = posTo.getPosY();
	ChessPieceColor colorF = aux.m_board[xF][yF].getColor();
	ChessPieceType typeF = aux.m_board[xF][yF].getType();
	bool jaque = false;

			//per fer que un peó es converteixi en dama automaticament si arriba al final.
	if ((posTo.getPosY() == 0 && aux.m_board[xF][yF].getType() == CPT_Pawn) || (posTo.getPosY() == 7 && aux.m_board[xF][yF].getType() == CPT_Pawn))
	{
		aux.m_board[xT][yT].setTypeAndColor(CPT_Queen, colorF);
		aux.m_board[xF][yF].setTypeAndColor(CPT_EMPTY, CPC_NONE);
	}
	else
	{
		aux.m_board[xT][yT].setTypeAndColor(typeF, colorF);
		aux.m_board[xF][yF].setTypeAndColor(CPT_EMPTY, CPC_NONE);
	}
	if (aux.jaque(colorF))
		jaque = true;

	return jaque;
}

VecOfPositions  Chessboard::AuxGetValidMoves(const ChessPosition& pos)
{
	VecOfPositions temporal;

	switch (GetPieceTypeAtPos(pos))
	{
	case CPT_King:
		movKing(pos, temporal);
		break;
	case CPT_Queen:
		movDiagonal(pos, temporal);
		movRecte(pos, temporal);
		break;
	case CPT_Rook:
		movRecte(pos, temporal);
		break;
	case CPT_Bishop:
		movDiagonal(pos, temporal);
		break;
	case CPT_Knight:
		movKnight(pos, temporal);
		break;
	case CPT_Pawn:
		movPawn(pos, temporal);
		break;
	case CPT_EMPTY:
		break;
	}
	return temporal;
}

bool Chessboard::jaqueMate(ChessPieceColor torn)
{
	//comproven si es pot fer algun moviment, es a dir, si hi ha o no jaque mate
	bool mate = true;
	VecOfPositions temporal;
	for (int i = 0; i < NUM_COLS; i++)
	{
		for (int j = 0; j < NUM_ROWS; j++)
		{
			if ((m_board[i][j].getColor() == torn))
			{
				ChessPosition posTemp(i, j);
				temporal = GetValidMoves(posTemp);
				if (!temporal.empty())
					return false;
			}
		}
	}
	return mate;
}