/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 07:03:55 by azybert           #+#    #+#             */
/*   Updated: 2018/07/21 12:56:48 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*end_this_pain(t_gnl_node *node, char *tmp_line, int k, char *line)
{
	if (tmp_line[k] != '\n' && k == 0)
	{
		node->ended = 1;
		return (NULL);
	}
	if (node->to_read > 0)
		ft_strcpy(node->next_line, &tmp_line[k + 1]);
	tmp_line[k] = '\0';
	if (!(line = ft_strdup(tmp_line)))
	{
		free(tmp_line);
		return (NULL);
	}
	free(tmp_line);
	return (line);
}

char	*ft_function(t_gnl_node *node, char *line)
{
	int			k;
	char		*tmp_line;

	k = 0;
	tmp_line = NULL;
	if (node->to_read > 0)
		if (!(tmp_line = ft_strdup(node->next_line)))
			return (NULL);
	while (1)
	{
		if (node->to_read <= 0)
		{
			if (!(tmp_line = ft_realloc(tmp_line, (k + BUFF_SIZE + 1))))
				return (NULL);
			node->to_read = read(node->fd, &tmp_line[k], BUFF_SIZE);
			if (node->to_read <= 0)
				return (end_this_pain(node, tmp_line, k, line));
			tmp_line[k + node->to_read] = '\0';
		}
		while (node->to_read-- > 0 && tmp_line[k] != '\n')
			k++;
		if (tmp_line[k] == '\n')
			return (end_this_pain(node, tmp_line, k, line));
	}
}

t_gnl_node *get_node(t_gnl_list *global, int fd)
{
	t_gnl_node *node;
	t_gnl_node *new;

	node = global->first;
	while (node->next != NULL)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	if (node->fd == fd)
		return (node);
	else
	{
		if ((new = malloc(sizeof(*new))) == NULL)
			return (NULL);
		new->fd = fd;
		new->to_read = 0;
		new->ended = 0;
		if ((new->next_line = malloc(sizeof(char *) * BUFF_SIZE + 1)) == NULL)
			return (NULL);
		new->next = NULL;
		node->next = new;
		return (new);
	}
}

t_gnl_list	*set_gnl_list(int fd)
{
	t_gnl_list	*global;
	t_gnl_node *first_node;

	if ((global = malloc(sizeof(*global))) == NULL)
		return (NULL);
	if ((first_node = malloc(sizeof(*first_node))) == NULL)
		return (NULL);
	first_node->fd = fd;
	first_node->to_read = 0;
	first_node->ended = 0;
	if ((first_node->next_line = malloc(sizeof(char *) *
					BUFF_SIZE + 1)) == NULL)
		return (NULL);
	first_node->next = NULL;
	global->first = first_node;
	return (global);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl_list	*global = NULL;
	t_gnl_node		*node;

	if (read(fd, NULL, 0) < 0)
		return (-1);
	if (global == NULL)
		if ((global = set_gnl_list(fd)) == NULL)
			return (-1);
	if ((node = get_node(global, fd)) == NULL)
		return (-1);
	if ((*line = ft_function(node, *line)) == NULL && node->ended == 0)
		return (-1);
	if (node->ended == 1)
		return (0);
	return (1);
}
