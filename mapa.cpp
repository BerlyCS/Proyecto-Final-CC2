#pragma once
#include "animation.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <vector>


using namespace sf;
using namespace std;

class Block{
    protected:
        Sprite sprite;
        float sizeBlock;
    public:
        Block(int WIDTH, int HEIGHT){
            int x = WIDTH;
            int y = HEIGHT;
            int min = x > y ? y : x;
            sizeBlock = (float(min) / 13);
        }


        Sprite& getSprite(){
            return sprite;
        }

        void setSprite(Sprite& sprite) {
            this->sprite = sprite;
        }

        void draw(RenderWindow& window){
            window.draw(sprite);
            //window.draw(collider);
        }

        float getBlockSize() {return sizeBlock; }

        virtual bool IsCollidable() = 0;
};

class Wall : public Block{
    public:
        Wall(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){
        }

        bool IsCollidable() {return true;}
};

class WeakWall : public Block{
    public:
        WeakWall(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){
        }

        bool IsCollidable() {return true;}
};

class Tile : public Block{
    public:
        Tile(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){
        }

        bool IsCollidable() {return false;}
};

class Mapa_2 {
private:
    Texture texture;
    float sizeBlock;
    vector< vector<Block*>> sprites_map;
    vector< vector<char>> matriz;

public:
    Mapa_2(int WIDTH, int HEIGHT, int map_style=0) {
        texture.loadFromFile("images/wall_textur.png");
        IntRect frames[3];

        //
        for(int i =0 ; i<3 ; i++) {
            frames[2] = IntRect(0,16*map_style,16,16);
            frames[1] = IntRect(16,16*map_style,16,16);
            frames[0] = IntRect(32,16*map_style,16,16);
        }

        int x = WIDTH;
        int y = HEIGHT;
        int min = x > y ? y : x;
        sizeBlock = (float(min) / 13);
        cout<<"sizeBlock: "<<sizeBlock<<endl;

        matriz = vector<vector<char>>(13, vector<char>(13, ' '));
        generarMatriz();
        // Inicializar sprites_map y matriz
        for (int i = 0; i < 13; i++) {
            vector<Block*> filaSprites;
            for (int j = 0; j < 13; j++) {
                Block* bloque;
                Sprite sprite;
                sprite.setTexture(texture);
                if (matriz[i][j] == '#') {
                    bloque = new Wall(WIDTH, HEIGHT);
                    sprite.setTextureRect(frames[0]);
                } else if (matriz[i][j] == 'x') {
                    bloque = new WeakWall(WIDTH, HEIGHT);
                    sprite.setTextureRect(frames[1]);
                } else {
                    bloque = new Tile(WIDTH, HEIGHT);
                    sprite.setTextureRect(frames[2]);
                }
                auto size = frames[0].getSize();
                bloque->setSprite(sprite);
                bloque->getSprite().setScale(sizeBlock/size.x, sizeBlock/size.y);
                bloque->getSprite().setPosition(sizeBlock * j, sizeBlock * i);
                filaSprites.push_back(bloque);
            }
            sprites_map.push_back(filaSprites);
        }
    }

    /* Toma una coordenada del mapa y retorna la posicion en pantalla*/
    Vector2f get_coords(int x, int y) {
        cout<<x*sizeBlock<<' '<<y*sizeBlock<<endl;
        return Vector2f(x*sizeBlock,y*sizeBlock);
    }

    /*Toma una coordenada de pantalla y retorna la posicion en la matriz*/
    Vector2f get_coords(Vector2f pos) {
        return Vector2f(pos.x/sizeBlock, pos.y/sizeBlock);
    }

    void generarMatriz() {
        srand(time(NULL));
        for (int j = 0; j < 13; j++) {
            for (int k = 0; k < 13; k++) {
                if (j == 0 || k == 0 || j == 12 || k == 12) {
                    matriz[j][k] = '#';  // Asignar '#' a la matriz en los bordes
                } else {
                    if (j % 2 == 0 && k % 2 == 0) {
                        matriz[j][k] = '#';  // Asignar '#' a la matriz en posiciones pares
                    } else {
                        if((j<=2 && k<=2) || (j>=10 && k>=10)){
                            matriz[j][k] = ' ';
                            continue;
                        }
                        int aux = rand() % 6;
                        if (aux == 0) {
                            matriz[j][k] = ' ';
                        } else {
                            matriz[j][k] = 'x';
                        }
                    }
                }
            }
        }
    }

    void Print() const {
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                std::cout << matriz[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void draw(RenderWindow& window) {
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                sprites_map[i][j]->draw(window);
            }
        }
    }

    vector<vector<char>> getMatriz(){
        return matriz;
    }

    vector<vector<Block*>> getMatrizSprites(){
        return sprites_map;
    }

    int getBlockSize() {
        return sizeBlock;
    }
};
