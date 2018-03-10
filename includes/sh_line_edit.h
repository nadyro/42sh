/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:07:51 by azybert           #+#    #+#             */
/*   Updated: 2018/03/10 17:56:58 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LINE_EDIT_H
# define SH_LINE_EDIT_H

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

# define BUFFER 4

typedef struct	s_coord
{
	size_t	x;
	size_t	y;
}				t_coord;

typedef struct	s_prompt
{
	char		*line;
	char		c[6];
	int			nb_read;
	size_t		pos;
	size_t		total;
	t_coord		*origin;
	t_coord		*size;
	bool		quotes;
	bool		dquotes;
}				t_prompt;

void			termanip(int sig);
char			*prompt();
void			get_cursor_pos(t_coord *actualize);
int				ft_putshit(int c);
void			move_cursor(t_prompt *prompt, size_t new_pos, bool save);
char			*prompt_stock(t_prompt *prompt);
void			prompt_delete(t_prompt *prompt);
void			prompt_backdel(t_prompt *prompt);
void			ft_cursor_left(t_prompt *prompt);
void			ft_cursor_right(t_prompt *prompt);
void			ft_cursor_start(t_prompt *prompt);
void			ft_cursor_end(t_prompt *prompt);
void			ft_cursor_word_left(t_prompt *prompt);
void			ft_cursor_word_right(t_prompt *prompt);
void			ft_cursor_up(t_prompt *prompt);
void			ft_cursor_down(t_prompt *prompt);

#endif
