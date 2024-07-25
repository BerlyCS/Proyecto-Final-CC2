#include "mapa.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

using namespace sf;
using namespace std;

Block::Block(int WIDTH, int HEIGHT){
    int x = WIDTH;
    int y = HEIGHT;
    int min = x > y ? y : x;
    sizeBlock = (float(min) / 13);
}

Sprite& Block::getSprite(){
    return sprite;
}

void Block::setSprite(Sprite& sprite) {
    this->sprite = sprite;
}

void Block::draw(RenderWindow& window){
    window.draw(sprite);
    //window.draw(collider);
}

float Block::getBlockSize(){
    return sizeBlock;
}


Wall::Wall(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){}

bool Wall::IsCollidable(){
    return true;
}
bool Wall::IsBreakable(){
    return false;
}


WeakWall::WeakWall(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){}

bool WeakWall::IsCollidable(){
    return true;
}
bool WeakWall::IsBreakable(){
    return true;
}


Tile::Tile(int WIDTH, int HEIGHT) : Block(WIDTH, HEIGHT){}

bool Tile::IsCollidable(){
    return false;
}
bool Tile::IsBreakable(){
    return false;
}

Texture FireTile::fireTexture = Texture();

FireTile::FireTile(Vector2f& position, int direction, float size) : duration(0.5f) {
    //direction 
    //0=horiontal
    //1=vertical
    //
        /* fireTexture = make_shared<Texture>(Texture()); */
        fireTexture.loadFromFile("images/fire.png");
        fireSprite.setTexture(fireTexture);
        fireSprite.setTextureRect(IntRect(16*direction,0, 16,16));
        fireSprite.setPosition(position);
        fireSprite.setScale(float(size)/16.0f, size/16.0f);
        timer.restart();
    }

bool FireTile::isExpired() const {
        return timer.getElapsedTime().asSeconds() >= duration;
    }

void FireTile::draw(RenderWindow& window) {
        if (!isExpired()) {
            window.draw(fireSprite);
        }
    }
FloatRect FireTile::get_rect() {
    return fireSprite.getGlobalBounds();
}

Mapa_2::Mapa_2(int WIDTH, int HEIGHT, int map_style) : map_style(map_style) {
    screen_size = Vector2i(WIDTH, HEIGHT);
    texture.loadFromFile("images/wall_textur.png");
    IntRect frames[3];

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
    for (int j = 0; j < 13; j++) {
        vector<Block*> filaSprites;
        for (int i = 0; i < 13; i++) {
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

void Mapa_2::to_tile_at(Vector2i index) {
    /* cout<<flush<<"Deleting: "<<index.x<<' '<<index.y<<' '<<sprites_map[index.x][index.y]<<endl; */
    /* cout<<flush<<"deleting..."<<endl; */
    /* delete sprites_map[index.y][index.x]; */
    /* cout<<flush<<"deleted!"<<endl; */
    /* cout<<flush<<"setting new tile..."<<endl; */
    sprites_map[index.x][index.y] = new Tile(get_screen_size().x, get_screen_size().y);
    Block* bloque = sprites_map[index.x][index.y];

    /* cout<<flush<<"done..."<<endl; */

    Sprite sprite;
    sprite.setTexture(texture);
    IntRect frames = IntRect(0,16*map_style,16,16);
    sprite.setTextureRect(frames);

    auto size = frames.getSize();
    bloque->setSprite(sprite);
    bloque->getSprite().setScale(sizeBlock/size.x, sizeBlock/size.y);
    bloque->getSprite().setPosition(sizeBlock * index.x, sizeBlock * index.y);
}

Vector2i Mapa_2::get_screen_size() const {
    return screen_size;
}

/* Toma una coordenada del mapa y retorna la posicion en pantalla*/
Vector2f Mapa_2::get_coords(Vector2i pos) const {
    /* cout<<x*sizeBlock<<' '<<y*sizeBlock<<endl; */
    return Vector2f(pos.x*sizeBlock,pos.y*sizeBlock);
}

/* Vector2i get_coords(Vector2f pos) { */
/*     return Vector2i(pos.x/sizeBlock, pos.y/sizeBlock); */
/* } */

/*Toma una coordenada de pantalla y retorna la posicion en la matriz*/
Vector2i Mapa_2::get_mat_coords(Vector2f pos) {
    return Vector2i((pos.x/sizeBlock), (pos.y/sizeBlock));
}

Block*& Mapa_2::get_block_at(int x, int y) {
    return sprites_map[x][y];
}

int Mapa_2::get_map_style() {
    return map_style;
}

void Mapa_2::generarMatriz() {
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

void Mapa_2::Print() const {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            std::cout << matriz[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Mapa_2::draw(RenderWindow& window) {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            sprites_map[i][j]->draw(window);
        }
    }

    for (auto it = fire.begin(); it != fire.end(); it++) {
        if (it->isExpired()) {
            /* fire.erase(it); */
        }
        else {
            it->draw(window);
        }
    }
}

vector<vector<char>> Mapa_2::getMatriz(){
    return matriz;
}

vector<vector<Block*>> Mapa_2::getMatrizSprites(){
    return sprites_map;
}

int Mapa_2::getBlockSize() {
    return sizeBlock;
}

void Mapa_2::insertFire(Vector2i pos, int dir) {
    auto coords = get_coords(pos);
    fire.push_back(FireTile(coords,dir,sizeBlock));
}

vector<FireTile>& Mapa_2::getFire() {
    return fire;
}

