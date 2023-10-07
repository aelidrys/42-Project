/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:16:16 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/25 11:40:08 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//return the position of the first delim from set find in str

int	ft_strchars_i(const char *str, char *set)
{
	int	position;

	position = 0;
	if (!str)
		return (-1);
	while (str[position] != '\0')
	{
		if (ft_strchr(set, str[position]))
			return (position);
		position++;
	}
	return (-1);
}

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

char	**ft_mat_rep_in(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_rows_number(*big))
		return (NULL);
	aux = ft_calloc(ft_rows_number(*big)
			+ ft_rows_number(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	ft_free_envp(big);
	*big = aux;
	return (*big);
}

char	**ft_ext_mat(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_rows_number(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_free_envp(&in);
			ft_free_envp(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	ft_free_envp(&in);
	return (out);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);
		}
	}
	envp = ft_ext_mat(envp, aux[1]);
	free(aux[1]);
	return (envp);
}
