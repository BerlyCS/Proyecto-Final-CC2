#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "menu.h"
#include <SFML/Graphics/Font.hpp>
#include <chrono>
#include <thread>
#include "sound.hpp"

using namespace std;
using namespace sf;

class Facade_game {
    private:
        RenderWindow window;
        Font font;
        Mapa_2 mapa;
        Menu menu;
        bool Game_started;
        Clock clock;
        Player_one player;
        Player_two player2;
        int WIDTH;
        int HEIGHT;
    public:
        Facade_game(int SCREEN_SIZE);
        bool is_Running();
        void update_game();
};

