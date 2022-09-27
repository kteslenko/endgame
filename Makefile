CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
UNAME = $(shell uname)
LDFLAGS = -Wl,-rpath,resources/SDL/$(UNAME)/lib -Wl,-rpath,resources/SDL_mixer/$(UNAME)/lib
INC_DIRS = -Iinc -Iresources/SDL/include/SDL2 -Iresources/SDL_mixer/include/SDL2
LIB_DIRS = -Lresources/SDL/$(UNAME)/lib -Lresources/SDL_mixer/$(UNAME)/lib
LIBS = -lSDL2 -lSDL2_mixer

OUT = endgame

all: $(OUT)

$(OUT): src/*.c
	$(CC) $(CFLAGS) $(INC_DIRS) $(LIB_DIRS) $(LDFLAGS) $(LIBS) -o $@ $^

uninstall:
	rm -f $(OUT)

clean:

reinstall: uninstall all
