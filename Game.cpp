#include "Game.hpp"
Game::Game()
{
	m_window.create(sf::VideoMode(800,800),"Chess GUI");
    m_window.setFramerateLimit(10);
	Board::init_sprite();
	m_main_board.init_start_board();
}
void Game::run()
{
    while (m_window.isOpen())
    {
        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            
	        switch (event.type)
	        {
	        case sf::Event::Closed:
                m_window.close();
                break;
	        case sf::Event::KeyPressed:
		        if(event.key.code == sf::Keyboard::Space)
		        {
                    m_main_board.flip_board();
		        }
	        }
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }
        m_window.clear();
        m_main_board.draw_board(m_window);
        m_window.display();
    }
}
