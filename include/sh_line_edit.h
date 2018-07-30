/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_line_edit.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:07:51 by azybert           #+#    #+#             */
/*   Updated: 2018/07/30 07:32:22 by azybert          ###   ########.fr       */
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

# define BUFFER 4
# define UNUSED(x) (void)(x)

extern struct s_prompt		*prompt;

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

typedef struct	s_prompt
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
}				t_prompt;

typedef struct	s_stat_data
{
	char		*overage;
	char		*old_line;
	char		*copied;
	t_node		*history;
	t_node		*matches;
	t_node		*current;
}				t_stat_data;

char			*get_pwd(void);
void			termanip(int sig);
char			*line_edit_main_loop(char *d_prompt, t_node *history);
void			get_cursor_pos(t_coord *actualize, t_prompt *prompt);
int				ft_putshit(int c);
void			esc_react(t_prompt *prompt, int nb_user_entry, char *user_entry,
				t_stat_data *stat_data);
void			history_next(t_prompt *prompt, t_stat_data *stat_data);
void			history_prev(t_prompt *prompt, t_stat_data *stat_data);
t_node			*add_to_history(char *cmd, t_node *node);
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
void			sig_react(t_prompt *prompt, char c);
void			handle_sig(void);
void			ignore_handle(void);
void			reverse_handle(void);
void			term_clear(void);
t_prompt		*malloc_prompt(t_prompt *prompt, t_stat_data *data,
				char *d_prompt);
t_stat_data		*malloc_stat(void);
void			free_prompt(t_prompt *prompt);
void			ft_flush(t_prompt *prompt);
void			secure_stock(t_prompt *prompt, char *to_stock);
void			selection_mode(t_prompt *prompt, t_stat_data *stat_data);
void			search_mode(t_prompt *prompt, t_stat_data *stat_data);
void			auto_complete(t_prompt *prompt);
void			prompt_clean(void);

//History

void			write_history_file(t_node *history);

// Autocompletion
char			**fetch_from_env_o(void);
char			**fetch_from_env_a(char **all_paths);
t_node			*fetch_binaries(char **all_paths);
t_node			*add_elements(t_node *lst, char *file_bin);
t_node			*cmp_user_entry(t_node *lst, char *user_entry);
t_node			*cmp_space_entry(char *a_name, int is_null);
t_node			*fetch_names(char *user_entry);
int				fetch_names_dirent(char *user_entry);
void			clean_tabs(char **t, int j);
void			send_nudes(t_node **my_phone);
void			free_lists(t_node *lst);
void			print_nudes(t_node *matches);
char			**lst_to_array(t_node *matches);
int				write_completion(t_prompt *prompt, int *y);
#endif
