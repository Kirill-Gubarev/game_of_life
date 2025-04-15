#include "area.h"

#include <stdlib.h>
#include <string.h>

char* area;
char* area_count_alive;

int area_width;
int area_height;
int area_length;

void area_init(int width, int height){
	area_width = width;
	area_height = height;
	area_length = width * height;
	area = calloc(area_length, sizeof(char));
	area_count_alive = calloc(area_length, sizeof(char));
}

void area_term(){
	free(area);
	free(area_count_alive);
}

int area_get_width(){
	return area_width;
}
int area_get_height(){
	return area_height;
}
int area_get_length(){
	return area_length;
}

int wrap_coordinate(int coord, int limit){
	return (coord + limit) % limit;
}

void area_count_alive_add(int x, int y){
	x = wrap_coordinate(x, area_width);
	y = wrap_coordinate(y, area_height);

	area_count_alive[y * area_width + x] += 1;
}
void area_set(int x, int y, char tile){
	x = wrap_coordinate(x, area_width);
	y = wrap_coordinate(y, area_height);

	area[y * area_width + x] = tile;
}
char area_count_alive_get(int x, int y){
	x = wrap_coordinate(x, area_width);
	y = wrap_coordinate(y, area_height);

	return area_count_alive[y * area_width + x];
}
char area_get(int x, int y){
	x = wrap_coordinate(x, area_width);
	y = wrap_coordinate(y, area_height);

	return area[y * area_width + x];
}

void area_count_alive_clear(){
	memset(area_count_alive, 0, area_length);
}
void area_count_alive_add_around(int x, int y){
	area_count_alive_add(x - 1, y - 1);
	area_count_alive_add(x    , y - 1);
	area_count_alive_add(x + 1, y - 1);

	area_count_alive_add(x - 1, y    );
	area_count_alive_add(x + 1, y    );

	area_count_alive_add(x - 1, y + 1);
	area_count_alive_add(x    , y + 1);
	area_count_alive_add(x + 1, y + 1);
}
void tile_update(int x, int y){
	char tile = area_get(x, y);
	int count_alive = area_count_alive_get(x, y);

	if(tile & TILE_ALIVE){
		if(count_alive < 2 || count_alive > 3)
			area_set(x, y, tile & ~TILE_ALIVE | TILE_CHANGED);
	}
	else if(count_alive == 3){
		area_set(x, y, tile | TILE_ALIVE | TILE_CHANGED);
	}
}
void area_update(){
	//count alive tiles
	area_count_alive_clear();
	for(int y = 0; y < area_height; ++y){
		for(int x = 0; x < area_width; ++x){
			char tile = area_get(x, y);
			if(tile & TILE_ALIVE)
				area_count_alive_add_around(x, y);
		}
	}

	//update tiles
	for(int y = 0; y < area_height; ++y){
		for(int x = 0; x < area_width; ++x){
			tile_update(x, y);
		}
	}
}
void area_clear(){
	memset(area, TILE_CHANGED, area_length);
}
void area_rand_fill(double chance){
	for(int y = 0; y < area_height; ++y){
		for(int x = 0; x < area_width; ++x){
			if(((double)rand() / RAND_MAX) <= chance)
				area_set(x, y, TILE_ALIVE | TILE_CHANGED);
		}
	}
}
