main:
	g++ main.cpp -I/usr/include/ -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

windows:
	g++ main.cpp -I D:\Libs\SFML-2.5.1\include -L D:\libs\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o p.exe
