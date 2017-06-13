CC=g++
EXE=corn
CCFLAGS=-std=c++11 -g
SRC=corn_main.cpp \
	corn.cpp
OBJS=$(subst .cpp,.o,$(SRC))

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CCFLAGS) -o $(EXE) $(OBJS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJS) $(EXE)

dist-clean: clean
	rm -rf *~
