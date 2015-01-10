#! /usr/bin/make

.NULL: .exe

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
TARGETS = $(basename $(SOURCES))

INIT_SHADER = ../Common/InitShader.o

CXXOPTS = -mno-cygwin -mwin32 -g
CXXDEFS = -DFREEGLUT_STATIC -DGLEW_STATIC
CXXINCS = -I../../include

CXXFLAGS = $(CXXOPTS) $(CXXDEFS) $(CXXINCS)

LDOPTS =
LDDIRS = -L../../lib/windows
LDLIBS = -lfreeglut -lglew32 -lopengl32 -lgdi32 -lwinmm

LDFLAGS = $(LDOPTS) $(LDDIRS) $(LDLIBS)

DIRT = $(wildcard *.o *.i *~ */*~ *.log)

#-----------------------------------------------------------------------------

.PHONY: Makefile

default all: $(TARGETS)

$(TARGETS): $(INIT_SHADER)

%: %.cpp
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

#-----------------------------------------------------------------------------

%.i: %.cpp
	$(CXX) -E $(CXXFLAGS) $< | uniq > $@

#-----------------------------------------------------------------------------

clean:
	$(RM) $(DIRT)

rmtargets:
	$(RM) $(TARGETS)

clobber: clean rmtargets
