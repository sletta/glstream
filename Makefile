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

SPACE 			    :=
SPACE               +=

# GLSTREAM_LOGGING means: 1=warn, 2=info/warn, 3=debug/info/warn
DEFINES             := -DGLSTREAM_LOGGING=3
CXXFLAGS            := -g -std=c++11 -fPIC $(DEFINES)
INCLUDES            := -Ikhronos_registry -Isrc

LIB_VERSION         := 0.0.1

CLIENT_LIB_BASENAME := glstream
CLIENT_LIB_NAME     := lib$(CLIENT_LIB_BASENAME).$(LIB_SUFFIX).$(LIB_VERSION)

SERVER_LIB_BASENAME := glstreamserver
SERVER_LIB_NAME     := lib$(SERVER_LIB_BASENAME).$(LIB_SUFFIX).$(LIB_VERSION)

HEADERS             := src/egls.h \
					   src/logging.h \
					   src/server.h \
					   src/transport.h \


# Toplevel build
all: $(CLIENT_LIB_NAME) $(SERVER_LIB_NAME) simpleegl exampleserver



# Object files..
egl.o: src/egl.cpp $(HEADERS)
	$(CC) -c $(CXXFLAGS) $(INCLUDES) src/egl.cpp

transport.o: src/transport_uds.cpp $(HEADERS)
	$(CC) -c $(CXXFLAGS) $(INCLUDES) src/transport_uds.cpp -o transport.o

server.o: src/server.cpp $(HEADERS)
	$(CC) -c $(CXXFLAGS) $(INCLUDES) src/server.cpp -o server.o



# The libraries we're generating..
$(SERVER_LIB_NAME): transport.o server.o
	$(CC) -shared transport.o server.o -o $(SERVER_LIB_NAME)
	ln -sf $(SERVER_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 4, $(subst ., ,$(SERVER_LIB_NAME))))
	ln -sf $(SERVER_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 3, $(subst ., ,$(SERVER_LIB_NAME))))
	ln -sf $(SERVER_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 2, $(subst ., ,$(SERVER_LIB_NAME))))


$(CLIENT_LIB_NAME): egl.o transport.o
	$(CC) -shared egl.o transport.o -o $(CLIENT_LIB_NAME)
	ln -sf $(CLIENT_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 4, $(subst ., ,$(CLIENT_LIB_NAME))))
	ln -sf $(CLIENT_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 3, $(subst ., ,$(CLIENT_LIB_NAME))))
	ln -sf $(CLIENT_LIB_NAME) $(subst $(SPACE),.,$(wordlist 1, 2, $(subst ., ,$(CLIENT_LIB_NAME))))



# Examples
simpleegl: examples/simpleegl.cpp $(CLIENT_LIB_NAME) $(SERVER_LIB_NAME)
	$(CC) $(CXXFLAGS) $(INCLUDES) examples/simpleegl.cpp -o simpleegl -L. -l$(CLIENT_LIB_BASENAME)

exampleserver: examples/exampleserver.cpp $(CLIENT_LIB_NAME) $(SERVER_LIB_NAME)
	$(CC) $(CXXFLAGS) $(INCLUDES) examples/exampleserver.cpp -o exampleserver -L. -l$(SERVER_LIB_BASENAME)


clean:
	rm -f *.o
	rm -f lib*
	rm -f simpleegl
	rm -rf exampleserver




