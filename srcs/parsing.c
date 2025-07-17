/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:00:23 by lnul-hak          #+#    #+#             */
/*   Updated: 2025/04/13 18:47:57 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	error_messages(int n)
{
	if (n == 0)
		printf("Invalid file extension!\n");
	if (n == 1)
		printf("Unable to open file!\n");
	if (n == 2)
		printf("Invalid identifier!\n");
	if (n == 3)
		printf("Invalid map!\n");
	if (n == 4)
		printf("Map must be last element!\n");
	if (n == 5)
		printf("Path for texture is invalid!\n");
	if (n == 6)
		printf("Colour for is invalid! Acceptable range is [0,255]!\n");
	return (1);
}

int	parsing(int ac, char **av, t_data *data)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		ft_memset(&data->tex[i], 0, sizeof(t_img));
		ft_memset(&data->texture[i], 0, sizeof(char *));
	}
	ft_memset(data->rgb, 0, sizeof(data->rgb));
	ft_memset(data, 0, sizeof(*data));
	data->fd = -1;
	data->player_x = -1;
	data->player_y = -1;
	if (check_it(ac, av, data))
		return (1);
	data->player_x *= T_S;
	data->player_x += T_S / 2;
	data->player_y *= T_S;
	data->player_y += T_S / 2;
	ft_lstclear(&data->lines, free);
	data->start_map = NULL;
	close(data->fd);
	data->fd = -1;
	return (0);
}
