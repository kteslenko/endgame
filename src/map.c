#include "map.h"

t_map *new_map(int max_blocks, int coins_count) {
    t_map *map = malloc(sizeof(t_map));

    map->blocks = malloc(sizeof(t_block) * max_blocks);
    map->size = 0;
	map->coins = malloc(sizeof(t_coin) * coins_count);
	map->coins_count = coins_count;

    return map;
}

void clean_map(t_map *map) {
	free(map->blocks);
	free(map->coins);
	free(map);
}

int count_coins(t_map *map) {
	int count = 0;
	
	for (int i = 0; i < map->coins_count; i++) {
		if (!map->coins[i].collected) {
			count++;
		}
	}

	return count;
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

static void add_coins(t_map *map) {
	map->coins[0] = (t_coin){false, {43, 468, 20, 20}};
	map->coins[1] = (t_coin){false, {274, 468, 20, 20}};
	map->coins[2] = (t_coin){false, {396, 404, 20, 20}};
	map->coins[3] = (t_coin){false, {618, 404, 20, 20}};
	map->coins[4] = (t_coin){false, {747, 404, 20, 20}};
	map->coins[5] = (t_coin){false, {1197, 404, 20, 20}};
	map->coins[6] = (t_coin){false, {1256, 404, 20, 20}};
	map->coins[7] = (t_coin){false, {1566, 404, 20, 20}};
	map->coins[8] = (t_coin){false, {1718, 404, 20, 20}};
	map->coins[9] = (t_coin){false, {1964, 404, 20, 20}};
	map->coins[10] = (t_coin){false, {1938, 148, 20, 20}};
	map->coins[11] = (t_coin){false, {1575, 148, 20, 20}};
	map->coins[12] = (t_coin){false, {1046, 84, 20, 20}};
	map->coins[13] = (t_coin){false, {1169, 84, 20, 20}};
	map->coins[14] = (t_coin){false, {1109, 84, 20, 20}};
	map->coins[15] = (t_coin){false, {2348, 212, 20, 20}};
	map->coins[16] = (t_coin){false, {2470, 340, 20, 20}};
	map->coins[17] = (t_coin){false, {2581, 340, 20, 20}};
	map->coins[18] = (t_coin){false, {2707, 532, 20, 20}};
	map->coins[19] = (t_coin){false, {2988, 532, 20, 20}};
	map->coins[20] = (t_coin){false, {3158, 532, 20, 20}};
	map->coins[21] = (t_coin){false, {3943, 532, 20, 20}};
	map->coins[22] = (t_coin){false, {4207, 532, 20, 20}};
	map->coins[23] = (t_coin){false, {4520, 532, 20, 20}};
	map->coins[24] = (t_coin){false, {5085, 532, 20, 20}};
	map->coins[25] = (t_coin){false, {5214, 532, 20, 20}};
	map->coins[26] = (t_coin){false, {5437, 532, 20, 20}};
	map->coins[27] = (t_coin){false, {5651, 532, 20, 20}};
	map->coins[28] = (t_coin){false, {5852, 596, 20, 20}};
	map->coins[29] = (t_coin){false, {6275, 532, 20, 20}};
	map->coins[30] = (t_coin){false, {6425, 532, 20, 20}};
	map->coins[31] = (t_coin){false, {6613, 596, 20, 20}};
	map->coins[32] = (t_coin){false, {6856, 596, 20, 20}};
	map->coins[33] = (t_coin){false, {7189, 532, 20, 20}};
	map->coins[34] = (t_coin){false, {7561, 532, 20, 20}};
	map->coins[35] = (t_coin){false, {7800, 532, 20, 20}};
	map->coins[36] = (t_coin){false, {7974, 532, 20, 20}};
	map->coins[37] = (t_coin){false, {8223, 532, 20, 20}};
	map->coins[38] = (t_coin){false, {8355, 532, 20, 20}};
	map->coins[39] = (t_coin){false, {8858, 468, 20, 20}};
	map->coins[40] = (t_coin){false, {9465, 468, 20, 20}};
	map->coins[41] = (t_coin){false, {9830, 468, 20, 20}};
	map->coins[42] = (t_coin){false, {10222, 468, 20, 20}};
	map->coins[43] = (t_coin){false, {10760, 468, 20, 20}};
	map->coins[44] = (t_coin){false, {10950, 468, 20, 20}};
	map->coins[45] = (t_coin){false, {11253, 468, 20, 20}};
	map->coins[46] = (t_coin){false, {11525, 468, 20, 20}};
	map->coins[47] = (t_coin){false, {11807, 468, 20, 20}};
	map->coins[48] = (t_coin){false, {12201, 340, 20, 20}};
	map->coins[49] = (t_coin){false, {12350, 276, 20, 20}};
	map->coins[50] = (t_coin){false, {12523, 212, 20, 20}};
	map->coins[51] = (t_coin){false, {2836, 340, 20, 20}};
	map->coins[52] = (t_coin){false, {3006, 340, 20, 20}};
	map->coins[53] = (t_coin){false, {3142, 340, 20, 20}};
	map->coins[54] = (t_coin){false, {3364, 276, 20, 20}};
	map->coins[55] = (t_coin){false, {3490, 212, 20, 20}};
	map->coins[56] = (t_coin){false, {3608, 148, 20, 20}};
	map->coins[57] = (t_coin){false, {5519, 276, 20, 20}};
	map->coins[58] = (t_coin){false, {5645, 148, 20, 20}};
	map->coins[59] = (t_coin){false, {5910, 148, 20, 20}};
	map->coins[60] = (t_coin){false, {6250, 148, 20, 20}};
	map->coins[61] = (t_coin){false, {6503, 148, 20, 20}};
	map->coins[62] = (t_coin){false, {6822, 212, 20, 20}};
	map->coins[63] = (t_coin){false, {7036, 84, 20, 20}};
	map->coins[64] = (t_coin){false, {7237, 84, 20, 20}};
	map->coins[65] = (t_coin){false, {7428, 212, 20, 20}};
	map->coins[66] = (t_coin){false, {7612, 84, 20, 20}};
	map->coins[67] = (t_coin){false, {7838, 84, 20, 20}};
	map->coins[68] = (t_coin){false, {8149, 148, 20, 20}};
	map->coins[69] = (t_coin){false, {8579, 148, 20, 20}};
	map->coins[70] = (t_coin){false, {8860, 148, 20, 20}};
	map->coins[71] = (t_coin){false, {9320, 212, 20, 20}};
	map->coins[72] = (t_coin){false, {9365, -172, 20, 20}};
	map->coins[73] = (t_coin){false, {9459, -172, 20, 20}};
	map->coins[74] = (t_coin){false, {9561, -172, 20, 20}};
	map->coins[75] = (t_coin){false, {9641, -171, 20, 20}};
	map->coins[76] = (t_coin){false, {9752, -172, 20, 20}};
	map->coins[77] = (t_coin){false, {9843, -172, 20, 20}};
	map->coins[78] = (t_coin){false, {9934, -171, 20, 20}};
	map->coins[79] = (t_coin){false, {10014, -172, 20, 20}};
	map->coins[80] = (t_coin){false, {10091, -44, 20, 20}};
	map->coins[81] = (t_coin){false, {10181, -44, 20, 20}};
	map->coins[82] = (t_coin){false, {10261, -43, 20, 20}};
	map->coins[83] = (t_coin){false, {10423, -44, 20, 20}};
	map->coins[84] = (t_coin){false, {10513, -43, 20, 20}};
	map->coins[85] = (t_coin){false, {10596, -44, 20, 20}};
	map->coins[86] = (t_coin){false, {10677, -59, 20, 20}};
	map->coins[87] = (t_coin){false, {10830, -43, 20, 20}};
	map->coins[88] = (t_coin){false, {10921, -43, 20, 20}};
	map->coins[89] = (t_coin){false, {11011, -44, 20, 20}};
	map->coins[90] = (t_coin){false, {11090, -43, 20, 20}};
	map->coins[91] = (t_coin){false, {11181, -43, 20, 20}};
	map->coins[92] = (t_coin){false, {11271, -44, 20, 20}};
	map->coins[93] = (t_coin){false, {11351, -43, 20, 20}};
	map->coins[94] = (t_coin){false, {11435, -43, 20, 20}};
	map->coins[95] = (t_coin){false, {11516, -44, 20, 20}};
	map->coins[96] = (t_coin){false, {11595, -43, 20, 20}};
}

t_map *build_level(SDL_Texture **textures) {
    t_map *map = new_map(1000, 97);

	add_coins(map);

	build_block(map, textures[FIRE], 130, 470, 64, 30);

	build_platform(map, textures[GROUND], 0, 500, 5);
	build_platform(map, textures[GROUND], 316, 436, 2);
	build_platform(map, textures[GROUND], 508, 436, 2);

	build_block(map, textures[BUSH], 850, 400, 58, 37);
	build_block(map, textures[TREE1], 920, 305, 120, 134);

	build_platform(map, textures[GROUND], 700, 436, 9);
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
	// new levels
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

	build_platform(map, textures[GROUND], 7736, 116, 2);
	build_platform(map, textures[GROUND], 8056, 180, 2);
	build_platform(map, textures[GROUND], 8568, 180, 1);
	build_platform(map, textures[GROUND], 8824, 180, 1);	
	build_platform(map, textures[GROUND], 7736, 564, 1);
	build_platform(map, textures[GROUND], 7928, 564, 1);
	build_platform(map, textures[GROUND], 8120, 564, 5);
	build_platform(map, textures[GROUND], 8568, 500, 5);
	build_platform(map, textures[GROUND], 8952, 500, 1); //9016 500

	build_platform(map, textures[GROUND], 9016, 500, 20); 
	build_platform(map, textures[GROUND], 9272, 244, 1);
	build_platform(map, textures[DIRT], 9336, 308, 5); 
	build_platform(map, textures[DIRT], 9336, 244, 5); 
	build_platform(map, textures[DIRT], 9336, 180, 11); 
	build_platform(map, textures[DIRT], 9336, 116, 11);
	build_platform(map, textures[DIRT], 9336, 52, 11);
	build_platform(map, textures[DIRT], 9336, -12, 11);
	build_platform(map, textures[DIRT], 9336, -76, 11);
	build_platform(map, textures[GROUND], 9336, -140, 11);
	build_platform(map, textures[DIRT], 9720, 308, 5); 
	build_platform(map, textures[DIRT], 9720, 244, 5); 
	build_platform(map, textures[DIRT], 10040, -12, 4); 
	build_platform(map, textures[DIRT], 10040, 52, 4); 
	build_platform(map, textures[DIRT], 10040, 116, 4); 
	build_platform(map, textures[DIRT], 10040, 180, 4); 
	build_platform(map, textures[DIRT], 10040, 308, 4); 
	build_platform(map, textures[DIRT], 10040, 244, 4); //10360 244

	build_platform(map, textures[GROUND], 10360, 500, 20);
	build_platform(map, textures[DIRT], 10424, 308, 4);
	build_platform(map, textures[DIRT], 10424, 244, 4); 
	build_platform(map, textures[DIRT], 10360, 180, 5); 
	build_platform(map, textures[DIRT], 10360, 116, 5);
	build_platform(map, textures[DIRT], 10360, 52, 5);
	build_platform(map, textures[DIRT], 10360, -12, 5);
	build_platform(map, textures[DIRT], 10744, 308, 7); 
	build_platform(map, textures[DIRT], 10744, 244, 7); 
	build_platform(map, textures[DIRT], 10744, 180, 7); 
	build_platform(map, textures[DIRT], 10744, 116, 7); 
	build_platform(map, textures[DIRT], 10744, 52, 7); 
	build_platform(map, textures[DIRT], 10744, -12, 7); 
	build_platform(map, textures[DIRT], 11192, -12, 6); 
	build_platform(map, textures[DIRT], 11192, 52, 6); 
	build_platform(map, textures[DIRT], 11192, 116, 6); 
	build_platform(map, textures[DIRT], 11256, 180, 5); 
	build_platform(map, textures[DIRT], 11256, 244, 5); 
	build_platform(map, textures[DIRT], 11256, 308, 5); 

	build_platform(map, textures[GROUND], 11704, 500, 3); 
	build_platform(map, textures[GROUND], 11896, 436, 3); 
	build_platform(map, textures[GROUND], 12088, 372, 3); 
	build_platform(map, textures[GROUND], 12280, 308, 2);
	build_platform(map, textures[GROUND], 12408, 244, 3); 
	build_block(map, textures[FIRE], 12536, 220, 64, 30);
	build_block(map, textures[ROCK], 11896, 410, 46, 29);
	build_block(map, textures[ROCK], 12204, 345, 46, 29);
	


    return map;
}
