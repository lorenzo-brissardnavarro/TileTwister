CXX = g++ # le compilateur utilisé

CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude # les options passées
LDLIBS = -lcpr $(shell pkg-config --libs sdl3 sdl3-ttf sdl3-image)
CPPFLAGS = $(shell pkg-config --cflags sdl3 sdl3-ttf sdl3-image)

SRC = src/main.cpp src/Grid.cpp src/Game.cpp src/Window.cpp src/GameObject.cpp # la liste des fichiers .cpp à compiler ensemble

BIN = main #le nom du programme généré

all: $(BIN)

# commande de compilation
$(BIN): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDLIBS)

clean:
	rm -f $(BIN)

.PHONY: all clean