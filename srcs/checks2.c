/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:16:13 by lnul-hak          #+#    #+#             */
/*   Updated: 2025/04/13 17:36:35 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_ext(char *file)
{
	char	*ptr;

	ptr = ft_strrchr(file, '.');
	if (!ptr || ft_strncmp(ptr, ".cub", 5))
		return (error_messages(0));
	return (0);
}

int	check_perm(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (error_messages(1));
	}
	return (fd);
}

int	check_args(char *file, t_data *data)
{
	if (check_ext(file))
		return (0);
	data->fd = check_perm(file);
	if (data->fd == 1)
		return (0);
	if (check_idf(data->fd, data))
		return (0);
	if (scan_map(data))
		return (0);
	map_init(data);
	if (flood_fill(data, 0, 0))
		return (0);
	return (1);
}

int	check_it(int ac, char **av, t_data *data)
{
	if (ac == 2)
	{
		if (!check_args(av[1], data))
		{
			clear_data(data);
			return (1);
		}
	}
	return (0);
}
