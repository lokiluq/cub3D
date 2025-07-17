/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measurements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:38:10 by cbaey             #+#    #+#             */
/*   Updated: 2025/04/17 12:51:33 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	measure_distance(t_data *data)
{
	int		map_x;
	int		map_y;
	int		side;

	side = 0;
	init_info(data, &data->measure);
	map_x = (int)(data->player_x / T_S);
	map_y = (int)(data->player_y / T_S);
	while (1)
	{
		side = choose_side(&data->measure, &map_x, &map_y, side);
		if (map_x < 0 || map_x >= data->max_w_map
			|| map_y < 0 || map_y >= data->max_h_map)
			return (-1);
		if (data->map[map_y][map_x] == '1')
			break ;
		if (side == 1)
			data->measure.dist_y += data->measure.delta_y;
		else
			data->measure.dist_x += data->measure.delta_x;
	}
	return (wall_distance(data, data->measure.dist_x,
			data->measure.dist_y, side));
}

int	choose_side(t_measure *measure, int *map_x, int *map_y, int side)
{
	if (measure->dist_x < measure->dist_y)
	{
		*map_x += measure->step_x;
		side = 0;
	}
	else
	{
		*map_y += measure->step_y;
		side = 1;
	}
	return (side);
}

int	find_wall_texture(t_data *data, int side)
{
	if (data->ray_angle >= 0 && data->ray_angle <= M_PI_2)
	{
		if (side != 0)
			return (1);
		else
			return (2);
	}
	else if (data->ray_angle >= M_PI_2 && data->ray_angle <= M_PI)
	{
		if (side != 0)
			return (1);
		else
			return (3);
	}
	else if (data->ray_angle >= M_PI && data->ray_angle <= 3 * M_PI / 2)
		return (!side * 3);
	else
		return (!side * 2);
}

double	wall_distance(t_data *data, double dist_x, double dist_y, int side)
{
	double	x;
	double	y;

	if (side == 0)
	{
		x = dist_x * data->ray_x;
		y = dist_x * data->ray_y;
	}
	else
	{
		x = dist_y * data->ray_x;
		y = dist_y * data->ray_y;
	}
	x += data->player_x;
	y += data->player_y;
	data->tex_index = find_wall_texture(data, side);
	if (side == 0)
		return (data->tex[data->tex_index].tex_x
			= fmod(y, T_S) / (double)T_S, dist_x);
	else
		return (data->tex[data->tex_index].tex_x
			= fmod(x, T_S) / (double)T_S, dist_y);
}
