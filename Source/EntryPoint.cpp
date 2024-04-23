
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <json/json.h>

#include "Runtime/Configs/ConfigUtils.h"
#include "Runtime/Core/Systems/ObjectManager.h"
#include "Runtime/Engine/Engine.h"
#include "Runtime/Engine/Implementations/SFMLEngine.h"
#include "Runtime/Maths/Maths.h"

int main(int argc, char* argv[]){

    // AParserBase* Parser = AObjectManager::Get()->InstanciateNewObject<AJsonParser>(AJsonParser::StaticClass());
    // Parser->WriteDataToFile("", "", nullptr);
    // FVector2D A;
    // FVector2D B;
    // float result = FVector2D::Dot(A, B);
    
    
    // std::string str;
    // int Data;
    // std::stringstream(str) << Data;
    // AEngine* Engine = AObjectManager::Get()->InstanciateNewObject<AEngine>(ASFMLEngine::StaticClass());
    // FClass Class = ASFMLEngine::StaticClass();
    //Engine->Start();
    //delete Engine;
   
    return 0;
    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    //
    // while (window.isOpen()){
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //      
    //      if (event.type == sf::Event::Closed) {
    //          window.close();
    //      }
    //     }
    //
    //     auto object1 = AObjectManager::Get()->InstanciateNewObject<AEntity>(AEntity::StaticClass());
    //     auto object2 = AObjectManager::Get()->InstanciateNewObject<AEngine>(AEngine::StaticClass());
    //
    //     Factory<ABaseObject>* Factory = AObjectManager::Get()->InternFactory;
    //     std::cout << "test";
    //     // std::filesystem::path OffsetPath = "../../";
    //     // std::filesystem::path Path = std::filesystem::current_path();
    //     // auto test = Path.parent_path();
    //     //
    //     // auto test2 = Path.root_directory();
    //     // Path += OffsetPath;
    //     // std::string Test = Path.generic_string();
    //     //
    //     // std::cout << test2;
    //
    //     //std::cout << FilerHelpers::GetProjectDirectoryAsString();
    //
    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }
    // return 0;
 }
