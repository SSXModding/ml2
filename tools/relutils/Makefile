# relutils makefile
CXX = g++
CXXFLAGS = -std=c++23 -g
LINKFLAGS = -lelf

all: rellink reldump

rellink: diagman.o rellink.o
	$(CXX) $(CXXFLAGS) $^ $(LINKFLAGS) -o $@

reldump: reldump.o
	$(CXX) $(CXXFLAGS) $^ $(LINKFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	-rm reldump rellink *.o

# hand dependencies
diagman.o: diagman.hpp
reldump.o: rel_format.hpp types.hpp
rellink.o: rel_format.hpp types.hpp