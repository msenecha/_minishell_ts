###############################################################################
################################### SOURCES ###################################

NAME			= minishell
CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror -fsanitize=address
LIB				= -lasan -L$(LIBFT_DIR) -lft -lreadline
INCLUDES		= -I$(HEADERS_DIR) -I$(LIBFT_DIR)

LIBFT_DIR		= ./libft/
LIBFT_LIB		= $(LIBFT_DIR)libft.a

HEADERS_DIR		= ./includes/
SRC_DIR			= ./src
SUBDIR			= builtin executing parsing env signals

SRCS 			= $(wildcard $(SRC_DIR)/*.c $(foreach fd, $(SUBDIR), $(SRC_DIR)/$(fd)/*.c))
OBJS 			= $(SRCS:.c=.o)

###############################################################################
################################### RULES #####################################

all: $(NAME)

$(NAME): libft $(OBJS)
	echo "\nCompiling objects ...\n"
	@$(CC) -o $(NAME) $(OBJS) $(LIB)
	@$(MAKE) clean

%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -sC $< -o $@ $(INCLUDES)

.SILENT:
libft:
	echo "\nCreating libft.a ...\n"
	@$(MAKE) -sC $(LIBFT_DIR)

.SILENT:
clean:
	echo "\nCleaning object files ...\n"
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	echo "\nDeleting $(NAME) ...\n"
	@rm -f $(LIBFT_LIB)
	@rm -f $(NAME)

.SILENT:
re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all libft clean fclean re
