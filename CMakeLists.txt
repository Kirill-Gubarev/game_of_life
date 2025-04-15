cmake_minimum_required(VERSION 3.28)
project(game_of_life LANGUAGES C)

add_executable(${PROJECT_NAME}
	src/main.c
	src/renderer.c			src/renderer.h
	src/game.c				src/game.h
	src/area.c				src/area.h
)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} ncursesw)
