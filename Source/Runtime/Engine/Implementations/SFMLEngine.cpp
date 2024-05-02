#include "SFMLEngine.h"

#include "../../Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../../Utils/TemplateUtils.h"

void ASFMLEngine::Start() {
    Super::Start();

    m_window = new sf::RenderWindow(sf::VideoMode(200, 200), "Astral Engine");
    Run();
}

void ASFMLEngine::Run() {
    Super::Run();

    sf::CircleShape shape(100.f);
    while (m_window->isOpen()) {

        DeltaTime = 0;
        
        HandleSFMLEvents();//Handle All Events including Inputs

        m_window->clear();
        m_window->draw(shape);
        m_window->display();
    }
    End();
}

void ASFMLEngine::HandleSFMLEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)){
        //First Handling all cosmetic SFML events
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        //Handle the inputs
        if (IsSFMLEventInputType(event)) {
            ASFMLInputManager* SFMLInputManager = Cast<ASFMLInputManager>(GetInputManager());
            if (SFMLInputManager != nullptr) {
                SFMLInputManager->HandleSFMLInputEvent(event);
            }
        }
    }
}

bool ASFMLEngine::IsSFMLEventInputType(const sf::Event& Event) const {
    return Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased || Event.type == sf::Event::MouseMoved || Event.type == sf::Event::MouseButtonPressed ||Event.type == sf::Event::MouseButtonReleased || Event.type == sf::Event::MouseWheelMoved || Event.type == sf::Event::MouseWheelScrolled;
}

sf::RenderWindow* ASFMLEngine::GetWindow() {
    return m_window;
}


void ASFMLEngine::End() {
    
    delete m_window;
    m_window = nullptr;
    
    Super::End();
}

