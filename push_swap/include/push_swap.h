/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:56:01 by vandre            #+#    #+#             */
/*   Updated: 2024/02/19 01:44:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/include/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				lindex;
	struct s_stack	*next;
	struct s_stack	*prev;
}				t_stack;

void	init_stack_a(t_stack **stack_a, char **argv, int i);
int		check_argv(char	*str);
int		check_duplicate(t_stack *stack_a, int nb);
void	append(t_stack **stack, int nb);
void	len_sort(t_stack *stack_a, t_stack *stack_b);
int		is_sorted(t_stack **stack_a);
void	get_index(t_stack **stack);
void	free_stack(t_stack **stack_a, t_stack **stack_b);
void	free_sa(t_stack **stack_a);
void	free_argv(char **argv, int j);
int		stack_len(t_stack *stack);

void	sort_two(t_stack **stack_a);
void	sort_three(t_stack **stack_a);
void	sort_four(t_stack **stack_a, t_stack **stack_b);
void	sort_five(t_stack **stack_a, t_stack **stack_b);
void	radix_sort(t_stack **stack_a, t_stack **stack_b);
int		get_min1(t_stack **stack, int val);
int		get_dist(t_stack **stack, int index);

t_stack	*find_last(t_stack *stack_a);
t_stack	*find_max(t_stack *stack_a);
t_stack	*find_min(t_stack *stack_a);

void	sa(t_stack	**stack_a);
void	sb(t_stack	**stack_b);
void	ss(t_stack	**stack_a, t_stack	**stack_b);
void	pa(t_stack	**stack_a, t_stack	**stack_b);
void	pb(t_stack	**stack_a, t_stack	**stack_b);
void	ra(t_stack	**stack_a);
void	rb(t_stack	**stack_b);
void	rr(t_stack	**stack_a, t_stack	**stack_b);
int		rra(t_stack	**stack_a);
int		rrb(t_stack	**stack_b);
int		rrr(t_stack	**stack_a, t_stack	**stack_b);

#endif