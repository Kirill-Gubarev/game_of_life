#include "renderer.h"
#include "game.h"

#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	rend_init();
	game_init();
	game_run();
	game_term();
	rend_term();
	return 0;
}
