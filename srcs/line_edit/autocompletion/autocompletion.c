/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:04:15 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/21 13:15:58 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

t_list	*add_elements(t_list *lst, char *file_bin)
{
	t_list	*first;
	t_list	*elements;

	first = lst;
	elements = NULL;
	if (!(elements = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	elements->content = ft_strdup(file_bin);
	elements->next = NULL;
	if (lst == NULL)
	{
		elements->previous = NULL;
		lst = elements;
		return (lst);
	}
	while (first->next != NULL)
		first = first->next;
	first->next = elements;
	elements->previous = first;
	return (first);
}

t_list	*cmp_user_entry(t_list *lst, char *user_entry)
{
	t_list			*directories;
	t_list			*matches;
	DIR				*directory;
	struct dirent	*elements;
	struct stat		st;

	matches = NULL;
	directories = lst;
	while (directories && user_entry != NULL)
	{
		if ((directory = opendir(directories->content))
				&& (lstat(directories->content, &st) != -1))
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

t_list	*cmp_space_entry(char *a_name)
{
	t_list			*matches;
	DIR				*directory;
	struct dirent	*elements;
	struct stat		st;

	matches = NULL;
	if ((lstat(a_name, &st) != -1) && (directory = opendir(a_name)))
	{
		while ((elements = readdir(directory)) != NULL)
			matches = add_elements(matches, elements->d_name);
		closedir(directory);
	}
	return (matches);
}

int		main(int argc, char **argv)
{
	t_list	*matches;

	(void)argc;
	matches = fetch_names(argv[1]);
	print_nudes(matches);
}
