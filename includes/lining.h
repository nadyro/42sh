/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lining.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:12:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/23 15:40:54 by nsehnoun         ###   ########.fr       */
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

struct					s_cursor_data
{
	int		pos;
	int		col;
	int		row;
	char	buffer[BUFFER];
};
struct					s_line_data
{
	void	*content;
	void	*old_content;
	char	buffer[BUFFER];
	int		length;
	int		resize_history[512];
	int		*extended_index_history;
	int		nb_resize;
	struct s_cursor_data	*cd;
};
int						fprint_char(int c);
void					get_infoterm(void);
struct s_line_data		*init_linedata(void);
struct s_cursor_data	*init_cursordata(void);
void					manage_movement(char *t, struct s_line_data *ld, int *i);
void					manage_validation(char *t, int *s, struct s_line_data *ld);
void					reallocate_mem_line(int *s, struct s_line_data *ld);
void					print_line_data(struct s_line_data *ld);
void					move_left(int *index, struct s_line_data *ld);
void					move_right(int *index, struct s_line_data *ld);
#endif
