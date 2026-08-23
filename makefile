CXX      := g++

TARGET   := bin/main.exe
SRCS     := src/*.cpp

all:
	$(CXX) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	del /Q $(TARGET)