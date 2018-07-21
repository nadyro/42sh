/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:55:26 by azybert           #+#    #+#             */
/*   Updated: 2017/12/03 22:22:37 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_power(int nbr, int power)
{
	int	new_nbr;

	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	new_nbr = nbr;
	while (power-- > 1)
		new_nbr = new_nbr * nbr;
	return (new_nbr);
}
