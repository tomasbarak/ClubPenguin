#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include "functions.h"
sf::RenderWindow window(sf::VideoMode(950, 600), "Club Penguin", sf::Style::Titlebar | sf::Style::Close);

int main(){
    sf::Texture background;
    sf::Sprite backgroundSprite;
    sf::CircleShape hola(15.f);
    hola.setFillColor(sf::Color::Black);
    if (!background.loadFromFile("background.jpg", sf::IntRect())){
        return -1;
    }
bool a = false;
    setBG(&backgroundSprite, &background);
    while(window.isOpen()){
        std::vector<sf::Drawable*> sceneObjects = {&backgroundSprite, &hola};
        window.clear();
        //Aca adentro va lo que quiero dibujar
        std::thread staticScene(drawScene, sceneObjects, &window);
        staticScene.join();

        std::thread events(eventHandler, &window);
        events.join();
        if(!a){
            for(float i = 1; i < 11; i+=0.1) {
                //std::cout << hola.getPosition().x << std::endl;
                calcMovement((float)i/10, hola);
                std::cout << hola.getPosition().x << std::endl;
            }
            a = true;

        }

        window.display();
        if(!window.isOpen()){
            break;
        }
    }
    std::cout << "Ventana cerrada";
    return 0;
}