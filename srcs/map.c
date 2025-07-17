/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:17:46 by lnul-hak          #+#    #+#             */
/*   Updated: 2025/04/13 18:44:00 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <limits.h>

int	store_position(t_data *data, int player, int x, int y)
{
	if (player <= 4)
	{
		if (data->player_x != -1)
			return (1);
		data->player_x = x;
		data->player_y = y;
		data->player_angle = player * M_PI_2;
	}
	return (0);
}

void	update_width(t_data *data, int x)
{
	if (data->max_w_map < x)
		data->max_w_map = x;
}

int	scan_map(t_data	*data)
{
	int		x;
	int		y;
	t_list	*tmp;
	char	*res;

	y = 0;
	tmp = data->start_map;
	while (tmp)
	{
		x = -1;
		while (((char *)tmp->content)[++x])
		{
			res = ft_strchr("10 \nENWS", ((char *)tmp->content)[x]);
			if (!res || store_position(data, ft_strlen(res), x, y))
				return (error_messages(3));
		}
		y++;
		update_width(data, x);
		tmp = tmp->next;
	}
	data->max_h_map = y;
	if (data->player_x == -1)
		printf("No player found!\n");
	return (data->player_x == -1);
}

void	map_init(t_data *data)
{
	int		i;
	char	**twodmap;
	t_list	*tmp;

	i = 0;
	tmp = data->start_map;
	twodmap = ft_calloc(sizeof(char *), data->max_h_map + 3);
	while (i < data->max_h_map + 2)
	{
		twodmap[i] = ft_calloc(sizeof(char), data->max_w_map + 3);
		ft_memset(twodmap[i], ' ', sizeof(char) * data->max_w_map + 2);
		i++;
	}
	i = 1;
	while (i < data->max_h_map + 1 && tmp)
	{
		ft_memcpy(twodmap[i] + 1, tmp->content, ft_strlen(tmp->content));
		i++;
		tmp = tmp->next;
	}
	data->player_x += 1;
	data->player_y += 1;
	data->map = twodmap;
	data->max_w_map += 2;
	data->max_h_map += 2;
}

int	flood_fill(t_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x >= data->max_w_map || y >= data->max_h_map || data->map[y][x] == '1'
		|| data->map[y][x] == 'F')
		return (0);
	else if (data->map[y][x] == '0' || data->map[y][x] == 'N'
		|| data->map[y][x] == 'E' || data->map[y][x] == 'S'
		|| data->map[y][x] == 'W')
		return (error_messages(3));
	data->map[y][x] = 'F';
	return (flood_fill(data, x + 1, y) || flood_fill(data, x - 1, y)
		|| flood_fill(data, x, y + 1) || flood_fill(data, x, y - 1));
}
