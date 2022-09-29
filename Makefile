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
	LDFLAGS = -Iresource/SDL2/include -Lresource/SDL2/lib -Wl,-rpath,resource/SDL2/lib
	PKGCONF = $(shell pkg-config SDL2_mixer SDL2_image SDL2_ttf --cflags-only-other --libs)
endif

all: $(OUT)

$(OUT): src/*.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(PKGCONF) $(FFLAGS) -o $@ $^

uninstall:
	rm -f $(OUT)

clean:

reinstall: uninstall all
