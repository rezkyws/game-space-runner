
#ifndef Imaniar_S_F_H
#define Imaniar_S_F_H

void load_box();

void cek_box();

bool is_empty_box(addr_map c_box[], int map[MAX_ROW][MAX_COL]);

void load_hscore(); //ditambah

int cek_highscore(int hscore, int score);//ditambah

void write_hscore(int hscore); //ditambah

void move_right_left (char action[],char dir[]);

void idle();

void climb_up();

void climb_dw();

void pause();

#endif
