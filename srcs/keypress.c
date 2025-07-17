/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:38:33 by cbaey             #+#    #+#             */
/*   Updated: 2025/04/13 10:38:45 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int key_code, t_data *data)
{
	if (key_code == XK_w)
		data->flags.w_flag = true;
	if (key_code == XK_d)
		data->flags.d_flag = true;
	if (key_code == XK_s)
		data->flags.s_flag = true;
	if (key_code == XK_a)
		data->flags.a_flag = true;
	if (key_code == XK_Left)
		data->flags.left_flag = true;
	if (key_code == XK_Right)
		data->flags.right_flag = true;
	if (key_code == XK_Escape)
	{
		clear_data(data);
		exit(0);
	}
	return (0);
}

int	key_release(int key_code, t_data *data)
{
	if (key_code == XK_w)
		data->flags.w_flag = false;
	if (key_code == XK_d)
		data->flags.d_flag = false;
	if (key_code == XK_s)
		data->flags.s_flag = false;
	if (key_code == XK_a)
		data->flags.a_flag = false;
	if (key_code == XK_Left)
		data->flags.left_flag = false;
	if (key_code == XK_Right)
		data->flags.right_flag = false;
	return (0);
}

int	cross_button(t_data *data)
{
	clear_data(data);
	exit (1);
}

void	register_mlx(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, render_function, data);
	mlx_hook(data->win_ptr, DestroyNotify,
		StructureNotifyMask, cross_button, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_loop(data->mlx_ptr);
}
