# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 18:36:08 by msenecha          #+#    #+#              #
#    Updated: 2023/11/16 20:10:00 by msenecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
## ARGUMENTS

NAME				= libft.a
CC					= gcc
CFLAGS				= -g -Wall -Wextra -Werror
RM					= rm -f

################################################################################
## SOURCES

SRC 				= ft_atoi.c ft_atoi_base.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
					ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
					ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
					ft_strdup.c ft_strncpy.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
					ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strcmp.c ft_strnstr.c ft_strrchr.c \
					ft_strtrim.c ft_substr.c ft_toupper.c ft_tolower.c \
					get_next_line.c ft_printf.c ft_printhex.c ft_printnbr.c ft_printstr.c \
					ft_printptr.c ft_printunsd.c

OBJECTS				= $(SRC:.c=.o)

################################################################################
## RULES
all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
