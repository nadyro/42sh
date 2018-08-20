/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <tcanaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:40:04 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/16 16:40:09 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	sh_close(int x, char *msg)
{
	termanip(35);
	ft_putstr_fd(msg, 2);
	exit(x);
}