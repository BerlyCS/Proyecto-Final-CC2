main: main.o bomb.o player.o sound.o mapa.o menu.o facade.o animation.o
	g++ main.o bomb.o player.o mapa.o menu.o sound.o facade.o animation.o -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g3 -Wall -Wextra -Wpendatic -Wabi -std=c++17
	./game

windows:
	g++ main.cpp -I D:\Libs\SFML-2.5.1\include -L D:\libs\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o p.exe

powerup:
	g++ powerup.cpp -I/usr/include/ -o powerup -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
