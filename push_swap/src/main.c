/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:27:44 by vandre            #+#    #+#             */
/*   Updated: 2024/02/19 01:25:09 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	len_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*tmp;
	int		i;

	tmp = stack_a;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == 2)
		sort_two(&stack_a);
	if (i == 3)
		sort_three(&stack_a);
	if (i == 4)
		sort_four(&stack_a, &stack_b);
	if (i == 5)
		sort_five(&stack_a, &stack_b);
	if (i > 5)
		radix_sort(&stack_a, &stack_b);
	free_stack(&stack_a, &stack_b);
}

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	char		**split_argv;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	if (argc == 2)
	{	
		split_argv = ft_split(argv[1], ' ');
		init_stack_a(&stack_a, split_argv, 0);
	}
	if (argc > 2)
		init_stack_a(&stack_a, argv, 1);
	len_sort(stack_a, stack_b);
	return (0);
}
