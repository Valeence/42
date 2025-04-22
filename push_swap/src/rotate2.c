/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:43:29 by vandre            #+#    #+#             */
/*   Updated: 2024/01/30 00:20:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	do_rra_or_rrb(t_stack **stack)
{
	t_stack	*prev_last;
	t_stack	*last;

	if (!*stack || !(*stack)->next)
		return ;
	prev_last = NULL;
	last = *stack;
	while (last->next)
	{
		prev_last = last;
		last = last->next;
	}
	if (prev_last)
		prev_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

int	rra(t_stack **stack)
{
	if (!*stack || !(*stack)->next)
		return (-1);
	do_rra_or_rrb(stack);
	ft_printf("rra\n");
	return (0);
}

int	rrb(t_stack **stack)
{
	if (!*stack || !(*stack)->next)
		return (-1);
	do_rra_or_rrb(stack);
	ft_printf("rrb\n");
	return (0);
}

int	rrr(t_stack **a, t_stack **b)
{
	rra(a);
	rrb(b);
	ft_printf("rrr\n");
	return (0);
}
