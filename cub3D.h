/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:40:00 by cbaey             #+#    #+#             */
/*   Updated: 2025/04/17 13:48:12 by cbaey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <assert.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define T_S 40
# define W_HEIGHT 800
# define W_WIDTH 800
# define MAP_HEIGHT 12
# define MAP_WIDTH 20
# define MOVE_SPEED 1
# define ROTATE_SPEED 0.01

typedef struct s_img
{
	void	*img_ptr;
	char	*address;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	double	tex_x;
}	t_img;

typedef struct s_flags
{
	bool	w_flag;
	bool	d_flag;
	bool	s_flag;
	bool	a_flag;
	bool	left_flag;
	bool	right_flag;
}		t_flags;

typedef struct s_measure
{
	double	delta_x;
	double	delta_y;
	double	dist_x;
	double	dist_y;
	int		step_x;
	int		step_y;
}		t_measure;

typedef struct s_move
{
	double	temp_x;
	double	temp_y;
	double	dx;
	double	dy;
	double	x_incre;
	double	y_incre;
}		t_move;

typedef struct s_data
{
	t_img		tex[4];
	t_img		img;
	t_flags		flags;
	t_measure	measure;
	t_move		move;
	t_list		*lines;
	t_list		*start_map;
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		ray_x;
	double		ray_y;
	double		player_angle;
	double		ray_angle;
	double		ray_distance;
	int			fd;
	char		*texture[4];
	int			rgb[2];
	int			max_h_map;
	int			max_w_map;
	int			tex_index;
	int			map_x;
	int			map_y;
}		t_data;

int		parsing(int ac, char **av, t_data *data);
void	free_array(char **arr);
int		extract_colour(char *content);
int		validate_line(t_list *node, t_data *data);
int		clear_data(t_data *data);
int		check_idf(int fd, t_data *data);
int		scan_map(t_data *data);
void	map_init(t_data *data);
int		flood_fill(t_data *data, int x, int y);
int		error_messages(int n);
int		check_ext(char *file);
int		check_perm(char *file);
int		check_args(char *file, t_data *data);
int		parsing(int ac, char **av, t_data *data);
void	movement(t_data *data);
void	register_mlx(t_data *data);
double	measure_distance(t_data *data);
void	init_info(t_data *data, t_measure *scales);
int		choose_side(t_measure *measure, int *map_x, int *map_y, int side);
double	wall_distance(t_data *data, double dist_x, double dist_y, int side);
int		render_function(t_data *data);
int		key_press(int key_code, t_data *data);
int		key_release(int key_code, t_data *data);
int		cross_button(t_data *data);
int		find_wall_texture(t_data *data, int side);
void	wall_movement(t_data *data, double temp,
			double player_still, double *player_mvt);
void	movement_keys(t_flags flags, t_move *move);
void	movement(t_data *data);
int		check_it(int ac, char **av, t_data *data);
void	cast_rays(t_data *data);

#endif
