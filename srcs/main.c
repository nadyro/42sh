/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:40:11 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/21 14:05:44 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		start_secure(void)
{
	struct stat		buf;
	struct winsize	term;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &term) == -1 || \
			(ioctl(STDERR_FILENO, TIOCGWINSZ, &term) == -1) || \
			(ioctl(STDIN_FILENO, TIOCGWINSZ, &term) == -1))
		sh_close(1, "");
	fstat(0, &buf);
	if (buf.st_size > 0)
		sh_close(1, "");
}

char			*ft_getenv(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (tmp->var && var && ft_strcmp(tmp->var, var) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

static void		add_underscore(t_env *env)
{
	t_env		*tmp;

	tmp = env;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp("_", tmp->var) == 0)
				return ;
			tmp = tmp->next;
		}
		if (tmp && tmp->next == NULL)
		{
			if (!(tmp->next = (t_env *)malloc(sizeof(t_env))))
				return ;
			tmp->next->var = ft_strdup("_");
			tmp->next->val = ft_strdup("/usr/bin/env");
			tmp->next->prev = tmp;
			tmp->next->next = NULL;
			return ;
		}
	}
}

static void		init_shell_ints(t_shell *shell)
{
	shell->last_hd = -1;
	shell->last_id = -1;
	shell->history_length = 0;
	shell->o_history = 0;
	shell->to_add = 0;
	shell->last_added = 0;
	shell->is_a = 0;
}

int				main(int argc, char **argv, char **env)
{
	t_shell			shell;
	char			*name_term;

	(void)argc;
	(void)argv;
	start_secure();
	shell.list = (env && env[0]) ? env_setup(env) : env_init();
	if (ft_getenv("_", shell.list) == NULL)
		add_underscore(shell.list);
	shell.envv = (shell.list) ? env_to_tab(shell.list) : NULL;
	init_shell_ints(&shell);
	shell.appnd_hst = NULL;
	if (!(name_term = ft_getenv("TERM", shell.list)))
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	main_loop(NULL, shell);
	return (0);
}
