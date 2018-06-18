/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:07:51 by azybert           #+#    #+#             */
/*   Updated: 2018/06/18 17:36:13 by azybert          ###   ########.fr       */
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
# define UNUSED(x) (void)(x)

extern struct s_prompt	*prompt;

typedef struct	s_coord
{
	size_t	x;
	size_t	y;
}				t_coord;

typedef enum	e_quotes
{
	none,
	quotes,
	dquotes
}				t_quotes;

typedef struct	s_prompt
{
	char		*line;
	char		*buf;
	size_t		pos;
	size_t		total;
	t_coord		*origin;
	t_coord		*size;
	t_quotes	quotes;
}				t_prompt;

typedef struct	s_node
{
	char			*cmd;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct	s_stat_data
{
	char		*overage;
	int			line_save;
	t_node		*history;
	t_node		*current;
}				t_stat_data;

void			termanip(int sig);
char			*line_edit_main_loop();
void			get_cursor_pos(t_coord *actualize, t_prompt *prompt);
int				ft_putshit(int c);
int				esc_react(t_prompt *prompt, int nb_user_entry, char *user_entry,
				t_stat_data *stat_data);
void			history_next(t_prompt *prompt, t_stat_data *stat_data);
void			history_prev(t_prompt *prompt, t_stat_data *stat_data);
void			add_to_history(char *cmd, t_stat_data *stat_data);
int				data_react(t_prompt *prompt);
char			*prompt_stock(t_prompt *prompt, char *user_entry);
void			prompt_delete(t_prompt *prompt);
void			prompt_backdel(t_prompt *prompt);
void			write_data(t_prompt *prompt, char *to_display, size_t size);
void			move_cursor(t_prompt *prompt, size_t new_pos, bool save);
size_t			ft_add_nl(t_prompt *prompt, size_t new_pos);
void			ft_cursor_word_left(t_prompt *prompt);
void			ft_cursor_word_right(t_prompt *prompt);
void			ft_cursor_up(t_prompt *prompt);
void			ft_cursor_down(t_prompt *prompt);
char			*quotes_managing(t_prompt *prompt, char *to_return);
//void			handle_sig(void);
//void			handle_int(int sig);
//void			handle_resize(int sig);
t_prompt		*malloc_prompt(t_prompt *prompt, t_stat_data *data);
void			free_prompt(t_prompt *prompt);
void			ft_flush(t_prompt *prompt);

#endif
