/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmplt_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:20:41 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/14 15:21:09 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

t_node	*lighten_fetch_names(char *ue, t_node *bin, t_node *mat)
{
	if (ue && (ft_strcmp(ue, ".") != 0
		&& ft_strcmp(ue, "..") != 0))
	{
		if (ue && (ft_strcmp(ue, " ") == 0 || ft_strcmp(ue, "") == 0))
			mat = cmp_space_entry(ue, 0);
		else
			mat = cmp_user_entry(bin, ue);
	}
	return (mat);
}