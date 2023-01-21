#include "ExtendedBoard.hpp"
ExtendedBoard::ExtendedBoard()
	:Board()
{
	m_board_spr.setTexture(TextureManager::get_texture(BOARD_WHITE_TEXTURE_PATH));
	m_board_spr.setPosition(sf::Vector2f(0, 0));
	m_is_upright = true;
	m_held_piece = -1;
}
sf::Vector2f ExtendedBoard::index_to_spr_pos(const int& index)const
{
	const int x_pos = (index % 8)-1;
	const int y_pos = static_cast<int>(std::floor(index / 8));
	if (m_is_upright)
	{
		return sf::Vector2f(static_cast<float>(x_pos*100),static_cast<float>(abs(y_pos-7)*100));
	}
	return sf::Vector2f(static_cast<float>(abs(x_pos-7) * 100), static_cast<float>(y_pos * 100));

}
int ExtendedBoard::spr_pos_to_index(const sf::Vector2f& pos)
{
	sf::Vector2i adjusted_pos = 
		sf::Vector2i(static_cast<int>(pos.x) + 50,
			static_cast<int>(pos.y) + 50);
	adjusted_pos.x = static_cast<int>(std::floor(adjusted_pos.x / 100));
	adjusted_pos.y = static_cast<int>(std::floor(adjusted_pos.y / 100));
	return board_to_index(adjusted_pos);
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
					,abs(m_pieces[i]->get_sprite_pos().y - 700)));
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
	
	if(m_held_piece != -1)
	{
		window.draw(m_pieces[m_held_piece]->get_sprite());
	}
}
void ExtendedBoard::on_click(const sf::Vector2i& mouse_pos)
{
	if(m_held_piece == -1)
	{
		//finds the piece that the use is trying to select
		for(size_t i = 0; i < m_pieces.size();++i)
		{
			if(m_pieces[i] == nullptr)
				break;
			if(m_pieces[i]->get_sprite().getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
			{
				if(m_is_whites_turn == m_pieces[i]->is_white())
				{
					m_held_piece = static_cast<int>(i);
					return;
				}
			}
		}
	}
	else
	{
		m_pieces[m_held_piece]->set_sprite_position(sf::Vector2f(static_cast<float>(mouse_pos.x - 50),
			static_cast<float>(mouse_pos.y - 50)));
	}
}
void ExtendedBoard::on_release()
{
	if(m_held_piece != -1)
	{
		std::vector<Move> possible_moves = generate_possible_moves_for_piece(m_held_piece);
		const int target_index = spr_pos_to_index(m_pieces[m_held_piece]->get_sprite_pos());
		bool move_made = false;
		for(const auto& i : possible_moves)
		{
			if(m_held_piece == i.m_start_pos && target_index == i.m_end_pos)
			{
				//make move
				move_made = true;
			}
		}
		if(move_made == false)
		{
			m_pieces[m_held_piece]->set_sprite_position(index_to_spr_pos(m_held_piece));
		}
		m_held_piece = -1;
	}
}
