/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:17:27 by abouassi          #+#    #+#             */
/*   Updated: 2022/10/29 20:46:10 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_str(char *st, char *ed)
{
	int	i;

	i = 0;
	while (&st[i] != ed)
		i++;
	return (i);
}

static char	*skip_last(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len - 1]) != NULL)
		len--;
	return ((char *)&s1[len]);
}

static char	*skip_first(char const *s1, char const *set, int *i)
{
	int	y;

	y = 0;
	while (s1[y])
	{
		if (ft_strchr(set, s1[y]) == NULL)
			break ;
		y++;
	}
	*i = y;
	return ((char *)&s1[*i]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*fs;
	char	*ed;
	int		i;
	int		len;
	char	*dest;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (!*set)
		return (ft_strdup(s1));
	if (!*s1)
		return (ft_strdup(""));
	fs = skip_first(s1, set, &i);
	ed = skip_last(s1, set);
	if (*fs == '\0')
		return (ft_strdup(""));
	len = len_str(fs, ed);
	dest = ft_substr(s1, i, len);
	return (dest);
}
