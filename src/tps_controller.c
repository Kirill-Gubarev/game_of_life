#include "tps_controller.h"

#include <time.h>

double tps = 8;
int tick_delay_ms = 0;
struct timespec last_time;

void tick_delay_ms_update(){
	tick_delay_ms = (int)(1000.0 / tps);
}

void tps_init(){
	clock_gettime(CLOCK_MONOTONIC, &last_time);
	tick_delay_ms_update();
}

void tps_delay(){
	struct timespec current_time;
	clock_gettime(CLOCK_MONOTONIC, &current_time);

	long elapsed_ms = (current_time.tv_sec - last_time.tv_sec) * 1000
					 + (current_time.tv_nsec - last_time.tv_nsec) / 1000000;
	
	if (elapsed_ms < tick_delay_ms) {
		long remaining_ms = tick_delay_ms - elapsed_ms;
		struct timespec remaining_time = {
			.tv_sec = remaining_ms / 1000,
			.tv_nsec = (remaining_ms % 1000) * 1000000
		};
		nanosleep(&remaining_time, NULL);
	}

	long new_nsec = last_time.tv_nsec + (tick_delay_ms % 1000) * 1000000;
	long new_sec = last_time.tv_sec + (tick_delay_ms / 1000) + (new_nsec / 1000000000);
	new_nsec %= 1000000000;

	last_time.tv_sec = new_sec;
	last_time.tv_nsec = new_nsec;
}

void tps_increase_delay(){
	if(tps <= 1.0) return;
	tps /= 2;
	tick_delay_ms_update();
}

void tps_reduce_delay(){
	if(tps >= 256) return;
	tps *= 2;
	tick_delay_ms_update();
}
