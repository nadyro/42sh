/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 16:16:05 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/30 17:23:13 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

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
		if (!(all_paths = (char **)malloc(sizeof(char *) * (y + 1))))
			return (NULL);
		all_paths[y] = NULL;
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
		return (all_paths);
	}
	return (NULL);
}

t_node	*fetch_binaries(char **all_paths)
{
	t_node	*tmp;
	t_node	*first;
	t_node	*binaries;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		if (!(tmp = (t_node *)malloc(sizeof(t_node))))
			return (NULL);
		tmp->cmd = ft_strdup(all_paths[i]);
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

int		fetch_names_dirent(char *user_entry)
{
	struct stat		st;

	if ((lstat(user_entry, &st) != -1))
		if (st.st_mode & S_IFDIR)
			return (0);
	return (1);
}

t_node	*fetch_names(char *user_entry)
{
	char	**p;
	char	**k;
	t_node	*binaries;
	t_node	*binaries_1;
	t_node	*matches;

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
	if (user_entry && (ft_strncmp(user_entry, " ", 1) == 0
				|| ft_strcmp(user_entry, "") == 0))
		matches = cmp_space_entry("./", 0);
	else
		matches = cmp_user_entry(binaries, user_entry);
	matches = (matches ? matches : cmp_space_entry(user_entry, 1));
	free_lists(binaries_1);
	return (matches);
}