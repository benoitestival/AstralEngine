
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#include "Runtime/Core/Engine/Engine.h"
#include "Runtime/Core/Entities/Entity.h"
#include "Runtime/Core/Systems/ObjectManager.h"

int main(int argc, char* argv[]){
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
   
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
         
         if (event.type == sf::Event::Closed) {
             window.close();
         }
        }

        auto object1 = AObjectManager::Get()->InstanciateNewObject<AEntity>(AEntity::StaticClass());
        auto object2 = AObjectManager::Get()->InstanciateNewObject<AEngine>(AEngine::StaticClass());

        Factory<ABaseObject>* Factory = AObjectManager::Get()->InternFactory;
        std::cout << "test";
        // std::filesystem::path OffsetPath = "../../";
        // std::filesystem::path Path = std::filesystem::current_path();
        // auto test = Path.parent_path();
        //
        // auto test2 = Path.root_directory();
        // Path += OffsetPath;
        // std::string Test = Path.generic_string();
        //
        // std::cout << test2;

        //std::cout << FilerHelpers::GetProjectDirectoryAsString();

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
 }
