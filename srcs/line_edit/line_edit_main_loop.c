/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/03/15 19:49:57 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

t_prompt		*prompt;

void			handle_resize(int sig)
{
	struct winsize	w;

	//clear and rewrite
	tputs(tgetstr("cl", NULL), 0, ft_putshit);
	get_cursor_pos(prompt->origin);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	write(1, "prompt> ", 8);
	get_cursor_pos(prompt->origin);
	write_data(prompt, prompt->line, prompt->total);
	move_cursor(prompt, prompt->pos, true);
	signal(sig, handle_resize);
}

static void		free_prompt(t_prompt *prompt)
{
	free(prompt->line);
	free(prompt->origin);
	free(prompt->size);
	free(prompt);
}

static t_prompt	*malloc_prompt(void)
{
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

static int		react(t_prompt *prompt, int nb_user_entry, char *user_entry)
{
	int	mem;

	if (ft_isprint(user_entry[0]))
	{
		mem = 0;
		while (mem < nb_user_entry && ft_isprint(user_entry))
			prompt_stock(prompt, &user_entry[mem++]);
		return (0);
	}
	else if (nb_user_entry == 1 && user_entry[0] == 127 && prompt->pos > 0)
		prompt_delete(prompt);
	else if (nb_user_entry == 4 && user_entry[3] == 126 &&
			prompt->pos < prompt->total)
		prompt_backdel(prompt);
	/*else if (nb_user_entry == 3 && user_entry[2] == 65)
	 historique up;
	else if (nb_user_entry == 3 && user_entry[2] == 66)
	historique down;*/
	else if (nb_user_entry == 3 && user_entry[2] == 68 && prompt->pos > 0)
		move_cursor(prompt, prompt->pos - 1, true);
	else if (nb_user_entry == 3 && user_entry[2] == 67 &&
			prompt->pos < prompt->total)
		move_cursor(prompt, prompt->pos + 1, true);
	else if (nb_user_entry == 3 && user_entry[2] == 72)
		move_cursor(prompt, 0, true);
	else if (nb_user_entry == 3 && user_entry[2] == 70)
		move_cursor(prompt, prompt->total, true);
	else if (nb_user_entry == 6 && user_entry[5] == 68)
		ft_cursor_word_left(prompt);
	else if (nb_user_entry == 6 && user_entry[5] == 67)
		ft_cursor_word_right(prompt);
	else if (nb_user_entry == 6 && user_entry[5] == 65)
		ft_cursor_up(prompt);
	else if (nb_user_entry == 6 && user_entry[5] == 66)
		ft_cursor_down(prompt);
	else if (nb_user_entry == 1 && user_entry[0] == '\n')
	{
		move_cursor(prompt, prompt->total, true);
		prompt_stock(prompt, user_entry);
		return (1);
	}
	return (0);
}

char			*line_edit_main_loop(void)
{
	char		user_entry[6];
	char		*to_return;
	int			nb_user_entry;

	//char		*BC;
	//char		*UP;
	//t_prompt	*prompt;
	//BC = tgetstr ("le", NULL);
	//UP = tgetstr ("up", NULL);
	write(1, "prompt> ", 8);
	prompt = malloc_prompt(); //real main loop begins after it
	to_return = NULL;
	signal(SIGWINCH, handle_resize);
	while (to_return == NULL || prompt->quotes != none)
	{
		nb_user_entry = read(1, user_entry, 6);
		if (react(prompt, nb_user_entry, user_entry))
			to_return = check_quotes(prompt, to_return);
	}
	free_prompt(prompt);
	return (to_return);
}
