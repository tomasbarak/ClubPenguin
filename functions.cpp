#include "functions.h"

sf::Vector2f click(500,500);
float pos_x= 0;
float pos_y = 0;

void setBG(sf::Sprite *backgroundSprite, sf::Texture *backgroundTexture){
    backgroundSprite->setTexture(*backgroundTexture);
    backgroundSprite->scale(0.25f, 0.25f);
}

void drawObjects(sf::Drawable *objectToDraw, sf::RenderWindow *window){
    window->draw(*objectToDraw);
}
void drawScene(std::vector<sf::Drawable*> drawObjectList, sf::RenderWindow *window){
    for(int i = 0; i < drawObjectList.size(); i++){
        drawObjects(drawObjectList[i], window);
    }
}

void eventHandler(sf::RenderWindow *window){
    sf::Event event;
    while (window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            exit(0);
        }
    }
}

void movePenguin(sf::CircleShape *penguinSprite, sf::RenderWindow *window){
    float x = 0.1;
}
void calcMovement(float lambda, sf::CircleShape &pinguino){
    pinguino.setPosition((click - pinguino.getPosition() * lambda)+pinguino.getPosition());
}
