/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:28 by abouassi          #+#    #+#             */
/*   Updated: 2023/07/20 18:28:54 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*new_img(t_info *cub, char *str, char c)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(cub->mlx->ptr, str,
			&img->width, &img->heigth);
	if (!img->ptr)
		ft_error("xpm file not valid");
	img->dir = c;
	img->addr = mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->next = NULL;
	return (img);
}

void	add_img(t_img **lst, t_img *new)
{
	t_img	*ptr;

	if (lst && new)
	{
		if (*lst)
		{
			ptr = *lst;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new;
		}
		else
			*lst = new;
	}
}
