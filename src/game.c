#include "game.h"

#include "renderer.h"
#include "area.h"
#include "tps_controller.h"

#define NCURSES_WIDECHAR 1
#include <ncursesw/ncurses.h>
#include <pthread.h>
#include <time.h>

void game_init(){
	area_init(rend_get_width(), rend_get_height());
	tps_init();
}

void game_term(){
	area_term();
}

char ch = 0;
char is_paused = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void game_step(){
	area_update();
	rend_refresh();
}
void* game_update(){
	while (ch != 'q') {
		tps_delay();
		if(!is_paused){
			pthread_mutex_lock(&mutex);
			game_step();
			pthread_mutex_unlock(&mutex);
		}
	}
	return NULL;
}

void game_run(){
	pthread_t game_update_thread;
	if (pthread_create(&game_update_thread, NULL, game_update, NULL) != 0) {
		perror("pthread_create");
		return;
	}
	pthread_detach(game_update_thread);

	while ((ch = getch()) != 'q') {
		switch(ch){
			case 'c':
				pthread_mutex_lock(&mutex);
				area_clear();
				rend_refresh(); 
				pthread_mutex_unlock(&mutex);
			break;
			case 'r':
				pthread_mutex_lock(&mutex);
				area_rand_fill(0.05); 
				rend_refresh();
				pthread_mutex_unlock(&mutex);
			break;
			case ' ':
			case 'p': is_paused = !is_paused; break;
			case '+':
			case '=': tps_reduce_delay(); break;
			case '-':
			case '_': tps_increase_delay(); break;
			case 'u': if(is_paused) game_step(); break;
		}
		napms(1000 / 60);
	}
}
