#include "../../includes/42sh_line_edit.h"

void get_cursor_pos(t_coord *actualize)
{
	char	buf[100];
	int		loop;

	write(1, "\033[6n", 4);
	ft_bzero(buf, 100);
	read(1, buf, 100);
	actualize->y = ft_atol(&buf[2]);
	loop = 2;
	while (buf[loop] != ';')
		loop++;
	actualize->x = ft_atol(&buf[5]);
}
