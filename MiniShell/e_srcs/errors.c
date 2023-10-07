/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:34:20 by aelidrys          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error1(char *s1, int x)
{
	if (x)
		while (s1 && *s1)
			write (2, s1++, 1);
	if (!x)
		perror(s1);
	exit(1);
}

void	check_error(int a, int b)
{
	if (a == -1 || b == -1)
	{
		perror("minishell");
		exit(0);
	}
}

int	check_key(t_shell *shell, char *key, char *cmd, int a)
{
	char	**s;
	size_t	x;

	x = 0;
	if (!key)
		return (1);
	s = get_key_and_val(shell, key, NULL, 0);
	if (s)
	{
		if ((s[0][0] >= 65 && s[0][0] <= 90) || s[0][0] == '_'
			|| (s[0][0] >= 97 && s[0][0] <= 122))
			while (s[0][x] && ((s[0][x] >= 65 && s[0][x] <= 90)
				|| (s[0][x] >= 97 && s[0][x] <= 122) || s[0][x] == '_'
				|| (s[0][x] >= '0' && s[0][x] <= '9')))
				x++;
		free(s[0]);
		free(s[1]);
		free(s);
		if ((a && (!key[x] || (key[x] == '=' && x != 0) || (key[x] == '+'
						&& key[x + 1] == '='))) || (!a && !key[x]))
			return (1);
	}
	a_printf("minishell: %s: `%s': not a valid identifier\n", cmd, key, 2);
	g_shell->g_status = 1;
	return (0);
}
