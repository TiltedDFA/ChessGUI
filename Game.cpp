#include "Game.hpp"
Game::Game()
{
	m_window.create(sf::VideoMode(800,800),"Chess GUI", sf::Style::Titlebar);
    m_window.setFramerateLimit(60);
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
		        switch (event.key.code)
		        {
				case sf::Keyboard::Space:
					m_main_board.flip_board();
                    break;
				case sf::Keyboard::Escape:
					m_window.close();
                    break;
				default:
					break;
		        }
                break;
	        default:
                break;
	        }
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_main_board.on_click(sf::Mouse::getPosition(m_window));
        }
        else
        {
            m_main_board.on_release();
        }
        m_window.clear();
        m_main_board.draw_board(m_window);
        m_window.display();
    }
}
