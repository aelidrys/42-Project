/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:14:07 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/25 11:36:41 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_rows_number(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

void	ft_free_envp(char ***envp)
{
	int	count;

	count = 0;
	while (envp && envp[0] && envp[0][count])
	{
		free(envp[0][count]);
		count++;
	}
	if (envp)
	{
		free(envp[0]);
		*envp = NULL;
	}
}

char	**ft_dup_envp(char **envp)
{
	char	**dup_enpv;
	int		number_rows;
	int		count;

	count = 0;
	number_rows = ft_rows_number(envp);
	dup_enpv = (char **)malloc(sizeof(char *) * (number_rows + 1));
	if (!dup_enpv)
		return (NULL);
	while (envp[count])
	{
		dup_enpv[count] = ft_strdup(envp[count]);
		if (!dup_enpv[count])
		{
			ft_free_envp(&envp);
			return (NULL);
		}
		count++;
	}
	dup_enpv[count] = NULL;
	return (dup_enpv);
}
