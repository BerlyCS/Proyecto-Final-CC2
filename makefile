main:
	g++ main.cpp mapa.cpp menu.cpp -I/usr/include/ -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g3 -Wall -Wextra
	./test.exe

windows:
	g++ main.cpp -I D:\Libs\SFML-2.5.1\include -L D:\libs\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o p.exe

bomb: 
	g++ bomb.cpp -I/usr/include/ -o bomb -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

powerup: 
	g++ powerup.cpp -I/usr/include/ -o powerup -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
