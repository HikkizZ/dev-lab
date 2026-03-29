# Makefile para el servidor del juego Cuatro en Línea

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread
TARGET = Server

all: $(TARGET)

$(TARGET): Server.cpp
	$(CXX) $(CXXFLAGS) Server.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
