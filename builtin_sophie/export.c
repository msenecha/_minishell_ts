/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:39:20 by svidal            #+#    #+#             */
/*   Updated: 2023/11/17 17:22:07 by svidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_env_var(char *str, t_gen *gen)
{
	t_env	*new_var;

	new_var = ft_lstnew_env(str);
	if (!new_var)
		return (1);
	ft_lstadd_back(&(gen->env), new_var);
	return (0);
}

void	ft_update_env_var(char *name_var, char *new_value, t_gen *gen)
{
	t_env	*var;

	var = gen->env;
	while (var)
	{
		if (ft_strcmp(var->key, name_var) == 0)
		{
			free(var->value);
			var->value = ft_strdup(new_value);
			return ;
		}
		var = var->next;
	}
}

int	search_for_key(char *str, t_gen *gen)
{
	t_env	*var;

	var = gen->env;
	while (var)
	{
		if (ft_strncmp(str, var->key, ft_strlen(str)) == 0)
			return (0);
		else
			var = var->next;
	}
	return (1);
}

int	ft_handle_export_args(char *arg_value, t_gen *gen)
{
	int		i;
	char	**tmp;

	i = 0;
	if (ft_syntax_valid(arg_value, &i) == 0)
	{
		tmp = ft_split(arg_value, '=');
		if (tmp[0] && tmp[1])
		{
			if (search_for_key(tmp[0], gen) == 0)
				ft_update_env_var(tmp[0], tmp[1], gen);
			else
				ft_add_env_var(arg_value, gen);
			my_free(tmp);
		}
		else
		{
			my_free(tmp);
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	ft_export(t_args *args, t_gen *gen)
{
	int	j;

	j = 0;
	if (args[j].arg_value == NULL)
		return (ft_env(gen->env), 0);
	while (args[j].arg_value)
	{
		if (ft_handle_export_args(args[j].arg_value, gen) == 1)
			return (1);
		j++;
	}
	return (0);
}
