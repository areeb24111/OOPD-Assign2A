
#OOPD-Assign2b

all: debug optimized

debug: Q1_debug

Q1_debug: main.cpp
	g++ -g -o Q1_debug main.cpp

optimized: Q1_optimized

Q1_optimized: main.cpp
	g++ -O3 -o Q1_optimized main.cpp

