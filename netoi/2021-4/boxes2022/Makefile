CC = g++

SRC := $(shell ls *.cpp)
TESTS := $(shell ls *.tst)
PROG := $(SRC:%.cpp=%)
PASS += $(TESTS:%.tst=%.pass)


all: clean $(PROG) $(PASS)

% : %.cpp
	$(CC) -g -O0 -o $@ $<

%.pass : %.tst
	valgrind -q ./$(PROG) < $< || touch $@

clean:
	rm -f $(PROG) $(PASS)
