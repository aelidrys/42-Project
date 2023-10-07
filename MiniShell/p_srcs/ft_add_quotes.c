/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:50:48 by yrimah            #+#    #+#             */
/*   Updated: 2023/05/27 14:50:52 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_quotes(t_quotes **lqts, int q)
{
	t_quotes	*quote_new;
	t_quotes	*quote_tmp;

	if (lqts)
	{
		quote_new = malloc(sizeof(t_quotes));
		quote_new->quote = q;
		quote_new->next = NULL;
		if (*lqts)
		{
			quote_tmp = *lqts;
			while (quote_tmp->next)
				quote_tmp = quote_tmp->next;
			quote_tmp->next = quote_new;
		}
		else
			*lqts = quote_new;
	}
}
