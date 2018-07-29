/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:05:30 by antoipom          #+#    #+#             */
/*   Updated: 2018/07/29 19:51:29 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct	s_shell
{
	char					**envv;
	char					**args;
	char					*full_path;
	char					*line;
	int 					*tok;
	int						new_fd;
	int						i;
	int						p;
	int						l;
	int						st;
	int						error;
	int						s_out;
	int						s_in;
	int						s_err;
	t_env					*list;
	t_node					*history;
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
int				cd_path(t_shell *shell);
void			free_table(char **tabs);
int				builtin_check(t_shell *shell);
void			free_env(t_env *list);
int				has_paths(t_shell *shell, int cdpath);
t_env			*env_init(void);
void			update_old_pwd(t_shell *shell, char *new_pwd);
int				cd_opt_check(t_shell *shell);
void	    	cd_canon(t_shell *shell);
void			read_history(t_node *history);

#endif
