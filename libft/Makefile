# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 18:31:36 by tnaton            #+#    #+#              #
#    Updated: 2022/05/30 12:24:13 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = libft.h

DIR = $(shell pwd | xargs basename)

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c\
ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c\
ft_strlcpy.c ft_tolower.c ft_bzero.c ft_putnbr_fd.c ft_strlen.c\
ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c\
ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c\
get_next_line.c get_next_line_utils.c ft_atoi_base.c ft_power.c\
ft_strjoin_free.c ft_strcmp.c ft_strtrim_free.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c\
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS = $(SRCS:.c=.o)

OBJSBONUS = $(BONUS:.c=.o)

CC		= clang
RM		= rm -f

ifeq (libft,$(DIR))

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

NAME = libft.a

$(NAME): $(OBJS) $(HEADER)
	ar rcs $@ $?

.PHONY: all
all:	${NAME}

.PHONY: clean
clean:
		${RM} ${OBJS} ${OBJSBONUS}

.PHONY: fclean
fclean:	clean
	${RM} ${NAME}

.PHONY: re
re: fclean all

.PHONY: bonus
bonus:	${OBJS} ${OBJSBONUS} ${HEADER}
		ar rcs ${NAME} $?

endif

.c.o:	
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}
$(OBJS) : libft.h

$(OBJSBONUS) : libft.h

.SECONDARY: $(OBJS) $(OBJSBONUS)
