CC        := clang++
CFLAGS    := -std=c++11

HEDERS    := `pkg-config --cflags glfw3`
LIBS      := `pkg-config --libs glfw3`
LIBS_EXT  := libs/libvulkan.1.2.189.dylib

BIN_NAME  := vulkan-example

all: build

build:
	$(CC) $(CFLAGS) *.cpp $(HEDERS) $(LIBS) $(LIBS_EXT) -o $(BIN_NAME) -DDEBUG
