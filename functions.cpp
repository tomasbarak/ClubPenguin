#include "functions.h"

sf::Vector2f click;
float pos_x= 0;
float pos_y = 0;
std::vector<sf::Vector2f> posMov;

void setBG(sf::Sprite *backgroundSprite, sf::Texture *backgroundTexture){
    backgroundSprite->setTexture(*backgroundTexture);
    backgroundSprite->scale(0.25f, 0.25f);
}

void drawObjects(sf::Drawable *objectToDraw, sf::RenderWindow *window){
    window->draw(*objectToDraw);
}
void drawScene(std::vector<sf::Drawable*> drawObjectList, sf::RenderWindow *window){

}
int calcIntersection(float mouseX, float mouseY, std::vector<sf::RectangleShape*> colliders, sf::CircleShape mouseBounds){
    //1 Skybox
    for(int i = 0; i < colliders.size(); i++){
        if(mouseBounds.getGlobalBounds().intersects(colliders[i]->getGlobalBounds())){
            std::cout << "1";
            return 1;
        }
    }

    return 0;
}
void eventHandler(sf::RenderWindow *window, std::vector<sf::Drawable*> staticScene, std::vector<sf::Drawable*> dynamicScene, sf::Sprite *pinguino, std::vector<sf::Texture*> textures, std::vector<sf::RectangleShape*> colliders){
    sf::Event event;
    while (window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            exit(0);
        }else if(event.type == sf::Event::MouseButtonPressed){
            posMov.clear();
            if(event.mouseButton.button == sf::Mouse::Left){
                selectAnimation(sf::Vector2<int>(event.mouseButton.x, event.mouseButton.y), *pinguino, textures);
                sf::CircleShape mouseCircle(25);
                mouseCircle.setOrigin(mouseCircle.getLocalBounds().width/2, mouseCircle.getLocalBounds().height/2 );
                mouseCircle.setPosition(event.mouseButton.x, event.mouseButton.y);
                int boxIntersected;
                boxIntersected = calcIntersection(event.mouseButton.x, event.mouseButton.y, colliders, mouseCircle);
                if(boxIntersected != 1) {
                    for (int i = 1; i < 101; i += 1) {
                        click.x = event.mouseButton.x;
                        click.y = event.mouseButton.y;
                        posMov.push_back(calcMovement((float) i / 100, *pinguino));
                    }
                }
            }
        }
    }
}

void movePenguin(sf::Sprite *pinguino, sf::RenderWindow *window){
    if(posMov.size() > 0){
        pinguino->setPosition(posMov[0]);
        posMov.erase(posMov.begin());
        delay(10);
    }
}
sf::Vector2f calcMovement(float lambda, sf::Sprite &pinguino){
    sf::Vector2f aux2 = click - pinguino.getPosition();
    sf::Vector2f aux3 = aux2*lambda;
    sf::Vector2f aux =aux3+pinguino.getPosition();
    //pinguino.setPosition(aux);
    return aux;
}
void delay(int ms){
    sf::Clock clock;
    int inicio = clock.getElapsedTime().asMilliseconds();
    while(clock.getElapsedTime().asMilliseconds() < inicio + ms);
}
void changeAnimation(int animationIndex, sf::Sprite &pinguino, std::vector<sf::Texture*> penguinTextures){
    pinguino.setTexture(*penguinTextures[animationIndex]);
}
int selectAnimation(sf::Vector2<int> ClickPosition, sf::Sprite &pinguino, std::vector<sf::Texture*> penguinTextures){
    sf::Vector2<float> penguinPosition = pinguino.getPosition();
    if(ClickPosition.y < (penguinPosition.y + pinguino.getLocalBounds().height) && ClickPosition.y > (penguinPosition.y - pinguino.getLocalBounds().height)){
        if(ClickPosition.x > penguinPosition.x)changeAnimation(6, pinguino, penguinTextures);
        else if(ClickPosition.x < penguinPosition.x) changeAnimation(7, pinguino, penguinTextures);
    }
    else if(ClickPosition.y > penguinPosition.y){
        if(ClickPosition.x > (penguinPosition.x + pinguino.getLocalBounds().width)) changeAnimation(4, pinguino, penguinTextures);
        else if(ClickPosition.x < (penguinPosition.x - pinguino.getLocalBounds().width)) changeAnimation(5, pinguino, penguinTextures);
        else changeAnimation(0, pinguino, penguinTextures);
    }
    else if(ClickPosition.y < penguinPosition.y) {
        if (ClickPosition.x > (penguinPosition.x + pinguino.getLocalBounds().width))
            changeAnimation(2, pinguino, penguinTextures);
        else if (ClickPosition.x < (penguinPosition.x - pinguino.getLocalBounds().width))
            changeAnimation(3, pinguino, penguinTextures);
        else changeAnimation(1, pinguino, penguinTextures);

    }
    else{
        changeAnimation(0, pinguino, penguinTextures);
    }
}