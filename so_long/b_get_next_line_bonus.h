/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_get_next_line_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:35:43 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/31 08:33:39 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_GET_NEXT_LINE_BONUS_H
# define B_GET_NEXT_LINE_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2, int a);
size_t	a_lent(char *s);
void	*ft_calloc(size_t c, size_t s);
char	*ft_strdup(char *s1, int n, char **p);
char	*ft_strdup1(char *s1, int a, int m);
#endif
