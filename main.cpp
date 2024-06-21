#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <execution>
#include <fstream>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class mapa {
    private:
        char** grid;
        Sprite wall;
        int block_size;
    public:
        mapa(RenderWindow& window) {
            grid = new char*[13];
            for (int i=0; i<13;i++) {
                grid[i] = new char[13];
                for (int j=0; j<13; j++)
                    grid[i][j] = ' ';
            }

            for (int i=0; i<13; i++) {
                grid[i][0] = '#';
                grid[0][i] = '#';
                grid[12][i] = '#';
                grid[i][12] = '#';
            }
            for (int i=2; i<11; i+=2) {
                for (int j=2; j<11; j+=2) {
                    grid[i][j] = '#';
                }
            }
            int x = window.getSize().x;
            int y = window.getSize().y;
            int max = x<y ? y : x;
            block_size = max/13;
            Texture wall_img;
            wall_img.loadFromFile("images/wall.png");
            Sprite wall(wall_img);
            auto size = wall.getTexture()->getSize();
            wall.scale(float(block_size)/size.x,float(block_size)/size.y);
        } 

        void print_layout() const {
            for (int i=0; i<13; i++) {
                for (int j=0; j<13; j++) {
                    cout<<grid[i][j]<< ' ';
                }
                cout<<endl;
            }
        }
        
        void draw(RenderWindow& window) {
            for (int i=0; i<13; i++) {
                for (int j=0; j<13; j++) {
                    window.draw(wall);
                }
            }
        }
        
};

int main() {
    mapa map;
    map.print_layout();

    RenderWindow window(VideoMode::getFullscreenModes()[0], "Bouncing balls", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGTH = window.getSize().y;

    /* Font font; */
    /* if (!font.loadFromFile("pixelated.ttf")) { */

    /*     return EXIT_FAILURE; */
    /* } */

    while (window.isOpen()) {
        Event event;
        //Eventos
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();            
            
        }
        map.draw(window);
        //logica aqui
    }
    return EXIT_SUCCESS;
}
