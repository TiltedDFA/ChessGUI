#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <string>

#define PIECE_TEXTURE_PATH "assets/Chess_Pieces_Sprite.png"
#define BOARD_TEXTURE_PATH "assets/board.png"
#define WINDOW_TITLE "ChessEngine"

class Display
{
private:
	static sf::Vector2i get_piece_position(uint8_t* piece);
	static sf::Vector2i get_board_pos(const sf::Sprite& spr);
public:
	Display();

	static void init(const std::array<uint8_t*, 64>& board);
	static void draw(sf::RenderWindow& window);
	static void move_piece(const sf::Vector2i& mouse_pos, const std::array<uint8_t*, 64>& board);
	static void piece_released();
public:
	//some constants related displaying
	static constexpr int SCREEN_HEIGHT = 1000;
	static constexpr int SCREEN_WIDTH = 1000;
private:
	static Display* m_s_instance;
	sf::Texture m_piece_spr_sheet;
	sf::Texture m_board_txtr;
	sf::Sprite m_background;
	bool m_piece_is_held;
	sf::Sprite* m_held_sprite;
	std::vector<sf::Sprite> m_draw_list;
};

