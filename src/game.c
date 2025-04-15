#include "game.h"

#include "renderer.h"
#include "area.h"

#include <ncursesw/ncurses.h>

void game_init(){
	area_init(rend_get_width(), rend_get_height());
}
void game_term(){
	area_term();
}

void game_run(){
	char ch;
	while((ch = getch()) != 'q'){
		switch(ch){
			case 'c':
				area_clear();
			break;
			case 'r':
				area_rand_fill(0.05);
			break;
			case 'u':
				area_update();
			break;
		}
		rend_refresh();
	}
}
