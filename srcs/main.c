/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:43:22 by cbaey             #+#    #+#             */
/*   Updated: 2025/07/17 17:14:18 by lnul-hak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render_function(t_data *data)
{
	movement(data);
	if (data->flags.right_flag == true)
	{
		data->player_angle += ROTATE_SPEED;
		if (data->player_angle >= 2 * M_PI)
			data->player_angle -= 2 * M_PI;
	}
	if (data->flags.left_flag == true)
	{
		data->player_angle -= ROTATE_SPEED;
		if (data->player_angle <= 0.0)
			data->player_angle += 2 * M_PI;
	}
	data->dir_x = cos(data->player_angle);
	data->dir_y = sin(data->player_angle);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = -1;
	if (argc != 2)
		return (printf("Usage: ./cub3D <file containing colours,textures and map(*.cub)>"), 1);
	if (parsing(argc, argv, &data) == 1)
		return (1);
	ft_memset(&data.flags, 0, sizeof (t_flags));
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
	data.img.address = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp,
			&data.img.size_line, &data.img.endian);
	while (++i < 4)
	{
		data.tex[i].img_ptr = mlx_xpm_file_to_image(data.mlx_ptr,
				data.texture[i], &data.tex[i].width, &data.tex[i].height);
		if (data.tex[i].img_ptr == NULL)
			return (printf("Invalid texture!\n"), clear_data(&data), 1);
		data.tex[i].address = mlx_get_data_addr(data.tex[i].img_ptr,
				&data.tex[i].bpp, &data.tex[i].size_line, &data.tex[i].endian);
	}
	register_mlx(&data);
}
