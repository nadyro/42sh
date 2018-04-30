/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lining.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:12:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/30 21:07:58 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINING_H
# define LINING_H

# include "../libft/libft.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>

# define BUFFER 1024
# define COLSTART 11
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define BCYAN "\x1B[96m"
# define NORMAL "\x1b[0m"

struct					s_cursor_data
{
	int		pos_x;
	int		pos_y;
	int		x;
	int		col;
	int		row;
};
struct					s_line_data
{
	void					*content;
	void					*old_content;
	char					*buff;
	char					*buffer;
	int						current_size;
	int						length;
	int						resize_history[512];
	int						nb_resize;
	struct s_cursor_data	*cd;
};
int						fprint_char(int c);
void					get_infoterm(void);
struct s_line_data		*init_linedata(void);
void					clean_linedata(struct s_line_data *ld);
struct s_cursor_data	*init_cursordata(void);
void					manage_movement(char *t, struct s_line_data *ld);
void					manage_validation(struct s_line_data *ld);
void					reallocate_mem_line(struct s_line_data *ld);
void					print_line_data(struct s_line_data *ld);
void					move_left(struct s_line_data *ld);
void					move_right(struct s_line_data *ld);
void					move_up(struct s_line_data *ld);
void					move_down(struct s_line_data *ld);
void					update_linedata(char t, struct s_line_data *ld);
void					cursor_pos(struct s_line_data *ld);
void					ft_putscolors(char *str, char *color);
void					write_change(struct s_line_data *ld);
void					manage_buffer(struct s_line_data *ld, char t, int *i);
#endif
