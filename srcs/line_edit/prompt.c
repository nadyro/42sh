/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/03/10 17:42:18 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

//#define malloc(x) (rand() % 10 ? malloc(x) : 0)

static t_prompt	*malloc_prompt()
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
	prompt->nb_read = 0;
	prompt->pos = 0;
	prompt->total = 0;
	get_cursor_pos(prompt->origin);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	prompt->quotes = false;
	prompt->dquotes = false;
	return (prompt);
}

static int		ft_analyze(t_prompt *prompt)
{
	if (prompt->nb_read == 1 && ft_isprint(prompt->c[0]))
		prompt_stock(prompt);
	else if (prompt->nb_read == 1 && prompt->c[0] == 127 && prompt->pos > 0)
		prompt_delete(prompt);
	else if (prompt->nb_read == 4 && prompt->c[3] == 126 &&
			prompt->pos < prompt->total)
		prompt_backdel(prompt);
	/*else if (prompt->nb_read == 3 && prompt->c[2] == 65)
	// historique up;
	else if (prompt->nb_read == 3 && prompt->c[2] == 66)
	//historique down;*/
	else if (prompt->nb_read == 3 && prompt->c[2] == 68 && prompt->pos > 0)
		ft_cursor_left(prompt);
	else if (prompt->nb_read == 3 && prompt->c[2] == 67 &&
			prompt->pos < prompt->total)
		ft_cursor_right(prompt);
	else if (prompt->nb_read == 3 && prompt->c[2] == 72)
		ft_cursor_start(prompt);
	else if (prompt->nb_read == 3 && prompt->c[2] == 70)
		ft_cursor_end(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 68)
		ft_cursor_word_left(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 67)
		ft_cursor_word_right(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 65)
		ft_cursor_up(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 66)
		ft_cursor_down(prompt);
	else if (prompt->nb_read == 1 && prompt->c[0] == 10)
		return (0);
	return (1);
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
	
	prompt = malloc_prompt();
	//call signal functions
	k = 1;
	while (k == 1)
	{
		prompt->nb_read = read(1, prompt->c, 6);
		k = ft_analyze(prompt);
	}
	ft_cursor_end(prompt);
	if (prompt->line != NULL)
		to_return = ft_strdup(prompt->line);
	else
		to_return = NULL;
	//free function
	return (to_return);
}
