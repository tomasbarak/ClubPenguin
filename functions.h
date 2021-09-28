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
void eventHandler(sf::RenderWindow *window);
void movePenguin(sf::CircleShape *penguinSprite, sf::RenderWindow *window);
void calcMovement(float lambda, sf::CircleShape &pinguino);
#endif //CLUBPENGUIN_FUNCTIONS_H
