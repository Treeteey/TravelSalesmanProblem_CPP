FILES = graph.cc  main.cc  window.cc #solution.cc
GCC = g++ -std=c++17
OUT = graph
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: compile run

compile:
	$(GCC) $(FILES) -o $(OUT) $(SFML)

run:
	./$(OUT)