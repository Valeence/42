/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2-5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:01:10 by vandre            #+#    #+#             */
/*   Updated: 2024/02/19 01:43:52 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_two(t_stack **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);
}

void	sort_three(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	first = *stack_a;
	second = first->next;
	third = second->next;
	if (first->value < second->value && second->value < third->value)
		return ;
	else if (first->value < third->value && third->value < second->value)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (second->value < first->value && first->value < third->value)
		sa(stack_a);
	else if (second->value < third->value && third->value < first->value)
		ra(stack_a);
	else if (third->value < first->value && first->value < second->value)
		rra(stack_a);
	else if (third->value < second->value && second->value < first->value)
	{
		sa(stack_a);
		rra(stack_a);
	}
}

void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	dist;
	int	min;

	if (is_sorted(stack_a))
		return ;
	min = get_min1(stack_a, -1);
	dist = get_dist(stack_a, min);
	if (dist == 1)
		sa(stack_a);
	else if (dist == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (dist == 3)
		rra(stack_a);
	if (is_sorted(stack_a))
		return ;
	pb(stack_a, stack_b);
	sort_three(stack_a);
	pa(stack_a, stack_b);
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	int	dist;
	int	min;

	min = get_min1(stack_a, -1);
	dist = get_dist(stack_a, min);
	if (dist == 1)
		sa(stack_a);
	else if (dist == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (dist == 3)
	{
		rra(stack_a);
		rra(stack_a);
	}
	else if (dist == 4)
		rra(stack_a);
	if (is_sorted(stack_a))
		return ;
	pb(stack_a, stack_b);
	sort_four(stack_a, stack_b);
	pa(stack_a, stack_b);
}
