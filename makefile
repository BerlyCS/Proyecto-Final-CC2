main: main.o bomb.o player.o sound.o mapa.o menu.o facade.o
	g++ main.o bomb.o player.o mapa.o menu.o sound.o facade.o -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g3 -Wall -Wextra
	./test.exe

windows:
	g++ main.cpp -I D:\Libs\SFML-2.5.1\include -L D:\libs\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o p.exe

bomb.o: bomb.cpp
	g++ -c bomb.cpp -I/usr/include/ -o bomb.o -g3

player.o: player.cpp
	g++ -c player.cpp -I/usr/include/ -o player.o -g3

sound: sound.cpp
	g++ -c sound.cpp -I/usr/include/ -o sound.o -g3


powerup:
	g++ powerup.cpp -I/usr/include/ -o powerup -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
