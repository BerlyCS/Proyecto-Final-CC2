#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iostream>
#include <ctime>
#include <vector>


using namespace sf;
using namespace std;

class Block {
    private:
        Texture texture;
        Sprite sprite;
        float sizeBlock;
        friend class Wall;
        friend class WeakWall;
        friend class Yard;
    public:
        Block(int WIDTH, int HEIGHT){
            int x = WIDTH;
            int y = HEIGHT;
            int min = x > y ? y : x;
            sizeBlock = (float(min) / 13);
        }

        Texture& getTexture(){
            return texture;
        }

        Sprite& getSprite(){
            return sprite;
        }

        void dibujar(RenderWindow& window){
            window.draw(sprite);
        }
};

class Wall : public Block {
    public:
        Wall(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){
            texture.loadFromFile("images/wall_1.png");
            sprite.setTexture(texture);
        }
};

class WeakWall : public Block {
    public:
        WeakWall(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){
            texture.loadFromFile("images/weak_wall_1.png");
            sprite.setTexture(texture);
        }
};

class Yard : public Block {
    public:
        Yard(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){
            texture.loadFromFile("images/tile_1.png");
            sprite.setTexture(texture);
        }
};

class Mapa_2 {
private:
    Texture wallTexture;
    Texture weakWall, tileText;
    float sizeBlock;
    vector< vector<Block*>> sprites_map;
    vector< vector<char>> matriz;

public:
    Mapa_2(int WIDTH, int HEIGHT) {
        wallTexture.loadFromFile("images/wall_1.png");
        weakWall.loadFromFile("images/weak_wall_1.png");
        tileText.loadFromFile("images/tile_1.png");

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
                
                if (matriz[i][j] == '#') {
                    bloque = new Wall(WIDTH, HEIGHT);
                } else if (matriz[i][j] == 'x') {
                    bloque = new WeakWall(WIDTH, HEIGHT);
                    //sprite.setTexture(weakWall);
                } else {
                    bloque = new Yard(WIDTH, HEIGHT);
                    //sprite.setTexture(tileText);
                }
                auto size = bloque->getTexture().getSize();
                bloque->getSprite().setScale(sizeBlock/size.x, sizeBlock/size.y);
                bloque->getSprite().setPosition(sizeBlock * j, sizeBlock * i);
                filaSprites.push_back(bloque);
            }
            sprites_map.push_back(filaSprites);
        }
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
                sprites_map[i][j]->dibujar(window);
            }
        }
    }

    vector<vector<char>> getMatriz(){
        return matriz;
    }
};
