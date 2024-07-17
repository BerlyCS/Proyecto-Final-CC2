#include "bomb.h"
#include "mapa.h"

Bomb::Bomb(Mapa_2& mapa, Vector2f position, Vector2i mat_pos,int radius) : frames(0.2f){
    //se establece el tamaño de la bomba al tamaño de un bloque del mapa
    bomb.setSize(Vector2f(mapa.getBlockSize(), mapa.getBlockSize()));
    bomb.setPosition(position);
    bomb.setFillColor(Color::Transparent);

    this->position = position;
    alive = true;
    lifeTimer.restart();

    texture = make_unique<Texture>(Texture());
    texture->loadFromFile("images/bomb.png");
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    frames.setRects(0, 0, 16, 16, 3);
    frames.addFrame(IntRect(16,0,16,16));
    frames.applyToSprite(sprite);
    sprite.setScale(Vector2f(mapa.getBlockSize()/16.f, mapa.getBlockSize()/16.f));

    this->radius = radius; //radius 1
    this->m = mat_pos;
}

bool Bomb::isAlive() const {
    return alive;
}

void Bomb::update() {
    if (lifeTimer.getElapsedTime().asSeconds() >= 2.0) {
        alive = false;
    }
}

void Bomb::draw(RenderWindow& window, float dt) {
    frames.update(dt);
    frames.applyToSprite(sprite);
    /* if (alive) { */
    /* window.draw(bomb); */
    window.draw(sprite);
    /* } */
}

Vector2f Bomb::getPosition() const {
    auto size = bomb.getSize();
    auto pos = bomb.getPosition();
    Vector2f center_pos = Vector2f(pos.x+size.x/2, pos.y+size.y/2);
    return center_pos;
}

//Por alguna razon se borran los objetos en
//con las coordenadas invertidas
void Bomb::destroy(Mapa_2 &map) {
    for (int i = 1; i<=radius; i++) {
        //up tiles
        if ( m.y - i >= 0 ) {
            if ( map.get_block_at(m.x, m.y - i)->IsBreakable() ) {
                delete map.get_block_at(m.x, m.y - i);
                map.to_tile_at(Vector2i(m.x,m.y - i));
            }
        }
        //down tiles
        if ( m.y + i <= 13 ) {
            if ( map.get_block_at(m.x, m.y + i)->IsBreakable() ) {
                delete map.get_block_at(m.x, m.y + i);
                map.to_tile_at(Vector2i(m.x,m.y + i));
            }
        }
        //left tiles
        if ( m.x - i > 0 ) {
            if ( map.get_block_at(m.x - i, m.y)->IsBreakable() ) {
                delete map.get_block_at(m.x - i, m.y);
                map.to_tile_at(Vector2i(m.x - i,m.y));
            }
        }
        //right tiles
        if ( m.x + i < 13 ) {
            if ( map.get_block_at(m.x + i, m.y)->IsBreakable() ) {
                delete map.get_block_at(m.x+i, m.y);
                map.to_tile_at(Vector2i(m.x+i,m.y ));
            }
        }
    }
    /* if(map.getMatrizSprites()[matrizIndex.x-1][matrizIndex.y]->IsCollidable()){
        cout<<"->"<<endl;
        delete map.getMatrizSprites()[matrizIndex.x+1][matrizIndex.y];
    map.getMatrizSprites()[matrizIndex.x+1][matrizIndex.y] = new Tile(map.get_screen_size().x, map.get_screen_size().y);
    }*/            
}
Vector2f Bomb::get_center_pos() {
    Vector2f size = sprite.getGlobalBounds().getSize();
    Vector2f pos = sprite.getPosition();
    return Vector2f(pos.x + size.x/2, pos.y + size.y/2);
}

Sprite& Bomb::get_sprite() {
    return sprite;
}

Vector2f Bomb::collision(FloatRect playerCollider, Vector2f movement){
    FloatRect bombCollider = sprite.getGlobalBounds();
    if(playerCollider.intersects(bombCollider) && stayBomb == false){
        return Vector2f(-movement.x, -movement.y);
    } else if (playerCollider.intersects(bombCollider) && stayBomb == true) {
        return Vector2f(0, 0);
    } else if (!playerCollider.intersects(bombCollider)){
        stayBomb = false;
        return Vector2f(0, 0);
    }
}

void Bomb::bombKill(FloatRect playerCollider, Mapa_2 map, bool &isAlive){
    for(int i=1; i<=radius; i++){
        if ( m.y - i >= 0 ) {
            if (playerCollider.intersects(map.get_block_at(m.x, m.y - i)->getSprite().getGlobalBounds())) {
                isAlive = false;
            }
        }

        if ( m.y + i <= 13 ) {
            if (playerCollider.intersects(map.get_block_at(m.x, m.y + i)->getSprite().getGlobalBounds())) {
                isAlive = false;
            }
        }

        if ( m.x - i > 0 ) {
            if (playerCollider.intersects(map.get_block_at(m.x - i, m.y)->getSprite().getGlobalBounds())) {
                isAlive = false;
            }
        }

        if ( m.x + i < 13 ) {
            if (playerCollider.intersects(map.get_block_at(m.x + i, m.y)->getSprite().getGlobalBounds())) {
                isAlive = false;
            }
        }
    }
}

