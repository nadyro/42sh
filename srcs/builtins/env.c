/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:36:41 by arohani           #+#    #+#             */
/*   Updated: 2018/07/26 18:05:03 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#define USGERROR "\nusage: env [-i] [name=value ...] [utility [argument ...]]\n"

static void		add_to_env_i(t_shell *shell, int *k)
{
	char	**env;
	int		i;

	i = 0;
	if (!(env = (char **)malloc(sizeof(char *) * (*k - 1))))
		return ;
	*k = 2;
	while (shell->args[*k] && ft_strchr(shell->args[*k], '=')
		&& ft_strlen(shell->args[*k]) != 1)
		env[i++] = ft_strdup(shell->args[(*k)++]);
	env[i] = 0;
	if (shell->args && (shell->args[*k]) && !(ft_strchr(shell->args[*k], '=')))
	{
		shell->list->last = *k;
		shell->list->mod = (env && env[0]) ? env_setup(env) : NULL;
		ft_exec(shell, env);
		if (env && env[0])
			free_table(env);
		free_env(shell->list->mod);
	}
	else if (env && env[0])
	{
		ft_print_table(env);
		free_table(env);
	}
}

static void		ash_env_i(t_shell *shell)
{
	char	**env;
	int		k;

	env = NULL;
	k = 2;
	while (shell->args[k] && ft_strchr(shell->args[k], '='))
		k++;
	if (k > 2)
		add_to_env_i(shell, &k);
	else if (shell->list && shell->args &&
		(shell->args[k]) && !(ft_strchr(shell->args[k], '=')))
	{
		shell->list->last = k;
		ft_exec(shell, env);
	}
	else
		ft_print_table(env);
}

static void		process_env_args(t_shell *shell)
{
	char	**envs;

	envs = NULL;
	if (shell->args && shell->args[1])
	{
		if (ft_strchr(shell->args[1], '=') && ft_strlen(shell->args[1]) != 1)
		{
			ash_env_mod(shell);
			envs = env_to_tab(shell->list->mod);
			if (shell->args[shell->list->last])
				(envs) ? ft_exec(shell, envs) : ft_exec(shell, shell->envv);
			else
				ft_print_table(envs);
			free_env(shell->list->mod);
		}
		else if (!(shell->args[shell->list->last]))
			ft_print_table(envs);
		else
			ft_exec(shell, shell->envv);
	}
	if (envs && envs[0])
		free_table(envs);
}

int				ash_env(t_shell *shell)
{
	if (shell->args && shell->args[1] && ft_strcmp(shell->args[1], "-i") == 0)
		ash_env_i(shell);
	else if (shell->args && shell->args[1] &&
		shell->args[1][0] == '-' && shell->args[1][1])
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(shell->args[1][1], 2);
		ft_putstr_fd(USGERROR, 2);
	}
	else if (shell->args && shell->args[1])
		process_env_args(shell);
	else if (shell->args[1] == 0)
		ft_print_table(shell->envv);
	return (1);
}

char			**env_to_tab(t_env *list)
{
	char	**tabs;
	int		count;
	t_env	*tmp;
	char	*str;

	count = 0;
	tmp = list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	if (!(tabs = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	tabs[count] = 0;
	tmp = list;
	count = 0;
	while (tmp)
	{
		str = ft_strjoin(tmp->var, "=");
		tabs[count++] = (tmp->val) ? ft_strjoin(str, tmp->val) : ft_strdup(str);
		ft_strdel(&str);
		tmp = tmp->next;
	}
	return (tabs);
}
