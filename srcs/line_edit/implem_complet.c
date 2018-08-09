/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_complet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 03:07:12 by azybert           #+#    #+#             */
/*   Updated: 2018/08/09 09:19:44 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void		final_display(t_prompt *prompt, char *to_display)
{
	size_t	rpos;
	char	*rline;

	rpos = prompt->pos;
	move_cursor(prompt, 0, true);
	rline = prompt->line;
	prompt->line = to_display;
	prompt->total = ft_strlen(prompt->line);
	tputs(tgetstr("cd", NULL), 0, ft_putshit);
	write_data(prompt, prompt->line, prompt->total);
	prompt->line = rline;
	prompt->total = ft_strlen(prompt->line);
	move_cursor(prompt, rpos, true);
}

void		completion_display_aux(t_prompt *prompt,
		t_node *complete, int nb, int max)
{
	char	*to_display;
	char	*spn;
	int		count;

	if (!(to_display =
				ft_memalloc(sizeof(char) * nb * max + 1 + prompt->total + 1)))
		exit(1);
	ft_strcat(to_display, prompt->line);
	ft_strcat(to_display, "\n");
	count = 0;
	while (complete)
	{
		ft_strcat(to_display, complete->cmd);
		spn = ft_strchr(to_display, '\0');
		if (++count % (prompt->size->x / max) == 0)
			ft_strcat(to_display, "\n");
		else
			ft_memset(spn, ' ', max - ft_strlen(complete->cmd));
		complete = complete->next;
		(complete != NULL ? free(complete->prev->cmd) : 0);
		(complete != NULL ? free(complete->prev) : 0);
	}
	final_display(prompt, to_display);
	free(to_display);
}

void		completion_display(t_prompt *prompt, t_node *complete)
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
	completion_display_aux(prompt, complete, nb, max);
	free(loop->cmd);
	free(loop);
}

static void	auto_complete_aux(t_prompt *prompt, t_node *complete)
{
	while (prompt->pos > 0 && prompt->line[prompt->pos - 1] != '/'
			&& prompt->line[prompt->pos - 1] != ' ')
		prompt_delete(prompt);
	secure_stock(prompt, complete->cmd);
	free(complete->cmd);
	free(complete);
}

void		auto_complete(t_prompt *prompt)
{
	t_node	*complete;
	char	*arg;
	char	*halp;
	char	*to_free;

	arg = ft_strndup(prompt->line, prompt->pos);
	halp = (ft_strrchr(arg, ' ') ? ft_strrchr(arg, ' ') : 0);
	to_free = arg;
	if (halp == NULL)
		arg = ft_strndup(prompt->line, prompt->pos);
	else
		arg = ft_strdup(halp);
	complete = fetch_names(arg);
	while (complete && complete->prev)
		complete = complete->prev;
	if (complete && complete->next == NULL)
		auto_complete_aux(prompt, complete);
	else if (complete)
		completion_display(prompt, complete);
	free(arg);
	free(to_free);
}
