#include "SFMLEngine.h"

#include "../../../Render/Systems/RenderManager.h"
#include "../../Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../../Time/TimerManager.h"
#include "../../World/World.h"

void ASFMLEngine::Start() {
    Super::Start();

    m_window = new sf::RenderWindow(sf::VideoMode(200, 200), "Astral Engine");
    
    GuardedLoop();
}

void ASFMLEngine::GuardedLoop() {
    while (m_window->isOpen()) {
     Tick(CalculateDeltaSeconds());
    }
    End();
}


void ASFMLEngine::Tick(float DeltaTime) {
    AEngine::Tick(DeltaTime);

    HandleSFMLInputs();
    
    GetTimerManager()->Tick(DeltaTime);
    GetActiveWorld()->Tick(DeltaTime);

    GetRenderManager()->Draw();
}


void ASFMLEngine::HandleSFMLInputs() {
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

