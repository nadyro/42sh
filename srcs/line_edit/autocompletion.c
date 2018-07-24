/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:04:15 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/21 19:21:32 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

t_node	*add_elements(t_node *lst, char *file_bin)
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

t_node	*cmp_user_entry(t_node *lst, char *user_entry)
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

t_node	*cmp_space_entry(char *a_name, int	is_null)
{
	t_node			*matches;
	DIR				*directory;
	struct dirent	*elements;
	struct stat		st;

	matches = NULL;
	if (is_null == 1 && (directory = opendir("./")))
	{
		while ((elements = readdir(directory)) != NULL)
		if ((ft_strncmp(elements->d_name, a_name, ft_strlen(a_name))) == 0)
				matches = add_elements(matches, elements->d_name);
		closedir(directory);
	}
	else if (is_null == 0 && (lstat(a_name, &st) != -1) 
			&& (directory = opendir(a_name)))
	{
		while ((elements = readdir(directory)) != NULL)
			matches = add_elements(matches, elements->d_name);
		closedir(directory);
	}
	return (matches);
}

char	**lst_to_array(t_node *matches)
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

int		write_completion(t_prompt *prompt, int *y)
{
	t_node	*matches;
	char	**matches_tab;
	int		i;
	int		x;

	x = *y;
	matches = NULL;
	matches_tab = NULL;
	i = 0;
	matches = fetch_names(prompt->line);
	while (matches && matches->prev != NULL)
		matches = matches->prev;
	matches_tab = lst_to_array(matches);
	while (matches_tab[i])
			i++;
	if (i != 0)
	{
		ft_putstr(matches_tab[x++]);
		ft_putstr(" ");
	}
	if (i == x)
		x = 0;
	*y = x;
	return (i);
}