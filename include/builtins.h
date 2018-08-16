/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:05:30 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/16 12:07:03 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define RESET "\033[0;0m\033[39m\033[49m"
# define C01 "\x1B[96m"
# define C02 "\033[35m"
# define C03 "\033[32m"
# define C04 "\033[33m"
# define C05 "\033[31m"
# define C06 "\033[34m\033[46m"
# define C07 "\033[34m\033[43m"
# define C08 "\033[30m\033[41m"
# define C09 "\033[30m\033[46m"
# define C10 "\033[42m\033[30m"
# define C11 "\033[43m\033[30m"

# include "../libft/libft.h"
# include "sh_line_edit.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/wait.h>
# include <sys/syslimits.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

typedef struct	s_env
{
	char					*var;
	char					*val;
	int						last;
	struct s_env			*prev;
	struct s_env			*next;
	struct s_env			*mod;
}				t_env;

typedef struct	s_history
{
	int		c;
	int		d;
	int		d_arg;
	int		a;
	int		a_to_f;
	int		n;
	int		n_to_f;
	int		r;
	int		r_to_f;
	int		w;
	int		w_to_f;
	int		p;
	int		s;
	int		h;
	int		no_write;
	int		vide;
}				t_history;

typedef struct	s_shell
{
	char					**envv;
	char					**args;
	char					*full_path;
	char					*line;
	int						*tok;
	int						new_fd;
	int						redir_error;
	int						last_hd;
	int						bin_ret;
	int						i;
	int						p;
	int						l;
	int						st;
	int						error;
	int						s_out;
	int						s_in;
	int						s_err;
	int						history_length;
	int						o_history;
	int						is_a;
	int						last_added;
	int						to_add;
	char					*home_env;
	t_env					*list;
	t_node					*history;
	t_node					*appnd_hst;
}				t_shell;

t_env			*env_setup(char **env);
void			ash_loop(t_shell *shell);
int				ash_execute(t_shell *shell);
int				ash_env(t_shell *shell);
int				ash_exit(t_shell *shell);
int				ash_cd(t_shell *shell);
int				regular_cd(t_shell *shell);
int				ash_echo(t_shell *shell);
int				ash_setenv(t_shell *shell);
int				ash_unsetenv(t_shell *shell);
int				ash_env_mod(t_shell *shell);
void			add_to_mod(t_shell *shell);
t_env			*mod_init(t_shell *shell);
int				ft_exec(t_shell *shell, char **env);
char			**env_to_tab(t_env *list);
char			*arg_full_path(t_shell *shell);
int				cd_path(t_shell *shell, int i, char **paths);
int				cd_error_mgmt(char *operand);
char			**fetch_cd_paths(t_shell *shell);
void			free_table(char **tabs);
int				builtin_check(t_shell *shell);
void			free_env(t_env *list);
int				has_paths(t_shell *shell, int cdpath);
t_env			*env_init(void);
void			executing_directory(t_shell *shell);
void			update_old_pwd(t_shell *shell, char *new_pwd);
int				cd_opt_check(t_shell *shell);
void			cd_canon(t_shell *shell);
int				cd_get_last(t_shell *shell, char ***split);
void	    	handle_dot_dots(t_shell *shell);
int				ash_history(t_shell *shell);
int				check_warn(t_shell *shell, t_history *hist_args, int y);
int				check_warn_w(t_history *hist_args, t_shell *shell, int y);
int				check_warn_a(t_history *hist_args, t_shell *shell, int y);
int				check_warn_r(t_history *hist_args, t_shell *shell, int y);
int				check_warn_n(t_history *hist_args, t_shell *shell, int y);
void			print_hist_args(t_history *hist_args);
void			write_history_mem_to_file(t_shell *shell);
void			write_history_file(t_shell *shell, int to_f);
void			print_history(int *x, char **cmd, int to_free);
void			read_history(t_node *history, int nbr);
void			dispatch_history_print(t_shell *shell);
void			dispatch_history_d(t_shell *shell, t_history *hist_args);
void			append_history_mem_to_file(t_shell *shell);
void			append_history_mem_to_arg(t_shell *shell);
void			write_history_mem_to_arg(t_shell *shell);
void			lighten_dispatching(t_history *hist_args, t_shell *shell);
void			write_arg_p(t_shell *shell);
void			write_arg_s(t_shell *shell);
void			history_helper(void);
void			history_errors(t_history *hist_args);
void			free_after_del(t_node *to_free, t_shell *shell);
char			*filter_args_2(char **args);
t_node			*append_history_to_mem(t_node *hstry, t_shell *shell, int to_f);
t_node			*init_nonvoid_history(char *cmd, t_node *history);
t_node			*dispatch_history_queries(t_history *hist_args, t_shell *shell);
t_node			*clear_history_mem(t_shell *history);
t_node			*delete_history_line(t_shell *shell, int to_del);
t_node			*get_last_cmds(t_node *history, int nbr);
t_node			*fill_history_file(t_node *history, t_shell *shell);
t_node			*fill_arg_file(t_node *history, t_shell *shell);
t_node			*write_history_to_mem(t_node *history, t_shell *shell);
t_node			*lighten_append_hst(int *index, int fd, t_shell *shell, t_node *history);
t_history		*init_hist_args(void);
t_history		*check_history_args(t_shell *shell);
t_history		*check_if_flag(t_shell *shell, t_history *hist_args);
t_history		*check_if_flag_2(t_shell *shell, t_history *hist_args);
t_history		*check_d_arg(int y, t_shell *shell, t_history *hist_args);
t_history		*fill_hist_args(t_shell *shell, t_history *hist_args, int *i);
t_history		*handle_args(t_history *hist_args, t_shell *shell, int *i);

#endif
