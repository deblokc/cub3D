# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 11:59:08 by tnaton            #+#    #+#              #
#    Updated: 2022/06/06 16:45:17 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs libft
vpath %.h srcs libft
vpath %.o srcs

NAME = cub3D

NAME_BONUS = cub3D_bonus

LIBFT = libft/libft.a

MLX = minilibx/libmlx_Linux.a

OBJDIR := objs

OBJDIR_BONUS := objs_bonus

SRC = main.c checkmap.c free.c parseinfo.c parseinfo2.c parsemap.c mlx.c mlx2.c mlx3.c mlx4.c utils.c raisewalls.c

SRC_BONUS =  main.c checkmap.c free.c parseinfo.c parseinfo2.c parsemap.c mlx.c mlx2.c mlx3.c mlx4.c utils.c raisewalls.c

source = $(addprefix srcs/,$(SRC))

source_bonus = $(addprefix srcs_bonus/,$(SRC_BONUS))

CFLAGS = -Wall -Werror -Wextra -Iinc -g

CC = clang

object = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

object_bonus = $(addprefix $(OBJDIR_BONUS)/,$(SRC_BONUS:.c=.o))

$(NAME) : $(object) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(object) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

$(NAME_BONUS) : $(object_bonus) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(object_bonus) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

-include libft/Makefile

$(LIBFT) : $(SRCS) $(source) $(BONUS) libft.h
	$(MAKE) bonus -C ./libft

$(MLX) : 
	$(MAKE) -C ./minilibx

$(object) : | $(OBJDIR)

$(object_bonus) : | $(OBJDIR_BONUS)

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR_BONUS)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

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

$(object_bonus) : libft/libft.h inc/cub3D.h

.SECONDARY : $(object)
