/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 07:30:34 by azybert           #+#    #+#             */
/*   Updated: 2018/08/07 11:36:15 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	ft_flush(t_prompt *prompt)
{
	char	user_entry[4096];
	char	*to_free;

	ignore_handle();
	termanip(33);
	ft_bzero(user_entry, 4096);
	while (read(0, user_entry, 4095) > 0 && !(prompt->end))
	{
		to_free = prompt->buf;
		prompt->buf = ft_strjoin(prompt->buf, user_entry);
		if (prompt->buf == NULL)
		{
			prompt->buf = to_free;
			prompt->end = 1;
		}
		else
		{
			free(to_free);
			ft_bzero(user_entry, 4095);
			termanip(34);
		}
	}
	termanip(33);
	handle_sig();
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
}
