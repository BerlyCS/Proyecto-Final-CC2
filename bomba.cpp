#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "animation.cpp"
using namespace sf; 

class Bomba {
    private:
        int power;
        Texture images;
        Sprite sprite;
        int type;
        Time time_placed;
        ASprite frames;
        bool exploded;
    public:
        Bomba(int power, int type, Vector2f position, Time time ) : frames(0.2f), exploded(false) {
            this->power = power;
            this->type = type;
            images.loadFromFile("ejemplos/bomb.png");
            sprite.setTexture(images);
            frames.setRects(0, 0, 23, 23, 3);
            frames.applyToSprite(sprite);
            //sprite.setPosition(std::floor(position.x / 20) * 20,std:: floor(position.y / 20) * 20);
            time_placed = time;
        }

        void draw(RenderWindow& window, float dt) {
            if(!exploded){
                //frames.setRects(0,0,16,16,1);
                frames.applyToSprite(sprite);
                window.draw(sprite);
            }
        }
        bool shouldExplode(Time actual_time){
            return (actual_time-time_placed).asMilliseconds()>3000;
        }
        void explode(){
            exploded=true;
        }
        bool isExploded() const{
            return exploded;
        }
        FloatRect getBounds() const{
            return sprite.getGlobalBounds();
        }
        Vector2f getPosition() const{
            return sprite.getPosition();
        }
};
