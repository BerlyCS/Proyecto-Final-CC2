#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
class Mapa_2;
#include "animation.h"

using namespace sf;
using namespace std;
class Bomb{
    private:
        RectangleShape bomb;
        unique_ptr<Texture> texture;
        Sprite sprite;
        ASprite frames;
        Vector2f position;
        Vector2i m;
        Clock lifeTimer;
        bool alive;
        int radius;

        bool stayBomb;
    public:
        Bomb(Mapa_2& mapa, Vector2f position, Vector2i mat_pos,int radius = 1);
        bool isAlive() const;
        void update();
        void draw(RenderWindow& window, float dt);
        Vector2f getPosition() const;
        void destroy(Mapa_2 &map);
        Vector2f get_center_pos();
        Sprite& get_sprite();
        Vector2f collision(FloatRect playerCollider, Vector2f movement);
        void bombKill(FloatRect playerCollider, Mapa_2 map, bool &isAlive);
};

