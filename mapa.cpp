#include <SFML/Graphics.hpp>

using namespace sf;
class mapa {
    private:
        char** grid;
        Sprite wall;
        int block_size;
        Texture wall_img;
    public:
        mapa(int WIDTH, int HEIGHT) {
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
            int x = WIDTH;
            int y = HEIGHT;
            int max = x<y ? y : x;
            block_size = max/13;
            wall_img.loadFromFile("images/wall.png");
            Sprite wall(wall_img);
            auto size = wall.getTexture()->getSize();
            wall.scale(float(block_size)/size.x,float(block_size)/size.y);
            wall.setPosition(Vector2f(210,3));
        } 

        void print_layout() const {
            for (int i=0; i<13; i++) {
                for (int j=0; j<13; j++) {
                    /* cout<<grid[i][j]<< ' '; */
                }
                /* cout<<endl; */
            }
        }
        
        void draw(RenderWindow& window) {
            window.draw(wall);
                    
        }
        
};


