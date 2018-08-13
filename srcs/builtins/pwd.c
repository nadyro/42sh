/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:32:14 by arohani           #+#    #+#             */
/*   Updated: 2018/08/13 16:59:52 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		finish_pwd_switch(t_shell *shell, t_env *tmp, char *old_pwd)
{
	tmp->val = (old_pwd && old_pwd[0]) ? ft_strdup(old_pwd) : NULL;
	if (old_pwd && old_pwd[0])
		ft_strdel(&old_pwd);
	if (shell->envv && shell->envv[0])
		free_table(shell->envv);
	shell->envv = env_to_tab(shell->list);
	return ;
}

static char		*get_old_pwd(t_shell *shell, t_env **tmp, char *new_pwd)
{
	char	*old_pwd;

	old_pwd = ((*tmp)->val) ? ft_strdup((*tmp)->val) : NULL;
	if ((*tmp)->val && (*tmp)->val[0])
	{
		free((*tmp)->val);
		(*tmp)->val = ft_strdup(new_pwd);
		(*tmp) = shell->list;
	}
	return (old_pwd);
}

static void		append_old_pwd(char *old_pwd, t_env **tmp)
{
	t_env	*temp;

	temp = NULL;
	if (!((*tmp)->next) && ft_strcmp((*tmp)->var, "OLDPWD") != 0)
	{
		temp = (!((*tmp)->next)) ? *tmp : NULL;
		if (!(temp->next))
		{
			if (!(temp->next = (t_env *)malloc(sizeof(t_env))))
				return ;
			temp->next->prev = temp;
			temp->next->var = ft_strdup("OLDPWD");
			temp->next->val = ft_strdup(old_pwd);
			if (old_pwd)
				ft_strdel(&old_pwd);
			temp->next->next = NULL;
		}
	}
}

static int		switch_existing_pwd(t_shell *shell, t_env **tmp, char *new_pwd)
{
	char	*old_pwd;
	t_env	*temp;

	old_pwd = get_old_pwd(shell, tmp, new_pwd);
	temp = shell->list;
	while (temp)
	{
		if (ft_strcmp(temp->var, "OLDPWD") == 0)
		{
			if (temp->val && temp->val[0])
				ft_strdel(&(temp->val));
			if (old_pwd && old_pwd[0])
				finish_pwd_switch(shell, temp, old_pwd);
			return (1);
		}
		if (!(temp->next) && ft_strcmp(temp->var, "OLDPWD") != 0)
		{
			append_old_pwd(old_pwd, &temp);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void			update_old_pwd(t_shell *shell, char *new_pwd)
{
	int		ret;
	t_env	*tmp;

	ret = 0;
	tmp = shell->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PWD") == 0)
		{
			ret = switch_existing_pwd(shell, &tmp, new_pwd);
			if (ret == 1)
				return ;
		}
		else
			tmp = tmp->next;
	}
}
