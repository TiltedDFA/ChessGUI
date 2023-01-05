#include "Game.hpp"
Game::Game() {
	m_display.init(m_board.get_piece_array());
    m_window.setFramerateLimit(60);
    m_window.create(sf::VideoMode(Display::SCREEN_WIDTH, Display::SCREEN_HIGHT)
        ,Display::WINDOW_TITLE);
}
void Game::Run() {
     sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        m_window.clear();
        m_window.draw(shape);
        m_window.display();
    }
}