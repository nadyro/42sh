/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:40:11 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/17 15:51:55 by antoipom         ###   ########.fr       */
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

int				main(int argc, char **argv, char **env)
{
	t_shell			shell;
	char			*name_term;

	(void)argc;
	(void)argv;
	start_secure();
	shell.list = (env && env[0]) ? env_setup(env) : env_init();
	shell.envv = (shell.list) ? env_to_tab(shell.list) : NULL;
	shell.redir_error = 0;
	shell.last_hd = -1;
	shell.history_length = 0;
	shell.o_history = 0;
	shell.to_add = 0;
	shell.last_added = 0;
	shell.is_a = 0;
	shell.appnd_hst = NULL;
	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	main_loop(NULL, shell);
	return (0);
}
