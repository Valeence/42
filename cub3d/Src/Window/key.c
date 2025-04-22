/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:02:08 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:02:25 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	keystrokes_management(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		destroy(data);
	if (keycode == XK_Left || keycode == XK_Right)
		rotate_view(keycode, data);
	if (keycode == XK_a || keycode == XK_w
		|| keycode == XK_d || keycode == XK_s)
		move_player(keycode, data);
	return (0);
}
