#ifndef GAME_H
#define GAME_H

#include "matrix.h"
#include "config.h"

/* Game states */
#define GAME_STOPPED 0
#define GAME_RUNNING 1
#define GAME_PAUSED  2
#define GAME_OVER    3

/* Game outcome */
#define OUTCOME_VICTORY 0
#define OUTCOME_DEFEAT  1

/* Playground */
#define FIELD_EMPTY       0
#define FIELD_FLAG_OFF  (-1)
#define FIELD_FLAG_ON   (-2)
#define FIELD_REVEALED  (-3)
#define FIELD_MULTIPLE  (-4)
#define FIELD_MINE        9

struct game_state {
	int state;
	int outcome;
	int fields_to_reveal;
	int fields_revealed;
};

struct playground {
	struct matrix *surface;
	struct matrix *minefield;
};

struct game {
	struct game_state game_state;
	struct config config;
	struct playground playground;
};

void game_init(struct game *game);
void game_reinit(struct game *game);
void game_destroy(struct game *game);

struct game_state *game_state_get(struct game *game);

struct difficulty *game_config_difficulty_get(struct game *game);
void game_config_difficulty_set(struct game *game, struct difficulty *difficulty);
struct controls *game_config_controls_get(struct game *game);
void game_config_controls_set(struct game *game, struct controls *controls);

/*
 * Updates game_state
 * Returns:
 * 	1-8: number of mines around field
 * 	9: player hit a mine
 * 	-1: Field is already revealed
 */
int game_playground_reveal(struct game *game, int row, int column);
void game_playground_toggle_flag(struct game *game, int row, int column);

#endif /* GAME_H */
