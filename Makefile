# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 11:59:08 by tnaton            #+#    #+#              #
#    Updated: 2022/05/30 13:07:04 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs libft
vpath %.h srcs libft
vpath %.o srcs

NAME = cub3D

LIBFT = libft/libft.a

MLX = minilibx/libmlx_Linux.a

OBJDIR := objs

SRC = main.c 

source = $(addprefix srcs/,$(SRC))

CFLAGS = -Wall -Werror -Wextra -Iinc

CC = clang

object = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

$(NAME) : $(object) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@ $(object)

-include libft/Makefile

$(LIBFT) : $(SRCS) $(source) $(BONUS) libft.h
	$(MAKE) bonus -C ./libft

$(MLX) : 
	$(MAKE) -C ./minilibx

$(object) : | $(OBJDIR)

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) :
	mkdir $(OBJDIR)

.PHONY: debug
debug : $(object) $(LIBFT) $(MLX)
	gcc -g3 -fsanitize=address $(object) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
	rm -rf $(object)
	$(MAKE) clean -C ./libft

.PHONY: fclean
fclean :
	rm -rf $(NAME) $(object) $(OBJDIR)
	$(MAKE) fclean -C ./libft
	$(MAKE) clean -C ./minilibx

.PHONY: re
re : fclean all

$(object) : libft/libft.h inc/cub3D.h

.SECONDARY : $(object)
