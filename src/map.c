#include "map.h"

t_map *new_map(int max_blocks) {
    t_map *map = malloc(sizeof(t_map));

    map->blocks = malloc(sizeof(t_block) * max_blocks);
    map->size = 0;

    return map;
}

void push_block(t_map *map, t_block block) {
    map->blocks[map->size] = block;
    map->size++;
}

void build_platform(t_map *map, SDL_Texture *texture, float x, float y, int len) {
    t_block block = {true, {x, y, 64, 64}, texture};

    for (int i = 1; i <= len; i++) {
        push_block(map, block);
        block.rect.x += 64;
	}
}

void build_block(t_map *map, SDL_Texture *texture, float x, float y, float w, float h) {
    t_block block = {false, {x, y, w, h}, texture};
    push_block(map, block);
}

t_map *build_level(SDL_Texture **textures) {
    t_map *map = new_map(1000);

	build_block(map, textures[FIRE], 130, 470, 64, 30);

	build_platform(map, textures[GROUND], 0, 500, 5);
	build_platform(map, textures[GROUND], 316, 436, 2);
	build_platform(map, textures[GROUND], 508, 436, 2);

	build_block(map, textures[BUSH], 850, 400, 58, 37);
	build_block(map, textures[TREE1], 920, 305, 120, 134);

	build_platform(map, textures[GROUND], 700, 436, 9);
	build_platform(map, textures[DIRT], 1148, 308, 2);
	build_platform(map, textures[DIRT], 1148, 244, 2);
	build_platform(map, textures[DIRT], 1148, 180, 2);
	build_platform(map, textures[GROUND], 1020, 116, 4);

	build_platform(map, textures[GROUND], 1276, 436, 5);
	build_block(map, textures[ROCK], 1748, 410, 46, 29);
	build_block(map, textures[TREE2], 1756, 275, 152, 160);

	build_platform(map, textures[GROUND], 1660, 436, 5);
	build_platform(map, textures[GROUND], 1980, 372, 2);
	build_platform(map, textures[GROUND], 2108, 308, 1);

	build_block(map, textures[BUSH], 2281, 207, 58, 37);

	build_platform(map, textures[GROUND], 2172, 244, 3);
	build_platform(map, textures[GROUND], 2428, 372, 2);
	build_platform(map, textures[GROUND], 1852, 180, 3);
	build_platform(map, textures[GROUND], 1660, 180, 2);
	build_platform(map, textures[GROUND], 1532, 180, 1);
	build_platform(map, textures[GROUND], 1276, 116, 3);
	
	build_platform(map, textures[GROUND], 2428, 372, 3);
	build_platform(map, textures[DIRT], 2556, 436, 1);
	build_platform(map, textures[DIRT], 2556, 500, 1);
	build_platform(map, textures[DIRT], 2556, 564, 1);
	build_platform(map, textures[DIRT], 2556, 628, 1);
	build_platform(map, textures[DIRT], 2556, 692, 1);
	build_platform(map, textures[GROUND], 2748, 372, 4);
	build_platform(map, textures[GROUND], 3068, 372, 2);
	build_platform(map, textures[GROUND], 3260, 308, 2);
	build_platform(map, textures[GROUND], 3388, 244, 2);
	build_platform(map, textures[GROUND], 3580, 180, 1);
	build_platform(map, textures[GROUND], 2684, 564, 2);
	build_platform(map, textures[GROUND], 2876, 564, 3);
	build_platform(map, textures[GROUND], 3128, 564, 9);

	build_block(map, textures[BENCH], 3904, 522, 86, 41); 
	build_block(map, textures[LOGS], 4154, 515, 92, 51);
	build_block(map, textures[POOL], 4494, 470, 89, 93);
	build_platform(map, textures[GROUND], 3704, 564, 20);

	build_platform(map, textures[GROUND], 5048, 564, 1);
	build_platform(map, textures[GROUND], 5176, 564, 1);
	build_platform(map, textures[GROUND], 5368, 564, 1);
	build_platform(map, textures[GROUND], 5496, 308, 1);
	build_platform(map, textures[GROUND], 5624, 180, 1);
	build_platform(map, textures[GROUND], 5880, 180, 1);
	build_platform(map, textures[GROUND], 6072, 180, 4);
	build_platform(map, textures[GROUND], 5624, 564, 1);
	build_platform(map, textures[GROUND], 5752, 628, 3);
	build_platform(map, textures[GROUND], 6200, 564, 2); //top 6392 180 //bottom 6392 564

	build_platform(map, textures[GROUND], 6392, 180, 3);
	build_platform(map, textures[GROUND], 6712, 244, 2);
	build_platform(map, textures[GROUND], 6956, 116, 2);
	build_platform(map, textures[GROUND], 7212, 116, 1);
	build_platform(map, textures[GROUND], 7404, 244, 1);
	build_platform(map, textures[GROUND], 7596, 116, 1);
	build_platform(map, textures[GROUND], 6392, 564, 1);
	build_platform(map, textures[GROUND], 6520, 628, 3);
	build_platform(map, textures[GROUND], 6776, 628, 3);
	build_platform(map, textures[GROUND], 7096, 564, 2);
	build_platform(map, textures[GROUND], 7480, 564, 3); //top 7736 116 bottom 7736 564

	build_platform(map, textures[GROUND], 7736, 116, 2);
	build_platform(map, textures[GROUND], 8056, 180, 2);
	build_platform(map, textures[GROUND], 8568, 180, 1);
	build_platform(map, textures[GROUND], 8824, 180, 1);	
	build_platform(map, textures[GROUND], 7736, 564, 1);
	build_platform(map, textures[GROUND], 7928, 564, 1);
	build_platform(map, textures[GROUND], 8120, 564, 5);
	build_platform(map, textures[GROUND], 8568, 500, 5);
	build_platform(map, textures[GROUND], 8952, 500, 1);

    return map;
}
