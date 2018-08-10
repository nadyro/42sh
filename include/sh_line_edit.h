/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_line_edit.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:07:51 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:48:37 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LINE_EDIT_H
# define SH_LINE_EDIT_H

# include "libft.h"

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
# include <dirent.h>
# include <sys/stat.h>

# define BUFFER 512
# define UNUSED(x) (void)(x)

extern struct s_g_prpt		*g_prpt;

typedef struct	s_coord
{
	size_t	x;
	size_t	y;
}				t_coord;

typedef struct	s_node
{
	char			*cmd;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct	s_g_prpt
{
	char		*line;
	char		*buf;
	char		*disp;
	int			end;
	size_t		pos;
	size_t		total;
	t_coord		*origin;
	t_coord		*size;
	t_node		*history;
	t_node		*current;
}				t_g_prpt;

typedef struct	s_stat_data
{
	char		*overage;
	char		*old_line;
	char		*copied;
	t_node		*matches;
}				t_stat_data;

void			ft_cursor_up(t_g_prpt *g_prpt);
void			ft_cursor_down(t_g_prpt *g_prpt);
void			ft_cursor_word_left(t_g_prpt *g_prpt);
void			ft_cursor_word_right(t_g_prpt *g_prpt);

t_node			*add_elements(t_node *lst, char *file_bin);
t_node			*cmp_user_entry(t_node *lst, char *user_entry);
t_node			*cmp_space_entry(char *a_name, int is_null);
char			**lst_to_array(t_node *matches);

void			clean_tabs(char **t, int j);
void			send_nudes(t_node **my_phone);
void			free_lists(t_node *lst);
void			print_nudes(t_node *matches);
int				is_pre_binary(char c);

void			get_cursor_pos(t_coord *actualize, t_g_prpt *g_prpt);
int				ft_putshit(int c);
size_t			ft_add_nl(t_g_prpt *g_prpt, size_t new_pos);
void			move_cursor(t_g_prpt *g_prpt, size_t new_pos, bool save);

char			**fetch_from_env_o(void);
char			**fetch_from_env_a(char **all_paths);
t_node			*fetch_binaries(char **all_paths);
t_node			*fetch_names(char *user_entry);
int				fetch_names_dirent(char *user_entry);

t_node			*add_to_history(char *cmd, t_node *node);
void			history_next(t_g_prpt *g_prpt, t_stat_data *stat_data);
void			history_prev(t_g_prpt *g_prpt, t_stat_data *stat_data);

void			auto_complete(t_g_prpt *g_prpt);

char			*line_edit_main_loop(char *d_g_prpt, t_node *history);

void			g_prpt_delete(t_g_prpt *g_prpt);
void			g_prpt_backdel(t_g_prpt *g_prpt);
char			*g_prpt_stock(t_g_prpt *g_prpt, char *user_entry);

void			ft_flush(t_g_prpt *g_prpt);
void			g_prpt_clean(void);

void			esc_react(t_g_prpt *g_prpt, int nb_user_entry,
				char *user_entry, t_stat_data *stat_data);
int				data_react(t_g_prpt *g_prpt);
void			sig_react(t_g_prpt *g_prpt, char c);
void			secure_stock(t_g_prpt *g_prpt, char *to_stock);

void			search_mode(t_g_prpt *g_prpt, t_stat_data *stat_data);
void			selection_mode(t_g_prpt *g_prpt, t_stat_data *stat_data);

void			sig_ignore(int s);

void			handle_sig(void);
void			handle_int(int sig);
void			handle_resize(int sig);
void			term_clear(void);
void			reverse_handle(void);

void			ignore_handle(void);

void			free_g_prpt(t_g_prpt *g_prpt);
t_g_prpt		*malloc_g_prpt(t_g_prpt *g_prpt, t_stat_data *data,
				char *d_g_prpt);
t_stat_data		*malloc_stat(void);

void			termanip(int sig);

void			write_data(t_g_prpt *g_prpt, char *to_display, size_t size);

char			*get_pwd(void);

#endif
