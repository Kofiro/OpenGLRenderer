CC = g++
CFLAGS = -I"C:\GLFW\include" -I"C:\GLFW\include\glad"
LFLAGS = -L"C:\GLFW\lib" -lglfw3 -lopengl32 -lgdi32

SRC = src/main.cpp src/shader.cpp src\glad.c
OUT = bin/openglrenderer.exe

all:
	mkdir bin
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LFLAGS)

clean:
	rmdir /s /q bin