CXX = g++

TARGET = dungeon_quest
SRCS = main.cpp player.cpp game.cpp file.cpp

all:
	$(CXX) -o $(TARGET) $(SRCS)

clean:
	rm $(TARGET)
