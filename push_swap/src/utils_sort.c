/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 01:36:06 by vandre            #+#    #+#             */
/*   Updated: 2024/02/19 01:38:36 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	get_min1(t_stack **stack, int val)
{
	t_stack	*head;
	int		min;

	head = *stack;
	min = head->lindex;
	while (head->next)
	{
		head = head->next;
		if ((head->lindex < min) && head->lindex != val)
			min = head->lindex;
	}
	return (min);
}

int	get_dist(t_stack **stack, int index)
{
	t_stack	*head;
	int		dist;

	dist = 0;
	head = *stack;
	while (head)
	{
		if (head->lindex == index)
			break ;
		dist++;
		head = head->next;
	}
	return (dist);
}
