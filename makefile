CXX= g++
CXXFLAGS=-c -Wall -g -std=c++11

all:		proj

clean:
	@rm -f *.o proj

file_conversions.o: file_conversions.h file_conversions.cpp 
	$(CXX) $(CXXFLAGS) file_conversions.cpp -o file_conversions.o

instructions.o: instructions.h instructions.cpp
	$(CXX) $(CXXFLAGS) instructions.cpp -o instructions.o

pipeline.o: pipeline.h pipeline.cpp
	$(CXX) $(CXXFLAGS) pipeline.cpp -o pipeline.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.o
		
proj:	file_conversions.o instructions.o pipeline.o main.o
	$(CXX) file_conversions.o instructions.o pipeline.o main.o -o proj

gdb:
	gdb ./proj

val:
	valgrind --leak-check=full --track-origins=yes ./proj

run:
	./proj