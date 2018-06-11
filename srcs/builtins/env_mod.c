/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:47:41 by arohani           #+#    #+#             */
/*   Updated: 2018/06/11 13:15:26 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	change_mod_values_3(t_shell *shell, t_env *mods, int k, char **av)
{
	char	*chr;

	chr = ft_strchr(shell->args[k], '=');
	if (mods->var)
		ft_strdel(&mods->var);
	mods->var = ft_strdup(av[0]);
	if (mods->val)
		ft_strdel(&(mods->val));
	mods->val = (av[1]) ? ft_strdup(chr + 1) : NULL;
	while ((chr = ft_strchr(shell->args[k], '=')))
		*chr = '&';
	k = 1;
	if (av && av[0])
		free_table(av);
}

static int	change_mod_values_2(t_shell *shell, t_env *mods, int k, t_env *head)
{
	char	*chr;
	char	**av;
	int		last;

	last = shell->list->last;
	while (k < last && shell->args[k])
	{
		if ((chr = ft_strchr(shell->args[k], '=')))
		{
			av = ft_strsplit(shell->args[k], '=');
			if (ft_strcmp(av[0], mods->var) == 0)
			{
				change_mod_values_3(shell, mods, k, av);
				mods = head;
				break ;
			}
			else if (av && av[0])
				free_table(av);
			k++;
		}
		else
			k++;
	}
	return (k);
}

static void	change_mod_values(t_shell *shell, t_env *head)
{
	int		k;
	int		last;
	t_env	*mods;

	k = 1;
	last = shell->list->last;
	mods = head;
	while (mods)
	{
		k = change_mod_values_2(shell, mods, k, head);
		if (k == last && mods)
		{
			mods = mods->next;
			k = 1;
		}
	}
}

int			ash_env_mod(t_shell *shell)
{
	t_env	*tmp;
	int		k;
	t_env	*mods;
	char	*chr;

	k = 1;
	tmp = shell->list;
	tmp->mod = env_setup(shell->envv);
	while (shell->args[k] && (chr = ft_strchr(shell->args[k], '=')))
		k++;
	shell->list->last = (k == 1 && shell->args[k]
		&& shell->args[k + 1]) ? 2 : k;
	mods = tmp->mod;
	change_mod_values(shell, mods);
	k = 1;
	while (shell->args && shell->args[k] && k < shell->list->last)
	{
		if (ft_strchr(shell->args[k], '='))
			add_to_mod(shell);
		k++;
	}
	return (1);
}
