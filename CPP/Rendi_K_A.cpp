#include "../LodeRunner12.h"

extern int			state,
					highscore,
					k,e,
					matriksmap[MAX_ROW][MAX_COL];
extern path			character;
extern addr_char	c_enemy[3];
extern board		brd;
extern head_queue	lubang;
extern img			map;
extern addr_map		c_box[5],
					c_ladder,
					t_c_char,
					t_c_enm[3];

extern mtrks_lvl mtrks_map;

void window()
{
    initwindow(MAX_WIDTH, MAX_HEIGHT, "Space Runner",CENTER_X,CENTER_Y);
}

void load_board()
{
	char poin[10];
    setcolor(WHITE);
    //diubah semua
    settextstyle(BOLD_FONT,HORIZ_DIR, 1);
    sprintf(poin,"Highscore : %d", highscore);
    outtextxy(50,550,poin);
    sprintf(poin,"Score : %d", brd.score);
    outtextxy(270,550,poin);
    sprintf(poin,"Level : %d", brd.level+1);
    outtextxy(450,550,poin);
    sprintf(poin,"Life : %d", brd.life);
    outtextxy(650,550,poin);

}

bool is_die (int i, int j, int matriksmap[MAX_ROW][MAX_COL])
{
	return ((matriksmap[i][j] == 1) 
		|| (i == c_enemy[0].pos.i && j == c_enemy[0].pos.j) 
		|| (i == c_enemy[1].pos.i && j == c_enemy[1].pos.j) 
		|| (i == c_enemy[2].pos.i && j == c_enemy[2].pos.j));
}

bool is_game_over (int life)
{
	return (life < 2);
}

void reset(bool die)
{
	int cur;
	if (die && state != STATE_RESTORE) {
    	//reset box
        for(cur = 0; cur < 4; cur++)
        	mtrks_map.cur->map[c_box[cur].i][c_box[cur].j] = 5;
        for(cur = 0; cur < 3; cur++)
        	mtrks_map.cur->map[t_c_enm[cur].i][t_c_enm[cur].j] = 8;
        mtrks_map.cur->map[t_c_char.i][t_c_char.j] = 6;
        mtrks_map.cur->map[c_ladder.i][c_ladder.j] = 7;
        k = 0;
        e = 0;
    }
}

void game_over (bool g_over, bool die, int score, img map)
{
	if (die && state != STATE_RESTORE) {
		if (g_over) {
	    	setcolor(RED);
	
			setfillstyle(SOLID_FILL, BLACK);
			rectangle(getmaxx()/2-245, getmaxy()/2-80, getmaxx()/2+245, getmaxy()/2+10);
			floodfill(getmaxx()/2, getmaxy()/2, RED);
	        
			highscore=cek_highscore(highscore,brd.score);
			settextstyle(BOLD_FONT,HORIZ_DIR, 8);
			outtextxy(getmaxx()/2-235,getmaxy()/2-70,"Game Over!");
			state = STATE_MENU;
			play_gameover();
			swapbuffers();
			delay(3000);
	    }else {
	        setcolor(RED);
	        
			setfillstyle(SOLID_FILL, BLACK);
			rectangle(getmaxx()/2-128, getmaxy()/2-80, getmaxx()/2+128, getmaxy()/2+10);
			floodfill(getmaxx()/2, getmaxy()/2, RED);
	        
		    settextstyle(BOLD_FONT,HORIZ_DIR, 8);
		    outtextxy(getmaxx()/2-118,getmaxy()/2-70,"Dead!");
		    printf("Dead!" );
		    play_death();
		    swapbuffers();
		    state = STATE_START;
		    brd.life--;
			free(map);
		    delay(3000);
		}
	}
}

void crt_node (addr_lvl *p)
{
	*p=(addr_lvl)malloc(sizeof(level));
	(*p)->next=NULL;
	printf("\nNode Berhasil Dibuat ");
}

void ins_akhir (addr_lvl *p, addr_lvl PNew)
{
	addr_lvl tail;

	tail = *p;
	while (tail->next!=NULL)
	{
		tail=tail->next;
	}
	tail->next=PNew;
}

