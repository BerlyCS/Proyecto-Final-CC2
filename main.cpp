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

//si encuentran una mejor implementacion pueden aplicarlo sobre lo
//que ya esta

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

        //para poder cambiar los controles
        virtual void controlar() = 0;
        void draw(RenderWindow& win) {
            win.draw(sprite);
        }
/*
        void validadMovimiento(vector<vector<char>> matriz){
            int ejex, ejey = 0;
            int num = 1000/13;
            for(int i=0; i<13; i++){
                ejex = 0;
                for(int j=0; j<13; j++){
                    if(matriz[i][j] == '#'){
                        if (sprite.getGlobalBounds().getPosition().x > ejex) sprite.move(-0.9f,0);
                    }
                }
                ejex += num;
            }

            ejey += num;
        }
*/

        void colider(RenderWindow& win){
            RectangleShape colider(Vector2f(55, 55));
            colider.setPosition(Vector2f(sprite.getGlobalBounds().getPosition().x, sprite.getGlobalBounds().getPosition().y+30));
            colider.setFillColor(Color::Yellow);
            win.draw(colider);
        }
};

class player_one : public Player {
    public:
        player_one() : Player() {
            sprite.setPosition(Vector2f(100,100));
            if (!(
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               )) {
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

class Player_two : public Player {
    public:
        Player_two() : Player() {
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                sprite.move(0, -speed);
                sprite.setTexture(images[0]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                sprite.move(0, speed);
                sprite.setTexture(images[2]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                sprite.move(-speed, 0);
                sprite.setTexture(images[1]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                sprite.move(speed, 0);
                sprite.setTexture(images[3]);
            }
        }
};

int main() {
    //RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Bomberman");
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    //mapa map(WIDTH, HEIGHT);
    Mapa_2 mapa(WIDTH, HEIGHT);
    mapa.Print();

    //map.print_layout();
    player_one player;
    Player_two player_dos;

    while (window.isOpen()) {
        Event event;
        
        //Eventos
        while (window.pollEvent(event)) {
            //player.validadMovimiento(mapa.getMatriz());
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        window.clear(Color::Black);
        player.controlar();
        player_dos.controlar();
        mapa.draw(window);
        player.draw(window);
        player_dos.draw(window);
        player.colider(window);
        window.display();
        //logica aqui
    }
    return EXIT_SUCCESS;
}
