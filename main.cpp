#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>
#include<iostream>
#include "mapa.cpp"
#include "menu.cpp"
#include "animation.cpp"

//si encuentran una mejor implementacion pueden aplicarlo sobre lo
//que ya esta

using namespace sf;
using namespace std;

//WIP
void place_bomb(Vector2f coords) {

}

class Bomba {
    private:
        int power;
        Texture images[3];
        Sprite sprite;
        int type;
        Time time_placed;
        double x,y;
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
        Texture texture;
        ASprite down_frames, up_frames, left_frames, right_frames;
        Sprite sprite;
        Vector2f pos;
        double speed;
        int bombcount, bombpower, lives;
        bool isAlive;
        RectangleShape hitbox;
    public:
        Player() : down_frames(0.2f), up_frames(0.2f), left_frames(0.2f), right_frames(0.2f) {
            speed = 5.0f;
            bombcount = 1;
        }

        //para poder cambiar los controles
        virtual void controlar(float& dt) = 0;

        void draw(RenderWindow& win) {
            win.draw(sprite);
        }

};

class Player_one : public Player {
    public:
        Player_one(Mapa_2& mapa) : Player() {
            pos = mapa.get_coords(1, 1);
            sprite.setPosition(pos);

            sprite.setPosition(Vector2f(100,100));

            if (!(texture.loadFromFile("images/IMG_20240628_190401.png"))) {
                cout<<"No se pudo cargar las texturas del jugador 1"<<endl;
            }
            sprite.setTexture(texture);
            sprite.scale(Vector2f(4,4));
            down_frames.setRects(0, 0, 16, 24, 3);
            down_frames.addFrame(IntRect(16,0,16,24));
            up_frames.setRects(0, 24, 16, 24, 3);
            up_frames.addFrame(IntRect(16,24,16,24));
            left_frames.setRects(0, 48, 16, 24, 3);
            left_frames.addFrame(IntRect(16,48,16,24));
            right_frames.setRects(0, 72, 16, 24, 3);
            right_frames.addFrame(IntRect(16,72,16,24));

            down_frames.applyToSprite(sprite);
        }
        void controlar(float& dt)
        {
            down_frames.update(dt);
            up_frames.update(dt);
            left_frames.update(dt);
            right_frames.update(dt);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                sprite.move(0, -speed);
                up_frames.applyToSprite(sprite);
                /* sprite.setTexture(images[0]); */
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                sprite.move(0, speed);
                down_frames.applyToSprite(sprite);
                /* sprite.setTexture(images[2]); */
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                sprite.move(-speed, 0);
                left_frames.applyToSprite(sprite);
                /* sprite.setTexture(images[1]); */
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                sprite.move(speed, 0);
                right_frames.applyToSprite(sprite);
                /* sprite.setTexture(images[3]); */
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                place_bomb(pos);
            }
        }
};

/* class Player_two : public Player { */
/*     public: */
/*         Player_two() : Player() { */
/*             sprite.setPosition(Vector2f(100,100)); */
/*             if (!( */
/*                 images[0].loadFromFile("images/W1.png") && */
/*                 images[1].loadFromFile("images/A1.png") && */
/*                 images[2].loadFromFile("images/S1.png") && */
/*                 images[3].loadFromFile("images/D1.png") */ 
/*                )) { */
/*                 cout<<"No se pudo cargar las texturas del jugador 2"<<endl; */
/*             } */
/*         } */
/*         void controlar() */
/*         { */
/*             if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) */
/*             { */
/*                 sprite.move(0, -speed); */
/*                 sprite.setTexture(images[0]); */
/*             } */
/*             if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) */
/*             { */
/*                 sprite.move(0, speed); */
/*                 sprite.setTexture(images[2]); */
/*             } */
/*             if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) */
/*             { */
/*                 sprite.move(-speed, 0); */
/*                 sprite.setTexture(images[1]); */
/*             } */
/*             if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) */
/*             { */
/*                 sprite.move(speed, 0); */
/*                 sprite.setTexture(images[3]); */
/*             } */
/*             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { */
/*                 /1* place_bomb(Vector2i(x,y)); *1/ */
/*             } */
/*         } */
/* }; */

int main() {
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    Mapa_2 mapa(WIDTH, HEIGHT);
    Menu menu;
    mapa.Print();
    bool Game_started = false;
    Clock clock;

    Player_one player(mapa);
    /* Player_two player_dos; */

    while (window.isOpen()) {
        Event event;
        
        //eventos
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        if (!Game_started) {
            menu.handleEvent(window, Game_started);
            menu.draw(window);
            continue;
        }
        float dt = clock.restart().asSeconds();
        window.clear(Color::Black);
        player.controlar(dt);
        /* player_dos.controlar(); */
        mapa.draw(window);
        player.draw(window);
        /* player_dos.draw(window); */
        window.display();
    }
    return EXIT_SUCCESS;
}
