/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:43:34 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_variables(int *in, char **str, char **aux)
{
	*in = -2;
	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
}

void	process_aux(char **args, int *i, char **aux)
{
	int	counter;

	counter = 0;
	aux[0] = args[*i];
	if (aux[0][counter] == '\'' || aux[0][counter] == '"')
		add_quotes(&(g_shell->quotes), 1);
	else
		add_quotes(&(g_shell->quotes), 0);
}

void	help_process_quotes(char ***aux, int *begin, int *end)
{
	if ((*aux)[0][*begin] == '\"')
	{
		while ((*aux)[0][*begin] == '\"')
			(*begin)++;
		if (*begin == 1)
			*end = ft_strlen((*aux)[0]) - *begin;
		else
			*end = ft_strlen((*aux)[0]) - (*begin * 2) + 1;
	}
	if ((*aux)[0][*begin] == '\'')
	{
		while ((*aux)[0][*begin] == '\'')
			(*begin)++;
		if (*begin == 1)
			*end = ft_strlen((*aux)[0]) - *begin;
		else
			*end = ft_strlen((*aux)[0]) - (*begin * 2) + 1;
	}
}

void	process_quotes(int *begin, int *end, char **aux)
{
	int	counter;

	counter = 0;
	if ((aux[0][counter] == '\'' && aux[0][counter + 1] != '\"') ||
		(aux[0][counter] == '\"' && aux[0][counter + 1] != '\''))
	{
		while (aux[0][counter] == '\'' || aux[0][counter] == '\"')
		{
			help_process_quotes(&aux, begin, end);
			counter++;
		}
	}
	else
	{
		if (aux[0][*begin] == '\'' || aux[0][*begin] == '\"')
		{
			(*begin)++;
			*end = ft_strlen(aux[0]) - *begin;
		}
	}
}

void	validate_input(char **args, int *i, int *in)
{
	char	*error;

	error = "minishell: syntax error near unexpected token `newline'";
	if (!args[*i] || *in == -1)
	{
		*i = -1;
		if (*in != -1)
		{
			ft_putendl_fd(error, 2);
			g_shell->g_status = 258;
		}
	}
}
