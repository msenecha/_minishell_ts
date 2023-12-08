/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:45:11 by svidal            #+#    #+#             */
/*   Updated: 2023/11/17 01:33:37 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_env *env, t_args *args)
{
	int		i;

	if (args[0].arg_value == NULL)
		return (1);
	i = 0;
	while (args[i].arg_value)
	{
		ft_remove_var_env(&env, args[i].arg_value);
		i++;
	}
	return (0);
}

void	ft_remove_var_env(t_env **env, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous == NULL)
				*env = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}
