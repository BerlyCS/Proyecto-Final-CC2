main: main.o bomb.o player.o sound.o mapa.o menu.o facade.o animation.o
	g++ main.o bomb.o player.o mapa.o menu.o sound.o facade.o animation.o -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g3 -Wall -Wextra -Wpedantic -Wabi -std=c++17
	./game

windows: main.o bomb.o player.o sound.o mapa.o menu.o facade.o animation.o
	g++ main.o bomb.o player.o sound.o mapa.o menu.o facade.o animation.o -I D:\Libs\SFML-2.6.1\include -L D:\libs\SFML-2.6.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game.exe
	.\game.exe

SFML_LIB = D:\libs\SFML-2.6.1\lib
SFML_INCLUDE = D:\Libs\SFML-2.6.1\include

compilar:
	g++ -c main.cpp -o main.o -I ${SFML_INCLUDE}
	g++ -c bomb.cpp -o bomb.o -I ${SFML_INCLUDE}
	g++ -c player.cpp -o player.o -I ${SFML_INCLUDE}
	g++ -c sound.cpp -o sound.o -I ${SFML_INCLUDE}
	g++ -c mapa.cpp -o mapa.o -I ${SFML_INCLUDE}
	g++ -c menu.cpp -o menu.o -I ${SFML_INCLUDE}
	g++ -c facade.cpp -o facade.o -I ${SFML_INCLUDE}
	g++ -c animation.cpp -o animation.o -I ${SFML_INCLUDE}
	g++ main.o bomb.o player.o sound.o mapa.o menu.o facade.o animation.o -I ${SFML_INCLUDE} -L ${SFML_LIB} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game.exe
