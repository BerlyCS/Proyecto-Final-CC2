#pragma once
#include "player.h"
#include "mapa.h"
#include "sound.hpp"
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

vector<FloatRect> Player::bombasColliders;

Player::Player() : down_frames(0.15f), up_frames(0.15f), left_frames(0.15f), right_frames(0.15f), isBomb(false) {
    speed = 5.0f;
    bombcount = 1;
    bombpower = 2;
    isAlive=true;
}

void Player::check_deaths(Mapa_2& map) {
    for (auto it = map.getFire().begin(); it != map.getFire().end(); it++) {
        if (it->get_rect().intersects(collider.getGlobalBounds()) && !it->isExpired()) {
            isAlive = false;
        }
    }
}

bool Player::alive() {
    return isAlive;
}

void Player::kill() {
    isAlive = false;
}

//Devolver un Vector2f para obtener los valores de los puntos *sugerencia.....!!!!!!!!!
void Player::move(Vector2f movement){
    position += movement;
    sprite.setPosition(position);

    collider.setPosition(Vector2f(position.x+8, position.y + sprite.getGlobalBounds().height*0.45));
    collider.setFillColor(Color::Red);
}

 void Player::draw(RenderWindow& win) {
    win.draw(sprite);
    /*win.draw(collider);*/
}

Sprite Player::getSprite(){
    return sprite;
}

void Player::checkCollision(Mapa_2& map, Vector2f movement){
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

    bool aux;
    if(!bombasColliders.empty()){
        for(auto &bombas : bombasColliders){
            aux = false;
            for(auto &mybombs : bombs){
                if(bombas == mybombs.get_sprite().getGlobalBounds()){
                    move(mybombs.collision(collider.getGlobalBounds(), movement));
                    aux = true;
                    break;
                }
            }
            if(playerBounds.intersects(bombas) && aux == false){
                move(-movement);
            }
        }
    }


/*

    if(!bombasColliders.empty()){
        for(auto &bomb: bombasColliders){
            if(playerBounds.intersects(bomb)){
                move(-movement);
            }
        }
    }
*/
}

Player_one::Player_one(Mapa_2& mapa, int WIDTH, int HEIGHT){
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

    collider.setSize(Vector2f(blockSize-blockSize*0.2, blockSize- blockSize*0.2));
}

void Player_one::joystockControl(Mapa_2 &map, RenderWindow& window, float& dt)
{
    down_frames.update(dt);
    up_frames.update(dt);
    left_frames.update(dt);
    right_frames.update(dt);
    Vector2f movement;

    if(sf::Joystick::isConnected(0)){
        float xAxis = sf::Joystick::getAxisPosition(0, Joystick::X);
        float yAxis = sf::Joystick::getAxisPosition(0, Joystick::Y);
        Vector2f direction(xAxis, yAxis);
        if(xAxis > 0){
            right_frames.applyToSprite(sprite);
        }

        if(xAxis < 0){
            left_frames.applyToSprite(sprite);
        }

        if(yAxis > 0){
            down_frames.applyToSprite(sprite);
        }

        if(yAxis < 0){
            up_frames.applyToSprite(sprite);
        }

        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                    
        if(length>0){
            direction /= length;
            movement = Vector2f(direction.x*speed, direction.y*speed);
        }
    }

    if (Joystick::isButtonPressed(0, 7)) {

        if (isBomb == false) { // Cooldown de 0.5 segundos entre bombas
            Vector2i matrizIndex = map.get_mat_coords(get_center_pos());
            Sound_Singleton::play_bombplace();
            /* cout<<get_center_pos().x<<' '<<get_center_pos().y<<endl; */
            cout<<matrizIndex.x<<' '<<matrizIndex.y<<endl;
            Vector2f bombPosition = map.get_coords(matrizIndex);
            cout<<"Bomb pos: "<<bombPosition.x<<", "<<bombPosition.y<<endl;
            bombs.push_back(Bomb(map, bombPosition, matrizIndex, bombpower));
            isBomb = true;
        }
    }

    for (auto& bomb : bombs) {
        bomb.update();
    }
    move(movement);
    checkCollision(map, movement);
    if(!bombs.empty()){  // OJO solo esoty evaluando la colision de la primera bomba del Vector, cuando se agregue más bombas observar!!!!!!!!
        move(bombs[0].collision(collider.getGlobalBounds(), movement));
    }
    /* cout<<sprite.getPosition().x<<' '<<sprite.getPosition().y<<endl; */

    for (auto it = bombs.begin(); it != bombs.end();) {
        if (!it->isAlive()) {
            Sound_Singleton::play_bombexplosion();
            it->destroy(map);
            //this->isAlive = false;
            it->bombKill(collider.getGlobalBounds(), map, isAlive);
            it = bombs.erase(it);
            isBomb = false;
        } else {
            it->draw(window,dt);
            ++it;
        }
    }
    /* auto pos_mat = map.get_mat_coords(Vector2f(collider.getPosition())); */
    /* cout<<pos_mat.x<<' '<<pos_mat.y<<endl; */
}

