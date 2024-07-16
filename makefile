main:
	g++ main.cpp -I/usr/include/ -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g3 -Wall -Wextra
	./test.exe

windows:
	g++ main.cpp -o game.exe -L C:\Users\User\Documents\SFML\lib -I C:\Users\User\Documents\SFML\include -lsfml-graphics -lsfml-window -lsfml-system
	sfml-app.exe

bomb: 
	g++ bomb.cpp -I/usr/include/ -o bomb -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

powerup: 
	g++ powerup.cpp -I/usr/include/ -o powerup -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
