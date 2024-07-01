#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#include "mapa.cpp"

//si encuentran una mejor implementacion pueden aplicarlo sobre lo
//que ya esta

using namespace sf;
using namespace std;

void place_bomb(Vector2i coords) {

}

class Bomba {
    private:
        int power;
        Texture image;
        Sprite sprite;
        int type;
        Time time_placed;
        //double x,y;
        Vector2f position;
    public:
        Bomba(int power, int type,Vector2f position,Time time) : power(power), type(type), position(position), time_placed(time) {
            image.loadFromFile("images/bomb3.png");
            if(!image.loadFromFile("images/bomb3.png")){
                cout<<"No se pudo cargar la textura de la bomba"<<endl;
            }

            sprite.setTexture(image);
            sprite.setPosition(position);
        }

        void draw(RenderWindow& window, Time actual_time) {
            Time seconds_passed = actual_time - time_placed;
            if (seconds_passed.asMilliseconds() > 3000 ) {
                
            } else {
                window.draw(sprite);
                return;
            }
        }
        bool shouldExplode(Time actual_time){
            return (actual_time-time_placed).asMilliseconds()>3000;
        }
};

class Player {
    protected:
        Texture images[4];
        Sprite sprite;
        double x,y, speed;
        int bombcount;
        vector<Bomba> bombas;
    public:
        Player(){
            speed = 5.0f;
            bombcount = 1;
        }
        virtual void controlar(list<Bomba>& bombas, Clock& clock) = 0;
        //para poder cambiar los controles
        void draw(RenderWindow& window) {
            //for(auto& bomba:bombas){
            //    bomba.draw(win, actual_time);
            //}
            window.draw(sprite);
        }
        /*
        void place_bomb(Vector2i coords){
            if(bombcount>0){
                Bomba bomba(1,1,sprite.getPosition());
                bombas.push_back(bomba);
                bombcount--;
            }
        }
        void update_bombs(Time actual_time){
            bombas.erase(remove_if(bombas.begin(), bombas.end(),[actual_time](Bomba& bomba){
                return bomba.shouldExplode(actual_time);
            }), bombas.end());
        }*/
        Vector2f getPosition() const {
            return sprite.getPosition();
        }

        void setPosition(const Vector2f& position) {
            sprite.setPosition(position);
        }
};

class Player_one : public Player {
    public:
        Player_one() : Player() {
            sprite.setPosition(Vector2f(100,100));
            if (!(
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               )) {
                cout<<"No se pudo cargar las texturas del jugador 1"<<endl;
            }
        }
        void controlar(list<Bomba>& bombas, Clock& clock) override
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                bombas.emplace_back(1, 1, getPosition(), clock.getElapsedTime());
            }
        }
};

class Player_two : public Player {
    public:
        Player_two() : Player() {
            sprite.setPosition(Vector2f(100,100));
            if (!(
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               )) {
                cout<<"No se pudo cargar las texturas del jugador 2"<<endl;
            }
        }
        void controlar(list<Bomba>& bombas, Clock& clock) override
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
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    Mapa_2 mapa(WIDTH, HEIGHT);
    mapa.Print();

    Player_one player;
    Player_two player_dos;
    Clock clock;
    list<Bomba> bombas;

    while (window.isOpen()) {
        Event event;
        
        //eventos
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
    
        window.clear(Color::Black);
        player.controlar(bombas,clock);
        player_dos.controlar(bombas,clock);
        mapa.draw(window);
        player.draw(window);
        player_dos.draw(window);
        Time actual_time=clock.getElapsedTime();
        for (auto it=bombas.begin(); it != bombas.end();) {
            it->draw(window, actual_time);
            if(it->shouldExplode(actual_time)){
                it=bombas.erase(it);
            }else{
                ++it;
            }
        }
        window.display();

        //logica aqui
    }
    return EXIT_SUCCESS;
}
