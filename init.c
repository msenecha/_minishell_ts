/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:36 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/04 00:39:10 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_count(t_input *cmd)
{
	cmd->i = -1;
	cmd->count_double = 0;
	cmd->count_single = 0;
	cmd->in_double_quotes = 0;
	cmd->in_single_quotes = 0;
}

t_lexer	*init_lexer(t_lexer *lex, char *line)
{
	lex->state = START;
	lex->quotes = NO_QUOTES;
	lex->line = line;
	lex->index = -1;
	lex->start = 0;
	lex->end = 0;
	lex->quote_start = 0;
	lex->quote_end = 0;
	lex->quote_type = '\0';
	lex->token_list = malloc(sizeof(t_list));
	if (lex->token_list == NULL)
		exit(EXIT_FAILURE);
	lex->token_list->head = NULL;
	lex->previous_token = NULL;
	return (lex);
}

void	init_sublist_parser(t_parser *data, t_list *tokens)
{
	data->command_list = malloc(sizeof(t_command));
	if (data->command_list == NULL)
		exit(ALLOC_ERROR);
	data->cmd_sub_list = malloc(sizeof(t_list));
	if (data->cmd_sub_list == NULL)
		exit(ALLOC_ERROR);
	data->command_list->head = NULL;
	data->cmd_sub_list->head = NULL;
	data->cmd_sub_list->next = NULL;
	data->current = tokens->head;
	data->pipe_token = NULL;
	data->new = NULL;
}

void	re_init_sublist(t_parser *data)
{
	data->cmd_sub_list = malloc(sizeof(t_list));
	if (data->cmd_sub_list == NULL)
		exit(ALLOC_ERROR);
	data->cmd_sub_list->head = NULL;
	data->cmd_sub_list->next = NULL;
	data->pipe_token = NULL;
	data->current = data->current->next;
}
