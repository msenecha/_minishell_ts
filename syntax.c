/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:53:50 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/04 21:05:41 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void free_token_list(t_node *head) 
// {
// 	t_node *current;
// 	t_node *next;

// 	current = head;
// 	while (current != NULL) 
// 	{
// 		next = current->next;
// 		free(current->value);
// 		free(current);
// 		current = next;
//     }
// }

void	add_token_to_list(t_node **head, t_node *new_token)
{
	t_node	*current;

	if (*head == NULL)
	{
		*head = new_token;
		new_token->previous = NULL;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_token;
		new_token->previous = current;
	}
}

t_node	*create_new_token(char *value, t_lexer *lexer)
{
	t_node	*new_token;
	
	new_token = malloc(sizeof(t_node));
	if (new_token == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire pour le token\n");
        exit(EXIT_FAILURE);
	}
	new_token->value = value;
	new_token->next = NULL;
	new_token->previous = NULL;
	if (lexer->quotes == IN_DOUBLE_QUOTES)
	{
		new_token->quote_state = IN_DOUBLE_QUOTES;
		lexer->quotes = NO_QUOTES;
	}
	else if (lexer->quotes == IN_SINGLE_QUOTES)
	{
		new_token->quote_state = IN_SINGLE_QUOTES;
		lexer->quotes = NO_QUOTES;
	}
	else
		new_token->quote_state = NO_QUOTES;
	printf("\033[1;34mNode value:\033[0m \033[1;32m%s\033[0m\n", new_token->value);
	printf("\033[1;34mquote_state:\033[0m \033[1;32m%u\033[0m\n", new_token->quote_state);
	return (new_token);
}

void	parse_token(t_node *token, t_lexer *lex)
{
	printf("\033[1;34mPrevious:\033[0m \033[1;32m%p\033[0m\n", (void *)lex->previous_token);
	if (token->quote_state == NO_QUOTES && !lex->previous_token)
	{
		token->type = COMMAND;
		printf("\033[1;34mtype:\033[0m \033[1;32mcommand\033[0m\n\n");
	}
	else if (token->quote_state == NO_QUOTES && lex->previous_token->type == PIPE)
	{
		token->type = COMMAND;
		printf("\033[1;34mtype:\033[0m \033[1;32mcommand\033[0m\n\n");
	}
	else if (token->value[0] == '-' && token->quote_state == NO_QUOTES && lex->previous_token->type == COMMAND)
	{
		token->type = COMMAND;
		printf("\033[1;34mtype:\033[0m \033[1;32moptions\033[0m\n\n");
	}
	else if (token->quote_state == IN_DOUBLE_QUOTES && strcmp(&(token->value[0]), "$") == 0)
	{
		token->type = ENV_VAR;
		printf("\033[1;34mtype:\033[0m \033[1;32menv_var\033[0m\n\n");
	}
	else if((token->quote_state == IN_DOUBLE_QUOTES || token->quote_state == IN_SINGLE_QUOTES) && lex->previous_token != NULL)
	{
		token->type = ARGUMENT;
		printf("\033[1;34mtype:\033[0m \033[1;32margument\033[0m\n\n");
	}
	else if (strcmp(&(token->value[0]), "|") == 0)
	{
		token->type = PIPE;
		printf("\033[1;34mtype:\033[0m \033[1;32mpipe\033[0m\n\n");
	}
	else if (strcmp(&(token->value[0]), "&") == 0)
	{
		token->type = AMPER;
		printf("\033[1;34mtype:\033[0m \033[1;32mamper\033[0m\n\n");
	}
	else if (strcmp(&(token->value[0]), ">") == 0)
	{
		token->type = REDIRECTION;
		printf("\033[1;34mtype:\033[0m \033[1;32mredirection\033[0m\n\n");
	}
	else if (strcmp(&(token->value[0]), "<") == 0)
	{
		token->type = LEFT_REDIRECT;
		printf("\033[1;34mtype:\033[0m \033[1;32mleft redirection\033[0m\n\n");
	}
	else if (strcmp(token->value, ">>") == 0)
	{
		token->type = DOUBLE_REDIRECT;
		printf("\033[1;34mtype:\033[0m \033[1;32mdouble redirect\033[0m\n\n"); 
	}
	else
	{
		token->type = ARGUMENT;
		printf("\033[1;34mtype:\033[0m \033[1;32margument\033[0m\n\n");
	}
	lex->previous_token = token;
}

void	add_token(t_lexer *lexer, char *token_value)
{
	t_node	*new_token;

	new_token = create_new_token(token_value, lexer);
	//lexer->previous_token = new_token;
	parse_token(new_token, lexer);
	add_token_to_list(&(lexer->token_list->head), new_token);
}

