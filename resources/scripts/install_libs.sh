cd ..

UNAME=$(uname)
RES_DIR=$(pwd)

cd $RES_DIR/libs_sources/SDL
rm -rf build
mkdir build
cd build
if [[ "$UNAME" == "Darwin" ]]; then
	CC=../build-scripts/clang-fat.sh ../configure --prefix=$RES_DIR/SDL --exec-prefix=$RES_DIR/SDL/$UNAME
else
	../configure --prefix=$RES_DIR/SDL --exec-prefix=$RES_DIR/SDL/$UNAME
fi
make -j$(nproc)
make install

cd $RES_DIR/libs_sources/SDL_mixer
rm -rf build
mkdir build
cd build
SDL2_CONFIG=$RES_DIR/SDL/$UNAME/bin/sdl2-config ../configure --prefix=$RES_DIR/SDL_mixer --exec-prefix=$RES_DIR/SDL_mixer/$UNAME
make -j$(nproc)
make install

rm -rf $RES_DIR/SDL/share
rm -rf $RES_DIR/SDL/$UNAME/bin
rm -rf $RES_DIR/SDL/$UNAME/lib/cmake
rm -rf $RES_DIR/SDL/$UNAME/lib/pkgconfig
rm -rf $RES_DIR/SDL_mixer/$UNAME/lib/cmake
rm -rf $RES_DIR/SDL_mixer/$UNAME/lib/pkgconfig
