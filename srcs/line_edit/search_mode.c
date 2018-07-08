/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 06:09:10 by azybert           #+#    #+#             */
/*   Updated: 2018/07/08 06:49:27 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

char	*search_mode(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->old_live)
	{
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
	stat_data->old_line = prompt->line;
	prompt->line = ft_strdup("\0");
}
