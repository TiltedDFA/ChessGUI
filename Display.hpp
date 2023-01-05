#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <assert.h>
#include <string>
class Display
{
private:
	static sf::Vector2i get_piece_position(uint8_t* piece);
public:
	Display();

	static void init(const std::array<uint8_t*, 64>& board);
	static void update_draw_list(const uint8_t*& piece);
	static void draw(sf::RenderWindow& window);
public:
	//some constants related displaying
	static constexpr std::string PIECE_TEXTURE_PATH = "assets/Chess_Pieces_Sprite.png";
	static constexpr std::string BOARD_TEXTURE_PATH = "assets/board.png";
	static constexpr std::string WINDOW_TITLE = "ChessEngine";
	static constexpr int SCREEN_HIGHT = 1000;
	static constexpr int SCREEN_WIDTH = 1000;
private:
	static Display* m_s_instance;
	sf::Texture m_piece_spr_sheet;
	sf::Texture m_board_txtr;
	std::vector<sf::Sprite> m_draw_list;
};

