/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:43:25 by antoipom          #+#    #+#             */
/*   Updated: 2018/04/20 14:17:27 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			*lexer_alloc(int *tk_arr, int *arr_size)
{
	int		*new;
	int		i;

	i = 0;
	*arr_size = *arr_size * 2;
	new = (int*)malloc(sizeof(int) * (*arr_size));
	(new == NULL) ? exit(1) : 0; //error handling?
	ft_memset(new, -1, *arr_size * sizeof(int));
	while (tk_arr[i] != -1)
	{
		new[i] = tk_arr[i];
		i++;
	}
	free(tk_arr);
	return (new);
}
