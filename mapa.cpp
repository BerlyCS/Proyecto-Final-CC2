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

class block {
    protected:
        int block_size;
        Sprite sprite;
        Sprite& getSprite() {
            return sprite;
        }

};

class wall : public block {

};

class weak_wall : public block {

};
class tile : public block {

};

class Mapa_2 {
private:
    Texture texture;
    float sizeBlock;
    vector< vector<Sprite>> sprites_map;
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
            vector<Sprite> filaSprites;
            for (int j = 0; j < 13; j++) {
                Sprite sprite;
                sprite.setTexture(texture);

                if (matriz[i][j] == '#') {
                    sprite.setTextureRect(frames[0]);
                } else if (matriz[i][j] == 'x') {
                    sprite.setTextureRect(frames[1]);
                } else {
                    sprite.setTextureRect(frames[2]);
                }
                auto size = frames[0].getSize();
                sprite.setScale(sizeBlock/size.x, sizeBlock/size.y);
                sprite.setPosition(sizeBlock * j, sizeBlock * i);
                filaSprites.push_back(sprite);
            }
            sprites_map.push_back(filaSprites);
        }
    }

    /* Toma una coordenada del mapa y retorna la posicion en pantalla*/
    Vector2f get_coords(int x, int y) {
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
                window.draw(sprites_map[i][j]);
            }
        }
    }
    int getBlockSize() {
        return sizeBlock;
    }
};
