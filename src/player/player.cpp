#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

using namespace std;

class player {
    private:
        sf::Sprite  sprites[12];
        double x,y;

    public:
        player(/*use builder desing patern to specify the player sprite */);
        void move();

};

int main() {

}
