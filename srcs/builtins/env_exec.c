/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:00:45 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 16:46:07 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"

static char	**get_new_args(t_shell *shell)
{
	int		count;
	int		start;
	char	**args;

	args = NULL;
	start = shell->list->last;
	count = 0;
	while (shell->args && shell->args[start++])
		count++;
	if (count)
	{
		if (!(args = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
	}
	count = 0;
	start = shell->list->last;
	while (shell->args && shell->args[start])
		args[count++] = ft_strdup(shell->args[start++]);
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
		shell->args = get_new_args(shell);
		shell->envv = mod;
		ast_execute(shell, cmd, 1);
		shell->envv = tmp;
		return (cmd->cmd_ret);
	}
	return (0);
}
