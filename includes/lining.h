/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lining.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:45:21 by kernel_pani       #+#    #+#             */
/*   Updated: 2018/04/21 22:47:27 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINING_H
# define LINING_H

#include "../libft/libft.h"

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


struct	line_data
{
	void	*content;
	void	*old_content;
	char	buffer[BUFFER];
	int	length;
	int	resize_history[512];
	int	*extended_index_history;
	int	nb_resize;
};
int			fprint_char(int c);
void			get_infoterm(void);
struct line_data	*init_linedata(void);
void			manage_movement(char *t, struct line_data *ld, int *index);
void			manage_validation(char *t, int *s, struct line_data *ld);
void			reallocate_mem_line(int *s, struct line_data *ld);
void			print_line_data(struct line_data *ld);
void			move_left(int *index, struct line_data *ld);
void			move_right(int *index, struct line_data *ld);
#endif
