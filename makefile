CXX      := g++
CXX_FLAGS := -std=c++20

TARGET   := bin/termi.exe
SRCS     := src/*.cpp

all:
	$(CXX) $(CXX_FLAGS) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	del /Q $(TARGET)