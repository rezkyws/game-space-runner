#include "../LodeRunner12.h"

extern int			state,
					matriksmap[MAX_ROW][MAX_COL],
					k,e;
extern path			character;
extern addr_char	c_char,
					c_enemy[3];
extern board		brd;
extern head_queue	lubang;
extern img			map;

extern mtrks_lvl mtrks_map;

bool is_allow (int i, int j,int a, int b) {
	return (mtrks_map.cur->map[i][j]!=a && mtrks_map.cur->map[i][j]!=b);
}

void left (int &i, int &j, int &x, int &y){
	if ((is_allow (i,j-1,1,2) && j>0 && (x>((j-1)*30))) || (mtrks_map.cur->map[i][j]!=2 && mtrks_map.cur->map[i][j]!=1 && x>(j)*30)){
			
        x = x - 6;
//        if (x<((j)*30)-24)
        if (x<(j*30)-18)
            j = j - 1;

		if (mtrks_map.cur->map[i][j]!=4 || (mtrks_map.cur->map[i][j] == 4 && y != i*30)){
			move_right_left("Run","Left");
		}else if (((x<=((j)*30) && mtrks_map.cur->map[i][j-1]==4 && mtrks_map.cur->map[i][j]==4) || (mtrks_map.cur->map[i][j-1]!=4 && x>((j)*30)+24)) && y == i*30){
			move_right_left("Rope","Left");
		}

        character.dir = 'L';

		printf("x = %d\n",x);
        printf("j = %d\n",j);
    }
}

void right (int &i, int &j, int &x, int &y){
	if ((is_allow (i,j+1,1,2) && j<25 && (x<((j+1)*30))) || (mtrks_map.cur->map[i][j]!=2 && mtrks_map.cur->map[i][j]!=1 && x<(j)*30)){
			
        x = x + 6;
        if (x>(j*30)+18)
            j = j + 1;

		if (mtrks_map.cur->map[i][j]!=4){
			move_right_left("Run","Right");
		}else if (((x>=((j)*30) && mtrks_map.cur->map[i][j+1]==4 && mtrks_map.cur->map[i][j]==4) || (mtrks_map.cur->map[i][j+1]!=4 && x<((j)*30)-24)) && y == i*30){
			move_right_left("Rope","Right");
		}

        character.dir = 'R';
        printf("x = %d\n",x);
        printf("j = %d\n",j);
    }

}

void up (int &i, int &j, int &x, int &y){
	if ((is_allow (i-1,j,1,2) && is_allow (i,j,4,0) && (y>((i-1)*30)) && x == j*30) || (is_allow (i,j,1,2) && y>i*30)){
        
		y = y - 6;
//        if (y<=((i)*30)-6)
        if (y<(i*30)-15)
            i = i - 1;
		printf("y = %d\n",y);
        printf("i = %d\n",i);
		
		if (mtrks_map.cur->map[i][j]==3 || (mtrks_map.cur->map[i][j]!=3 && y > i*30)){
			climb_up();
		}
    }
}

void down (int &i, int &j, int &x, int &y){
	if ((is_allow (i+1,j,1,2) && y<((i+1)*30)) || (mtrks_map.cur->map[i][j]==3 && y<(i)*30)){
        
		y = y + 6;
//        if (y==((i+1)*30))
        if (y>(i*30)+15)
            i = i + 1;
        printf("y = %d\n",y);
        printf("i = %d\n",i);

		if (mtrks_map.cur->map[i][j]==3 || (mtrks_map.cur->map[i][j]!=3 && y > i*30)){
			climb_dw();
		}
    }
}

void fall (int &i, int &j, int &x, int &y){
	if (state != STATE_FALL) play_fall();
	if((mtrks_map.cur->map[i+1][j] == 0 && (is_allow (i,j,4,3) || y>(i)*30)) || mtrks_map.cur->map[i+1][j] == 5 || mtrks_map.cur->map[i+1][j] == 4){
		
		state = STATE_FALL;
	    y = y + 6;
        if (y>(i*30)+15)
            i = i + 1;

		if (character.dir == DIR_RIGHT){
			sprintf(character.path_img,"Run\\Right\\1.gif");
		}else{
			sprintf(character.path_img,"Run\\Left\\1.gif");
		}
	}else if ((mtrks_map.cur->map[i][j] == 4 && y< i*30) || (mtrks_map.cur->map[i][j] == 0 && mtrks_map.cur->map[i+1][j] != 0 && y<(i)*30)){
		state = STATE_FALL;
	    y = y + 6;
        if (y>(i*30)+15)
            i = i + 1;

		if (character.dir == DIR_RIGHT){
			sprintf(character.path_img,"Run\\Right\\1.gif");
		}else{
			sprintf(character.path_img,"Run\\Left\\1.gif");
		}
	}else
	{
		stop_fall();
		state = STATE_PLAY;
	}
//        printf("y = %f\n",y);
//        printf("i = %d\n",i);
}

