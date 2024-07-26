#include "facade.hpp"
#include "menu.h"
Facade_game::Facade_game(int SCREEN_SIZE) : window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Bomberman"), player(mapa, SCREEN_SIZE, SCREEN_SIZE), player2(mapa), mapa(SCREEN_SIZE, SCREEN_SIZE, rand()%7), menu(SCREEN_SIZE) {
    window.setVerticalSyncEnabled(true);
    mapa.Print();
    Game_started = false;
    Sound_Singleton::init();//agrega singleton
    Sound_Singleton::play_menu_theme();
    
    font.loadFromFile("font.ttf");

    /* cout<<"estilo: "<<mapa.get_map_style()<<endl; */
}

bool Facade_game::is_Running() {
    return window.isOpen();
}

void Facade_game::update_game() {
    Event event;
    
    //eventos
    while (window.pollEvent(event)) {
        //player.validadMovimiento(mapa.getMatriz());
        if (event.type == Event::Closed)
            window.close();
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            Sound_Singleton::stop_battle();
            Sound_Singleton::play_menu_theme();
            Game_started = false;
        } 

    }
    if (!Game_started) {
        menu.handleEvent(window, Game_started);
        menu.draw(window);
        return;
    }
    float dt = clock.restart().asSeconds();
    window.clear(Color::Black);
    mapa.draw(window);
    player.controlar(mapa, window, dt);
    player2.controlar(mapa, window, dt);
    //player.joystockControl(mapa, window, dt);
    /* player_dos.controlar(mapa); */
    /* player_dos.controlar(); */
    if (player.alive()) 
        player.draw(window);
    else {
        cout<<"gano jugador 2"<<endl;
        Button p2(Vector2f(150,150), "Gano el jugador 2", font, 60, 30);
        p2.draw(window);
        window.display();

        this_thread::sleep_for(chrono::seconds(3));
        window.close();
    }
    if (player2.alive())
        player2.draw(window);
    else {
        cout<<"gano jugador 1"<<endl;
        Button p1(Vector2f(150,150), "Gano el jugador 1", font, 60, 30);
        p1.draw(window);
        window.display();
        this_thread::sleep_for(chrono::seconds(3));
        window.close();
    }
    player.check_deaths(mapa);
    player2.check_deaths(mapa);
    /* player_dos.draw(window); */
    window.display();
}

