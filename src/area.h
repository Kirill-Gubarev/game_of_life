#pragma once

#define TILE_ALIVE		0x01
#define TILE_CHANGED	0x02

void area_init(int width, int height);
void area_term();

int area_get_width();
int area_get_height();
int area_get_length();

void area_set(int x, int y, char ch);
char area_get(int x, int y);

void area_update();
void area_clear();
void area_rand_fill(double chance);
