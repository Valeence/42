/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:58:30 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	cont_nb_here(t_Token *curr)
{
	t_Token	*shr_here;
	int		i;

	i = 0;
	shr_here = curr;
	while (shr_here != NULL)
	{
		if (shr_here->type == E_HEREDOC)
			i++;
		if (shr_here->token_str[0] == '|' || shr_here->type == E_OUT
			|| shr_here->type == E_APPEND)
			break ;
		shr_here = shr_here->next;
	}
	return (i);
}

void	process_word_token(t_data *data, int i, t_Token *tmp)
{
	data->here[i].delim = ft_split(tmp->next->next->token_str, ' ');
	if (tmp->next->next->next != NULL
		&& tmp->next->next->next->type == E_HEREDOC)
	{
		tmp = tmp->next->next;
		data->flag_here = 1;
		data->here[i].exe = 0;
	}
	else
		data->here[i].exe = 1;
}

void	process_heredoc_token(t_data *data, int i, int nb, t_Token *tmp)
{
	data->here[i].delim = ft_split(tmp->next->token_str, ' ');
	if (data->flag_here == 1 && i + 1 == nb)
		data->here[i].exe = 1;
	else
		data->here[i].exe = 0;
}

void	init_here_doc(t_data *data, t_Token *curr, int nb)
{
	int		i;
	t_Token	*tmp;

	i = 0;
	tmp = curr;
	while (i < nb)
	{
		if (tmp->type == E_WORD && tmp->next->type == E_HEREDOC)
		{
			process_word_token(data, i, tmp);
			i++;
		}
		else if (tmp->type == E_HEREDOC)
		{
			process_heredoc_token(data, i, nb, tmp);
			i++;
		}
		tmp = tmp->next;
	}
}

void	lanch_her(t_Token *curr, t_data *data)
{
	int	i;
	int	grab_hd;

	data->curr_here_tmp = curr;
	i = 0;
	grab_hd = cont_nb_here(curr);
	data->here = malloc(sizeof(t_here) * grab_hd);
	init_here_doc(data, curr, grab_hd);
	i = 0;
	while (i < grab_hd)
	{
		if (fork_here(curr, data, &data->here[i]) == 2)
			break ;
		i++;
	}
	grab_hd = i;
	i = 0;
	while (i < grab_hd)
	{
		ft_free_tabtab(data->here[i].delim);
		i++;
	}
	free(data->here);
}
