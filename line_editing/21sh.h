/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:07:51 by azybert           #+#    #+#             */
/*   Updated: 2018/03/04 18:07:29 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_21_SH
# define H_21_SH

# include "../Libft/libft.h"

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

# define BUFFER 4000

typedef struct	s_prompt
{
	char		*line;
	char		c[6];
	size_t		modx;
	size_t		mody;
	size_t		posx;
	size_t		posy;
	size_t		line_pos;
	size_t		total;
	int			nb_read;
	char		quote;
	char		dquote;
}				t_prompt;

void	termanip(int sig);
char	*ft_prompt();
char	*ft_prompt_stock(t_prompt *prompt);
void	ft_prompt_delete(t_prompt *prompt);
void    ft_prompt_backdel(t_prompt *prompt);
int		ft_putshit(int c);
void    ft_cursor_left(t_prompt *prompt);
void    ft_cursor_right(t_prompt *prompt);
void    ft_cursor_start(t_prompt *prompt);
void    ft_cursor_end(t_prompt *prompt);
void    cursor_word_left(t_prompt *prompt);
void    cursor_word_right(t_prompt *prompt);

#endif
