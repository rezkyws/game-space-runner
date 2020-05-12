#include "../LodeRunner12.h"

extern int			state,
					matriksmap[MAX_ROW][MAX_COL],
					k;
extern path			character,
					path_enemy;
extern addr_char	c_char, 
					c_enemy[3];
extern board		brd;
extern head_queue	lubang;
extern img			map;
extern imgsize		size;

addr_map	c_box[5],
			c_ladder,
			t_c_char,
			t_c_enm[3];

extern mtrks_lvl mtrks_map;

int e=0;

void maps(int i, int j)
{
	switch(mtrks_map.cur->map[i][j])
    {
        case 0 :{
			break;//elemen kosong
		}
        case 1 :{
            draw_obj("brick",i,j);
            break;
        }
        case 2 :{
            draw_obj("hard_brick",i,j);
            break;
        }
        case 3 :{
            draw_obj("ladder",i,j);
            break;
        }
        case 4 :{
            draw_obj("rope",i,j);
            break;
        }
        case 5 :{
        	c_box[k].i = i;
        	c_box[k].j = j;
        	k++;
			break;
		}
        case 6 :{
            t_c_char.i = i;
            t_c_char.j = j;
            mtrks_map.cur->map[i][j] = 0;
            break;
        }
        case 7 :{
            c_ladder.i = i;
            c_ladder.j = j;
            mtrks_map.cur->map[i][j] = 0;
            break;
        }
        case 8 :{
            t_c_enm[e].i = c_enemy[e].pos.i = i;
            t_c_enm[e].j = c_enemy[e].pos.j = j;
            c_enemy[e].y = i*30;
            c_enemy[e].x = j*30;
            mtrks_map.cur->map[i][j] = 0;
            e++;
            sprintf(path_enemy.path_img,"Enemy\\alien_egg.gif");
            break;
        }
    }
}

void load_map(){
	char path[40];
	int i=0, j, m =1;
    while(i<20){
        j=0;
        printf("\n");
		while(j<26){
            printf("%d ",mtrks_map.cur->map[i][j]);
            maps(i, j);
        	j++;
    	}
    	i++;
    	// loading
		if(m > 10)
			m = 1;
        setactivepage(abs(getactivepage()-1));
        sprintf(path,"Image\\Loading\\%d.bmp", m);
        readimagefile(path, 0,0,800,600);
		m++;
        setactivepage(1-getactivepage());
	}
}

void draw_obj(char obj[],int i,int j) {
	char path[40];
	sprintf(path,"Image\\Map\\%s.gif", obj);
	readimagefile(path,10+30*j,30*i,39+30*j,29+30*i);
}

void draw_obj_mov (char obj[],int x,int y) {
	char path[40];
	sprintf(path,"Image\\Character\\%s", obj);
	readimagefile(path,10+x,y,39+x,29+y);
}

img alloc_img () {
	imgsize size = imagesize(0,0,800,600);
	return malloc(size);
}

void render ()
{
	clearviewport();
	setviewport(0, 0, getmaxx(), getmaxy(), 1);
	
	if (state == STATE_MENU) {
        load_hscore();
		reset (is_die (c_char.pos.i,c_char.pos.j,mtrks_map.cur->map) || state == STATE_MENU);
		free(map);
		menu();
	}else if (state != STATE_PAUSE){
		stop_next_level();
		if (state != STATE_START){
			game_over (is_game_over (brd.life),is_die (c_char.pos.i,c_char.pos.j,mtrks_map.cur->map),brd.score,map);
			reset (is_die (c_char.pos.i,c_char.pos.j,mtrks_map.cur->map));
		}
		if (state == STATE_START) {
			swapbuffers();
//			bgm();
            readimagefile("Image\\Background\\2.bmp",10, 0, 790, 510);
			load_map();
			
		    map = alloc_img();
		    
		    c_char.pos.i = t_c_char.i;
		    c_char.pos.j = t_c_char.j;
		    c_char.x = t_c_char.j*30;
		    c_char.y = t_c_char.i*30;
		    
		    state = STATE_PLAY;
		}else if (state == STATE_PLAY || state == STATE_FALL){
		    putimage(0,0,map, COPY_PUT);
		}else if (state == STATE_RESTORE){
			putimage(0,0,map, COPY_PUT);
			draw_obj("brick",lubang.front->info.brick.i,lubang.front->info.brick.j);
            deque(&lubang);
			state = STATE_PLAY;
		}
		
		load_board();
        getimage(0,0,800,600,map);
		load_box();
		
		if (state != STATE_RESTORE) 
			draw_obj_mov(character.path_img,c_char.x,c_char.y);
			
		draw_obj_mov(path_enemy.path_img,c_enemy[0].x,c_enemy[0].y);
		draw_obj_mov(path_enemy.path_img,c_enemy[1].x,c_enemy[1].y);
		draw_obj_mov(path_enemy.path_img,c_enemy[2].x,c_enemy[2].y);
		
		swapbuffers();	
		delay(50);
	}
}
