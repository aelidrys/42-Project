/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:44:29 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/29 19:21:58 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*y_get_env(char *var, t_env *env, int n, int *index)
{
	char	*tmp;
	int		n2;

	if (n < 0)
		n = ft_strlen(var);
	while (var && env)
	{
		n2 = n;
		if (n2 < ft_strchars_i(env->key, "\"\'$|>< "))
			n2 = ft_strchars_i(env->key, "\"\'$|>< ");
		tmp = ft_substr(var, 0, n2);
		*index = n2;
		if (!ft_strncmp(env->key, var, n2) && str_comp(env->key, tmp))
		{
			free(tmp);
			return (ft_substr(env->val, 0, ft_strlen(env->val)));
		}
		if (tmp)
			free(tmp);
		env = env->next;
	}
	return (NULL);
}

static char	*get_substr_var(char *str, int i)
{
	char	*aux;
	char	*path;
	char	*var;
	int		pos;
	int		index;

	var = NULL;
	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	index = 0;
	var = y_get_env(&str[i], g_shell->env, \
		ft_strchars_i(&str[i], "\"\'-+*.,:=~@#!<>$?^&|{}][%/ "), &index);
	if (!var && str[i] == '$')
		var = ft_itoa(g_shell->id);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_shell->g_status);
	else
		var = after_env_var(str, &i, &index, var);
	path = a_strjoin(aux, var, 0, 0);
	free(aux);
	aux = ft_strdup(path);
	help_free2(var, path, str);
	return (aux);
}

char	*expand_vars(char *str, int i, int quotes[2], int q)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] += (!quotes[1] && str[i] == '\'');
		quotes[1] += (!quotes[0] && str[i] == '\"');
		if (q)
			quotes[0] = 0;
		if (str[i] && quotes[0] % 2 == 0 && str[i] == '$' && str[i + 1])
		{
			if (!quotes[1] && ft_strchars_i("~%^{}:;<> ", &str[i + 1]))
				return (expand_vars(get_substr_var(str, ++i),
						-1, quotes, q));
			else if (quotes[1] && ft_strchars_i("~%^{}:;<>\"", &str[i + 1]))
				return (expand_vars(get_substr_var(str, ++i),
						-1, quotes, q));
		}
	}
	return (str);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~'
			&& (i == 0 || str[i - 1] == ' ' || str[i - 1] == '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}
