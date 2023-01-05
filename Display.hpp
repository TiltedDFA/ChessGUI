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
	static void update(const uint8_t*& piece);
public:
	static constexpr std::string TEXTURE_PATH = "assets/Chess_Pieces_Sprite.png";
	static constexpr int SCREEN_HIGHT = 1000;
	static constexpr int SCREEN_WIDTH = 1000;
private:
	static Display* m_s_instance;
	sf::Texture m_piece_spr_sheet;
	std::vector<sf::Sprite> m_draw_list;
};

