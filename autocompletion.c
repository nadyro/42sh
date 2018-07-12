/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:04:15 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/12 21:32:22 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/sh_line_edit.h"
#include "include/builtins.h"

char	**fetch_from_env_o(void)
{
	int		i;
	int		y;
	char	*path;
	char	**all_paths;

	i = 0;
	y = 1;
	path = getenv("PATH");
	if (path)
	{
		while (path[i] != '\0')
		{
			if (path[i] == ':')
				y++;
			i++;
		}
		if (!(all_paths = (char **)malloc(sizeof(char *) * (y + 2))))
			return (NULL);
		all_paths[y + 1] = NULL;
		return (all_paths);
	}
	return (NULL);
}

char	**fetch_from_env_a(char **all_paths)
{
	int		i;
	int		j;
	int		ap_index;
	char	*path;

	i = 0;
	j = 0;
	ap_index = 0;
	path = getenv("PATH");
	if (path)
	{
		while (path[i] != '\0')
		{
			if (path[i] == ':')
			{
				all_paths[ap_index++] = ft_strsub(path, j, i - j);
				j = i + 1;
			}
			i++;
		}
		all_paths[ap_index] = ft_strsub(path, j, i - j);
		all_paths[ap_index + 1] = ft_strdup(".");
		return (all_paths);
	}
	return (NULL);
}

t_list	*fetch_binaries(char **all_paths)
{
	t_list	*tmp;
	t_list	*first;
	t_list	*binaries;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		if (!(tmp = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		tmp->content = ft_strdup(all_paths[i]);
		tmp->next = NULL;
		if (i != 0)
			binaries->next = tmp;
		else if (i == 0)
			first = tmp;
		binaries = tmp;
		i++;
	}
	return (first);
}

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

void	clean_tabs(char **t, int j)
{
	int		i;

	i = 0;
	while (t[i])
		ft_strclr(t[i++]);
	i = 0;
	while (t[i])
		ft_strdel(&t[i++]);
	if (j == 0)
		free(t);
}

void	send_nudes(t_list **my_phone)
{
	t_list	*nudes;

	nudes = *my_phone;
	while (nudes)
	{
		ft_putendl(nudes->content);
		nudes = nudes->next;
	}
}

void	free_lists(t_list *lst)
{
	t_list	*binaries_1;
	t_list	*tmp;

	binaries_1 = lst;
	while (binaries_1)
	{
		tmp = binaries_1->next;
		free(binaries_1->content);
		free(binaries_1);
		binaries_1 = tmp;
	}
	binaries_1 = NULL;
	lst = NULL;
}

void	print_nudes(t_list *matches)
{
	if (matches)
	{
		while (matches->previous != NULL)
			matches = matches->previous;
		send_nudes(&matches);
		while (matches->previous != NULL)
			matches = matches->previous;
		free_lists(matches);
	}
}

int		main(int argc, char **argv)
{
	char	**p;
	char	**k;
	t_list	*binaries;
	t_list	*binaries_1;
	t_list	*matches;

	(void)argc;
	p = fetch_from_env_o();
	k = fetch_from_env_a(p);
	binaries = NULL;
	binaries_1 = NULL;
	if (k)
	{
		binaries_1 = fetch_binaries(k);
		binaries = binaries_1;
		clean_tabs(k, 1);
		clean_tabs(p, 0);
	}
	matches = cmp_user_entry(binaries, argv[1]);
	free_lists(binaries_1);
	print_nudes(matches);
}
