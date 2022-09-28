CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -Iinc -lm

OUT = endgame

all: $(OUT)

$(OUT): src/*.c
	$(CC) $(CFLAGS) `pkg-config sdl2 SDL2_mixer SDL2_image SDL2_ttf --cflags --libs` -o $@ $^

uninstall:
	rm -f $(OUT)

clean:

reinstall: uninstall all
