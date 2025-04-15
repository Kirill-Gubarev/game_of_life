#include "renderer.h"

#include "area.h"

#define NCURSES_WIDECHAR 1
#include <ncursesw/ncurses.h>
#include <locale.h>

void rend_init(){
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	curs_set(0);
}
void rend_term(){
	endwin();
}

void draw(int x, int y, char tile1, char tile2){
	if(tile1 & TILE_ALIVE){
		if(tile2 & TILE_ALIVE){
			mvaddwstr(y, x, L"█");
		}
		else{
			mvaddwstr(y, x, L"▀");
		}
	}
	else if(tile2 & TILE_ALIVE){
		mvaddwstr(y, x, L"▄");
	}
	else{
		mvaddwstr(y, x, L" ");
	}
}
void rend_refresh(){
	int width = area_get_width();
	int height = area_get_height();
	for(int y = 0; y < height; y += 2){
		for(int x = 0; x < width; ++x){
			char tile1 = area_get(x, y);
			char tile2 = area_get(x, y + 1);

			if((tile1 | tile2) & TILE_CHANGED){
				draw(x, y / 2, tile1, tile2);
				area_set(x, y, tile1 & ~TILE_CHANGED);
				area_set(x, y + 1, tile2 & ~TILE_CHANGED);
			}
		}
	}
}

int rend_get_width(){
	return getmaxx(stdscr);
}
int rend_get_height(){
	return getmaxy(stdscr) * 2;
}