void Player_one::controlar(Mapa_2 &map, RenderWindow& window, float& dt){
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
    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        if (isBomb == false) { // Cooldown de 0.5 segundos entre bombas
            Vector2i matrizIndex = map.get_mat_coords(get_center_pos());
            Sound_Singleton::play_bombplace();
            //cout<<get_center_pos().x<<' '<<get_center_pos().y<<endl;
            cout<<matrizIndex.x<<' '<<matrizIndex.y<<endl;
            Vector2f bombPosition = map.get_coords(matrizIndex);
            cout<<"Bomb pos: "<<bombPosition.x<<", "<<bombPosition.y<<endl;
            bombs.push_back(Bomb(map, bombPosition, matrizIndex, bombpower));
            int last = bombs.size();
            bombasColliders.push_back(bombs[last-1].get_sprite().getGlobalBounds());
            isBomb = true;
        }
    }

    for (auto& bomb : bombs) {
        bomb.update();
    }
    move(movement);
    checkCollision(map, movement);
    /* cout<<sprite.getPosition().x<<' '<<sprite.getPosition().y<<endl; */

    for (auto it = bombs.begin(); it != bombs.end();) {
        if (!it->isAlive()) {
            Sound_Singleton::play_bombexplosion();
            it->destroy(map);
            it = bombs.erase(it);
            bombasColliders.pop_back();
            isBomb = false;
        } else {
            it->draw(window,dt);
            ++it;
        }
    }
    /* auto pos_mat = map.get_mat_coords(Vector2f(collider.getPosition())); */
    /* cout<<pos_mat.x<<' '<<pos_mat.y<<endl; */
}


Player_two::Player_two(Mapa_2& mapa) : Player() {
    position = mapa.get_coords(Vector2i(11,10));
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
void Player_two::controlar(Mapa_2 &map, RenderWindow& window,float& dt){
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
    if (Keyboard::isKeyPressed(Keyboard::Space)) {

        if (isBomb == false) { // Cooldown de 0.5 segundos entre bombas
            Vector2i matrizIndex = map.get_mat_coords(get_center_pos());
            Sound_Singleton::play_bombplace();
            /* cout<<get_center_pos().x<<' '<<get_center_pos().y<<endl; */
            /* cout<<matrizIndex.x<<' '<<matrizIndex.y<<endl; */
            Vector2f bombPosition = map.get_coords(matrizIndex);
            /* cout<<"Bomb pos: "<<bombPosition.x<<", "<<bombPosition.y<<endl; */
            bombs.push_back(Bomb(map, bombPosition, matrizIndex, bombpower));
            int last = bombs.size();
            bombasColliders.push_back(bombs[last-1].get_sprite().getGlobalBounds());
            isBomb = true;
        }
    }
    for (auto& bomb : bombs) {
        bomb.update();
    }
    for (auto it = bombs.begin(); it != bombs.end();) {
        if (!it->isAlive()) {
            Sound_Singleton::play_bombexplosion();
            it->destroy(map);
            it = bombs.erase(it);
            bombasColliders.pop_back();
            isBomb = false;
        } else {
            it->draw(window,dt);
            ++it;
        }
    }
    move(movement);
    checkCollision(map, movement);
    /* cout<<sprite.getPosition().x<<' '<<sprite.getPosition().y<<endl; */
    /* auto pos_mat = map.get_mat_coords(Vector2f(collider.getPosition())); */
    /* cout<<pos_mat.x<<' '<<pos_mat.y<<endl; */
}
