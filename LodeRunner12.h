
#ifndef Lode_Runner_12_H
#define Lode_Runner_12_H

/* 
 * header 
 */
#include <stdio.h> 
#include <stdbool.h> 
#include <stdlib.h>
#include <malloc.h> 
#include <graphics.h>
#include <string.h>
#include <time.h>

/* 
 * window game
 */
#define MAX_WIDTH	(800)
#define MAX_HEIGHT	(600)
#define CENTER_X	((getmaxwidth()/2)-400)
#define CENTER_Y	((getmaxheight()/2)-300)

/* 
 * Ukuran matriks
 */
#define MAX_ROW	(20)
#define MAX_COL	(26)

/* 
 * Keadaan saat 
 */
#define STATE_MENU		0 //-1
#define STATE_START		1 //0
#define STATE_PLAY		2 //1
#define STATE_FALL		3 //2
#define STATE_RESTORE	4 //3
#define STATE_PAUSE		5 //4

/* 
 * Arah karakter
 */
#define DIR_RIGHT	'R'
#define DIR_LEFT	'L'

/*
 * struktur data
 */
typedef	void	*img;
typedef unsigned long imgsize;

typedef struct 	taddr_map{
        int 	i,
        		j;
} addr_map;

typedef struct 		taddr_char{
        addr_map	pos;
		int 		x,
        			y;
} addr_char;

typedef struct 	tboard{
        int 	level,
        		score,
        		life;
}board;

typedef	struct	tpath{
		char	path_img[40],
				dir;
}path;

typedef int 	matriks[MAX_ROW][MAX_COL];
typedef struct 	lvl *addr_lvl;
typedef struct 	lvl {
		matriks  map;
		addr_lvl next;
} level;

struct mtrks_lvl {
	addr_lvl first;
	addr_lvl cur;
};

/* -------------------- Queue ------------------- */
typedef struct 		tqueue{
		addr_map	brick;
        time_t		start,
        			taken;
        clock_t		clock_;
}queue;

typedef struct list_queue *addr_que;
struct list_queue{
    queue 	 info;
    addr_que next;
};

struct head_queue{
    addr_que front;
    addr_que rear;
};

/* ----------------- A Star ADT ----------------- */
typedef struct{
    addr_map pos;
	addr_map parent;
    double f;
	double g;
}elmt_list;

typedef struct list_grid *addr_ptr;
struct list_grid{
    elmt_list info;
    addr_ptr  next;
};

/* 
 * header kelompok
 */
#include "Header\\Imaniar_S_F.h"
#include "Header\\Luthfi_A.h"
#include "Header\\Rezky_W_S.h"
#include "Header\\Rendi_K_A.h"
#include "Header\\Satria_N_B.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

//isUlang(isMati()) mengganti var ulang dan mati

//isEmptyBox() mengganti var box

#endif
