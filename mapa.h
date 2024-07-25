#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>
#include <queue>
#include <vector>
#include <iostream>
#include <ctime>
#include <vector>
#include "animation.h"


using namespace sf;
using namespace std;

class Bomb;

class Block{
    protected:
        Sprite sprite;
        float sizeBlock;
    public:
        Block(int WIDTH, int HEIGHT);
        Sprite& getSprite();
        void setSprite(Sprite& sprite);
        void draw(RenderWindow& window);
        float getBlockSize();
        virtual bool IsCollidable() = 0;
        virtual bool IsBreakable() = 0;
        virtual ~Block() = default;
};

class Wall : public Block{
    public:
        Wall(int WIDTH, int HEIGHT);
        bool IsCollidable();
        bool IsBreakable();
        ~Wall() = default;
};

class WeakWall : public Block{
    public:
        WeakWall(int WIDTH, int HEIGHT);
        bool IsCollidable();
        bool IsBreakable();
        ~WeakWall() = default;
};

class Tile : public Block{
    public:
        Tile(int WIDTH, int HEIGHT);
        bool IsCollidable();
        bool IsBreakable();
        ~Tile() = default;
};

class FireTile {
private:
    Sprite fireSprite;
    static Texture fireTexture;
    Clock timer;
    float duration;
public:
    FireTile(Vector2f&, int, float); 
    bool isExpired() const;
    void draw(RenderWindow& window);
};

class Mapa_2 {
private:
    Texture texture;
    float sizeBlock;
    vector< vector<Block*>> sprites_map;
    vector< vector<char>> matriz;
    queue<Bomb*> bombsEvents;
    Vector2i screen_size;
    int map_style;
    vector<FireTile> fire;

public:
    Mapa_2(int WIDTH, int HEIGHT, int map_style=0);
    void to_tile_at(Vector2i index);
    Vector2i get_screen_size() const;
    Vector2f get_coords(Vector2i pos) const;
    Vector2i get_mat_coords(Vector2f pos);
    Block*& get_block_at(int x, int y);
    int get_map_style();
    void generarMatriz();
    void Print() const;
    void draw(RenderWindow& window);
    vector<vector<char>> getMatriz();
    vector<vector<Block*>> getMatrizSprites();
    int getBlockSize();
    void insertFire(Vector2i pos, int dir);
};

