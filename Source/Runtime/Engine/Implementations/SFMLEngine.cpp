#include "SFMLEngine.h"

void ASFMLEngine::Start() {
    Super::Start();

    m_window = new sf::RenderWindow(sf::VideoMode(200, 200), "Astral Engine");
    Run();
}

void ASFMLEngine::Run() {
    Super::Run();

    sf::CircleShape shape(100.f);
    while (m_window->isOpen()) {
        HandleSFMLEvents();

        m_window->clear();
        m_window->draw(shape);
        m_window->display();
    }
    End();
}

void ASFMLEngine::HandleSFMLEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}


void ASFMLEngine::End() {
    
    delete m_window;
    m_window = nullptr;
    
    Super::End();
}

