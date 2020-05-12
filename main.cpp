#include "LodeRunner12.h"

int			state = STATE_MENU,
			matriksmap[MAX_ROW][MAX_COL],
			k;
path		character,
			path_enemy;
addr_char	c_char,
			c_enemy[3];
board		brd;
head_queue	lubang;
img			map;

mtrks_lvl mtrks_map;

int main() {
	window();
	mtrks_map.first = NULL;
	load_matriksmap();
    while(true)
    {
    	control();
		render();
    }
	return 0;
}
