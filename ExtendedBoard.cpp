#include "ExtendedBoard.hpp"
ExtendedBoard::ExtendedBoard()
	:Board()
{
	m_board_spr.setTexture(TextureManager::get_texture(BOARD_WHITE_TEXTURE_PATH));
	m_board_spr.setPosition(sf::Vector2f(0, 0));
	m_is_upright = true;
}
void ExtendedBoard::flip_board()
{
	if (m_is_upright)
	{
		m_board_spr.setTexture(TextureManager::get_texture(BOARD_BLACK_TEXTURE_PATH));
		for (size_t i = 0; i < m_pieces.size(); ++i)
		{
			if (m_pieces[i] != nullptr)
			{
				m_pieces[i]->set_sprite_position(sf::Vector2f(
					abs(m_pieces[i]->get_sprite_pos().x - 700)
					, abs(m_pieces[i]->get_sprite_pos().y - 700)));
			}
		}
		m_is_upright = !m_is_upright;
	}
	else
	{
		m_board_spr.setTexture(TextureManager::get_texture(BOARD_WHITE_TEXTURE_PATH));
		for (size_t i = 0; i < m_pieces.size(); ++i)
		{
			if (m_pieces[i] != nullptr)
			{
				m_pieces[i]->set_sprite_position(sf::Vector2f(
					abs(m_pieces[i]->get_sprite_pos().x - 700)
					, abs(m_pieces[i]->get_sprite_pos().y - 700)));
			}
		}
		m_is_upright = !m_is_upright;
	}
}
void ExtendedBoard::draw_board(sf::RenderWindow& window)const
{
	window.draw(m_board_spr);
	for (const auto& i : m_pieces)
	{
		if (i != nullptr)
		{
			window.draw(i->get_sprite());
		}
	}
}