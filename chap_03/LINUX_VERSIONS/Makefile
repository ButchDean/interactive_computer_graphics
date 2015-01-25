LDLIBS = -lglut -lGLEW -lGL -lGLU

CXXINCS = -I../../include

INIT_SHADER = ../../common/InitShader.cpp
INIT_SHADER_OBJ = ../../common/InitShader.o
EXAMPLELIST = $(wildcard *.cpp)
TARGETS = $(basename $(EXAMPLELIST))

.PHONY: clean cleanall

all: $(TARGETS)

$(TARGETS): $(INIT_SHADER_OBJ)
	g++ -g -O2 $(CXXINCS) $(INIT_SHADER_OBJ) $@.cpp $(LDLIBS) -o $@
	
$(INIT_SHADER_OBJ): $(INIT_SHADER)
	g++ -c -Wall $(INIT_SHADER) -o $(INIT_SHADER_OBJ)

clean:
	rm $(TARGETS)
	
cleanall:
	rm $(INIT_SHADER_OBJ) $(TARGETS)
