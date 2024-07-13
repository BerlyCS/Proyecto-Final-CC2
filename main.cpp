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
#include <cmath>
#include <tuple>
#include "mapa.cpp"
#include "menu.cpp"
#include "animation.cpp"

//si encuentran una mejor implementacion pueden aplicarlo sobre lo
//que ya esta

using namespace sf;
using namespace std;

class Bomb{
    private:
        RectangleShape bomb;
        Sprite sprite;
        Texture texture;
        ASprite frames;
        Vector2f position;
        Clock lifeTimer;
        bool alive;
        int radius;
    public:
        Bomb(Mapa_2& mapa, Vector2f position, int radius = 1) : frames(0.1f){
            texture.loadFromFile("images/IMG_20240627_120859.png");

            //se establece el tamaño de la bomba al tamaño de un bloque del mapa
            bomb.setSize(Vector2f(mapa.getBlockSize(), mapa.getBlockSize()));
            bomb.setPosition(position);
            bomb.setFillColor(Color::Red);

            this->position = position;
            alive = true;
            lifeTimer.restart();

            sprite.setTexture(texture);
            sprite.setScale(Vector2f(mapa.getBlockSize()/16.f, mapa.getBlockSize()/16.f));
            sprite.setPosition(position);
            frames.setRects(0, 0, 16, 16, 3);
            frames.addFrame(IntRect(16,0,16,16));
            frames.applyToSprite(sprite);

            this->radius = radius; //radius 1
        }

        bool isAlive() const {
            return alive;
        }

        void update(float dt) {
            frames.update(dt);
            if (lifeTimer.getElapsedTime().asSeconds() >= 2.0) {
                alive = false;
            }
        }

        void draw(RenderWindow& window) {
            if (alive) {
                frames.applyToSprite(sprite);
                window.draw(bomb);
                window.draw(sprite);
            }
        }

        Vector2f getPosition() const {
            auto size = bomb.getSize();
            auto pos = bomb.getPosition();
            Vector2f center_pos = Vector2f(pos.x+size.x/2, pos.y+size.y/2);
            return center_pos;
        }

        void destroy(Mapa_2 &map, Vector2i matrizIndex) {
            for (int i = 1; i<=radius; i++) {
                //up tiles
                if ( matrizIndex.y - i >= 0 ) {
                    if ( map.get_block_at(matrizIndex.x, matrizIndex.y - i)->IsBreakable() ) {
                        delete map.get_block_at(matrizIndex.x, matrizIndex.y + i);
                        map.get_block_at(matrizIndex.x, matrizIndex.y - i) = new Tile(map.get_screen_size().x, map.get_screen_size().y);
                        
                    }
                }
                //down tiles
                if ( matrizIndex.y + i <= 13 ) {
                    if ( map.get_block_at(matrizIndex.x, matrizIndex.y + i)->IsBreakable() ) {
                        delete map.get_block_at(matrizIndex.x, matrizIndex.y + i);
                        map.get_block_at(matrizIndex.x, matrizIndex.y + i) = new Tile(map.get_screen_size().x, map.get_screen_size().y);
                    }
                }
                //left tiles
                if ( matrizIndex.x - i >= 0 ) {
                    if ( map.get_block_at(matrizIndex.x - i, matrizIndex.y)->IsBreakable() ) {
                        delete map.get_block_at(matrizIndex.x, matrizIndex.y + i);
                        map.get_block_at(matrizIndex.x - i, matrizIndex.y + i) = new Tile(map.get_screen_size().x, map.get_screen_size().y);
                    }
                }
                //right tiles
                if ( matrizIndex.x + i <= 13 ) {
                    if ( map.get_block_at(matrizIndex.x + i, matrizIndex.y)->IsBreakable() ) {
                        delete map.get_block_at(matrizIndex.x, matrizIndex.y + i);
                        map.get_block_at(matrizIndex.x + i, matrizIndex.y + i) = new Tile(map.get_screen_size().x, map.get_screen_size().y);
                    }
                }
            }
           /* if(map.getMatrizSprites()[matrizIndex.x-1][matrizIndex.y]->IsCollidable()){
                cout<<"->"<<endl;
                delete map.getMatrizSprites()[matrizIndex.x+1][matrizIndex.y];
                map.getMatrizSprites()[matrizIndex.x+1][matrizIndex.y] = new Tile(map.get_screen_size().x, map.get_screen_size().y);
            }*/
            
        }
};

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
        bool isBomb;
        vector<Bomb> bombs;

        Vector2f get_center_pos() {
            Vector2f size = collider.getSize();
            Vector2f pos = collider.getPosition();
            return Vector2f(pos.x + size.x/2, pos.y + size.y/2);
        }

    public:
        Player() : down_frames(0.2f), up_frames(0.2f), left_frames(0.2f), right_frames(0.2f), isBomb(false) {
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
        virtual void controlar(Mapa_2&, RenderWindow& window, float& dt) = 0;

        void draw(RenderWindow& win) {
            win.draw(sprite);
            /* win.draw(collider); */
        }

        Sprite getSprite() {return sprite;}

        void checkCollision(Mapa_2& map, Vector2f movement){
            FloatRect playerBounds = collider.getGlobalBounds();
            for(int i=0; i<13; i++){
                for(int j=0; j<13; j++){
                    Block* block = map.get_block_at(i, j);
                    if(block!=nullptr){
                        if (block->IsCollidable()) {
                        FloatRect blockBounds = block->getSprite().getGlobalBounds();
                        if(playerBounds.intersects(blockBounds)){
                            move(-movement);
                            return;
                            }
                        }
                    }
                }
            }
        }
};

