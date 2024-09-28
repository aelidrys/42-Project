/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_so_long_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:58:12 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/31 08:33:48 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_SO_LONG_BONUS_H
# define B_SO_LONG_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include "b_get_next_line_bonus.h"

typedef struct s_imge
{
	int		y;
	int		x;
	void	*c1;
	void	*c2;
	void	*c3;
	void	*e0;
	void	*a1;
	void	*a2;
	void	*a3;
	void	*a4;
	void	*a5;
	void	*ef;
	void	*w;
	void	*n;
}	t_imge;

typedef struct s_plyr
{
	int		x;
	int		y;
	void	*p_n;
	void	*p1_r;
	void	*p2_r;
	void	*p3_r;
	void	*p1_l;
	void	*p2_l;
	void	*p3_l;
	void	*p_u;
	void	*p_d;
}	t_plyr;

typedef struct b_enmy
{
	int				x;
	int				y;
	int				d;
	struct b_enmy	*next;
}	t_enmy;

typedef struct s_gam
{
	int		m_x;
	int		m_y;
	int		x;
	int		n_c;
	int		movs;
	int		n;
	int		b[4];
	void	*mlx;
	void	*win;
	char	**map;
	char	**map1;
	t_plyr	p;
	t_imge	img;
	t_enmy	*a;
}	t_gam;

void	anim_of_enemy(t_gam *gam, int x, int y, int n);
int		a_sersh(char **map, char c, int *x, int *y);
void	enemy_movs(t_gam *gam, int x, int y, int c);
int		valid_path(t_gam *gam, int x, int y, int n);
void	flod_fill(char **map, int x, int y, int n);
int		check_characters(t_gam *gam, int x, int y);
int		put_img(t_gam *gam, int x, int y, int k);
void	anim_of_sheep(t_gam *gam, int x, int y);
void	a_xpm_to_imge(t_gam *gam, int x, int y);
int		put_p(t_gam *gam, int x, int y, int k);
int		check_enmy(t_gam *gam, int x, int y);
void	add_enmy(t_gam *gam, int y, int x);
void	enmy_pos(t_gam *gam, int y, int x);
void	sw1_img(t_gam *gam, int k, int c);
int		check_map(t_gam *gam, char *p);
int		a_sersh_n(char **map, char c);
char	**spl(char const *s, char c);
void	print_numbr(int x, int x1);
int		a_event(int k, t_gam *gam);
void	ft_itoa(int n, char *p);
int		a_animation(t_gam *gam);
void	print_error(int x);
size_t	arg_lent(char **p);
void	print_str(char *s);
int		ft_exit(void);

#endif