#include "../LodeRunner12.h"

extern int			state,
					matriksmap[MAX_ROW][MAX_COL];
extern path			character;
extern addr_char	c_char;
extern board		brd;
extern head_queue	lubang;
extern img			map;

extern mtrks_lvl mtrks_map;

void wreck_left(){
	queue info;
	if(mtrks_map.cur->map[c_char.pos.i+1][c_char.pos.j-1] == 1){
		mtrks_map.cur->map[c_char.pos.i+1][c_char.pos.j-1] = 0;
        info.brick.i = c_char.pos.i+1;
        info.brick.j = c_char.pos.j-1;
        info.clock_ = clock();
        info.start = ((double)info.clock_)/CLOCKS_PER_SEC;
		enque(&lubang, info);
		
		clearviewport();
		setviewport(0, 0, getmaxx(), getmaxy(), 1);
		putimage(0,0,map, COPY_PUT);
        draw_obj("blank",c_char.pos.i+1,c_char.pos.j-1);
		getimage(0,0,800,600,map);

		draw_obj_mov(character.path_img,c_char.x,c_char.y);

		swapbuffers();
    }
}

void wreck_right(){
	queue info;
	if(mtrks_map.cur->map[c_char.pos.i+1][c_char.pos.j+1] == 1){
		mtrks_map.cur->map[c_char.pos.i+1][c_char.pos.j+1] = 0;
        info.brick.i = c_char.pos.i+1;
        info.brick.j = c_char.pos.j+1;
        info.clock_ = clock();
        info.start = ((double)info.clock_)/CLOCKS_PER_SEC;
		enque(&lubang, info);
		
		clearviewport();
		setviewport(0, 0, getmaxx(), getmaxy(), 1);
		putimage(0,0,map, COPY_PUT);
        draw_obj("blank",c_char.pos.i+1,c_char.pos.j+1);
		getimage(0,0,800,600,map);

		draw_obj_mov(character.path_img,c_char.x,c_char.y);

		swapbuffers();
	}
}

void count_time(){
	lubang.front->info.clock_ = clock() - lubang.front->info.clock_;
	lubang.front->info.taken = ((double)lubang.front->info.clock_)/CLOCKS_PER_SEC;
}

bool IsEmpty(addr_que p){
    return (p == NULL);
}

void enque(head_queue *p, queue info){
	addr_que last = (*p).rear;
	if(IsEmpty((*p).front)){
		(*p).front = (addr_que) malloc(sizeof (struct list_queue));
		(*p).front->info = info;
		(*p).front->next = NULL;
		(*p).rear = (*p).front;
	}else{
		last->next = (addr_que) malloc(sizeof (struct list_queue));
		last->next->info = info;
		last->next->next = NULL;
		(*p).rear = last->next;
	}
}

void deque (head_queue *p){
	addr_que PDel;
	if (!IsEmpty((*p).front)){
		PDel = (*p).front;
		(*p).front = (*p).front->next;
		(PDel)->next = NULL;
		free(PDel);
	}
}
