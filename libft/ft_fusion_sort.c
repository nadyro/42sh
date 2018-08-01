/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 05:39:30 by azybert           #+#    #+#             */
/*   Updated: 2018/07/20 01:11:03 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	merging(int *tab, int *sorted, int low, int high)
{
	int	l;
	int	h;
	int	i;
	int	mid;

	mid = (low + high) / 2;
	l = low;
	h = mid + 1;
	i = low;
	while (l <= mid && h <= high)
	{
		if (tab[l] <= tab[h])
			sorted[i] = tab[l++];
		else
			sorted[i] = tab[h++];
		i++;
	}
	while (l <= mid)
		sorted[i++] = tab[l++];
	while (h <= high)
		sorted[i++] = tab[h++];
	i = low - 1;
	while (++i <= high)
		tab[i] = sorted[i];
}

static void	sort(int *tab, int *sorted, int low, int high)
{
	if (high <= low)
		return ;
	sort(tab, sorted, low, (low + high) / 2);
	sort(tab, sorted, (low + high) / 2 + 1, high);
	merging(tab, sorted, low, high);
}

void		ft_fusion_sort(int *tab, int max)
{
	int	*sorted;

	if (!(sorted = malloc(sizeof(int) * max)))
		return ;
	sort(tab, sorted, 0, max - 1);
	free(sorted);
}
