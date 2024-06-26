#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

class Bomba {
    private:
        int power;
        sf::Texture images[3];
        sf::Sprite sprite;
        int type;
        sf::Clock clock;
        double x,y;
        void explode() {
            
        }
    public:
        Bomba(int power, int type, double x, double y) : x(x), y(y) {
            this->power = power;
            this->type = type;
            images[0].loadFromFile("images/bomb3.png");
        }

        void tick() {
            if (clock.getElapsedTime().asSeconds() > 3) {
                delete this;
            }
        }
};
