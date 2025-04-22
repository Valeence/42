/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:29:14 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:29:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	t_poss_cpy(t_position *destination, const t_position source)
{
	destination->line = source.line;
	destination->col = source.col;
	return ;
}

bool	t_pos_cmp_ptr(t_position *a, t_position *b)
{
	if (!a && !b)
		return (true);
	if ((a && !b) || (!a && b))
		return (false);
	if (a->line == b->line && a->col == b->col)
		return (true);
	return (false);
}

bool	t_pos_cmp(t_position a, t_position b)
{
	if (a.line == b.line && a.col == b.col)
		return (true);
	return (false);
}

t_position	t_poss_create_tuple(int line, int col)
{
	t_position	tuple;

	tuple.line = line;
	tuple.col = col;
	return (tuple);
}
