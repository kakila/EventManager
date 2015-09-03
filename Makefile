CPP = g++
CPP_FLAGS = -Wall -std=c++11

PROGRAM = test.out
OBJECTS = mock_dwenguino.o inputManager.o test.o
SOURCES = $(wildcard *.cpp) $(wildcard *.h)

all: $(OCT_FILES) $(PROGRAM) $(SOURCES)

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -c $< -o $@

test.out: $(OBJECTS)
	$(CPP) $(CPP_FLAGS) $^ -o $@

clean:
	-rm -f *.o *.*~

.PHONY: all clean

