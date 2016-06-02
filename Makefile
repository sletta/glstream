OSNAME := $(shell uname -s)

ifeq ($(OSNAME),Darwin)
    OS=osx
    CC=clang++
	LIB_SUFFIX  = dylib
else
    OS          = linux
    CC          = g++
	LIB_SUFFIX  = so
endif

SPACE 			 :=
SPACE            +=
CXXFLAGS         = -g -std=c++11 -stdlib=libc++
INCLUDES         = -Ikhronos_registry -Isrc/common

LIB_POSTFIX      = -stream

EGL_LIB_BASENAME = EGL$(LIB_POSTFIX)
EGL_LIB_NAME     = lib$(EGL_LIB_BASENAME).$(LIB_SUFFIX)

all: $(EGL_LIB_NAME) examples


$(EGL_LIB_NAME): egl.o
	$(CC) -shared egl.o -o $(EGL_LIB_NAME)

egl.o: src/egl.cpp
	$(CC) -c $(CXXFLAGS) $(INCLUDES) src/egl.cpp


examples: examples/simpleegl.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) examples/simpleegl.cpp -o simpleegl -L. -l$(EGL_LIB_BASENAME)


clean:
	rm *.o
	rm $(EGL_LIB_NAME)*
	rm simpleegl




