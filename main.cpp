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
        double speed;
        Vector2f position;
        int bombcount;
        RectangleShape collider;
    public:
        Player(){
            speed = 5.0f;
            bombcount = 1;
        }
//Devolver un Vector2f para obtener los valores de los puntos *sugerencia.....!!!!!!!!!
        void move(Vector2f movement){
            position += movement;
            sprite.setPosition(position);
            collider.setSize(Vector2f(60, 55));
            collider.setPosition(Vector2f(position.x, position.y+35));
            collider.setFillColor(Color::Red);
        }


        //para poder cambiar los controles
        virtual void controlar(Mapa_2) = 0;
        void draw(RenderWindow& win) {
            win.draw(sprite);
            win.draw(collider);
        }

        Sprite getSprite() {return sprite;}

        void checkCollision(Mapa_2& map, Vector2f movement){
            FloatRect playerBounds = collider.getGlobalBounds();
            for(int i=0; i<13; i++){
                for(int j=0; j<13; j++){
                    Block* block = map.getMatrizSprites()[i][j];
                    if(block && block->IsCollidable()){
                        FloatRect blockBounds = block->getSprite().getGlobalBounds();
                        if(playerBounds.intersects(blockBounds)){
                            move(-movement);
                            return;
                        }
                    }
                }
            }
        }
};

class player_one : public Player {
    public:
        player_one(Vector2f position) : Player() {
            this->position = position;
            if (!(
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               )) {
                cout<<"No se pudo cargar las texturas del jugador"<<endl;
            }
        }
        void controlar(Mapa_2 map)
        {
                Vector2f movement(0.0f, 0.0f);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    movement.y -= speed;
                    //sprite.move(0, -speed);
                    sprite.setTexture(images[0]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    movement.y += speed;
                    //sprite.move(0, speed);
                    sprite.setTexture(images[2]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    movement.x -= speed;
                    //sprite.move(-speed, 0);
                    sprite.setTexture(images[1]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                {
                    movement.x += speed;
                    //sprite.move(speed, 0);
                    sprite.setTexture(images[3]);
                }
                move(movement);
                checkCollision(map, movement);
            }
};

class Player_two : public Player {
    public:
        Player_two(Vector2f position) : Player() {
            this->position = position;
            if (
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               ) {
                cout<<"No se pudo cargar las texturas del jugador"<<endl;
            }
        }
        void controlar(Mapa_2 map)
        {
                Vector2f movement(0.0f, 0.0f);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    movement.y -= speed;
                    //sprite.move(0, -speed);
                    sprite.setTexture(images[0]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    movement.y += speed;
                    //sprite.move(0, speed);
                    sprite.setTexture(images[2]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    movement.x -= speed;
                    //sprite.move(-speed, 0);
                    sprite.setTexture(images[1]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
                {
                    movement.x += speed;
                    //sprite.move(speed, 0);
                    sprite.setTexture(images[3]);
                }
                move(movement);
                checkCollision(map, movement);
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

    Vector2f posPlayer1(WIDTH/13+10, HEIGHT/13-25);
    Vector2f posPlayer2(WIDTH/13*11+20, HEIGHT/13*11-15);

    //map.print_layout();
    player_one player(posPlayer1);
    Player_two player_dos(posPlayer2);

    while (window.isOpen()) {
        Event event;
        
        //Eventos
        while (window.pollEvent(event)) {
            //player.validadMovimiento(mapa.getMatriz());
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        window.clear(Color::Black);
        player.controlar(mapa);
        player_dos.controlar(mapa);
        mapa.draw(window);
        player.draw(window);
        player_dos.draw(window);
        window.display();
        //logica aqui
    }
    return EXIT_SUCCESS;
}
