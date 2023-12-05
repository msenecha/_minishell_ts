/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:39:01 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/04 21:06:55 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in_double_quotes et in_single_quotes sont initialisé à zero dans cette fonction 
// ils agiront comme des booléen, donc le zero représentera FAUX et l'inverse représentera
// 1 et donc VRAI

int count_quotes(t_input *cmd)
{
    init_count(cmd);
    while (cmd->line[++cmd->i] != '\0')
    {
        if (cmd->line[cmd->i] == '\"')
        {
            cmd->count_double++;
            cmd->in_double_quotes = !cmd->in_double_quotes;
        }
        else if (cmd->line[cmd->i] == '\'' && !cmd->in_double_quotes)
        {
            cmd->count_single++;
            cmd->in_single_quotes = !cmd->in_single_quotes;
        }
    }
    if (cmd->count_double % 2 == 0 && cmd->count_single % 2 == 0 && !cmd->in_double_quotes && !cmd->in_single_quotes)
        return (1);
    else if ((cmd->count_double % 2 != 0 || cmd->count_single % 2 != 0) && cmd->in_double_quotes && cmd->in_single_quotes)
        return (1);
    return (0);
}

t_list	*tokenize_command(char *command_line)
{
	char	*line_copy;
	t_list	*tokens;

	line_copy = strdup(command_line);
	printf("\n\033[1;34mline:\033[0m \033[1;91m%s\033[0m\n\n", line_copy);
	if (!line_copy)
		exit(ALLOC_ERROR);
	tokens = lexer(line_copy);
	free(line_copy); // a voir
	return (tokens);
}

// void free_token_list(t_list *token_list)
// {
//     t_node *current = token_list->head;
//     t_node *next;

//     while (current != NULL)
//     {
//         next = current->next;
//         free(current->value);
//         free(current);
//         current = next;
//     }

//     free(token_list);
// }

t_list	*process_command()
{
	t_input *command;
	t_list	*tokens_list;

	tokens_list = NULL;
	command = malloc(sizeof(t_input));
	if (!command)
		exit(ALLOC_ERROR);
	command->line = readline("minishell>$");
	if (!count_quotes(command))
	{
		command->line = readline("minishell>$");
	}
	else
	{
		if (command->line)
		{
			add_history(command->line);
			//free_token_list(tokens_list);
			tokens_list = tokenize_command(command->line);
			//parse_command(tokens_list);
		}
	}
	free(command);
	return (tokens_list);
}




