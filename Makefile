#all:
#	g++ test_out_root.cpp src/Cl.cpp -o hello

CC=g++
INCLUDES=`root-config --cflags`
CFLAGS=-c -Wall
LDFLAGS=`root-config --libs`
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test_spectrum

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
	
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	@echo "Sector clear!"