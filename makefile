# FILES = graph.cc  main.cc  solution.cc window.cc 
# GCC = g++ -std=c++20
# OUT = graph
# SFML = -lsfml-graphics -lsfml-window -lsfml-system

# all: compile run

# compile:
# 	$(GCC) $(FILES) -o $(OUT) $(SFML)

# run:
# 	./$(OUT)

all:
ifeq ($(OS),Windows_NT)
	rmdir /s /q build || exit 0
	mkdir build
	cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build . && graph.exe
else
	rm -rf build
	mkdir -p build
	cd build && cmake .. && cmake --build . && ./graph
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q build || exit 0
else
	rm -rf build
endif