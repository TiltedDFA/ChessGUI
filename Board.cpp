#include "Board.hpp"

Board::Board()
{
	m_board.fill(nullptr);
	m_casteling[0] = { true,true };
	m_casteling[1] = { true,true };
	m_half_move_num = 0;
	m_full_move_num = 0;
	m_is_whites_turn = true;
	init_board();
}
Board::~Board()
{
	for (const auto& i : m_board)
	{
		delete i;
	}
}
void Board::init_board()
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			auto* temp = new uint8_t;
			if (i == 0)
			{
				*temp = Piece::Pawn | Piece::White;
				m_board[8 + j] = temp;
			}
			else
			{
				*temp = Piece::Pawn | Piece::Black;
				m_board[48 + j] = temp;
			}
		}
	}
	m_board[0] = new uint8_t(Piece::Rook | Piece::White);
	m_board[7] = new uint8_t(Piece::Rook | Piece::White);
	m_board[56] = new uint8_t(Piece::Rook | Piece::Black);
	m_board[63] = new uint8_t(Piece::Rook | Piece::Black);

	m_board[1] = new uint8_t(Piece::Knight | Piece::White);
	m_board[6] = new uint8_t(Piece::Knight | Piece::White);
	m_board[57] = new uint8_t(Piece::Knight | Piece::Black);
	m_board[62] = new uint8_t(Piece::Knight | Piece::Black);

	m_board[2] = new uint8_t(Piece::Bishop | Piece::White);
	m_board[5] = new uint8_t(Piece::Bishop | Piece::White);
	m_board[58] = new uint8_t(Piece::Bishop | Piece::Black);
	m_board[61] = new uint8_t(Piece::Bishop | Piece::Black);

	m_board[3] = new uint8_t(Piece::Queen | Piece::White);
	m_board[59] = new uint8_t(Piece::Queen | Piece::Black);

	m_board[4] = new uint8_t(Piece::King | Piece::White);
	m_board[60] = new uint8_t(Piece::King | Piece::Black);
}
