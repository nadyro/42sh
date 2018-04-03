/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:39:02 by azybert           #+#    #+#             */
/*   Updated: 2018/04/03 21:06:23 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

t_prompt	*prompt;

int	main(void)
{
	char	*line;
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	termanip(0);
	signal(SIGINT, termanip);
	//handle_sig();
	while (1)
	{
		line = line_edit_main_loop();
		free(line);
	}
	termanip(2);
	return (0);
}
