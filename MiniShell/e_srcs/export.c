/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:35:34 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env_x(t_env *env, size_t x)
{
	while (env)
	{
		if (env->index == x)
			break ;
		env = env->next;
	}
	return (env);
}

t_env	*get_min(t_env *env)
{
	long	x;
	t_env	*tmp;
	t_env	*min;

	x = 0;
	tmp = env;
	while (tmp && tmp->index)
		tmp = tmp->next;
	min = tmp;
	x = 0;
	tmp = env;
	while (tmp && min)
	{
		if (!tmp->index && !ft_comper(min->key, tmp->key))
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

void	sort_env(t_env *env)
{
	int		x;
	int		y;
	t_env	*min;
	t_env	*tmp;

	x = 1;
	y = list_size(env, 1) + 1;
	tmp = env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	while (x < y)
	{
		min = get_min(env);
		if (min)
			min->index = x++;
	}
}

void	a_export(t_cmd *cmd, t_shell *shell)
{
	size_t	x;
	size_t	y;
	int		fd;
	t_env	*env_x;

	x = 1;
	y = 0;
	fd = cmd->out;
	if (fd == -2)
		fd = 1;
	g_shell->g_status = 0;
	while (cmd->cmmd[++y])
	{
		if (check_key(shell, cmd->cmmd[y], "export", 1))
			add_env(shell, cmd->cmmd[y]);
	}
	y = list_size(g_shell->env, 1);
	while (!cmd->cmmd[1] && x <= y)
	{
		env_x = get_env_x(g_shell->env, x++);
		if (env_x && env_x->val)
			a_printf("declare -x %s=\"%s\"\n", env_x->key, env_x->val, fd);
		else if (env_x)
			a_printf("declare -x %s\n", env_x->key, NULL, fd);
	}
}
