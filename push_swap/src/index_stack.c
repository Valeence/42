/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:08:35 by vandre            #+#    #+#             */
/*   Updated: 2024/02/01 14:28:08 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_stack	*search_index_min(t_stack **stack)
{
	t_stack	*head;
	t_stack	*min_cell;
	int		min_so_far;

	min_cell = NULL;
	min_so_far = INT_MAX;
	head = *stack;
	while (head)
	{
		if ((head->lindex == -1) && (head->value <= min_so_far))
		{
			min_cell = head;
			min_so_far = head->value;
		}
		head = head->next;
	}
	return (min_cell);
}

void	init_lindex(t_stack **stack)
{
	t_stack	*head;

	head = *stack;
	while (head)
	{
		head->lindex = -1;
		head = head->next;
	}
}

void	get_index(t_stack **stack)
{
	t_stack	*head;
	int		i;

	i = 0;
	init_lindex(stack);
	head = search_index_min(stack);
	while (head)
	{
		head->lindex = i++;
		head = search_index_min(stack);
	}
}
