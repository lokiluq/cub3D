/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:46:08 by cbaey             #+#    #+#             */
/*   Updated: 2025/04/17 13:44:20 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_pixel_put(t_img img, int x, int y, int colour)
{
	char	*address;

	if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT)
		return ;
	address = img.address + x * (img.bpp / 8) + y * (img.size_line);
	*(int *)address = colour;
}

void	init_info(t_data *data, t_measure *scales)
{
	scales->delta_x = T_S / fabs(cos(data->ray_angle));
	scales->delta_y = T_S / fabs(sin(data->ray_angle));
	if (data->ray_x < 0)
	{
		scales->step_x = -1;
		scales->dist_x = (fmod(data->player_x, T_S) / T_S) * scales->delta_x;
	}
	else
	{
		scales->step_x = 1;
		scales->dist_x = (1.0 - (fmod(data->player_x,
						T_S) / T_S)) * scales->delta_x;
	}
	if (data->ray_y < 0)
	{
		scales->step_y = -1;
		scales->dist_y = (fmod(data->player_y,
					T_S) / T_S) * scales->delta_y;
	}
	else
	{
		scales->step_y = 1;
		scales->dist_y = (1.0 - (fmod(data->player_y,
						T_S) / T_S)) * scales->delta_y;
	}
}

int	get_texture_pixel(t_img *texture, double x, double y)
{
	char	*addr;

	addr = texture->address + (int)((x * texture->bpp / 8)
			+ (y * texture->size_line));
	return (*(int *)addr);
}

void	fill_colours(t_data *data, int ray, double wall_height, double ratio)
{
	double	x;
	double	y;
	int		i;
	int		floor;
	int		ceiling;

	wall_height = ratio * W_HEIGHT;
	i = -wall_height / 2 - 1;
	x = ((data->tex[data->tex_index].tex_x) * data->tex[data->tex_index].width);
	while (++i < wall_height / 2)
	{
		y = ((double)((i + wall_height / 2)
					/ wall_height)) * (data->tex[data->tex_index].height);
		assert((int)x >= 0);
		img_pixel_put(data->img, ray, W_HEIGHT / 2 + i,
			get_texture_pixel(&data->tex[data->tex_index], (int)x, (int)y));
	}
	ceiling = W_HEIGHT / 2 + (-wall_height / 2);
	i = -1;
	while (++i <= ceiling)
		img_pixel_put(data->img, ray, i, data->rgb[1]);
	floor = W_HEIGHT / 2 + (wall_height / 2) - 1;
	while (++floor < W_HEIGHT)
		img_pixel_put(data->img, ray, floor, data->rgb[0]);
}

void	cast_rays(t_data *data)
{
	int		ray;
	double	distance;
	double	ray_angle;
	double	ratio;

	ray = -1;
	ray_angle = data->player_angle - ((M_PI / 3) / 2);
	while (++ray < W_WIDTH)
	{
		ray_angle = fmod(ray_angle, 2 * M_PI);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		data->ray_angle = ray_angle;
		data->ray_x = cos(data->ray_angle);
		data->ray_y = sin(data->ray_angle);
		distance = measure_distance(data) * cos(data->player_angle - ray_angle);
		ratio = 30 / distance;
		fill_colours(data, ray, 1.0, ratio);
		ray_angle += ((M_PI / 3) / W_WIDTH);
		if (data->ray_angle >= 2 * M_PI)
			data->ray_angle -= 2 * M_PI;
		else if (data->ray_angle <= 0.0)
			data->ray_angle += 2 * M_PI;
	}
}
