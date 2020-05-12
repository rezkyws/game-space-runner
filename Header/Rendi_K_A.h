
#ifndef Rendi_K_A_H
#define Rendi_K_A_H

void window();

void load_board();

bool is_die (int i, int j, int matriksmap[MAX_ROW][MAX_COL]);

bool is_game_over (int life);

void reset (bool die);

void game_over (bool g_over, bool die, int score, img map);

void load_matriksmap();

void menu();

void bgm();

void play_fall();

void stop_fall();

void play_peti();

void play_death();

void play_gameover();

void play_next_level();

void stop_next_level();

void play_explosion();

#endif
