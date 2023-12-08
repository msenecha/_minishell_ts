/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:45:28 by svidal            #+#    #+#             */
/*   Updated: 2023/11/22 17:46:35 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_args *args)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (args[i].arg_value)
	{
		if (args[i].is_option == TRUE
			&& ft_strcmp(args[i].arg_value, "-n") == 0)
			n = 1;
		printf("%s", args[i].arg_value);
		if (args[i + 1].arg_value && args[i + 1].arg_value[0] != '\0')
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}
