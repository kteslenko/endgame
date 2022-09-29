CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinc -lm
OUT = endgame
UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
	FFLAGS = -F resource/frameworks -rpath resource/frameworks \
		 -framework SDL2 \
		 -framework SDL2_image \
		 -framework SDL2_ttf \
		 -framework SDL2_mixer
else
	PKGCONF = $(shell pkg-config sdl2 SDL2_mixer SDL2_image SDL2_ttf --cflags --libs)
endif

all: $(OUT)

$(OUT): src/*.c
	$(CC) $(CFLAGS) $(PKGCONF) $(FFLAGS) -o $@ $^

uninstall:
	rm -f $(OUT)

clean:

reinstall: uninstall all
