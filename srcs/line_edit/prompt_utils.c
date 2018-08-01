/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 07:30:34 by azybert           #+#    #+#             */
/*   Updated: 2018/08/01 09:11:26 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	ft_flush(t_prompt *prompt)
{
	char	user_entry[4096];
	char	*to_free;

	termanip(33);
	ft_bzero(user_entry, 4096);
	ignore_handle();
	while (read(1, user_entry, 4095) > 0)
	{
		to_free = prompt->buf;
		prompt->buf = ft_strjoin(prompt->buf, user_entry);
		free(to_free);
		ft_bzero(user_entry, 4095);
		termanip(34);
	}
	handle_sig();
	termanip(33);
}

void	prompt_clean(void)
{
	free(prompt->line);
	if (!(prompt->line = ft_strdup("\0")))
		exit(1);
	prompt->pos = 0;
	prompt->total = 0;
	prompt->current = NULL;
	term_clear();
	write(1, "Your line was full, ", 20);
	write(1, "usually you don't need these, ", 30);
	write(1, "are you maybe sleeping on your keyboard?", 40);
}