class Player_one : public Player {

    public:
        Player_one(Mapa_2& mapa, int WIDTH, int HEIGHT){
            position = mapa.get_coords(Vector2i(1,1));
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
        void controlar(Mapa_2 &map, RenderWindow& window, float& dt)
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
                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    if (isBomb == false) { // Cooldown de 0.5 segundos entre bombas

                        Vector2i matrizIndex = map.get_mat_coords(get_center_pos());
                        /* cout<<get_center_pos().x<<' '<<get_center_pos().y<<endl; */
                        /* cout<<matrizIndex.x<<' '<<matrizIndex.y<<endl; */
                        Vector2f bombPosition = map.get_coords(matrizIndex);
                        cout<<"Bomb pos: "<<bombPosition.x<<", "<<bombPosition.y<<endl;
                        Bomb newBomb(map, bombPosition);
                        newBomb.destroy(map, map.get_mat_coords(position));
                        bombs.push_back(newBomb);
                        isBomb = true;
                    }
                }

                for (auto& bomb : bombs) {
                    bomb.update(dt);
                }
                move(movement);
                checkCollision(map, movement);
                /* cout<<sprite.getPosition().x<<' '<<sprite.getPosition().y<<endl; */

                for (auto it = bombs.begin(); it != bombs.end();) {
                    if (!it->isAlive()) {
                        it = bombs.erase(it);
                        isBomb = false;
                    } else {
                        it->draw(window);
                        ++it;
                    }
                }
                auto pos_mat = map.get_mat_coords(Vector2f(collider.getPosition()));
                /* cout<<pos_mat.x<<' '<<pos_mat.y<<endl; */
            }
        
};



int main() {
    //RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Bomberman");
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    Mapa_2 mapa(WIDTH, HEIGHT, 4);
    Menu menu;
    mapa.Print();
    bool Game_started = true;
    Clock clock;

    Player_one player(mapa, WIDTH, HEIGHT);

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
        mapa.draw(window);
        player.controlar(mapa, window, dt);
        /* player_dos.controlar(mapa); */
        /* player_dos.controlar(); */
        player.draw(window);
        /* player_dos.draw(window); */
        window.display();
    }
    return EXIT_SUCCESS;
}
