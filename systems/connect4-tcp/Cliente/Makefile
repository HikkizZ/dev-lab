# Makefile para el cliente del juego Cuatro en Línea

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = client

all: $(TARGET)

$(TARGET): Client.cpp
	$(CXX) $(CXXFLAGS) Client.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
