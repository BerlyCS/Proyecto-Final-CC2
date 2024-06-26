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
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include "mapa.cpp"

//si encuentran un mejor algoritmo pueden borrarlo

using namespace sf;
using namespace std;

class Bomba {
    private:
        int power;
        Texture images[3];
        Sprite sprite;
        int type;
        Time time_placed;
        double x,y;
        friend class mapa;
    public:
        Bomba(int power, int type, double x, double y, Time time ) : x(x), y(y) {
            this->power = power;
            this->type = type;
            images[0].loadFromFile("images/bomb3.png");
            sprite.setTexture(images[0]);
            time_placed = time;
        }

        void draw(RenderWindow& window, Time actual_time) {
            Time seconds_passed = actual_time - time_placed;
            if (seconds_passed.asMilliseconds() > 3000 ) {
                
            } else {
                window.draw(sprite);
                return;
            }
        }
};

class Player {
    protected:
        Texture images[4];
        Sprite sprite;
        double x,y, speed;
        int bombcount;
    public:
        Player(){
            speed = 5.0f;
            bombcount = 1;
        }

        void manejarEvento(const sf::Event& evento)
        {
            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::Up)
                {
                    sprite.move(0, -5.0f);
                    sprite.setTexture(images[0]);
                }
                else if (evento.key.code == sf::Keyboard::Down)
                {
                    sprite.move(0, 5.0f);
                    sprite.setTexture(images[2]);                }
                else if (evento.key.code == sf::Keyboard::Left)
                {
                    sprite.move(-5.0f, 0);
                    sprite.setTexture(images[1]);                }
                else if (evento.key.code == sf::Keyboard::Right)
                {
                    sprite.move(5.0f, 0);
                    sprite.setTexture(images[3]);                }
            }
        }
        //para poder cambiar los controles
        virtual void controlar() = 0;
        void draw(RenderWindow& win) {
            win.draw(sprite);
        }

};

class player_one : public Player {
    public:
        player_one() : Player() {
            sprite.setPosition(Vector2f(100,100));
            if (
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               ) {
                cout<<"No se pudo cargar las texturas del jugador"<<endl;
            }
        }
        void controlar()
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
    //mapa map(WIDTH, HEIGHT);
    Mapa_2 mapa(WIDTH, HEIGHT);
    
    //map.print_layout();
    player_one player;

    while (window.isOpen()) {
        Event event;
        
        //Eventos
        while (window.pollEvent(event)) {
            player.manejarEvento(event);
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        mapa.draw(window);
        player.controlar();
        window.clear(Color::Black);
        player.draw(window);
        //window.clear(Color::Black);
        window.display();
        //logica aqui
    }
    return EXIT_SUCCESS;
}
