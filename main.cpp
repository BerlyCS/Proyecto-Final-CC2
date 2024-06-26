#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>
#include "mapa.cpp"
#include "bomb.cpp"

using namespace sf;
using namespace std;

class Player {
    protected:
        Texture images[4];
        Sprite sprite;
        double x, y, speed;
        int bombcount, fire_upgrade;
        friend class powerup;
    public:
        Player() {
            speed = 5.0f;
            bombcount = 1;
            fire_upgrade = 3;
        }

        //para poder cambiar los controles
        virtual void manejarEvento() = 0;
        void draw(RenderWindow& win) {
            win.draw(sprite);
        }

};

class Player_one : public Player {
    public:
        Player_one() : Player() {
            sprite.setPosition(Vector2f(100,100));
            images[0].loadFromFile("images/Character_W_4.png");
            images[1].loadFromFile("images/Character_A_4.png");
            images[2].loadFromFile("images/Character_S_4.png");
            images[3].loadFromFile("images/Character_D_4.png");
        }
        void manejarEvento()
       {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                sprite.move(0, -speed);
                sprite.setTexture(images[0]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                sprite.move(0, speed);
                sprite.setTexture(images[2]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                sprite.move(-speed, 0);
                sprite.setTexture(images[1]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                sprite.move(speed, 0);
                sprite.setTexture(images[3]);
            }
        }
};

int main() {

    RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    mapa map(WIDTH, HEIGHT);
    map.print_layout();
    Player_one player;

    /* Font font; */
    /* if (!font.loadFromFile("pixelated.ttf")) { */

    /*     return EXIT_FAILURE; */
    /* } */

    while (window.isOpen()) {
        Event event;
        //Eventos
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();            
            
        }
        player.manejarEvento();
        window.clear(Color::Black);
        player.draw(window);
        /* map.draw(window); */
        window.display();
        //logica aqui
    }
    return EXIT_SUCCESS;
}
