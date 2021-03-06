CXX= g++
CXXFLAGS= -Wall -g -std=c++11 -O0

all: proj

clean:
	@rm -f *.o proj && echo "cleaning..."

file_conversions.o: file_conversions.h file_conversions.cpp 
	$(CXX) $(CXXFLAGS) -c file_conversions.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

instructions.o: instructions.h instructions.cpp
	$(CXX) $(CXXFLAGS) -c instructions.cpp

pipeline.o: pipeline.h pipeline.cpp
	$(CXX) $(CXXFLAGS) -c pipeline.cpp

pipeline_output.o: pipeline_output.h pipeline_output.cpp
	$(CXX) $(CXXFLAGS) -c pipeline_output.cpp

proj: file_conversions.o instructions.o pipeline.o main.o pipeline_output.o
	$(CXX) $(CXXFLAGS) main.o file_conversions.o instructions.o pipeline.o pipeline_output.o -o proj

gdb:
	gdb ./proj

val:
	valgrind --leak-check=full --track-origins=yes ./proj

run:
	./proj
