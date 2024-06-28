#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include "mapa.cpp"

//si encuentran una mejor implementacion pueden aplicarlo sobre lo
//que ya esta

using namespace sf;
using namespace std;

class Bomba {
    private:
        int power;
        Texture images[3];
        Sprite sprite;
        int type;
        Time time_placed;
        double x,y;
        friend class mapa;
    public:
        Bomba(int power, int type, double x, double y, Time time ) : x(x), y(y) {
            this->power = power;
            this->type = type;
            images[0].loadFromFile("images/bomb3.png");
            sprite.setTexture(images[0]);
            time_placed = time;
        }

        void draw(RenderWindow& window, Time actual_time) {
            Time seconds_passed = actual_time - time_placed;
            if (seconds_passed.asMilliseconds() > 3000 ) {
                
            } else {
                window.draw(sprite);
                return;
            }
        }
};

class Player {
    protected:
        Texture images[4];
        Sprite sprite;
        double speed;
        Vector2f psi, pid;
        int bombcount;
        int posMx, posMy;
    public:
        Player(){
            speed = 5.0f;
            bombcount = 1;
        }
//Devolver un Vector2f para obtener los valores de los puntos *sugerencia.....!!!!!!!!!
        void colider(RenderWindow& win){
            psi = Vector2f(sprite.getGlobalBounds().getPosition().x, sprite.getGlobalBounds().getPosition().y+30);
            pid = Vector2f(sprite.getGlobalBounds().getPosition().x+55, sprite.getGlobalBounds().getPosition().y+85);

            RectangleShape psid (Vector2f(5, 5));
            psid.setPosition(psi);
            psid.setFillColor(Color::Red);

            RectangleShape pidd (Vector2f(5, 5));
            pidd.setPosition(pid);
            pidd.setFillColor(Color::Red);

            win.draw(pidd);
            win.draw(psid);
        }

        //para poder cambiar los controles
        virtual void controlar(Mapa_2) = 0;
        void draw(RenderWindow& win) {
            win.draw(sprite);
        }
/*
        void validadMovimiento(vector<vector<char>> matriz){
            int ejex, ejey = 0;
            int num = 1000/13;
            for(int i=0; i<13; i++){
                ejex = 0;
                for(int j=0; j<13; j++){
                    if(matriz[i][j] == '#'){
                        if (sprite.getGlobalBounds().getPosition().x > ejex) sprite.move(-0.9f,0);
                    }
                }
                ejex += num;
            }

            ejey += num;
        }
*/

        void colider2(RenderWindow& win){
            RectangleShape colider(Vector2f(55, 55));
            colider.setPosition(Vector2f(sprite.getGlobalBounds().getPosition().x, sprite.getGlobalBounds().getPosition().y+30));
            colider.setFillColor(Color::Yellow);
            win.draw(colider);
        }
//Retorna un bool que verifica si avanzo o no
        bool validarMovimiento(Mapa_2 map){
            if(psi.x <= map.getMatrizSprites()[posMx][posMy-1]->getColliderID().x && map.getMatriz()[posMx][posMy-1] != ' '){
                //cout<<"<-"<<endl;
                sprite.move(0.5, 0);
                return false;
            } else if (pid.x >= map.getMatrizSprites()[posMx][posMy+1]->getColliderSI().x && map.getMatriz()[posMx][posMy+1] != ' '){
                //cout<<"->"<<endl;
                sprite.move(-0.5, 0);
                return false;
            } else if (psi.y <= map.getMatrizSprites()[posMx-1][posMy]->getColliderID().y && map.getMatriz()[posMx-1][posMy] != ' '){
                //cout<<"^|^"<<endl;
                sprite.move(0, 0.5);
                return false;
            } else if (pid.y >= map.getMatrizSprites()[posMx+1][posMy]->getColliderSI().y && map.getMatriz()[posMx+1][posMy] != ' '){
                //cout<<"v|"<<endl;
                sprite.move(0, -0.5);
                return false;

            } else {
                //cout<<" "<<endl;
                return true;
            }
        }

