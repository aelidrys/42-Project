/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:56:05 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/22 15:39:59 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

# define MOVE_SPEED 20
# define M_G 14

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*img_b;
	void	*img_n;
	void	*img_s;
	void	*img_w;
	void	*img_e;
	void	*i_w0;
	void	*i_w1;
	void	*i_w2;
	void	*i_w3;
	void	*i_c;
	void	*i_c1;
	void	*k_0;
	void	*k_1;
	void	*k_2;
	void	*k_3;
	void	*p_s;
}	t_mlx;

typedef struct s_point
{
	int		dir;
	int		check;
	float	x;
	float	y;
	double	r;
}	t_point;

typedef struct s_img
{
	char			dir;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				heigth;
	char			*addr;
	void			*ptr;
	struct s_img	*next;
}	t_img;

typedef struct s_var
{
	int		grid;
	int		x;
	int		y;
	int		s_x;
	int		end_x;
	int		s_y;
	int		end_y;
	int		org_x;
	int		org_y;
	int		check;
	float	cor_rd;
}	t_var;

typedef struct s_info
{
	int		start;
	int		stop_move;
	int		r_cor;
	int		l_cor;
	int		m_r;
	int		m_l;
	int		m_d;
	int		m_u;
	int		check_shot;
	int		numb_shot;
	int		change_wap;
	int		x_mouse;
	int		y_mouse;
	int		size;
	int		width;
	int		f;
	int		c;
	int		x_d;
	int		y_d;
	int		open_d;
	int		check_o_d;
	float	width1;
	float	x;
	float	y;
	float	p_x;
	float	p_y;
	char	*str;
	t_img	*img;
	t_img	**img_d;
	t_img	*big_img;
	t_img	*mini_img;
	char	**map;
	char	**map0;
	float	corner;
	float	r_corner;
	double	last_r;
	t_point	p;
	t_mlx	*mlx;
}	t_info;

int		mouse_view(int x, int y, t_info *cub);
void	check_cmp(char **map);
void	ft_puterr(char *err);
void	check_cmp_valid(char **map);
char	**get_map(char *file);
void	check_nwline(char *map);
void	store_info(char **map, t_info *cub);
int		my_color(char *color);
void	point_of_view(t_info *data);
void	cheak_map(char **map);
void	move_right(t_info *data, int size);
void	move_left(t_info *data, int size);
void	move_up(t_info *data, int size);
void	move_down(t_info *data, int size);
int		input_key(int key, t_info *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_mini_map(t_info *cub);
t_img	*new_img(t_info *cub, char *str, char c);
void	add_img(t_img **lst, t_img *new);
void	check_name_map(char *nmap);
t_info	get_position(char **str);
void	put_pix_mini(t_img*img, float x, float y, int color);
void	change_wap(t_info *cub);
void	draw_wap(t_info *cub, void *img, int x, int y);
void	put_pistol(t_info *cub);
void	put_knife(t_info *cub);
void	get_xpm_file(t_info *cub);
int		draw_wapeans(t_info *cub);

// aelidrys
void	ft_error(char *str);
void	motion(t_info *cub);
int		open_door(t_info *cub);
int		open_door(t_info *cub);
char	**get_element(char *str);
int		is_in_str(char *str, char c);
void	start_cub(t_info *cub, char **av);
int		get_color(t_img *data, int x, int y);
void	check_open_door(t_info *cub, int key);
void	det_direction(t_info *cub, float cor_rd);
void	draw_east_walls(t_info *cub, t_point p, int a);
void	draw_west_walls(t_info *cub, t_point p, int a);
void	draw_north_walls(t_info *cub, t_point p, int a);
void	my_mlx_pixel_put1(t_img *data, int x, int y, int color);
t_point	det_coord_x(t_info *cub, float cor_rd, char *str, int size);
int		is_coord_in_map_range(t_info *cub, int x, int y, int size);
t_point	det_coord_y(t_info *cub, float cor_rd, char *str, int size);
void	check_coll(t_point p, t_info *data, t_var *var, int grid);
int		rays_casting(t_info *cub, float cor_rd, char *str);
void	draw_south_walls(t_info *cub, t_point p, int a);
int		prm_moves1(char **map, char *str, int x, int y);
int		check_door_moves(t_info *cub, t_point *p);
int		input_key_relese(int key, t_info *cub);
int		check_first_element(char **arry);
int		a_event(int key, t_info *cub);
int		str_comp(char *s1, char *s2);
int		size_of_arry(char **arry);
int		draw_cub3d(t_info *cub);
void	stop_movs(t_info *cub);
void	ft_free(char **str);

#endif