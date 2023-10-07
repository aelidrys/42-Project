/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:13:40 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/29 19:26:35 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env(char *s, int i)
{
	t_env	*envx;
	char	**spl;

	envx = malloc(sizeof(t_env));
	spl = get_key_and_val(NULL, s, NULL, 0);
	envx->val = NULL;
	if (spl)
		envx->key = spl[0];
	if (spl && spl[1])
		envx->val = spl[1];
	free(spl);
	envx->index = 0;
	envx->next = NULL;
	if (i)
		free(s);
	return (envx);
}

void	add_back(t_env **env, t_env *new_env)
{
	t_env	*tmp;

	if (env && new_env)
	{
		if (*env)
		{
			tmp = *env;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
			new_env->prev = tmp;
		}
		else
		{
			*env = new_env;
			new_env->prev = NULL;
		}
	}
}

void	add_env(t_shell *shell, char *str)
{
	t_env	*env1;
	char	**spl;

	g_shell->y = 0;
	spl = get_key_and_val(shell, str, NULL, 0);
	env1 = a_get_env(g_shell->env, spl[0]);
	if (env1 && spl && spl[1])
	{
		if (g_shell->y == 1)
			env1->val = a_strjoin(env1->val, spl[1], 1, 0);
		else
		{
			free(env1->val);
			env1->val = a_strjoin(spl[1], NULL, 0, 0);
		}
		env1->a = 1;
	}
	if (!env1)
		add_back(&g_shell->env, new_env(str, 0));
	free(spl[0]);
	free(spl[1]);
	free(spl);
	sort_env(g_shell->env);
}

t_env	*a_get_env(t_env *env, char *key)
{
	while (env && key)
	{
		if (str_comp(env->key, key))
			return (env);
		env = env->next;
	}
	return (0);
}

char	**convert_env(t_env *env)
{
	char	**arry;
	int		x;
	int		y;
	int		z;

	x = 0;
	arry = malloc((list_size(env, 1) + 1) * sizeof(char *));
	while (env)
	{
		z = 0;
		y = 0;
		arry[x] = malloc(a_strlen(env->key) + a_strlen(env->val) + 2);
		while (env->key && env->key[z])
			arry[x][y++] = env->key[z++];
		if (env->val)
			arry[x][y++] = '=';
		z = 0;
		while (env->val && env->val[z])
			arry[x][y++] = env->val[z++];
		arry[x++][y] = '\0';
		env = env->next;
	}
	arry[x] = NULL;
	return (arry);
}
