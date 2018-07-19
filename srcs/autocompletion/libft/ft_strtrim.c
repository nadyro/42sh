/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:53:09 by azybert           #+#    #+#             */
/*   Updated: 2017/01/28 12:49:19 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static char	*ft_strtrim2(char *debut)
{
	char	*fin;
	int		k;
	int		m;

	fin = debut;
	k = -1;
	while (fin[++k])
		if (fin[k] != ' ' && fin[k] != '\n' && fin[k] != '\t')
			m = k;
	return (&fin[m]);
}

static char	*ft_strtrim3(void)
{
	char	*mem;

	mem = (char *)malloc(1);
	if (mem == NULL)
		return (NULL);
	*mem = '\0';
	return (mem);
}

char		*ft_strtrim(char const *s)
{
	char	*debut;
	char	*fin;
	char	*mem;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	debut = (char *)s;
	while (*debut && (*debut == ' ' || *debut == '\n' || *debut == '\t'))
		debut++;
	if (*debut == '\0')
		return (ft_strtrim3());
	fin = ft_strtrim2(debut);
	mem = (char *)malloc(fin - debut + 2);
	if (mem == NULL)
		return (NULL);
	tmp = mem;
	while (debut != fin)
		*(tmp++) = *(debut++);
	*tmp = *debut;
	*(++tmp) = '\0';
	return (mem);
}