void control()
{
	if (state == STATE_PLAY){
	    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) right(c_char.pos.i,c_char.pos.j,c_char.x,c_char.y);
	    if (GetAsyncKeyState(VK_LEFT) & 0x8000) left(c_char.pos.i,c_char.pos.j,c_char.x,c_char.y);
	    if (GetAsyncKeyState(VK_UP) & 0x8000) up(c_char.pos.i,c_char.pos.j,c_char.x,c_char.y);
	    if (GetAsyncKeyState(VK_DOWN) & 0x8000) down(c_char.pos.i,c_char.pos.j,c_char.x,c_char.y);
	    if (GetAsyncKeyState(0x5A) & 0x8000) wreck_left();
	    if (GetAsyncKeyState(0x58) & 0x8000) wreck_right();
	    if (GetAsyncKeyState(0x50) & 0x8000) pause();
	    
		if (!IsEmpty(lubang.front)) {
			count_time();
	        if (lubang.front->info.taken > 2+lubang.front->info.start){
	            mtrks_map.cur->map[lubang.front->info.brick.i][lubang.front->info.brick.j] = 1;
	            state = STATE_RESTORE;
	        }
		}
		
	    cek_box();
	    
		if (!GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_UP) && 
			!GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(0x5A) && !GetAsyncKeyState(0x58) && !GetAsyncKeyState(0x50))
	    		idle();

		if(c_char.pos.i < 0 && brd.level < 10)
        {
            state = STATE_START;
            play_next_level();
            brd.level++;
            k = 0;
            e = 0;
            mtrks_map.cur=mtrks_map.cur->next;
            printf("level = %d",brd.level);
        }
	}
	
	if (state == STATE_PAUSE || state == STATE_FALL)
	{
	    if (GetAsyncKeyState(0x50) & 0x8000) pause();
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) state = STATE_MENU;
	}

	if (state == STATE_PLAY || state == STATE_FALL) {
		enemy (c_char, c_enemy[0]);
		enemy (c_char, c_enemy[1]);
		enemy (c_char, c_enemy[2]);
		fall(c_char.pos.i,c_char.pos.j,c_char.x,c_char.y);
	}
}

/* ------------------------------ Enemy ---------------------------- */

void enemy_move (addr_ptr head, int grid[MAX_ROW][MAX_COL], int &i, int &j, int &x, int &y){
    addr_ptr temp = head;
    if(temp != NULL){
		if ((i == temp->info.pos.i && j == temp->info.pos.j)){
	        if (temp->next != NULL)temp = temp->next;
	        else return;
		}
	    if (j < temp->info.pos.j){
	    	x = x + 5;
		    if (x==((j+1)*30))
		        j = j + 1;
		}
	    if (j > temp->info.pos.j){
	    	x = x - 5;
		    if (x==((j-1)*30))
		    	j = j - 1;
		}
	    if (i < temp->info.pos.i){
	    	y = y + 5;
		    if (y==((i+1)*30))
		    	i = i + 1;
		}
	    if (i > temp->info.pos.i){
	    	y = y - 5;
		    if (y==((i-1)*30))
		        i = i - 1;
		}
    }
}

void enemy (addr_char ch, addr_char &enm) {
	int grid[MAX_ROW][MAX_COL];
	elmt_list start, end;
	structcopy(&start, enm);
	structcopy(&end, ch);
	generate_grid(grid,mtrks_map.cur->map);
	if (grid[end.pos.i][end.pos.j] == 0)
		enemy_move (a_star (start,end,grid), grid, enm.pos.i, enm.pos.j, enm.x, enm.y);
}

void structcopy(elmt_list *dest, addr_char src){
	(*dest).pos.i = src.pos.i;
	(*dest).pos.j = src.pos.j;
}

/* ------------------------ A Star Path Fnding --------------------- */

addr_ptr Create_Node (elmt_list info) {
	addr_ptr pNew;
	pNew = (addr_ptr) malloc(sizeof(list_grid));
	pNew->info = info;
	pNew->next = NULL;
	return pNew;
}

void ins_node (addr_ptr *head, elmt_list elm) {
	if(head == NULL){
	    *head = Create_Node(elm);
	}else{
	    addr_ptr pNew;
	    pNew = Create_Node(elm);
	    pNew->next = *head;
	    *head = pNew;
	}
}

elmt_list del_node (addr_ptr *head, elmt_list elm) {
	addr_ptr temp = *head; elmt_list X;
	while(temp != NULL){
	    if((elm.pos.i == temp->info.pos.i) && (elm.pos.j == temp->info.pos.j)){
			X = temp->info;
			if(*head == temp){
			    *head = temp->next;
			    temp->next = NULL;
			}else{
			    addr_ptr pBfr = *head;
			    while(pBfr->next != temp) pBfr = pBfr->next;
			    pBfr->next = temp->next;
			    temp->next = NULL;
			}
			free(temp);
			return X;
	    }
	    temp = temp->next;
	}
	return X;
}

