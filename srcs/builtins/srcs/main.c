/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:58:33 by arohani           #+#    #+#             */
/*   Updated: 2018/02/22 15:23:10 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_shell		shell;

	shell.list = (env && env[0]) ? env_setup(env) : env_init();
	shell.envv = (shell.list) ? env_to_tab(shell.list) : NULL;
	if (ac >= 1 && av)
		ash_loop(&shell);
	if (shell.list && shell.list->var && shell.list->var[0])
		free_env(shell.list);
	return (0);
}
