/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:16:01 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/29 19:07:10 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	return_fd(int fd, char *path, int flags[2])
{
	int	new_fd;

	if (fd > 2)
		close(fd);
	if (!path || fd == -1)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		error_handling(2, path);
	else if (!flags[0] && access(path, R_OK) == -1)
		error_handling(3, path);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		error_handling(3, path);
	if (flags[0] && flags[1])
		new_fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		new_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && fd != -1)
		new_fd = open(path, O_RDONLY);
	else
		new_fd = fd;
	return (new_fd);
}

t_cmd	*get_out_redirect(t_cmd *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->out = return_fd(node->out, args[*i], flags);
	if (!args[*i] || node->out == -1)
	{
		*i = -1;
		if (node->out != -1)
		{
			ft_putendl_fd(nl, 2);
			g_shell->g_status = 258;
		}
		else
			g_shell->g_status = 1;
	}
	return (node);
}

t_cmd	*get_double_out_redirect(t_cmd *node, char **args, int *i)
{
	int		flags[2];
	char	*error;

	flags[0] = 1;
	flags[1] = 1;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		node->out = return_fd(node->out, args[*i], flags);
	if (!args[*i] || node->out == -1)
	{
		*i = -1;
		if (node->out != -1)
		{
			ft_putendl_fd(error, 2);
			g_shell->g_status = 258;
		}
		else
			g_shell->g_status = 1;
	}
	return (node);
}

t_cmd	*get_in_redirect(t_cmd *node, char **args, int *i)
{
	int		flags[2];
	char	*error;

	error = NULL;
	get_in_help2(flags, &error);
	if ((str_comp(args[*i + 1], ">") && !args[*i + 2]))
	{
		node->in = -1;
		return (node);
	}
	else if (str_comp(args[*i + 1], ">") && str_comp(args[*i + 2], ">"))
	{
		*i = -1;
		error_handling(12, NULL);
		g_shell->g_status = 258;
		return (node);
	}
	else if (str_comp(args[*i + 1], ">") && args[*i + 2])
		get_in_help1(i, flags);
	(*i)++;
	if (args[*i])
		node->in = return_fd(node->in, args[*i], flags);
	if (!args[*i] || node->in == -1)
		get_in_help3(i, node, &error);
	return (node);
}

int	get_double_in_redirect(char **args, int *i)
{
	int		in;
	char	*aux[2];
	char	*str[2];
	int		begin;
	int		end;

	end = 0;
	begin = 0;
	initialize_variables(&in, str, aux);
	(*i)++;
	if (args[++(*i)])
	{
		process_aux(args, i, aux);
		process_quotes(&begin, &end, aux);
	}
	aux[0] = ft_substr(aux[0], begin, end - 1);
	in = get_here_doc(str, aux);
	free(aux[0]);
	validate_input(args, i, &in);
	return (in);
}
