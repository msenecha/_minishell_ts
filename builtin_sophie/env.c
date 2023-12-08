/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:32:52 by svidal            #+#    #+#             */
/*   Updated: 2023/11/08 17:07:32 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *var)
{
	while (var)
	{
		printf("%s", var->key);
		printf("=");
		printf("%s\n", var->value);
		var = var->next;
	}
	return (0);
}
