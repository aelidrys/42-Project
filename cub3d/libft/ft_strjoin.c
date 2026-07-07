/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:59:06 by abouassi          #+#    #+#             */
/*   Updated: 2023/06/07 10:57:41 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*tstr;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	tstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tstr)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		tstr[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		tstr[i] = s2[j];
		j++;
		i++;
	}
	tstr[i] = '\0';
	return (tstr);
}
