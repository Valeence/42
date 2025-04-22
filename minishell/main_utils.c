/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:50:19 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 22:51:21 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Include/MiniShell.h"

void	init_data(t_data *data)
{
	data->redi_out_bf_pipe = 0;
	data->first = 0;
	data->nb_cmd = 0;
	data->flag_qote = 0;
	data->str_here = NULL;
	data->data2->nb_file_in = 0;
	data->data2->redi_and_here = false;
	data->data2->in_single_quote = 0;
	data->data2->in_double_quote = 0;
	data->data2->nb_file_out = 0;
	data->data2->nb_file_in = 0;
	data->data2->pipe_bf_redi = 0;
}
