CPP = g++
CPP_FLAGS = -Wall -std=c++11
CPP_LFLAGS = -pthread

PROGRAM = test.out demo.out demo_callbck.out
OBJECTS = mock_dwenguino.o
TEST_OBJECTS = $(OBJECTS) test.o ObsPubManager.o
DEMO_OBJECTS = $(OBJECTS) demo.o ObsPubManager.o
DEMO_CLLBCK_OBJECTS = $(OBJECTS) demo_callbck.o CallbckPubManager.o
SOURCES = $(wildcard *.cpp) $(wildcard *.h)

all: $(PROGRAM)

debug: CPP_FLAGS += -DDEBUG -g
debug: all

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -c $^ -o $@

test.out: $(TEST_OBJECTS)
	$(CPP) $(CPP_FLAGS) $(CPP_LFLAGS) $^ -o $@

demo.out: $(DEMO_OBJECTS)
	$(CPP) $(CPP_FLAGS) $(CPP_LFLAGS) $^ -o $@

demo_callbck.out: $(DEMO_CLLBCK_OBJECTS)
	$(CPP) $(CPP_FLAGS) $(CPP_LFLAGS) $^ -o $@

clean:
	-rm -f *.o *.*~

.PHONY: all clean

