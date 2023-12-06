/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 00:40:54 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/06 17:06:56 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_list(t_list *token_list)
{
    if (token_list == NULL) 
    {
        printf("Token list is NULL.\n");
        exit(EXIT_FAILURE);
    }

    t_node *current = token_list->head;

    while (current != NULL)
    {
        printf("\033[1;34mValue:\033[0m \033[1;32m%s\033[0m, \033[1;34mType:\033[0m \033[1;32m%d\033[0m, \033[1;34mQuote State:\033[0m \033[1;32m%d\033[0m\n",
        current->value, current->type, current->quote_state);
        current = current->next;
    }
}

void	print_sublists(t_command *command_list)
{
        t_command *current_command = command_list;
        int sublist_number = 1;

        while (current_command->head != NULL)
        {
            printf("\n\033[1;32mSub-list %d:\033[0m\n\n", sublist_number);
            print_token_list(current_command->head);
            printf("\n");

            current_command->head = current_command->head->next;
            sublist_number++;
        }
}


void	print_command_list(t_command *command_list)
{
    t_command *cmd;
    
    cmd = command_list;
    printf("Command List:\n");
    print_sublists(cmd);
}

void	free_node_list(t_node *head)
{
    t_node *current = head;
    while (current != NULL)
    {
        t_node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

void	free_list(t_list *list)
{
	free_node_list(list->head);
	free(list);
}

void	free_command(t_command *command)
{
	t_list *current = command->head;
	while (current != NULL)
	{
		t_list *next = current->next;
		free_list(current);
		current = next;
	}
	free(command);
}