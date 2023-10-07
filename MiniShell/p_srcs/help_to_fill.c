/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_to_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:04:44 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/25 21:06:49 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*mini_init(void)
{
	t_cmd	*mini;

	mini = malloc(sizeof(t_cmd));
	if (!mini)
		return (NULL);
	mini->cmmd = NULL;
	mini->path = NULL;
	mini->next = NULL;
	mini->in = STDIN_FILENO;
	mini->out = STDOUT_FILENO;
	return (mini);
}

static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_dup_envp(args);
	while (temp && temp[++j])
	{
		aux = ft_last_split(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

int	help_fill1(char **args, char ***temp, t_list **cmds)
{
	*cmds = NULL;
	*temp = get_trimmed(args);
	if (!open_here_doc(args, -1))
	{
		ft_free_envp(temp);
		ft_free_envp(&args);
		return (0);
	}
	return (1);
}

void	help_fill2(t_list *cmds[2], int *i, char **args, char ***temp)
{
	cmds[1] = ft_lstlast(cmds[0]);
	if (*i == 0 || (args[*i][0] == '|' && args[*i + 1] && args[*i + 1][0]))
	{
		*i += args[*i][0] == '|';
		ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
		cmds[1] = ft_lstlast(cmds[0]);
	}
	*temp = args;
}

void	help_free(char **args, char ***temp)
{
	ft_free_envp(temp);
	ft_free_envp(&args);
}
