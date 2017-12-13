CFLAGS+=-O3  -mfpu=vfp -mfloat-abi=hard -Wall
LDFLAGS+=-lsigil -lGLESv2
INCLUDES+=-I ~/Library/framework/sigil-vc2015-win64/include
LIBS+=-L/opt/vc/lib
SRC= main.cpp
BIN=input

all: $(SRC)
	$(CXX) -o $(BIN) $(SRC) $(CFLAGS) $(INCLUDES) $(LIBS) $(LDFLAGS)

clean:
	-rm $(BIN)
