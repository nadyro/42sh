/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:39:02 by azybert           #+#    #+#             */
/*   Updated: 2018/03/03 23:21:27 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	main()
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
	line = ft_prompt();
	termanip(1);
	return (0);
}
