CUR_PATH=$(shell pwd)
CXXCFLAGS=
LIBS=
PROGS=rtlobject_test

all:	$(PROGS)
common =

rtlobject_test: $(common) rtlobject_test.o 
	g++ -g $(CXXFLAGS) -o $@ $(common) rtlobject_test.o $(LIBS)

.cpp.o:
	g++ $(CXXFLAGS) -c -g $< -o $@

clean:
	rm -f $(PROGS) *.o

