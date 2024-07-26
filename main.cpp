#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "mapa.h"
#include "animation.h"
#include "player.h"
#include "sound.hpp"
#include "facade.hpp"

using namespace sf;
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    
    Facade_game game(VideoMode::getDesktopMode().height);
    while (game.is_Running()) {
        game.update_game();
    }
    return EXIT_SUCCESS;
}
