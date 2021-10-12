//
// Created by barak on 28/9/21.
//
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#ifndef CLUBPENGUIN_FUNCTIONS_H
#define CLUBPENGUIN_FUNCTIONS_H



void setBG(sf::Sprite *backgroundSprite, sf::Texture *backgroundTexture);
void drawObjects(sf::Drawable *objectToDraw, sf::RenderWindow *window);
void drawScene(std::vector<sf::Drawable*> drawObjectList, sf::RenderWindow *window);
void eventHandler(sf::RenderWindow *window, std::vector<sf::Drawable*> staticScene, std::vector<sf::Drawable*> dynamicScene, sf::Sprite *pinguino, std::vector<sf::Texture*> textures, std::vector<sf::RectangleShape*> colliders);
void movePenguin(sf::Sprite *pinguino, sf::RenderWindow *window);
sf::Vector2f calcMovement(float lambda, sf::Sprite &pinguino);
void delay(int ms);
int calcIntersection(float mouseX, float mouseY, std::vector<sf::RectangleShape*> colliders, sf::CircleShape mouseBounds);
void changeAnimation(int animationIndex, sf::Sprite &pinguino, std::vector<sf::Texture> penguinTextures);
int selectAnimation(sf::Vector2<int> ClickPosition, sf::Sprite &pinguino, std::vector<sf::Texture*> penguinTextures);
#endif //CLUBPENGUIN_FUNCTIONS_H
