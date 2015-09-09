CPP = g++
CPP_FLAGS = -Wall -std=c++11

PROGRAM = test.out demo.out
OBJECTS = mock_dwenguino.o ObsPubManager.o
TEST_OBJECTS = $(OBJECTS) test.o 
DEMO_OBJECTS = $(OBJECTS) demo.o
SOURCES = $(wildcard *.cpp) $(wildcard *.h)

all: $(PROGRAM)

debug: CPP_FLAGS += -DDEBUG -g
debug: all

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -c $< -o $@

test.out: $(TEST_OBJECTS)
	$(CPP) $(CPP_FLAGS) $^ -o $@

demo.out: $(DEMO_OBJECTS)
	$(CPP) $(CPP_FLAGS) $^ -o $@

clean:
	-rm -f *.o *.*~

.PHONY: all clean

