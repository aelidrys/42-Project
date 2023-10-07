/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:16:34 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/27 16:16:40 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*after_env_var(char *str, int *i, int *index, char *var)
{
	char	*mytmp1;
	char	*mytmp2;

	mytmp1 = ft_substr(&str[*i], *index, ft_strlen(&str[*i]) - 1);
	mytmp2 = a_strjoin(var, mytmp1, 0, 0);
	free(mytmp1);
	free(var);
	return (mytmp2);
}

void	help_free2(char *var, char *path, char *str)
{
	free(var);
	free(path);
	free(str);
}

char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}
