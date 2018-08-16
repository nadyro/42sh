/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:04:15 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/16 10:16:56 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

t_node			*add_elements(t_node *lst, char *file_bin)
{
	t_node	*first;
	t_node	*elements;

	first = lst;
	elements = NULL;
	if (!(elements = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	elements->cmd = ft_strdup(file_bin);
	elements->next = NULL;
	if (lst == NULL)
	{
		elements->prev = NULL;
		lst = elements;
		return (lst);
	}
	while (first->next != NULL)
		first = first->next;
	first->next = elements;
	elements->prev = first;
	return (first);
}

t_node			*cmp_user_entry(t_node *lst, char *user_entry)
{
	t_node			*directories;
	t_node			*matches;
	DIR				*directory;
	struct dirent	*elements;
	struct stat		st;

	matches = NULL;
	directories = lst;
	while (directories && user_entry != NULL)
	{
		if ((directory = opendir(directories->cmd))
				&& (lstat(directories->cmd, &st) != -1))
		{
			while ((elements = readdir(directory)) != NULL)
				if (ft_strncmp(elements->d_name,
							user_entry, ft_strlen(user_entry)) == 0)
					matches = add_elements(matches, elements->d_name);
			closedir(directory);
		}
		directories = directories->next;
	}
	return (matches);
}

static	void	ft_norme(char *entry)
{
	if (entry != NULL)
		*(entry - 1) = '/';
}

t_node			*cmp_space_entry(char *a_name, int is_null)
{
	t_node			*matches;
	DIR				*directory;
	struct dirent	*elements;
	char			*entry;
	char			*path;

	UNUSED(is_null);
	matches = NULL;
	path = (a_name[0] == ' ' ? a_name + 1 : a_name);
	entry = ft_strrchr(a_name, '/');
	if (entry)
		*(entry++) = '\0';
	if ((directory = opendir((entry ? path : "./"))))
	{
		entry = (entry ? entry : path);
		while ((elements = readdir(directory)) != NULL)
			if (ft_strcmp(elements->d_name, ".") != 0
			&& ft_strcmp(elements->d_name, "..") != 0
			&& (ft_strncmp(elements->d_name, entry, ft_strlen(entry))) == 0)
				matches = add_elements(matches, elements->d_name);
		closedir(directory);
	}
	(entry != path && entry != a_name ? ft_norme(entry) : 0);
	return (matches);
}

char			**lst_to_array(t_node *matches)
{
	t_node	*lst;
	char	**matches_tab;
	int		i;

	i = 0;
	lst = matches;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	if (!(matches_tab = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	matches_tab[i] = NULL;
	i = 0;
	lst = matches;
	while (lst)
	{
		matches_tab[i++] = ft_strdup(lst->cmd);
		lst = lst->next;
	}
	return (matches_tab);
}
