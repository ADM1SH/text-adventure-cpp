CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = src/main.cpp src/Game.cpp src/Room.cpp src/Item.cpp \
    src/Player.cpp src/Parser.cpp src/Command.cpp src/NPC.cpp \
  src/Event.cpp src/SaveSystem.cpp src/WorldLoader.cpp

OBJ = $(SRC:.cpp=.o)

all: textadventure

textadventure: $(OBJ)
	$(CXX) $(CXXFLAGS) -o textadventure $(OBJ)

clean:
	rm -f src/*.o textadventure