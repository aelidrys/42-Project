/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_animation2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:07:39 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/29 08:48:38 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_enmy(t_gam *gam, int y, int x )
{
	t_enmy	*an;
	t_enmy	*a1;

	an = (t_enmy *)malloc(sizeof(t_enmy));
	an->x = x;
	an->y = y;
	an->next = NULL;
	if (gam && gam->a)
	{
		a1 = gam->a;
		while (a1->next)
		a1 = a1->next;
		a1->next = an;
	}
	else if (gam){
		gam->a = an;
	}
}

void	enmy_pos(t_gam *gam, int y, int x)
{
	gam->a = NULL;
	while (gam->map[y])
	{

		x = 0;
		while (gam->map[y][x])
		{
			if (gam->map[y][x] == 'A')
				add_enmy(gam, y, x);
			x++;
		}
		y++;
	}
}
