#include <SFML/Graphics.hpp>
#include "animation.cpp"
using namespace sf; 

class Bomba {
    private:
        int power;
        Texture images;
        Sprite sprite;
        int type;
        Time time_placed;
        double x,y;
        ASprite frames;
    public:
        Bomba(int power, int type, double x, double y, Time time ) : x(x), y(y), frames(0.2f) {
            this->power = power;
            this->type = type;
            images.loadFromFile("images/bomb3.png");
            sprite.setTexture(images);
            frames.setRects(0, 0, 16, 16, 3);
            frames.applyToSprite(sprite);
            time_placed = time;
        }

        void draw(RenderWindow& window, float dt) {
            frames.update(dt);
            frames.applyToSprite(sprite);
            window.draw(sprite);
        }
};
