# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaey <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 12:01:00 by cbaey             #+#    #+#              #
#    Updated: 2025/04/17 13:44:59 by cbaey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRCS = srcs/parsing.c srcs/cub3d.c srcs/checks1.c srcs/map.c srcs/measurements.c srcs/movement.c srcs/keypress.c srcs/checks2.c srcs/main.c
OBJSDIR = object_files
OBJS = $(addprefix $(OBJSDIR)/,$(notdir $(SRCS:.c=.o)))
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -Iinc -I$(LIBFT_DIR) -I$(MLX_DIR)
MLX_DIR = inc/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
VPATH = $(dir $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -L$(MLX_DIR) $(OBJS) -o $(NAME) -lmlx -lXext -lX11 -lft -lm

$(LIBFT):
	make -C $(LIBFT_DIR) all bonus

$(MLX):
	make -C $(MLX_DIR)

$(OBJSDIR)/%.o:%.c
	@mkdir -p $(OBJSDIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJSDIR)
	make -C$(LIBFT_DIR) clean
	make -C$(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C$(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
