main: main.o bomb.o player.o
	g++ main.o bomb.o player.o -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g3 -Wall -Wextra
	./test.exe

windows:
	g++ main.cpp -I D:\Libs\SFML-2.5.1\include -L D:\libs\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o p.exe

bomb.o: bomb.cpp
	g++ -c bomb.cpp -I/usr/include/ -o bomb.o

player.o: player.cpp
	g++ -c player.cpp -I/usr/include/ -o player.o

powerup:
	g++ powerup.cpp -I/usr/include/ -o powerup -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
