/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lining.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:12:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/26 21:35:51 by kernel_pa        ###   ########.fr       */
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

# define BUFFER 6
# define COLSTART 10

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
	void	*content;
	void	*old_content;
	char	buffer[BUFFER];
	int		current_size;
	int		length;
	int		resize_history[512];
	int		*extended_index_history;
	int		nb_resize;
	int		edit_mode;
	struct s_cursor_data	*cd;
};
int						fprint_char(int c);
void					get_infoterm(void);
struct s_line_data		*init_linedata(void);
void			clean_linedata(struct s_line_data *ld);
struct s_cursor_data	*init_cursordata(void);
void					manage_movement(char *t, struct s_line_data *ld, int *i);
void					manage_validation(char *t, int *s, struct s_line_data *ld);
void					reallocate_mem_line(int *s, struct s_line_data *ld);
void					print_line_data(struct s_line_data *ld);
void					move_left(int *index, struct s_line_data *ld);
void					move_right(int *index, struct s_line_data *ld);
void					move_up(int *index, struct s_line_data *ld);
void					move_down(int *index, struct s_line_data *ld);
void					update_linedata(char t, struct s_line_data *ld);
void			cursor_pos(struct s_line_data *ld);
#endif
