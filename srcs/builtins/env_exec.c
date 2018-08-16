/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:00:45 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 16:17:34 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"
#include <stdio.h>

static char	**get_new_args(t_shell *shell)
{
	int		count;
	int		start;
	char	**args;

	fprintf(stderr, "DEBUG 1, shell->list->last = %d\n", shell->list->last);
	args = NULL;
	start = shell->list->last;
	count = 0;
	fprintf(stderr, "DEBUG 2\n");
	while (shell->args && shell->args[start++])
		count++;
	fprintf(stderr, "DEBUG 3, count = %d\n", count);
	if (count)
	{
		if (!(args = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
	}
	count = 0;
	start = shell->list->last;
	fprintf(stderr, "DEBUG 4\n");
	while (shell->args && shell->args[start])
	{
		fprintf(stderr, "DEBUG 5, storing %s into new_args\n", shell->args[start]);
		args[count++] = ft_strdup(shell->args[start++]);
		fprintf(stderr, "DEBUG 5b, after attempt, args = %s\n", args[count - 1]);
	}
	if (count)
		args[count] = 0;
	if (shell->args && shell->args[0])
		free_table(shell->args);
	return (args);
}

int			ft_exec(t_shell *shell, t_ast *cmd, char **mod)
{
	char	**tmp;

	tmp = shell->envv;
	if (shell->list->last == 0 && shell->args[1])
		shell->list->last = 1;
	if (shell->args[0] != NULL)
	{
		fprintf(stderr, "before env exec, arg table is : \n");
		ft_print_table(shell->args);
		shell->args = get_new_args(shell);
		fprintf(stderr, "now the arg table is : \n");
		ft_print_table(shell->args);
		shell->envv = mod;
		ast_execute(shell, cmd);
		shell->envv = tmp;
		return (cmd->cmd_ret);
	}
	return (0);
}
