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


using namespace sf;
using namespace std;


class Player {
    protected:
        Texture texture;
        ASprite down_frames, up_frames, left_frames, right_frames;
        Sprite sprite;
        double speed;
        Vector2f position;
        RectangleShape collider;
        int bombcount, bombpower, lives;
        bool isAlive;
    public:
        Player() : down_frames(0.2f), up_frames(0.2f), left_frames(0.2f), right_frames(0.2f) {
            speed = 5.0f;
            bombcount = 1;
        }
    //Devolver un Vector2f para obtener los valores de los puntos *sugerencia.....!!!!!!!!!
        void move(Vector2f movement){
            position += movement;
            sprite.setPosition(position);
            collider.setPosition(Vector2f(position.x, position.y + sprite.getGlobalBounds().height*0.45));
            collider.setFillColor(Color::Red);
        }


        //para poder cambiar los controles
        virtual void controlar(Mapa_2&, float&) = 0;

        void draw(RenderWindow& win) {
            win.draw(sprite);
            /* win.draw(collider); */
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

class Player_one : public Player {
    public:

        Player_one(Mapa_2& mapa) : Player() {
            position = mapa.get_coords(1, 1);
            int blockSize = mapa.getBlockSize();

            if (!(texture.loadFromFile("images/player_one.png"))) {
                cout<<"no se cargo";
            }

            sprite.setTexture(texture);
            auto size = sprite.getGlobalBounds();
            Vector2f newsize = Vector2f(blockSize/16.f, blockSize/16.f);
            /* cout<<newsize.x<<' '<<newsize.y<<endl; */
            sprite.scale(newsize);
            sprite.setPosition(Vector2f(position.x, position.y-position.x*(2.f/3.f)));

            down_frames.setRects(0, 0, 16, 24, 3);
            down_frames.addFrame(IntRect(16,0,16,24));
            up_frames.setRects(0, 24, 16, 24, 3);
            up_frames.addFrame(IntRect(16,24,16,24));
            left_frames.setRects(0, 48, 16, 24, 3);
            left_frames.addFrame(IntRect(16,48,16,24));
            right_frames.setRects(0, 72, 16, 24, 3);
            right_frames.addFrame(IntRect(16,72,16,24));
            down_frames.applyToSprite(sprite);

            collider.setSize(Vector2f(blockSize-blockSize*0.15, blockSize- blockSize*0.15));
        }
        void controlar(Mapa_2 &map, float& dt)
        {
                down_frames.update(dt);
                up_frames.update(dt);
                left_frames.update(dt);
                right_frames.update(dt);
                Vector2f movement;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    movement.y -= speed;
                    up_frames.applyToSprite(sprite);
                    //sprite.move(0, -speed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    movement.y += speed;
                    down_frames.applyToSprite(sprite);
                    //sprite.move(0, speed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    movement.x -= speed;
                    left_frames.applyToSprite(sprite);
                    //sprite.move(-speed, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                {
                    movement.x += speed;
                    right_frames.applyToSprite(sprite);
                    //sprite.move(speed, 0);
                }
                move(movement);
                checkCollision(map, movement);
                /* cout<<sprite.getPosition().x<<' '<<sprite.getPosition().y<<endl; */
                auto pos_mat = map.get_mat_coords(Vector2f(collider.getPosition()));
                /* cout<<pos_mat.x<<' '<<pos_mat.y<<endl; */
            }
};

class Player_two : public Player {
    public:

        Player_two(Mapa_2& mapa) : Player() {
            position = mapa.get_coords(11, 10);
            int blockSize = mapa.getBlockSize();

            if (!(texture.loadFromFile("images/player2.png"))) {
                cout<<"no se cargo";
            }

            sprite.setTexture(texture);
            auto size = sprite.getGlobalBounds();
            Vector2f newsize = Vector2f(blockSize/16.f, blockSize/16.f);
            /* cout<<newsize.x<<' '<<newsize.y<<endl; */
            sprite.scale(newsize);
            sprite.setPosition(Vector2f(position.x, position.y-position.x*(2.f/3.f)));

            int size_x = 18, size_y=32;
            down_frames.setRects(0, 0, size_x, size_y, 3);
            down_frames.addFrame(IntRect(18,0,18,32));
            up_frames.setRects(0, 32, size_x, size_y, 3);
            up_frames.addFrame(IntRect(18,32,size_x,size_y));
            left_frames.setRects(0, 64, size_x, size_y, 3);
            left_frames.addFrame(IntRect(18,64,size_x,size_y));
            right_frames.setRects(0, 96, size_x, size_y, 3);
            right_frames.addFrame(IntRect(18,96,size_x,size_y));
            down_frames.applyToSprite(sprite);

            collider.setSize(Vector2f(blockSize-blockSize*0.15, blockSize- blockSize*0.15));
        }
        void controlar(Mapa_2 &map, float& dt)
        {
                down_frames.update(dt);
                up_frames.update(dt);
                left_frames.update(dt);
                right_frames.update(dt);
                Vector2f movement;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    movement.y -= speed;
                    up_frames.applyToSprite(sprite);
                    //sprite.move(0, -speed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    movement.y += speed;
                    down_frames.applyToSprite(sprite);
                    //sprite.move(0, speed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    movement.x -= speed;
                    left_frames.applyToSprite(sprite);
                    //sprite.move(-speed, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
                {
                    movement.x += speed;
                    right_frames.applyToSprite(sprite);
                    //sprite.move(speed, 0);
                }
                move(movement);
                checkCollision(map, movement);
                /* cout<<sprite.getPosition().x<<' '<<sprite.getPosition().y<<endl; */
                auto pos_mat = map.get_mat_coords(Vector2f(collider.getPosition()));
                /* cout<<pos_mat.x<<' '<<pos_mat.y<<endl; */
            }
};

int main() {
    //RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    RenderWindow window(VideoMode(700, 700), "Bomberman");
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;

    Mapa_2 mapa(WIDTH, HEIGHT, 4);
    mapa.Print();

    Menu menu;

    bool Game_started = true;

    Clock clock;

    Player_one player(mapa);
    Player_two player2(mapa);

    while (window.isOpen()) {
        Event event;
        
        //eventos
        while (window.pollEvent(event)) {
            //player.validadMovimiento(mapa.getMatriz());
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
        player.controlar(mapa, dt);
        /* player_dos.controlar(mapa); */
        /* player_dos.controlar(); */
        mapa.draw(window);
        player.draw(window);
        player2.draw(window);
        player2.controlar(mapa, dt);
        /* player_dos.draw(window); */
        window.display();
    }
    return EXIT_SUCCESS;
}
