/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:43:25 by antoipom          #+#    #+#             */
/*   Updated: 2018/04/10 16:45:57 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			*lexer_alloc(int *tk_tab, int *tab_size)
{
	int		*new;
	int		i;

	i = 0;
	*tab_size = *tab_size * 2;
	new = (int*)malloc(sizeof(int) * (*tab_size));
	ft_memset(new, -1, *tab_size * sizeof(int));
	while (tk_tab[i] != -1)
	{
		new[i] = tk_tab[i];
		i++;
	}
	free(tk_tab);
	return (new);
}