double heuristic(elmt_list start, elmt_list end) {
	return abs(start.pos.j - end.pos.j) + abs(start.pos.i - end.pos.i);
}

elmt_list find_min_f (addr_ptr X) {
    addr_ptr temp = X;
    addr_ptr pMin = X;
    
    while(temp != NULL){
        if(temp->info.f < pMin->info.f){
            pMin = temp;
        }
        temp = temp->next;
    }
    return pMin->info;
}

elmt_list is_parent (addr_ptr closed_set, addr_map parent) {
	addr_ptr temp = closed_set;
	while (temp != NULL) {
		if (temp->info.pos.i == parent.i && temp->info.pos.j == parent.j) {
			return temp->info;
		}
		temp = temp->next;
	}
}

addr_ptr construct_path (addr_ptr closed_set, elmt_list start, elmt_list end) {
	addr_ptr path = NULL;
	ins_node (&path, end);
	while (end.pos.i != start.pos.i || end.pos.j != start.pos.j) {
		end = is_parent(closed_set,end.parent);
		ins_node (&path, end);
	}
	return path;
}

addr_ptr find_neighbors (elmt_list cur, int map[MAX_ROW][MAX_COL]) {
	addr_ptr neighbors = NULL;
	elmt_list neighbor;
    int dirX[] = {0,0,-1,1};
    int dirY[] = {-1,1,0,0};
    
	for (int i = 0; i < 4; i++) {
        neighbor.pos.i = cur.pos.i + dirY[i];
        neighbor.pos.j = cur.pos.j + dirX[i];
        if ((neighbor.pos.i >= 0) 
		&& (neighbor.pos.i < MAX_ROW) 
		&& (neighbor.pos.j >= 0) 
		&& (neighbor.pos.j < MAX_COL) 
		&& (map[neighbor.pos.i][neighbor.pos.j] == 0)) {
        	neighbor.g = cur.g + 1.0;
        	neighbor.parent.i = cur.pos.i;
        	neighbor.parent.j = cur.pos.j;
			ins_node(&neighbors,neighbor);
		}
	}
	return neighbors;
}

bool is_in_list(addr_ptr head, elmt_list elm){
    addr_ptr temp = head;
    while(temp != NULL){
        if((temp->info.pos.i == elm.pos.i) && (temp->info.pos.j == elm.pos.j))
            if(temp->info.f >= elm.f)
                return true;
        temp = temp->next;
    }
    return false;
}

addr_ptr a_star (elmt_list start, elmt_list end, int map[MAX_ROW][MAX_COL]) {
	addr_ptr closed_set = NULL;
	addr_ptr open_set = NULL;
	addr_ptr neighbors;
	elmt_list cur, openneighbor;
	
	start.g = 0;
	start.f = start.g + heuristic(start, end);
	
	ins_node (&open_set, start);
	
	while (open_set != NULL) {
		cur = find_min_f (open_set);
		if (cur.pos.i == end.pos.i && cur.pos.j == end.pos.j) {
			end.parent = cur.parent;
			return construct_path(closed_set,start,end);
		}
		del_node (&open_set, cur);
		ins_node (&closed_set, cur);
		
		neighbors = find_neighbors(cur,map);
		while (neighbors != NULL) {
			if (!is_in_list(closed_set,neighbors->info)) {
				neighbors->info.f = neighbors->info.g + heuristic(neighbors->info, end);
				if (!is_in_list(open_set,neighbors->info)) {
					openneighbor = del_node (&neighbors, neighbors->info);
					ins_node (&open_set, openneighbor);
				}else {
					openneighbor = del_node (&open_set, neighbors->info);
					if (neighbors->info.g < openneighbor.g) {
						openneighbor.g = neighbors->info.g;
						openneighbor.parent = neighbors->info.parent;
					}
					ins_node (&open_set, openneighbor);
				}
			}else{
				del_node (&neighbors, neighbors->info);
			}
		}
	}
	
	return NULL;
}

void generate_grid(int arr[MAX_ROW][MAX_COL], int map[MAX_ROW][MAX_COL]){
    for(int i = 0; i < MAX_ROW; i++){
        for(int j = 0; j< MAX_COL; j++){
            if((map[i+1][j]== 1 || map[i+1][j]== 2 || map[i+1][j]== 3) && map[i][j]== 0)
            {
            	arr[i][j] = false;
			}else if(map[i][j]== 3 || map[i][j]== 4 || map[i][j]== 5)
			{
				arr[i][j] = false;
			}else{
				arr[i][j] = true;
			}
        }
    }
}