void load_matriksmap () {
	addr_lvl pNew = NULL;
	int read = 0,i,maps_t[MAX_ROW][MAX_COL];
	FILE *ifp = fopen("Library\\matriksmap.dat", "rb");
	read = fread(maps_t, sizeof(char), sizeof(maps_t), ifp);
	printf("read = %d", read);
	if (read == 0) {
	    printf("Error load matriks !");
	}else if (mtrks_map.first == NULL)
	{   i = 0;
	    while (!feof(ifp)){
            fseek(ifp, i*sizeof(pNew->map), SEEK_SET);
            if (mtrks_map.first == NULL) {
                crt_node(&mtrks_map.first);
                fread(mtrks_map.first->map, sizeof(char), sizeof(mtrks_map.cur->map), ifp);
            }else {
                crt_node(&pNew);
                fread(pNew->map, sizeof(char), sizeof(pNew->map), ifp);
                ins_akhir(&mtrks_map.first,pNew);
            }
            i++;
	    }
	    mtrks_map.cur = mtrks_map.first;
	}

	fclose(ifp);
}

void menu()
{
	bool kembali;
	bgm();
	int x=0, y=0;
    int maxx = getmaxx()/2, maxy = getmaxy()/2;
    clearviewport();
	setviewport(0, 0, getmaxx(), getmaxy(), 1);
    swapbuffers();
    clearviewport();
	setviewport(0, 0, getmaxx(), getmaxy(), 1);

	readimagefile("Image\\Menu\\Tampilan_Menu.bmp", 0,0,800,600);

//    getch();
	swapbuffers();
    while(state == STATE_MENU){
    	kembali = false;

        getmouseclick(WM_LBUTTONDOWN, x, y);
//        printf("%d,%d",x,y);
        //masuk ke permaianan
        if((x>110)&&(x<210)&&(y>33)&&(y<83)){
        	strcpy(character.path_img,"Image\\Character\\Idle\\1.gif");
			character.dir='R';
            brd.level = 0;
            brd.life = 3;
            brd.score = 0;
            mtrks_map.cur = mtrks_map.first;
            lubang.front = NULL;
			state = STATE_START;

        }
        //Menampilkan cara bermain
        else if((x>30)&&(x<290)&&(y>150)&&(y<205)){
		    clearviewport();
			setviewport(0, 0, getmaxx(), getmaxy(), 1);

        	readimagefile("Image\\Menu\\How to play.bmp",0,0,800,600);
		    swapbuffers();

		    while (!kembali){
		    	getmouseclick(WM_LBUTTONDOWN, x, y);

		    	if((x>15)&&(x<70)&&(y>8)&&(y<35)){
		            kembali = true;
		        }
			}
			menu();
        }
        //Menampilkan About
        else if((x>100)&&(x<220)&&(y>270)&&(y<325)){
		    clearviewport();
			setviewport(0, 0, getmaxx(), getmaxy(), 1);

        	readimagefile("Image\\Menu\\Creator.bmp",0,0,800,600);
		    swapbuffers();


		    while (!kembali){
		    	getmouseclick(WM_LBUTTONDOWN, x, y);

		    	if((x>15)&&(x<70)&&(y>8)&&(y<35)){
		            kembali = true;
		        }
			}
			menu();
		}
        //Menampilkan exit
        else if((x>118)&&(x<200)&&(y>390)&&(y<440)){
			clearviewport();
			setviewport(0, 0, getmaxx(), getmaxy(), 1);

            settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
            readimagefile("Image\\Menu\\Good_Bye.bmp",0,0,800,600);
			swapbuffers();
			printf("exit");
			delay(3000);
			free(map);
        	closegraph();
        	exit (0);
        }
    }   
}

void bgm()
{
    mciSendString("open \"Sound\\sound.mp3\" type mpegvideo alias bgm",NULL,0,NULL);
    mciSendString("play bgm repeat",NULL,0,NULL);
}
 //dari play_fall sampe bawah semuanya sound dan modul baru
void play_fall()
{
    mciSendString("play \"Sound\\fall.mp3\"",NULL,0,NULL);
}

void stop_fall()
{
    mciSendString("stop \"Sound\\fall.mp3\"",NULL,0,NULL);
}

void play_peti()
{
    mciSendString("play \"Sound\\peti.mp3\"",NULL,0,NULL);
}

void play_death()
{
    mciSendString("play \"Sound\\death.wav\"",NULL,0,NULL);
}

void play_gameover()
{
    mciSendString("play \"Sound\\gameover.wav\"",NULL,0,NULL);
}

void play_next_level()
{
    mciSendString("play \"Sound\\next_level.wav\"",NULL,0,NULL);
}

void stop_next_level()
{
    mciSendString("stop \"Sound\\next_level.wav\"",NULL,0,NULL);
}

void play_explosion()
{
    mciSendString("play \"Sound\\explosion.wav\"",NULL,0,NULL);
}
