/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnul-hak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:30:15 by lnul-hak          #+#    #+#             */
/*   Updated: 2025/04/13 18:47:53 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	extract_colour(char *content)
{
	int		i;
	char	**arr;
	int		rgb;
	int		j;

	i = -1;
	rgb = 0;
	arr = ft_split(content, ',');
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j] == ' ' || arr[i][j] == '\t')
			j++;
		if (!arr[i][j])
			return (free_array(arr), error_messages(6), -1);
		while (arr[i][j] && ft_isdigit(arr[i][j]))
			j++;
		if (arr[i][j] || ft_atoi(arr[i]) < 0 || ft_atoi(arr[i]) > 255)
			return (free_array(arr), error_messages(6), -1);
		rgb |= (ft_atoi(arr[i]) << (8 * (2 - i)));
	}
	if (i != 3)
		return (error_messages(6), free_array(arr), -1);
	return (free_array(arr), rgb);
}

int	validate_line(t_list *node, t_data *data)
{
	int					i;
	static bool			flags[7];
	static const char	*elems[] = {"NO", "SO", "EA", "WE", "F", "C", NULL};

	i = 0;
	while ((elems[i]) && ft_strncmp(node->content, elems[i], strlen(elems[i])))
		i++;
	if (i != 6 && flags[i] == true)
		return (printf("Duplicate idf!\n"), 1);
	flags[i] = true;
	if (!elems[i] && !data->start_map)
		data->start_map = node;
	if (i < 4)
		data->texture[i] = ft_strtrim(node->content + 2, " ");
	else if (i == 4 || i == 5)
		data->rgb[i - 4] = extract_colour((char *)node->content + 1);
	if (data->rgb[i - 4] == -1)
		return (1);
	if (i == 6 && ft_memchr(flags, false, sizeof(flags) - sizeof(bool)))
		return (error_messages(4));
	if (i != 6 && flags[6] == true)
		return (error_messages(4));
	return (0);
}

int	clear_data(t_data *data)
{
	int	i;

	i = -1;
	ft_lstclear(&data->lines, free);
	free_array(data->map);
	if (data->fd != -1)
		close(data->fd);
	while (++i < 4)
	{
		if (data->mlx_ptr && data->tex[i].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->tex[i].img_ptr);
		free(data->texture[i]);
	}
	if (data->mlx_ptr && data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	get_next_line(-1);
	ft_memset(data, 0, sizeof (*data));
	data->fd = -1;
	return (0);
}

int	empty_line(t_data *data, char *str)
{
	if (!data->start_map)
	{
		free(str);
		return (0);
	}
	clear_data(data);
	free(str);
	printf("empty line\n");
	exit (1);
}

int	check_idf(int fd, t_data *data)
{
	int		i;
	char	*str;
	t_list	*node;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (*str == '\n' && !empty_line(data, str))
			continue ;
		*ft_strchr(str, '\n') = '\0';
		node = ft_lstnew(str);
		if (validate_line(node, data))
		{
			ft_lstdelone(node, free);
			clear_data(data);
			return (1);
		}
		ft_lstadd_back(&data->lines, node);
	}
	return (0);
}
