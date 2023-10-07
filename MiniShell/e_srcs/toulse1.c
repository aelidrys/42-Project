/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toulse1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:55:56 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pid(t_pid **list, pid_t pid1)
{
	t_pid	*new_pid;
	t_pid	*tmp;

	if (list)
	{
		new_pid = malloc(sizeof(t_pid));
		new_pid->id = pid1;
		new_pid->next = NULL;
		if (*list)
		{
			tmp = *list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_pid;
		}
		else
			*list = new_pid;
	}
}

size_t	list_size(void *lst, int s)
{
	size_t	x;
	t_env	*lst1;
	t_cmd	*lst2;

	x = 0;
	if (s)
		lst1 = (t_env *)lst;
	if (!s)
		lst2 = (t_cmd *)lst;
	while (s && lst1)
	{
		x++;
		lst1 = lst1->next;
	}
	while (!s && lst2)
	{
		x++;
		lst2 = lst2->next;
	}
	return (x);
}

void	a_printf(char *s1, char *s2, char *s3, int fd)
{
	int	old_fd;

	old_fd = dup(1);
	dup2(fd, 1);
	if (s1 && s2 && s3)
		printf(s1, s2, s3);
	if (s1 && s2 && !s3)
		printf(s1, s2);
	dup2(old_fd, 1);
}

char	**get_key_and_val(t_shell *shell, char *s, char	**d, size_t	x)
{
	if (!s)
		return (NULL);
	d = malloc(2 * sizeof(char *));
	x = 0;
	while (s[x] && s[x] != '=')
		if (s[x++] == '+' && shell)
			g_shell->y = 1;
	d[0] = malloc(x + 1 * sizeof(char));
	x = 0;
	while (*s && *s != '=' && *s != '+')
		d[0][x++] = *(s++);
	d[0][x] = '\0';
	if (*s == '+')
		s++;
	if (!*(s++))
	{
		d[1] = NULL;
		return (d);
	}
	d[1] = malloc(a_strlen(s) + 1 * sizeof(char));
	x = 0;
	while (*s)
		d[1][x++] = *(s++);
	d[1][x] = '\0';
	return (d);
}
