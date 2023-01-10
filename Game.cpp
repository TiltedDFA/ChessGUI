#include "Game.hpp"
Game::Game() {
	Display::init(m_board.get_piece_array());
    m_window.setFramerateLimit(60);
    m_window.create(sf::VideoMode(Display::SCREEN_WIDTH, Display::SCREEN_HEIGHT)
        ,WINDOW_TITLE);
}
void Game::Run() {
    

    while (m_window.isOpen())
    {
        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
           // Display::move_piece(sf::Mouse::getPosition(m_window));
        }
        else
        {
            //Display::piece_released();
        }
        m_window.clear();
        
        Display::draw(m_window);
        m_window.display();
    }
}