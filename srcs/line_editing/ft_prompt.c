/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/03/04 22:41:25 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

//#define malloc(x) (rand() % 10 ? malloc(x) : 0)

static t_prompt	*malloc_prompt()
{
	t_prompt	*prompt;
	struct winsize w;

	if (!(prompt = malloc(sizeof(*prompt))))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->line = NULL;
	prompt->modx = w.ws_col;
	prompt->mody = w.ws_row;
	prompt->posx = 0;
	prompt->posy = 0;
	prompt->line_pos = 0;
	prompt->total = 0;
	prompt->nb_read = 0;
	prompt->quote = 0;
	prompt->dquote = 0;
	return (prompt);
}

static int		ft_analyze(t_prompt *prompt)
{
	if (prompt->nb_read == 1 && ft_isprint(prompt->c[0]))
		ft_prompt_stock(prompt);
	else if (prompt->nb_read == 1 && prompt->c[0] == 127 && prompt->line_pos > 0)
		ft_prompt_delete(prompt);
	else if (prompt->nb_read == 4 && prompt->c[3] == 126 &&
			prompt->line_pos < prompt->total)
		ft_prompt_backdel(prompt);
	/*else if (prompt->nb_read == 3 && prompt->c[2] == 65)
		// historique up;
	else if (prompt->nb_read == 3 && prompt->c[2] == 66)
		//historique down;*/
	else if (prompt->nb_read == 3 && prompt->c[2] == 68 && prompt->line_pos > 0)
		ft_cursor_left(prompt);
	else if (prompt->nb_read == 3 && prompt->c[2] == 67 &&
			prompt->line_pos < prompt->total)
		ft_cursor_right(prompt);
	else if (prompt->nb_read == 3 && prompt->c[2] == 72)
		ft_cursor_start(prompt);
	else if (prompt->nb_read == 3 && prompt->c[2] == 70)
		ft_cursor_end(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 68)
		cursor_word_left(prompt);
	else if (prompt->nb_read == 6 && prompt->c[5] == 67)
		cursor_word_right(prompt);
	//word up && word down
	else if (prompt->nb_read == 1 && prompt->c[0] == 10)
		return (0);
	return (1);
}

char			*ft_prompt()
{
	char		*to_return;
	int			k;
	t_prompt	*prompt;
//
	int fd = open("debug", O_CREAT | O_WRONLY | O_TRUNC, 0666);
//
	prompt = malloc_prompt();
	//call signal functions
	k = 1;
	while (k == 1)
	{
		prompt->nb_read = read(1, prompt->c, 6);
		k = ft_analyze(prompt);
		//
		write(fd, prompt->line, prompt->total);
		write(fd, "\n", 1);
		//
	}
	ft_cursor_end(prompt);
	if (prompt->line != NULL)
		to_return = ft_strdup(prompt->line);
	else
		to_return = NULL;
	free(prompt->line);
	free(prompt);
	return (to_return);
}