        bool validarMovimiento2(Mapa_2 map){
            if(map.getMatriz()[posMx][posMy-1] != ' '){
                if(psi.x < map.getMatrizSprites()[posMx][posMy-1]->getColliderID().x){
                    cout<<"<-"<<endl;
                    sprite.move(0.5, 0);
                    return false;
                } else {
                    posMy--;
                    return true;
                }
            }
            if(map.getMatriz()[posMx][posMy+1] != ' '){
                if (pid.x > map.getMatrizSprites()[posMx][posMy+1]->getColliderSI().x){
                    cout<<"->"<<endl;
                    sprite.move(-0.5, 0);
                    return false;
                } else {
                    posMy++;
                    return true;
                }
            }
            if(map.getMatriz()[posMx-1][posMy] != ' '){
                if (psi.y < map.getMatrizSprites()[posMx-1][posMy]->getColliderID().y){
                    cout<<"^|^"<<endl;
                    sprite.move(0, 0.5);
                    return false;
                } else {
                    posMx--;
                    return true;
                }
            }
            if(map.getMatriz()[posMx+1][posMy] != ' '){
                if (pid.y > map.getMatrizSprites()[posMx+1][posMy]->getColliderSI().y){
                    cout<<"v|"<<endl;
                    sprite.move(0, -0.5);
                    return false;

                } else {
                    posMx++;
                    return true;
                }
            } else {
                return true;
            }   
        }

        void moverMatriz(Mapa_2 map){
            cout<<"("<<posMx<<", "<<posMy<<")"<<endl;
            if(pid.x >= map.getMatrizSprites()[posMx][posMy+1]->getColliderSI().x){
                posMy++;
            } else if(psi.x <= map.getMatrizSprites()[posMx][posMy-1]->getColliderID().x){
                posMy--;
            } else if(psi.y <= map.getMatrizSprites()[posMx-1][posMy]->getColliderID().y){
                posMx--;
            } else if(pid.y >= map.getMatrizSprites()[posMx+1][posMy]->getColliderSI().y){
                posMx++;
            }
        }
};

class player_one : public Player {
    public:
        player_one(Vector2f position) : Player() {
            posMx = 1;
            posMy = 1;
            sprite.setPosition(position);
            if (!(
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               )) {
                cout<<"No se pudo cargar las texturas del jugador"<<endl;
            }
        }
        void controlar(Mapa_2 map)
        {
            //if (validarMovimiento(map) == true){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    sprite.move(0, -speed);
                    sprite.setTexture(images[0]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    sprite.move(0, speed);
                    sprite.setTexture(images[2]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    sprite.move(-speed, 0);
                    sprite.setTexture(images[1]);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                {
                    sprite.move(speed, 0);
                    sprite.setTexture(images[3]);
                }
            }
        //}
};

class Player_two : public Player {
    public:
        Player_two() : Player() {
            sprite.setPosition(Vector2f(100,100));
            if (
                images[0].loadFromFile("images/Character_W_4.png") &&
                images[1].loadFromFile("images/Character_A_4.png") &&
                images[2].loadFromFile("images/Character_S_4.png") &&
                images[3].loadFromFile("images/Character_D_4.png") 
               ) {
                cout<<"No se pudo cargar las texturas del jugador"<<endl;
            }
        }
        void controlar(Mapa_2 map)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                sprite.move(0, -speed);
                sprite.setTexture(images[0]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                sprite.move(0, speed);
                sprite.setTexture(images[2]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                sprite.move(-speed, 0);
                sprite.setTexture(images[1]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                sprite.move(speed, 0);
                sprite.setTexture(images[3]);
            }
        }
};

int main() {
    //RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Bomberman");
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    //mapa map(WIDTH, HEIGHT);
    Mapa_2 mapa(WIDTH, HEIGHT);
    mapa.Print();

    Vector2f posPlayer1(HEIGHT/13+10, HEIGHT/13-20);
    //Vector2f posPlayer1(300,300);

    //map.print_layout();
    player_one player(posPlayer1);
    Player_two player_dos;

    while (window.isOpen()) {
        Event event;
        
        //Eventos
        while (window.pollEvent(event)) {
            //player.validadMovimiento(mapa.getMatriz());
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        window.clear(Color::Black);
        player.controlar(mapa);
        player.moverMatriz(mapa);
        player_dos.controlar(mapa);
        mapa.draw(window);
        player.draw(window);
        player_dos.draw(window);
        player.colider(window);
        window.display();
        //logica aqui
    }
    return EXIT_SUCCESS;
}
