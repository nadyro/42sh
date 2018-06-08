/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:20:24 by arohani           #+#    #+#             */
/*   Updated: 2018/02/21 13:28:09 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env			*env_init(void)
{
	t_env	*head;
	char	cwd[256];

	if (!(head = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	head->prev = NULL;
	head->next = NULL;
	head->mod = NULL;
	head->var = ft_strdup("_");
	head->val = ft_strdup("/usr/bin/env");
	if (!(head->next = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	head->next->var = ft_strdup("PWD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_putstr_fd("error retrieving cwd\n", 2);
	head->next->val = (cwd[0]) ? ft_strdup(cwd) : NULL;
	head->next->prev = head;
	head->next->next = NULL;
	head->next->mod = NULL;
	return (head);
}

static t_env	*env_single(char *full_env)
{
	t_env	*list;
	char	*chr;
	char	**av;

	list = NULL;
	if (full_env && (chr = ft_strchr(full_env, '=')))
		if (!(list = (t_env *)malloc(sizeof(t_env))))
			return (NULL);
	if (list && full_env && chr)
	{
		av = ft_strsplit(full_env, '=');
		list->var = ft_strdup(av[0]);
		list->val = (chr + 1 && (chr + 1)[0]) ? ft_strdup(chr + 1) : NULL;
		list->mod = NULL;
		list->prev = NULL;
		list->next = NULL;
		if (av && av[0])
			free_table(av);
	}
	return (list);
}

t_env			*env_setup(char **env)
{
	t_env	*list;
	t_env	*head;
	t_env	*prev;
	int		i;

	i = 0;
	prev = NULL;
	list = (env[i] && ft_strchr(env[i], '=')) ? env_single(env[i]) : NULL;
	if (list)
	{
		list->last = 0;
		list->mod = NULL;
	}
	head = (list) ? list : NULL;
	while (env && env[++i])
	{
		list->next = env_single(env[i]);
		prev = list;
		list = list->next;
		list->prev = (prev) ? prev : NULL;
	}
	return (head);
}
