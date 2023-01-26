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
	const int x_pos = (index % 8);
	const int y_pos = static_cast<int>(std::floor(index / 8));
	if (m_is_upright)
	{
		return sf::Vector2f(static_cast<float>(abs(x_pos - 7) *100),static_cast<float>(abs(y_pos-7)*100));
	}
	return sf::Vector2f(static_cast<float>(x_pos * 100), static_cast<float>(y_pos * 100));

}
int ExtendedBoard::spr_pos_to_index(const sf::Vector2f& pos)
{
	sf::Vector2i adjusted_pos = 
		sf::Vector2i(static_cast<int>(pos.x) + 50,
			static_cast<int>(pos.y) + 50);
	adjusted_pos.x = static_cast<int>(std::floor(adjusted_pos.x / 100));
	adjusted_pos.y = static_cast<int>(std::floor(adjusted_pos.y / 100));
	int val = 0;
	val += adjusted_pos.x+1;
	val += 8 * (adjusted_pos.y - 1);
	return val;
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
void ExtendedBoard::draw_possible_moves(sf::RenderWindow& window)const
{
	if (m_held_piece != -1)
	{
		const std::vector<Move> possible_moves = generate_possible_moves_for_piece(static_cast<uint8_t>(m_held_piece));
		for (const auto& i : possible_moves)
		{
			sf::Vector2f sqr_pos = index_to_spr_pos(i.m_end_pos);
			sf::RectangleShape square_to_display;
			square_to_display.setPosition(sqr_pos);
			square_to_display.setFillColor(sf::Color(255, 0, 0, 128));
			square_to_display.setSize({ 100.0f,100.0f });
			window.draw(square_to_display);
		}
	}
	else
	{
		log("attempted to draw while not holding a piece");
	}
	//for(const auto& i : m_pos)
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
		draw_possible_moves(window);
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
					log("Piece held is " + std::to_string(i));
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
		std::vector<Move> possible_moves = generate_possible_moves_for_piece(static_cast<uint8_t>(m_held_piece));
		const int target_index = spr_pos_to_index(m_pieces[m_held_piece]->get_sprite_pos());
		bool move_made = false;
		for(const auto& i : possible_moves)
		{
			if(m_held_piece == i.m_start_pos && target_index == i.m_end_pos)
			{
				//make move
				log("move attempted");
				move_made = true;
				break;
			}
		}
		if(move_made == false)
		{
			log("Move reverted");
			log("Moved to: " + std::to_string(index_to_spr_pos(m_held_piece).x) + std::to_string(index_to_spr_pos(m_held_piece).y));
			m_pieces[m_held_piece]->set_sprite_position(index_to_spr_pos(m_held_piece));
			
		}
		m_held_piece = -1;
	}
}
