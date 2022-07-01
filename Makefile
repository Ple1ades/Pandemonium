all:
	g++ -Iimports/src/Include -Limports/src/lib/x64 -o build/main main.cpp -lmingw32 -lSDL2main -lSDL2 -l box2d -static -static-libgcc -static-libstdc++ -std=c++17