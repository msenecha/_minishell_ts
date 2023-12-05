/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:02:21 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/05 17:01:51 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env *head;
	head = env;

	while(head)
	{
		printf("KEY = %s", head->key);
		printf("\t\tVALUE = %s\n", head->value);
		head = head->next;
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_list	*token_list;
	t_env	*env;
	t_parser	*data;

	(void)ac;
	(void)av;

	env = init_env_list(envp);
	//print_env(env);
	while (1)
	{
		token_list = process_command();
		//parse_command(token_list);
		data = split_list_into_sublist(token_list);
		execute_command(data, env);
		free_command(data->command_list);
		free(data);
	}
	return 0;
}

