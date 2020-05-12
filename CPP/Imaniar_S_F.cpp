#include "../LodeRunner12.h"

extern int			state,
					matriksmap[MAX_ROW][MAX_COL],
					k;
extern path			character;
extern addr_char	c_char;
extern board		brd;
extern img			map;
extern addr_map		c_box[5],
					c_ladder;

extern mtrks_lvl mtrks_map;

int m = 1;
int status;
int highscore;

void load_box()
{
	int p = 0;
	while (k > p)
    {
        if (mtrks_map.cur->map[c_box[p].i][c_box[p].j] == 5)
        	draw_obj("box",c_box[p].i,c_box[p].j);
		p++;
    }
}

void cek_box()
{
	if (mtrks_map.cur->map[c_char.pos.i][c_char.pos.j] == 5)
    {
    	play_peti();
        mtrks_map.cur->map[c_char.pos.i][c_char.pos.j] = 0;
		brd.score = brd.score + 50;
        printf("point : %d\n",brd.score);
        printf("life : %d\n",brd.life);
        if(!is_empty_box(c_box, mtrks_map.cur->map))
        {
            mtrks_map.cur->map[c_ladder.i - 1][c_ladder.j]=3;
            mtrks_map.cur->map[c_ladder.i][c_ladder.j]=3;
	        clearviewport();

			setviewport(0, 0, getmaxx(), getmaxy(), 1);

			putimage(0,0,map, COPY_PUT);
			draw_obj("ladder",c_ladder.i-1,c_ladder.j);
			draw_obj("ladder",c_ladder.i,c_ladder.j);
			load_board();
			getimage(0,0,800,600,map);

			swapbuffers();
		}
    }
}

bool is_empty_box(addr_map c_box[], int map[MAX_ROW][MAX_COL]){
	int cur = 0;
	while (cur < 5){
		if (map[c_box[cur].i][c_box[cur].j] == 5) 
			return true;
		cur++;
	}
		
	return false;
}

void load_hscore()
{
    FILE *f = fopen("Library\\highscore.dat", "r");
    highscore =getw(f);
    fclose(f);
    printf("\nread highscore = %d", highscore);

}

void write_hscore(int hscore)
{
	FILE *f = fopen("Library\\highscore.dat", "w");
	putw(hscore,f);
	fclose(f);
}

int cek_highscore(int hscore, int score)
{
    if (hscore<score){
        write_hscore(score);
        return (score);
    } else{
        return (hscore);}
}

void move_right_left (char action[],char dir[]) {
	if(m > 8)
		m = 1;
	sprintf(character.path_img,"%s\\%s\\%d.gif", action, dir, m);
	m++;
}

void idle()
{
	if(m > 8)
	{
		m = 1;
	}
	if (((c_char.x>(c_char.pos.j*30)-18 && mtrks_map.cur->map[c_char.pos.i][c_char.pos.j-1]!=4 
		&& mtrks_map.cur->map[c_char.pos.i][c_char.pos.j] == 4) 
		|| (mtrks_map.cur->map[c_char.pos.i][c_char.pos.j-1]==4 
		&& mtrks_map.cur->map[c_char.pos.i][c_char.pos.j] == 4) 
		|| (c_char.x<(c_char.pos.j*30)+18 && mtrks_map.cur->map[c_char.pos.i][c_char.pos.j+1]!=4 
		&& mtrks_map.cur->map[c_char.pos.i][c_char.pos.j] == 4)) && c_char.y==c_char.pos.i*30)
	{
		sprintf(character.path_img,"Rope\\Right\\2.gif");
	}else if(mtrks_map.cur->map[c_char.pos.i][c_char.pos.j] == 3 || (mtrks_map.cur->map[c_char.pos.i][c_char.pos.j]!=3 && c_char.y > c_char.pos.i*30))
	{
		sprintf(character.path_img,"Climb\\1.gif");
	}else
	{
		if (character.dir == 'R')
		{
			sprintf(character.path_img,"Idle\\Right\\%d.gif", m);
		}else
		{
			sprintf(character.path_img,"Idle\\Left\\%d.gif", m);
		}

	}

//	delay(50);
	m++;
}

void climb_up()
{
	if(m > 8)
	{
		m = 1;
	}
	sprintf(character.path_img,"Climb\\%d.gif", m);
	m++;
}

void climb_dw()
{
	if(m < 1 || m > 8)
	{
		m = 8;
	}
	sprintf(character.path_img,"Climb\\%d.gif", m);
	m--;
	if(m == 0)
	{
		m = 1;
	}
}

void pause()
{
    printf("\npause");
    if (state == STATE_PAUSE)
    {
        state=status;
        printf("\nunpause");
    }
    else
    {
        status=state;
        state = STATE_PAUSE;
        setviewport(0, 0, getmaxx(), getmaxy(), 1);
        putimage(0,0,map, COPY_PUT);
        draw_obj_mov(character.path_img,c_char.x,c_char.y);
        setviewport(0, 0, getmaxx(), getmaxy(), 1);
        setcolor(RED);

        setfillstyle(SOLID_FILL, BLACK);
        rectangle(getmaxx()/2-151, getmaxy()/2-80, getmaxx()/2+151, getmaxy()/2+77);
        floodfill(getmaxx()/2, getmaxy()/2, RED);

        settextstyle(BOLD_FONT,HORIZ_DIR, 8);
        outtextxy(getmaxx()/2-141,getmaxy()/2-70,"PAUSED");
        settextstyle(COMPLEX_FONT,HORIZ_DIR, 2);
        outtextxy(getmaxx()/2-126,getmaxy()/2+15,"Press 'P' to Continue");
        outtextxy(getmaxx()/2-126,getmaxy()/2+41,"Press 'Enter' to Menu");

        swapbuffers();
        delay(100);
    }

    printf("test");
}

