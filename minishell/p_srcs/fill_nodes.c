/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:13:46 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/29 19:27:43 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*handle_redirection(t_cmd *node, char **a[2], int *i)
{
	if (str_comp(&a[0][*i + 2][0], ">"))
	{
		error_handling(12, NULL);
		g_shell->g_status = 258;
		node->out = -1;
		*i = -3;
		return (node);
	}
	else if (str_comp(&a[0][*i + 2][0], "<"))
	{
		error_handling(11, NULL);
		g_shell->g_status = 258;
		node->out = -1;
		*i = -3;
		return (node);
	}
	else
		node = get_double_out_redirect(node, a[1], i);
	return (node);
}

void	help_redirec(t_cmd *node, int *i)
{
	t_herdoc	*tmp;

	tmp = g_shell->hdc;
	node->in = g_shell->hdc->in;
	g_shell->hdc = g_shell->hdc->next;
	free(tmp);
	*i += 2;
}

t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_nodes_content);
	ft_free_envp(&temp);
	ft_free_envp(&args);
	return (NULL);
}

static t_cmd	*check_redirect(t_cmd *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = handle_redirection(node, a, i);
		else if (a[0][*i][0] == '>')
			node = get_out_redirect(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] == '<')
			help_redirec(node, i);
		else if (a[0][*i][0] == '<')
			node = get_in_redirect(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->cmmd = ft_ext_mat(node->cmmd, a[1][*i]);
		else
		{
			error_handling(10, NULL);
			g_shell->g_status = 258;
			*i = -3;
		}
		return (node);
	}
	error_handling(10, NULL);
	*i = -2;
	return (node);
}

t_list	*fill_nodes(char **args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];
	int		j;

	if (!help_fill1(args, &temp[1], &cmds[0]))
		return (NULL);
	while (args[++i])
	{
		help_fill2(cmds, &i, args, &temp[0]);
		j = i;
		cmds[1]->content = check_redirect(cmds[1]->content, temp, &i);
		if (i == -3)
			return (stop_fill(cmds[0], args, temp[1]));
		if (i < 0)
		{
			((t_cmd *)cmds[1]->content)->s = -1;
			i = j;
			while (args[i] && args[i + 1] && !str_comp(args[i + 1], "|"))
				i++;
		}
		if (!args[i])
			break ;
	}
	help_free(args, &temp[1]);
	return (cmds[0]);
}
