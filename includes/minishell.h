/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:51:56 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/06 18:16:20 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

//#define NULL __DARWIN_NULL
# define ALLOC_ERROR 1
# define	QUOTES_ERROR 1
# define EXIT_FAILURE 1

typedef enum
{
	COMMAND,		// mot
	PIPE,		// |
	ARGUMENT,
	ENV_VAR,
	AMPER,	// &
	LEFT_REDIRECT,		// <
	REDIRECTION,		// >
	DOUBLE_REDIRECT,		// >>
	T_NEWLINE,		// newline
	T_EOF		// end of file (CTRL + D)
} TOKEN;

typedef enum
{
	START, 				// début
	IN_WORD,			// En train de lire un mot
	IN_SINGLE_QUOTES,	// entre doubles cotes
	IN_DOUBLE_QUOTES,	// entre simples cotes
	NO_QUOTES			// pas de cotes
} STATE;

typedef struct s_node
{
	char			*value;
	struct s_node	*next;
	struct s_node	*previous;
	TOKEN			type;
	STATE			quote_state;
}		t_node;

typedef struct s_list
{
	struct s_node	*head;
	struct s_list	*next;
}		t_list;

typedef struct s_command
{
	t_list			*head;
}		t_command;

typedef struct s_parser
{
	t_command	*command_list;
	t_list		*cmd_sub_list;
	t_node		*current;
	t_node		*new;
	t_node		*pipe_token;
}		t_parser;

typedef struct s_lexer
{
	char	*line;
	char	quote_type;
	int		index;
	int		start;
	int		end;
	int		quote_start;
	int		quote_end;
	t_list	*token_list;
	t_node	*previous_token;
	STATE	state;
	STATE	quotes;
}		t_lexer;

typedef struct s_input
{
	char	*line;
	int		i;
	int		count_double;
	int		count_single;
	int		in_double_quotes;
	int		in_single_quotes;
}		t_input;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Parsing */

t_list		*process_command();
t_list		*tokenize_command(char *command_line);
//void 		parse_command(t_list *tokens);
t_parser	*split_list_into_sublist(t_list	*tokens);

/* lexer */

void		init_count(t_input *cmd);
void 		process_quotes(t_lexer *lx);
char		get_type(char c, t_lexer *lx);
t_lexer		*init_lexer(t_lexer *lex, char *line);
t_list		*lexer(char *line);

/* list functions */

void		add_token(t_lexer *lexer, char *token_value);
void 		free_token_list(t_list *token_list);

/* list parser */

void		init_sublist_parser(t_parser *data, t_list *tokens);
void		re_init_sublist(t_parser *data);

/* list utils + print test */

void		print_command_list(t_command *command_list);
void 		free_command(t_command *command);
void		free_list(t_list *list);
int			ft_lstsize(t_node *lst);
int			ft_envsize(t_env *lst);
t_env		*ft_lstnew_env(char *env);
void		ft_lstadd_back(t_env **lst, t_env *new);
void		my_free(char **argv);

/* environnement */

t_env		*init_env_list(char **env);
char		**env_to_str(t_env *env);

/* execution */

void 		execute_command(t_parser *data, t_env *env);
void		setup_redir(int type, char *path);
char		*search_in_bin(char *args, t_env *env);
char		*expand_arg(char *str, t_env *env);


#endif
