/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:52:50 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/18 21:42:07 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_get(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tstr;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	j = 0;
	tstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tstr)
		return (NULL);
	while (s1[i] != '\0')
	{
		tstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tstr[i++] = s2[j++];
	}
	tstr[i] = '\0';
	free(s1);
	return (tstr);
}
