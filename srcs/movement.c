/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:12:43 by cbaey             #+#    #+#             */
/*   Updated: 2025/04/17 13:34:08 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	movement_keys(t_flags flags, t_move *move)
{
	if (flags.w_flag == true)
	{
		move->temp_x += move->x_incre;
		move->temp_y += move->y_incre;
	}
	if (flags.d_flag == true)
	{
		move->temp_x -= move->y_incre;
		move->temp_y += move->x_incre;
	}
	if (flags.s_flag == true)
	{
		move->temp_x -= move->x_incre;
		move->temp_y -= move->y_incre;
	}
	if (flags.a_flag == true)
	{
		move->temp_x += move->y_incre;
		move->temp_y -= move->x_incre;
	}
}

void	calculate_wm(t_data *data, double temp, double player_still)
{
	if (player_still == data->player_x)
	{
		data->map_y = (temp + data->move.dy * 10) / T_S;
		data->map_x = (player_still + data->move.dx * 10) / T_S;
	}
	else
	{
		data->map_x = (temp + data->move.dx * 10) / T_S;
		data->map_y = (player_still + data->move.dy * 10) / T_S;
	}
}

void	wall_movement(t_data *data, double temp,
		double player_still, double *player_mvt)
{
	double	iter;

	iter = (M_PI / 180);
	while (iter < (2 * M_PI))
	{
		data->move.dy = sin(iter) * MOVE_SPEED;
		data->move.dx = cos(iter) * MOVE_SPEED;
		calculate_wm(data, temp, player_still);
		if (data->map_y < 0 || data->map_x < 0 || data->map_y >= data->max_h_map
			|| data->map_x >= data->max_w_map
			|| data->map[data->map_y][data->map_x] == '1'
			|| data->map[data->map_y][data->map_x] == 'F')
			return ;
		iter += (M_PI / 180);
	}
	*player_mvt = temp;
}

void	movement(t_data *data)
{
	data->move.y_incre = (MOVE_SPEED * sin(data->player_angle));
	data->move.x_incre = (MOVE_SPEED * cos(data->player_angle));
	data->move.temp_x = data->player_x;
	data->move.temp_y = data->player_y;
	movement_keys(data->flags, &data->move);
	wall_movement(data, data->move.temp_y, data->player_x, &data->player_y);
	wall_movement(data, data->move.temp_x, data->player_y, &data->player_x);
}
