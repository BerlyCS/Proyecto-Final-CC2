#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "mapa.h"
#include "bomb.h"
#include "animation.h"

using namespace sf;
using namespace std;

class IPlayer{
    virtual void collisionBomb(Vector2f) = 0;
};

class Player : public IPlayer {
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
        SoundBuffer bombplace_b;
        Sound bombplace;
        SoundBuffer bombexplosion_b;
        Sound bombexplosion;

        Vector2f get_center_pos() {
            Vector2f size = collider.getSize();
            Vector2f pos = collider.getPosition();
            return Vector2f(pos.x + size.x/2, pos.y + size.y/2);
        }

    public:
        Player();
    //Devolver un Vector2f para obtener los valores de los puntos *sugerencia.....!!!!!!!!!
        void move(Vector2f movement);
        //para poder cambiar los controles
        virtual void controlar(Mapa_2&, RenderWindow& window, float& dt) = 0;
        void draw(RenderWindow& win);
        Sprite getSprite();
        void checkCollision(Mapa_2& map, Vector2f movement);
        RectangleShape getCollider();
        void collisionBomb(Vector2f) override;
};

class Player_one : public Player {

    public:
        Player_one(Mapa_2& mapa, int WIDTH, int HEIGHT);
        void joystockControl(Mapa_2 &map, RenderWindow& window, float& dt);
        void controlar(Mapa_2 &map, RenderWindow& window, float& dt);
};

class Player_two : public Player {
    public:
    Player_two(Mapa_2& mapa);
    void controlar(Mapa_2 &map, RenderWindow& window,float& dt);
};

