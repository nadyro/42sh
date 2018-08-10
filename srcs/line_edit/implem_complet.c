/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_complet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 03:07:12 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:51:57 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	final_display(t_g_prpt *g_prpt, char *to_display)
{
	size_t	rpos;
	char	*rline;

	rpos = g_prpt->pos;
	move_cursor(g_prpt, 0, true);
	rline = g_prpt->line;
	g_prpt->line = to_display;
	g_prpt->total = ft_strlen(g_prpt->line);
	tputs(tgetstr("cd", NULL), 0, ft_putshit);
	write_data(g_prpt, g_prpt->line, g_prpt->total);
	g_prpt->line = rline;
	g_prpt->total = ft_strlen(g_prpt->line);
	move_cursor(g_prpt, rpos, true);
}

static void	completion_display_aux(t_g_prpt *g_prpt,
		t_node *complete, int nb, int max)
{
	char	*to_display;
	char	*spn;
	int		count;

	if (!(to_display =
				ft_memalloc(sizeof(char) * nb * max + 1 + g_prpt->total + 1)))
		exit(1);
	ft_strcat(to_display, g_prpt->line);
	ft_strcat(to_display, "\n");
	count = 0;
	while (complete)
	{
		ft_strcat(to_display, complete->cmd);
		spn = ft_strchr(to_display, '\0');
		if (++count % (g_prpt->size->x / max) == 0)
			ft_strcat(to_display, "\n");
		else
			ft_memset(spn, ' ', max - ft_strlen(complete->cmd));
		complete = complete->next;
		(complete != NULL ? free(complete->prev->cmd) : 0);
		(complete != NULL ? free(complete->prev) : 0);
	}
	final_display(g_prpt, to_display);
	free(to_display);
}

static void	completion_display(t_g_prpt *g_prpt, t_node *complete)
{
	t_node	*loop;
	size_t	max;
	int		nb;

	loop = complete;
	nb = 1;
	max = ft_strlen(loop->cmd);
	while (loop->next != NULL)
	{
		max = (ft_strlen(loop->next->cmd) > max ?
				ft_strlen(loop->next->cmd) : max);
		nb++;
		loop = loop->next;
	}
	max++;
	completion_display_aux(g_prpt, complete, nb, max);
	free(loop->cmd);
	free(loop);
}

static void	auto_complete_aux(t_g_prpt *g_prpt, t_node *complete)
{
	while (g_prpt->pos > 0 && g_prpt->line[g_prpt->pos - 1] != '/'
			&& g_prpt->line[g_prpt->pos - 1] != ' ')
		g_prpt_delete(g_prpt);
	secure_stock(g_prpt, complete->cmd);
	free(complete->cmd);
	free(complete);
}

void		auto_complete(t_g_prpt *g_prpt)
{
	t_node	*complete;
	char	*arg;
	char	*halp;
	char	*to_free;

	arg = ft_strndup(g_prpt->line, g_prpt->pos);
	halp = (ft_strrchr(arg, ' ') ? ft_strrchr(arg, ' ') : 0);
	if (halp && halp != arg && is_pre_binary(*(halp - 1)) == 1)
		halp = halp + 1;
	to_free = arg;
	if (halp == NULL)
		arg = ft_strndup(g_prpt->line, g_prpt->pos);
	else
		arg = ft_strdup(halp);
	complete = fetch_names(arg);
	while (complete && complete->prev)
		complete = complete->prev;
	if (complete && complete->next == NULL)
		auto_complete_aux(g_prpt, complete);
	else if (complete)
		completion_display(g_prpt, complete);
	free(arg);
	free(to_free);
	(g_prpt->origin->y < (size_t)-1000000 ? 0 : g_prpt_clean());
}
