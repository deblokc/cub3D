# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 11:59:08 by tnaton            #+#    #+#              #
#    Updated: 2022/06/13 18:39:34 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c libft
vpath %.o srcs libft
vpath %.h libft

NAME = cub3D

NAME_BONUS = cub3D_bonus

LIBFT = libft/libft.a

MLX = minilibx/libmlx_Linux.a

OBJDIR := objs

OBJDIR_BONUS := objs_bonus

SRC = main.c checkmap.c free.c parseinfo.c parseinfo2.c parsemap.c mlx.c mlx2.c mlx3.c mlx4.c utils.c raisewalls.c check_view_integrity.c getwalls.c draw_wall.c hooks.c

SRC_BONUS =  main.c checkmap.c free.c parseinfo.c parseinfo2.c parsemap.c mlx.c mlx2.c mlx3.c mlx4.c utils.c raisewalls.c check_view_integrity.c getwalls.c draw_wall.c doors.c utils2.c exit.c doors2.c

source = $(addprefix srcs/,$(SRC))

source_bonus = $(addprefix srcs_bonus/,$(SRC_BONUS))

CFLAGS = -Wall -Werror -Wextra -Iinc -g
CFLAGS_BONUS = -Wall -Werror -Wextra -Iinc_bonus -g

CC = clang

object := $(patsubst srcs/%.c,$(OBJDIR)/%.o,$(source)) 

object_bonus := $(patsubst srcs_bonus/%.c,$(OBJDIR_BONUS)/%.o,$(source_bonus))

$(NAME) : $(LIBFT) $(MLX) $(object)
	$(CC) $(CFLAGS) $(object) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

$(NAME_BONUS) : $(object_bonus) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS_BONUS) $(object_bonus) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

-include libft/Makefile

$(LIBFT) : $(SRCS)
	$(MAKE) all -C ./libft

$(MLX) : 
	$(MAKE) -C ./minilibx

$(object) : | $(OBJDIR)

$(object_bonus) : | $(OBJDIR_BONUS)

$(OBJDIR)/%.o: srcs/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR_BONUS)/%.o : srcs_bonus/%.c
	$(CC) $(CFLAGS_BONUS) -o $@ -c $<

$(OBJDIR) :
	mkdir $(OBJDIR)

$(OBJDIR_BONUS) :
	mkdir $(OBJDIR_BONUS)

.PHONY: bonus
bonus : $(NAME_BONUS) 

.PHONY: debug
debug : $(object) $(LIBFT) $(MLX)
	gcc -g3 -fsanitize=address $(object) $(MLX) -lXext -lX11 -lm -Iminilibx -o $@ $(LIBFT)

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
	rm -rf $(object) $(OBJDIR)
	rm -rf $(object_bonus) $(OBJDIR_BONUS)
	$(MAKE) clean -C ./libft

.PHONY: fclean
fclean :
	rm -rf $(NAME) $(object) $(OBJDIR)
	rm -rf $(NAME_BONUS) $(object_bonus) $(OBJDIR_BONUS)
	$(MAKE) fclean -C ./libft
	$(MAKE) clean -C ./minilibx

.PHONY: re
re : fclean all

$(object) : libft/libft.h inc/cub3D.h

$(object_bonus) : libft/libft.h inc_bonus/cub3D.h

.SECONDARY : $(object)

.SECONDARY : $(object_bonus)
