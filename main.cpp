#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include "functions.h"

sf::RenderWindow window(sf::VideoMode(950, 600), "Club Penguin", sf::Style::Titlebar | sf::Style::Close);

int main(){
    sf::Texture background;
    sf::Sprite backgroundSprite;
    sf::Sprite penguin;
    sf::Texture penguinTextureDown;//0
    sf::Texture penguinTextureUp;//1
    sf::Texture penguinTextureUpRight;//2
    sf::Texture penguinTextureUpLeft;//3
    sf::Texture penguinTextureDownRight;//4
    sf::Texture penguinTextureDownLeft;//5
    sf::Texture penguinTextureRight;//6
    sf::Texture penguinTextureLeft;//7
    std::vector<sf::Texture*> penguinTextures;
    if (!background.loadFromFile("background.jpg", sf::IntRect())){
        return -1;
    }
    if(!penguinTextureDown.loadFromFile("sprites/standing.png")){
        return -1;
    }
    if(!penguinTextureUp.loadFromFile("sprites/standing-up.png")){
        return -1;
    }
    if(!penguinTextureUpRight.loadFromFile("sprites/standing-right-up.png")){
        return -1;
    }
    if(!penguinTextureUpLeft.loadFromFile("sprites/standing-left-up.png")){
        return -1;
    }
    if(!penguinTextureDownRight.loadFromFile("sprites/standing-right-down.png")){
        return -1;
    }
    if(!penguinTextureDownLeft.loadFromFile("sprites/standing-left-down.png")){
        return -1;
    }
    if(!penguinTextureRight.loadFromFile("sprites/standing-right.png")){
        return -1;
    }
    if(!penguinTextureLeft.loadFromFile("sprites/standing-left.png")){
        return -1;
    }
    penguinTextures.push_back(&penguinTextureDown);
    penguinTextures.push_back(&penguinTextureUp);
    penguinTextures.push_back(&penguinTextureUpRight);
    penguinTextures.push_back(&penguinTextureUpLeft);
    penguinTextures.push_back(&penguinTextureDownRight);
    penguinTextures.push_back(&penguinTextureDownLeft);
    penguinTextures.push_back(&penguinTextureRight);
    penguinTextures.push_back(&penguinTextureLeft);

    sf::RectangleShape skyBox;
    skyBox.setSize(sf::Vector2f (window.getSize().x, window.getSize().y/3));
    skyBox.setFillColor(sf::Color(0, 0, 0, 150));
    skyBox.setPosition(0, 0);

    sf::RectangleShape bottomLeft;
    bottomLeft.setSize(sf::Vector2f (window.getSize().x/4, window.getSize().y/4));
    bottomLeft.setFillColor(sf::Color(0, 255, 0, 150));
    bottomLeft.setPosition(0, (window.getSize().y/4) * 3);

    sf::RectangleShape bottomRight;
    bottomRight.setSize(sf::Vector2f (window.getSize().x/4, window.getSize().y/4));
    bottomRight.setFillColor(sf::Color(0, 255, 0, 150));
    bottomRight.setPosition(((window.getSize().x/4) * 3)+50, (window.getSize().y/4) * 3.3);

    sf::RectangleShape topRight;
    topRight.setSize(sf::Vector2f (window.getSize().x/3.5, window.getSize().y/5));
    topRight.setFillColor(sf::Color(255, 0, 0, 150));
    topRight.setPosition(((window.getSize().x/4) * 2.8), (window.getSize().y/3));

    sf::RectangleShape topLeft;
    topLeft.setSize(sf::Vector2f (window.getSize().x/2.85, window.getSize().y/6));
    topLeft.setFillColor(sf::Color(255, 0, 0, 150));
    topLeft.setPosition(0, (window.getSize().y/3));

    sf::RectangleShape CoffeeDoor;
    CoffeeDoor.setSize(sf::Vector2f(window.getSize().x/16, window.getSize().y/10));
    CoffeeDoor.setFillColor(sf::Color(255, 0, 255, 150));
    CoffeeDoor.setPosition((window.getSize().x /16) * 5.8,(window.getSize().y/10) * 3.3);

    sf::RectangleShape NightClubWindow;
    NightClubWindow.setSize(sf::Vector2f(window.getSize().x/12, window.getSize().y /10));
    NightClubWindow.setFillColor(sf::Color(255, 0, 255, 150));
    NightClubWindow.setPosition((window.getSize().x / 12) * 6, (window.getSize().y /10) * 3.3);

    sf::RectangleShape giftShop;
    giftShop.setSize(sf::Vector2f(window.getSize().x / 16, window.getSize().y / 8));
    giftShop.setFillColor(sf::Color(255, 0, 255, 150));
    giftShop.setPosition((window.getSize().x / 12) * 7.6, (window.getSize().y /10)* 3.3);

    penguin.setScale(2, 2);
    setBG(&backgroundSprite, &background);
    penguin.setTexture(*penguinTextures[0]);
    penguin.setPosition(window.getSize().x/2, window.getSize().y/2);
    penguin.setRotation(0);
    penguin.setOrigin(penguin.getLocalBounds().width/2, penguin.getLocalBounds().height/2);
    while(window.isOpen()){
        std::vector<sf::Drawable*> sceneObjects = {&backgroundSprite, &penguin,/* &skyBox, &bottomLeft, &bottomRight, &topRight, &topLeft, &CoffeeDoor, &NightClubWindow, &giftShop*/};
        std::vector<sf::Drawable*> staticSceneObj = {&backgroundSprite, &skyBox, &bottomLeft, &bottomRight, &topRight, &topLeft, &CoffeeDoor, &NightClubWindow, &giftShop};
        std::vector<sf::Drawable*> dynamicSceneObj = {&penguin};
        std::vector<sf::RectangleShape*> colliders = {&skyBox, &bottomLeft, &bottomRight, &topRight, &topLeft, &CoffeeDoor, &NightClubWindow};
        //Aca adentro va lo que quiero dibujar
        //std::thread staticScene(drawScene, sceneObjects, &window);
        //staticScene.join();

        window.clear();

        std::thread events(eventHandler, &window, staticSceneObj, dynamicSceneObj, &penguin, penguinTextures, colliders);
        events.join();

        std::thread movement(movePenguin, &penguin, &window);
        movement.join();
        movePenguin(&penguin, &window);
        for(int i = 0; i < sceneObjects.size(); i++){
            drawObjects(sceneObjects[i], &window);
        }
        window.display();
        if(!window.isOpen()){
            break;
        }
    }
    std::cout << "Ventana cerrada";
    return 0;
}