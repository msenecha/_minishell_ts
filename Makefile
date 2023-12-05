NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -lreadline -fsanitize=address

HEADERS = minishell.h

SRCS =	main.c \
		process.c \
		syntax.c \
		init.c  \
		lexer.c \
		lexer_utils.c \
		list_parser.c \
		print_list_utils.c \
		env.c \
		exec.c

OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(SRCS)
	@echo "Compilation en cours..."
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "Compilation terminée!"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) $(OBJS)

re: fclean all

fclean: clean

.PHONY: all clean re fclean