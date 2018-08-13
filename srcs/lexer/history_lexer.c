/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <tcanaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:14:56 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/13 02:46:45 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "sh_line_edit.h"

static unsigned int	g_grp[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 5, 1, 0, 0, 0,
	0, 5, 0, 0, 0, 0, 0, 0, 3, 0, 0, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 5, 5,
	0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static unsigned char	g_otm[8][6][2] = {
	{
		{0, 1}, {1, 1},
		{0, 1}, {0, 1}, {0, 1}, {0, 1}
	},{
		{3, 1}, {6, 1},
		{4, 1}, {7, 1}, {5, 1}, {2, 0}
	},{
		{2, 0}, {2, 0},
		{2, 0}, {2, 0}, {2, 0}, {2, 0}
	},{
		{3, 1}, {3, 1},
		{3, 1}, {3, 1}, {3, 1}, {2, 0}
	},{
		{4, 1}, {4, 1},
		{4, 1}, {4, 1}, {4, 1}, {2, 0}
	},{
		{2, 0}, {2, 0},
		{2, 0}, {2, 0}, {5, 1}, {2, 0}
	},{
		{2, 0}, {2, 0},
		{2, 0}, {2, 0}, {2, 0}, {2, 0}
	},{
		{3, 1}, {3, 1},
			{3, 1}, {3, 1}, {5, 1}, {2, 0}
	}
};

/*
 **	otm[0] => stat
 **	otm[0] => cursor
 */

static void	history_get(int	*tko, char *str, int len)
{
	int		otm[2];
	int		old;
	int		start;

	ft_bzero(otm, sizeof(int) * 2);
	while (otm[0] != 2 && otm[1] < len)
	{
		old = otm[0];
		otm[0] = g_otm[old][(int)g_grp[(int)*(str + otm[1])]][0];
		(otm[0] != 0 && old == 0) ? start = otm[1] : 0;
		otm[1] += g_otm[old][(int)g_grp[(int)*(str + otm[1])]][1];
	}
	tko[0] = otm[0] == 2 ? old : otm[0];
	tko[1] = start;
	tko[2] = otm[1] - start;
}

static char *history_iresearch(int *tk, char *str, t_node *hist)
{
	int	i;

	i = tk[0] == 5 ? ft_natoi(str + tk[1] + 1, tk[2] - 1) : -1;
	if (i > 0)
	{
		while (hist && hist->next != NULL)
			hist = hist->next;
		while (i-- > 1 && hist)
			hist = hist->prev;
	}
	else if (i < 0)
	{
		while (i++ != -1 && hist)
			hist = hist->next;
	}
	else if (i == 0)
		return (NULL);
	if (hist && i == 0)
		return (hist->cmd);
	return (NULL);
}

static char	*history_research(int *tk, char *str, t_node *hist)
{
	int	shift;

	shift = tk[0] == 4 ? 2 : 1;
	if (tk[0] == 3 || tk[0] == 4 || tk[0] == 7)
		while (hist)
		{
			if (tk[0] == 3 && (int)ft_strlen(hist->cmd) >= (tk[2] - shift)
					&& !ft_memcmp(str + tk[1] + shift, hist->cmd, tk[2] - shift))
				return (hist->cmd);
			else if (tk[0] == 4 && (int)ft_strlen(hist->cmd) >= (tk[2] - shift)
					&& ft_strnstr2(hist->cmd, str + tk[1] + shift, tk[2] - shift))
				return (hist->cmd);
			hist = hist->next;
		}
	else if (tk[0] == 6 || tk[0] == 5)
		return (history_iresearch(tk, str, hist));
	return (NULL);
}

void		*history_ptr(int cmd, void *ptr)
{
	static t_node	*history = NULL;
	static void		**use;
	static int		n[2];
	void			**tmp;

	printf("USE: %p\nN[0]: %d\n", use, n[0]);
	if (cmd == 0)
	{
		history = (t_node*)ptr;
	}
	else if (cmd == 2 && history_ptr(3, ptr) == 0)
	{
		printf("ADD>%zu|n[0]>%d\n", (size_t)ptr, n[0]);
		tmp = use;
		if ((use = (void**)malloc(sizeof(void*) * n[0] + sizeof(size_t))) == NULL)
			return (NULL);
		n[1] = 0;
		while (n[1] < n[0])
		{
			use[n[1]] = tmp[n[1]];
			n[1]+=1;
		}
		use[n[1]] = ptr;
		n[0]++;
		free(tmp);
	}
	else if (cmd == 3)
	{
		for (int i = 0; i< n[0]; i++)
			printf("adr[%d]>%p | %p\n", i, use[i], ptr);
		n[1] = 0;
		while (n[1] < n[0] && use[n[1]] != ptr)
			n[1]++;
		if (n[1] < n[0] && use[n[1]] == ptr)
			return ((void*)1);
		return ((void*)0);
	}
	if (cmd == 4 || cmd == 0)
	{
		free(use);
		use = NULL;
		n[0] = 0;
	}
	if (cmd == 5)
	{
		return ((void*)(size_t)(n[0]>0));
	}
	return (history);
}

char		*event_not_exist(int *tk, char *line)
{
	ft_putstr("42sh: no such event: ");
	ft_putbyte(line + tk[1] + 1, tk[2] - 1);
	ft_putchar('\n');
	return (NULL);
}

char		*bang_replace(int *token, char *line)
{
	int		tk[3];
	char	*new_line;
	char	*history;
	int		hlen;

	history_get(tk, line + token[1], token[2]);
	if ((history = history_research(tk, line + token[1], history_ptr(1, NULL))) == NULL)
		return (event_not_exist(tk, line + token[1]));
	hlen = ft_strlen(history);
	//printf("[his]%zu\n[get]%zu\nhist>%s\n", (size_t)history_ptr(3, history), (size_t)history, history);
	if (history_ptr(3, history) || (hlen <= (int)ft_strlen(line) && ft_memcmp(line + token[1] + tk[1] + tk[2] - hlen, history, hlen) == 0))
	{
		token[0] = TK_WORD;
		return (NULL);
	}
	if (!(new_line = (char*)ft_memalloc(ft_strlen(line) + hlen - tk[2] + 1)))
		return (NULL);
	ft_memcpy(new_line, line, token[1] + tk[1]);
	ft_memcpy(new_line + tk[1] + token[1], history, hlen);
	ft_memcpy(new_line + tk[1] + token[1] + hlen, line + token[1] + tk[1] + tk[2], ft_strlen(line) - (token[1] + tk[1] + tk[2]));
	//printf("ORIGINset>%zu\n", (size_t)history);
	history_ptr(2, history);
	return (new_line);
}
