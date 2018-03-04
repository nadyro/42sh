#include "42sh.h"

void get_cursor_position(coord_t actualize)
{
	char buf[10];

	write(1, "\033[6n", 4);
	read(1, buf, 10);
	actualize->y = atoi(&buf[2]);
	actualize->x = atoi(&buf[5]);
}
