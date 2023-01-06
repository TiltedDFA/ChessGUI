#include "Display.hpp"

#include <array>
Display* Display::m_s_instance = nullptr;

Display::Display()
{
	assert(m_s_instance == nullptr);
	m_s_instance = this;
}
sf::Vector2i Display::get_piece_position(uint8_t* piece)
{
	int y_pos = 0;
	int x_pos = 0;
	//checks if the piece is white
	if ((*piece & 0b10000000) != 0b10000000)
	{
		y_pos = 100;
	}
	//checks if piece is queen
	if ((*piece & 0b00010000) == 0b00010000)
	{
		x_pos = 100;
	}
	//bishop
	else if ((*piece & 0b00001000) == 0b00001000)
	{
		x_pos = 200;
	}
	//knight
	else if ((*piece & 0b00000100) == 0b00000100)
	{
		x_pos = 300;
	}
	//rook
	else if ((*piece & 0b00000010) == 0b00000010)
	{
		x_pos = 400;
	}
	//pawn
	else if ((*piece & 0b00000001) == 0b00000001)
	{
		x_pos = 500;
	}
	return {x_pos,y_pos};
}

void Display::init(const std::array<uint8_t*, 64>& board)
{
	auto& board_texture = m_s_instance->m_board_txtr;
	if (!board_texture.loadFromFile(BOARD_TEXTURE_PATH))
	{
		throw std::runtime_error("Failed to load texture");
	}
	auto& board_sprite = m_s_instance->m_background;
	board_sprite.setTexture(board_texture);
	board_sprite.setPosition(sf::Vector2f(0, 0));
	auto& piece_texture = m_s_instance->m_piece_spr_sheet;
	if (!piece_texture.loadFromFile(PIECE_TEXTURE_PATH))
	{
		throw std::runtime_error("Failed to load texture");
	}	
	piece_texture.setSmooth(true);
	for(auto i = board.cbegin(); i < board.cend(); ++i)
	{
		if (*i != nullptr)
		{
			auto piece_position = get_piece_position(*i);
			//sets the correct texture for the piece based on it's type
			sf::Sprite temp_piece(piece_texture,{piece_position.x,piece_position.y,100,100});
			const int index = ( &(*i) - &board[0]) ;
			const int column = index % 8;
			const int row = (index - column) / 8;
			temp_piece.setScale(sf::Vector2f(1.25, 1.25));
			//temp_piece.
			temp_piece.setPosition(sf::Vector2f((SCREEN_HIGHT / 8) * (7-column),(SCREEN_WIDTH / 8) * (7-row)));
			m_s_instance->m_draw_list.push_back(temp_piece);
		}
	}
}
void Display::draw(sf::RenderWindow& window) {
	const auto& draw_list = m_s_instance->m_draw_list;
	const auto& background = m_s_instance->m_background;
	window.draw(background);
	for (const auto& i : draw_list)
	{
		window.draw(i);
	}
}
//need to work on a way to update the draw list. the pointers wouldn't work as they are right now as
//there would be no way to find the exact piece as the passed in pointer would hold the new position
//might need to store the old position of the piece as well as where it is moved to
void Display::update_draw_list(const uint8_t*& piece)
{
	
}
