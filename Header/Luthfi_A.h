#ifndef Luthfi_A_H 
#define Luthfi_A_H 

bool is_allow (int i, int j,int a, int b);

void left (int &i, int &j, int &x, int &y);

void right (int &i, int &j, int &x, int &y);

void up (int &i, int &j, int &x, int &y);

void down (int &i, int &j, int &x, int &y);

void fall (int &i, int &j, int &x, int &y);

void control();

/* ------------------------------ Enemy ---------------------------- */

void enemy_move (addr_ptr head, int grid[MAX_ROW][MAX_COL], int &i, int &j, int &x, int &y);

void enemy (addr_char ch, addr_char &enm);

void structcopy(elmt_list *dest, addr_char src);

/* ------------------------ A Star Path Fnding --------------------- */

addr_ptr create_node (elmt_list info);
void ins_node (addr_ptr *head, elmt_list elm);
elmt_list del_node (addr_ptr *head, elmt_list elm);
double heuristic(elmt_list start, elmt_list end);
elmt_list find_min_f (addr_ptr X);
elmt_list is_parent (addr_ptr closed_set, addr_map parent);
addr_ptr construct_path (addr_ptr closed_set, elmt_list start, elmt_list end);
addr_ptr find_neighbors (elmt_list cur, int map[MAX_ROW][MAX_COL]);
bool is_in_list(addr_ptr head, elmt_list elm);
addr_ptr a_star (elmt_list start, elmt_list end, int map[MAX_ROW][MAX_COL]);
void generate_grid(int arr[MAX_ROW][MAX_COL], int map[MAX_ROW][MAX_COL]);
 
#endif 
