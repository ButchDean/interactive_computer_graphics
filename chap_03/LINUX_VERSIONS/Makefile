LDLIBS = -lglut -lGLEW -lGL -lGLU

CXXINCS = -I../../include

INIT_SHADER = ../../common/InitShader.cpp
EXAMPLELIST = example1 example2 example6

.PHONY: clean

all: $(EXAMPLELIST)

$(EXAMPLELIST):
	g++ -g -O2 $(CXXINCS) $(INIT_SHADER) $@.cpp  $(LDLIBS) -o $@

clean:
	rm $(EXAMPLELIST)
