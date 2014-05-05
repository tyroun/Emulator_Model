CUR_PATH=$(shell pwd)
CXXCFLAGS=--save-temps
LIBS=
PROGS=rtlobject_test2

all:	$(PROGS)
common = loop.o

rtlobject_test2: $(common) rtlobject_test2.o 
	g++ -g $(CXXFLAGS) -o $@ $(common) rtlobject_test2.o $(LIBS)

.cpp.o:
	g++ $(CXXFLAGS) -c -g $< -o $@

clean:
	rm -f $(PROGS) *.o

