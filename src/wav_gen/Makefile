CUR_PATH=$(shell pwd)
CXXCFLAGS=--save-temps
LIBS=
PROGS=rtlobject_test2

all:	$(PROGS)
common = rtlobject.o

rtlobject_test: $(common) rtlobject_test2.o 
	g++ -g $(CXXFLAGS) -o $@ $(common) rtlobject_test2.o $(LIBS)

.cpp.o:
	g++ $(CXXFLAGS) -c -g $< -o $@

clean:
	rm -f $(PROGS) *.o

