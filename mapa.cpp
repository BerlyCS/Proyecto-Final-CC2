#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "bomb.cpp"
#include <iostream>
#include <ctime>
#include <vector>

using namespace sf;
using namespace std;

class mapa {
    private:
        char** grid;
        Sprite wall;
        int block_size;
        Texture wall_img;
        std::vector<Bomba*> list;
    public:
        mapa(int WIDTH, int HEIGHT) {
            grid = new char*[13];
            for (int i=0; i<13;i++) {
                grid[i] = new char[13];
                for (int j=0; j<13; j++)
                    grid[i][j] = ' ';
            }
private:
    char** grid;
    Sprite wall;
    int block_size;
    Texture wall_img;

public:
    mapa(int WIDTH, int HEIGHT) {
        grid = new char*[13];
        for (int i = 0; i < 13; i++) {
            grid[i] = new char[13];
            for (int j = 0; j < 13; j++)
                grid[i][j] = ' ';
        }

        for (int i = 0; i < 13; i++) {
            grid[i][0] = '#';
            grid[0][i] = '#';
            grid[12][i] = '#';
            grid[i][12] = '#';
        }
        for (int i = 2; i < 11; i += 2) {
            for (int j = 2; j < 11; j += 2) {
                grid[i][j] = '#';
            }
        }

        int x = WIDTH;
        int y = HEIGHT;
        int max = x < y ? y : x;
        block_size = max / 13;
        
        if (!wall_img.loadFromFile("images/wall.png")) {
            std::cerr << "Error cargando la textura: images/wall.png" << std::endl;
            // Manejar el error apropiadamente, por ejemplo, cargar una textura alternativa
        }

        wall.setTexture(wall_img);
        auto size = wall.getTexture()->getSize();
        wall.scale(float(block_size) / size.x, float(block_size) / size.y);
        wall.setPosition(Vector2f(210, 3));
    }

    ~mapa() {
        for (int i = 0; i < 13; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

        void print_layout() const {
            for (int i=0; i<13; i++) {
                for (int j=0; j<13; j++) {
                    cout<<grid[i][j]<< ' ';
                }
                cout<<endl;
            }
        }

        void add_bomb(int power, int type, int x, int y) {

        }
        
        //el mapa actualizara, funcionara como observer de los eventos que destruyen las paredes
        void update_map(RenderWindow& window) {
            window.draw(wall);
                    
        }
        
};



    void print_layout() const {
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                std::cout << grid[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void draw(RenderWindow& window) {
        window.draw(wall);
    }
};

class Mapa_2 {
private:
    Texture wallTexture;
    Texture weakWall;
    float sizeBlock;
    vector< vector<Sprite>> sprites_map;
    vector< vector<char>> matriz;  // Renombrada de vector< vector<int>> a vector< vector<char>>

public:
    Mapa_2(int WIDTH, int HEIGHT) {
        wallTexture.loadFromFile("images/wall.png");
        int x = WIDTH;
        int y = HEIGHT;
        int min = x > y ? y : x;
        sizeBlock = (min / 13);
        cout<<sizeBlock<<endl;

        // Inicializar sprites_map y matriz
        for (int i = 0; i < 13; i++) {
            vector<Sprite> filaSprites;
            vector<char> filaMatriz;
            for (int j = 0; j < 13; j++) {
                Sprite sprite;
                sprite.setTexture(wallTexture);
                sprite.setScale(sizeBlock, sizeBlock);
                sprite.setPosition(sizeBlock * i, sizeBlock * j);
                filaSprites.push_back(sprite);
                filaMatriz.push_back(' ');  // Inicializar matriz con espacios
            }
            sprites_map.push_back(filaSprites);
            matriz.push_back(filaMatriz);
        }
    }

    void generarMatriz() {
        srand(3);
        for (int j = 0; j < 13; j++) {
            for (int k = 0; k < 13; k++) {
                if (j == 0 || k == 0 || j == 12 || k == 12) {
                    sprites_map[j][k].setTexture(wallTexture);
                    matriz[j][k] = '#';  // Asignar '#' a la matriz en los bordes
                } else {
                    if (j % 2 == 0 && k % 2 == 0) {
                        matriz[j][k] = '#';  // Asignar '#' a la matriz en posiciones pares
                    } else {
                        int aux = rand() % 5;
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
                window.draw(sprites_map[i][j]);
            }
        }
    }
};