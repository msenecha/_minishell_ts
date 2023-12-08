/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:03:11 by svidal            #+#    #+#             */
/*   Updated: 2023/11/22 15:02:42 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_syntax_verif(const char *str, int *i)
{
	if (str[*i] == '=')
	{
		printf("syntax error\n");
		return (1);
	}
	if (str[*i] == ' ' || str[*i] == '\0')
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_syntax_arg(const char *str, int *i)
{
	if (ft_syntax_verif(str, i) == 1)
		return (1);
	while (str[*i] != '=' && str[*i] != '\0')
	{
		if (str[*i] == ' ')
		{
			printf("syntax error\n");
			return (1);
		}
		(*i)++;
	}
	if (str[*i] != '=')
	{
		printf("syntax error\n");
		return (1);
	}
	if (str[*i] != '\0')
		(*i)++;
	if (str[*i] == ' ')
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_syntax_char(const char *str, int *i)
{
	int	quotes;

	quotes = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			quotes = 1;
		if (((str[*i] >= 32 && str[*i] <= 47)
				|| (str[*i] >= 58 && str[*i] <= 64)
				|| (str[*i] >= 91 && str[*i] <= 94) || str[*i] == 96
				|| (str[*i] >= 123 && str[*i] < 127)) && quotes == 0)
		{
			printf("Error: not a valid identifier\n");
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	ft_syntax_valid(const char *str, int *i)
{
	if (ft_syntax_arg(str, i) == 1)
		return (1);
	else if (ft_syntax_char(str, i) == 1)
		return (1);
	else
		return (0);
}
