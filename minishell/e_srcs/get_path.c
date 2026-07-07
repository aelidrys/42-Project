/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 07:47:02 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free(char **arry)
{
	int	n;

	n = 0;
	while (arry && arry[n])
		free(arry[n++]);
	free(arry);
	return (NULL);
}

void	is_adiroctory(char *cmd)
{
	if (opendir(cmd))
	{
		a_printf("minishell: %s%s\n", cmd, ": is a directory", 2);
		exit(126);
	}
}

char	*get_pth(t_env *env, char **env_e, char *cmd, int n)
{
	char	*path;
	char	**s;
	t_env	*env1;

	if (!env || !cmd)
		return (0);
	if (!access(cmd, X_OK))
		execve(cmd, g_shell->cmd->cmmd, env_e);
	is_adiroctory(cmd);
	env1 = a_get_env(env, "PATH");
	if (!env1)
		return (NULL);
	s = spl(env1->val, ':', 1);
	while (s && s[++n])
	{
		path = a_strjoin(s[n], cmd, 2, 0);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
	}
	ft_free(s);
	if (access(path, X_OK) == -1)
		return (0);
	return (path);
}
