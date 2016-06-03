OSNAME := $(shell uname -s)

ifeq ($(OSNAME),Darwin)
    OS=osx
    CC=clang++
	LIB_SUFFIX  := dylib
else
    OS          := linux
    CC          := g++
	LIB_SUFFIX  := so
endif

SPACE 			 :=
SPACE            +=
CXXFLAGS         := -g -std=c++11 -fPIC
INCLUDES         := -Ikhronos_registry -Isrc/common

LIB_POSTFIX      := -stream
LIB_VERSION      := 0.0.1

EGL_LIB_BASENAME := EGL$(LIB_POSTFIX)
EGL_LIB_NAME     := lib$(EGL_LIB_BASENAME).$(LIB_SUFFIX).$(LIB_VERSION)

HEADERS          := src/egls.h

all: $(EGL_LIB_NAME) examples


$(EGL_LIB_NAME): egl.o
	$(CC) -shared egl.o -o $(EGL_LIB_NAME)
	ln -sf $(EGL_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 4, $(subst ., ,$(EGL_LIB_NAME))))
	ln -sf $(EGL_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 3, $(subst ., ,$(EGL_LIB_NAME))))
	ln -sf $(EGL_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 2, $(subst ., ,$(EGL_LIB_NAME))))

egl.o: src/egl.cpp $(HEADERS)
	$(CC) -c $(CXXFLAGS) $(INCLUDES) src/egl.cpp


examples: examples/simpleegl.cpp $(EGL_LIB_NAME)
	$(CC) $(CXXFLAGS) $(INCLUDES) examples/simpleegl.cpp -o simpleegl -L. -l$(EGL_LIB_BASENAME)


clean:
	rm *.o
	rm $(EGL_LIB_NAME)*
	rm simpleegl




