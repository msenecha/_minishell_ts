/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:18:46 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/06 17:06:51 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node *create_node(char *value, TOKEN type, STATE quote_state)
{
    t_node *new_node;

    new_node = malloc(sizeof(t_node));
    if (new_node == NULL)
        exit(EXIT_FAILURE);
    new_node->value = strdup(value);
    new_node->type = type;
    new_node->quote_state = quote_state;
    new_node->next = NULL;
    // new_node->previous = NULL;

    return new_node;
}

void add_node_to_list(t_node **head, t_node *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        t_node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
        new_node->previous = current;
    }
}

void add_list_to_command(t_command *command, t_list *new_list)
{
    t_list  *current;

    if (command->head == NULL)
        command->head = new_list;
    else
    {
        current = command->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_list;
    }
}

t_parser	*split_list_into_sublist(t_list	*tokens)
{
	t_parser	*d;
    
	d = malloc(sizeof(t_parser)); // a voir 
    init_sublist_parser(d, tokens);
    while (d->current != NULL)
	{
		if (d->current->type != PIPE)
		{
			d->new = create_node(d->current->value, d->current->type, d->current->quote_state);
			add_node_to_list(&(d->cmd_sub_list->head), d->new);
		}
		else if (d->current->type == PIPE)
		{
			d->pipe_token = create_node(d->current->value, d->current->type, d->current->quote_state);
			add_node_to_list(&(d->cmd_sub_list->head), d->pipe_token);
			add_list_to_command(d->command_list, d->cmd_sub_list);
			re_init_sublist(d);
			continue;
		}
		d->current = d->current->next;
	}
	if (d->cmd_sub_list != NULL && d->cmd_sub_list->head != NULL)
		add_list_to_command(d->command_list, d->cmd_sub_list);
	//print_command_list(d->command_list);
	//free_list(tokens);
    return (d);
	//free_command(d->command_list);
	//free(d);
}

// void parse_command(t_list *tokens)
// {
//     t_command   *command_list;
//     t_list      *cmd_sub_list;
//     t_node		*current_token;
//     t_node		*new_token; 

// 	command_list = malloc(sizeof(t_command));
// 	cmd_sub_list = malloc(sizeof(t_list));
// 	command_list->head = NULL;
// 	cmd_sub_list->head = NULL;
// 	cmd_sub_list->next = NULL;
// 	current_token = tokens->head;
// 	while (current_token != NULL)
// 	{
// 		if (current_token->type != PIPE)
// 		{
// 			new_token = create_node(current_token->value, current_token->type, current_token->quote_state);
// 			add_node_to_list(&(cmd_sub_list->head), new_token);
// 		}
// 		else if (current_token->type == PIPE)
// 		{
// 			t_node *pipe_token = create_node(current_token->value, current_token->type, current_token->quote_state);
// 			add_node_to_list(&(cmd_sub_list->head), pipe_token);
//  			add_list_to_command(command_list, cmd_sub_list);
//             cmd_sub_list = malloc(sizeof(t_list));
//             cmd_sub_list->head = NULL;
//             cmd_sub_list->next = NULL;
//             current_token = current_token->next;  // Avancez le current_token
//             continue;  // Passer à l'itération suivante de la boucle externe
// 		}
//         current_token = current_token->next;
//     }
// 	if (cmd_sub_list != NULL && cmd_sub_list->head != NULL)
// 	{
// 		add_list_to_command(command_list, cmd_sub_list);
// 	}
// 	print_command_list(command_list);
// 	free_list(tokens);
// 	free_command(command_list);
// }


