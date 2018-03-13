/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/03/13 20:50:45 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

static t_prompt	*malloc_prompt(void)
{
	t_prompt		*prompt;
	struct winsize	w;

	if (!(prompt = malloc(sizeof(*prompt))))
		exit(1);
	if (!(prompt->origin = malloc(sizeof(t_coord))))
		exit(1);
	if (!(prompt->size = malloc(sizeof(t_coord))))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->line = NULL;
	prompt->pos = 0;
	prompt->total = 0;
	get_cursor_pos(prompt->origin);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	prompt->quotes = none;
	return (prompt);
}

static void		react(t_prompt *prompt)
{
	if (prompt->nb_read == 1 && ft_isprint(prompt->c[0]))
		prompt_stock(prompt);
	else if (prompt->nb_read == 1 && prompt->c[0] == 127 && prompt->pos > 0)
		prompt_delete(prompt);
	else if (prompt->nb_read == 4 && prompt->c[3] == 126 &&
			prompt->pos < prompt->total)
		prompt_backdel(prompt);
	/*else if (prompt->nb_read == 3 && prompt->c[2] == 65)
	 historique up;
	else if (prompt->nb_read == 3 && prompt->c[2] == 66)
	historique down;*/
	else if (prompt->nb_read == 3 && prompt->c[2] == 68 && prompt->pos > 0)
		move_cursor(prompt, prompt->pos - 1, true);
	else if (prompt->nb_read == 3 && prompt->c[2] == 67 &&
			prompt->pos < prompt->total)
		move_cursor(prompt, prompt->pos + 1, true);
	else if (prompt->nb_read == 3 && prompt->c[2] == 72)
		move_cursor(prompt, 0, true);
	else if (prompt->nb_read == 3 && prompt->c[2] == 70)
		move_cursor(prompt, prompt->total, true);
	else if (prompt->nb_read == 6 && prompt->c[5] == 68)
		ft_cursor_word_left(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 67)
		ft_cursor_word_right(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 65)
		ft_cursor_up(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 66)
		ft_cursor_down(prompt);
	else if (prompt->nb_read == 1 && prompt->c[0] == '\n')
	{
		move_cursor(prompt, prompt->total, true);
		prompt_stock(prompt);
	}
}

char			*prompt()
{
	char		*to_return;
	int			k;
	//char		*BC;
	//char		*UP;
	t_prompt	*prompt;
	//BC = tgetstr ("le", NULL);
	//UP = tgetstr ("up", NULL);

	write(1, "prompt> ", 8);
	prompt = malloc_prompt();
	to_return = NULL;
	//call signal functions;
	k = 1;
	while (to_return == NULL || prompt->quotes != none)
	{
		prompt->nb_read = read(1, prompt->c, 6);
		react(prompt);
		if (prompt->total > 0 && prompt->line[prompt->total - 1] == '\n')
			to_return = check_quotes(prompt, to_return);
	}
	//free function;
	return (to_return);
}
