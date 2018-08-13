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

void	*history_m(int cmd, void *ptr)
{
	static t_node	*history;
	static int		use;

	if (cmd == 0)
	{
		history = (t_node*)ptr;
		use = 0;
	}
	else if (cmd == 1)
		use = 1;
	else if (cmd == 2)
		return ((void*)(size_t)use);
	return ((void*)history);
}

/*
 **	otm[0] => stat
 **	otm[0] => cursor
 */

void	history_get(int	*tko, char *str, int len)
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

char	*history_research(int *tk, char *str, t_node *hist)
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
