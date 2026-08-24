CXX      := g++

TARGET   := bin/main.exe
SRCS     := src/*.cpp

all:
	$(CXX) -std=c++20 $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	del /Q $(TARGET)