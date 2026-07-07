/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:33:55 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/25 11:46:26 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**split_all(char **args, t_shell *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		if (i <= 1 || (i > 1 && !str_comp(args[i - 1], "<")
				&& !str_comp(args[i - 2], "<")))
		{
			args[i] = expand_vars(args[i], -1, quotes, 0);
			args[i] = expand_path(args[i], -1, quotes,
					mini_getenv("HOME", prompt->envp, 4));
		}
		subsplit = ft_split_command(args[i], "<|>");
		ft_mat_rep_in(&args, subsplit, i);
		i += ft_rows_number(subsplit) - 1;
		ft_free_envp(&subsplit);
	}
	return (args);
}

void	parsing(char **args, t_shell *sh)
{
	args = split_all(args, sh);
	sh->commands = fill_nodes(args, -1);
}
